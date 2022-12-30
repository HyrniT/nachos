/**************************************************************
 *
 * userprog/ksyscall.h
 *
 * Kernel interface for systemcalls
 *
 * by Marcus Voelp  (c) Universitaet Karlsruhe
 *
 **************************************************************/

#ifndef __USERPROG_KSYSCALL_H__
#define __USERPROG_KSYSCALL_H__

#include "kernel.h"
#include "synchconsole.h"
#include <stdlib.h>
#include <stdint.h>

#define LF ((char)10)
#define CR ((char)13)
#define TAB ((char)9)
#define SPACE ((char)' ')

// Nguyen Quang Hien
#define MAX_NUM_LENGTH 11

// Buffer to read and write num
char numBuffer[MAX_NUM_LENGTH + 2];

void SysHalt()
{
  kernel->interrupt->Halt();
}

int SysAdd(int op1, int op2)
{
  return op1 + op2;
}

// Check character is blank (whitespace)
char isBlank(char c)
{
  return (c == LF || c == CR || c == TAB || c == SPACE);
}

// Read and store character in numBuffer until blank or end
void readNumberUntilBlank()
{
  // Set all characters in numBuffer to 0
  memset(numBuffer, 0, sizeof(numBuffer));

  char c = kernel->synchConsoleIn->GetChar();

  // Check end of file
  if (c == EOF)
  {
    DEBUG(dbgSys, "Unexpected end of file - number expected");
    return;
  }

  // Check blank
  if (isBlank(c))
  {
    DEBUG(dbgSys, "Unexpected whitespace - number expected");
    return;
  }

  int i = 0;

  while (!(isBlank(c) || c == EOF))
  {
    numBuffer[i++] = c;
    if (i > MAX_NUM_LENGTH) // i(max) = MAX_NUM_LENGTH + 1
    {
      DEBUG(dbgSys, "Number is too long");
      return;
    }
    c = kernel->synchConsoleIn->GetChar();
  }
}

// Check if num and string num are the same
bool compareNumToString(int num, const char *strnum)
{
  // Case all is equal 0
  if (num == 0)
  {
    return strcmp(strnum, "0") == 0;
  }

  int len = strlen(strnum);

  // Case number is positve but s not begin with '-'
  if (num < 0 && strnum[0] != '-')
  {
    return false;
  }

  // Convert negative (number and string number) to positive
  if (num < 0)
  {
    strnum++, --len, num = -num;
  }

  // Check positve number is equal to positive string number
  while (num > 0)
  {
    int digit = num % 10;

    if (strnum[len - 1] - '0' != digit)
      return false;

    --len;
    num /= 10;
  }
  // Check if the same length
  return (len == 0);
}

// SysReadNum(): char -> int
int SysReadNum()
{
  readNumberUntilBlank();

  int len = strlen(numBuffer);
  // Case 0
  if (len == 0)
    return 0;

  /*
      1 int has 4 bytes, each byte has 8 bits
      => 1 int has 32 bits
      => -2^31 <= int <= 2^31 + 1
  */

  // Case min and return value
  /*
     Because if this min 32-bit number (negative) convert into positive
     Its value is "2147483648", it exceeds the limit of max value "2147483647"
     Therefore, we must have this special case
  */
  if (strcmp(numBuffer, "-2147483648") == 0)
    return INT32_MIN;

  bool is_negative = (numBuffer[0] == '-');
  bool is_leading = true;
  int zeros = 0;
  int number = 0;

  // Convert numBuffer[](char*) to number(int)
  for (int i = is_negative; i < len; ++i)
  {
    char c = numBuffer[i];

    // Eliminate all zero number at first of string number
    if (c == '0' && is_leading)
      ++zeros;
    else
      is_leading = false;

    // Check valid character
    if (c < '0' || c > '9')
    {
      DEBUG(dbgSys, "Expected number but " << numBuffer << " found");
      return 0;
    }
    number = number * 10 + (c - '0'); //-'0': char->int
  }

  // 00                       01     or     -0
  if (zeros > 1 || (zeros && (number || is_negative)))
  {
    DEBUG(dbgSys, "Expected number but " << numBuffer << " found");
    return 0;
  }
  // Case negative
  if (is_negative)
    number = -number;

  // Check valid length and check after converting
  if ((len <= MAX_NUM_LENGTH - 2) && (compareNumToString(number, numBuffer)))
    return number;
  else
    DEBUG(dbgSys, "Expected int32 number but " << numBuffer << " found");
  return 0;
}

// SysPrintNum: int -> char
void SysPrintNum(int num)
{
  // Case 0
  if (num == 0)
    return kernel->synchConsoleOut->PutChar('0');

  // Case min
  if (num == INT32_MIN)
  {
    kernel->synchConsoleOut->PutChar('-');
    for (int i = 0; i < 10; ++i)
      kernel->synchConsoleOut->PutChar("2147483648"[i]);
    return;
  }

  // Case negative
  if (num < 0)
  {
    kernel->synchConsoleOut->PutChar('-');
    num = -num;
  }

  int n = 0;

  // Convert number(int) to numBuffer[](char*)
  while (num)
  {
    numBuffer[n++] = num % 10;
    num /= 10;
  }
  for (int i = n - 1; i >= 0; --i)
    kernel->synchConsoleOut->PutChar(numBuffer[i] + '0'); // +'0': int->char
}

bool SysCreate(char* fileName) 
{
  bool success;
  int fileNameLength = strlen(fileName);

  if (fileNameLength == 0) {
      DEBUG(dbgSys, "\nFile name can't be empty");
      success = false;

  } else if (fileName == NULL) {
      DEBUG(dbgSys, "\nNot enough memory in system");
      success = false;

  } else {
      DEBUG(dbgSys, "\nFile's name read successfully");
      if (!kernel->fileSystem->Create(fileName)) {
          DEBUG(dbgSys, "\nError creating file");
          success = false;
      } else {
          success = true;
      }
  }

  return success;
}

int SysOpen(char* fileName, int type) {
  if (type != 0 && type != 1) return -1;

  int id = kernel->fileSystem->Open(fileName, type);
  if (id == -1) return -1;
  DEBUG(dbgSys, "\nOpened file");
  return id;
}

int SysClose(int id) 
{ 
  return kernel->fileSystem->Close(id);
}

int SysRead(char* buff, int countChar, int fId) {
  if (fId == 0) {
      return kernel->synchConsoleIn->GetString(buff, countChar);
  }
  return kernel->fileSystem->Read(buff, countChar, fId);
}

int SysWrite(char* buff, int countChar, int fId) {
  if (fId == 1) {
      return kernel->synchConsoleIn->GetString(buff, countChar);
  }
  return kernel->fileSystem->Write(buff, countChar, fId);
}

int SysRemove(char *name)
{
  OpenFile *openFile = kernel->fileSystem->Open(name);
  if ((OpenFileId)openFile == 0)
  {
    delete openFile;
    return -1;
  }
  else
  {
    delete openFile;
    if (!kernel->fileSystem->Remove(name))
    {
      return -1;
    }
    else
    {
      return 1;
    }
  }
}

// Nguyen Van Hieu
char SysReadChar() { return kernel->synchConsoleIn->GetChar(); }

void SysPrintChar(char character)
{
  kernel->synchConsoleOut->PutChar(character);
}

int SysRandomNum() { return random(); }

char *SysReadString(int length)
{
  char *buffer = new char[length + 1];
  for (int i = 0; i < length; i++)
  {
    buffer[i] = SysReadChar();
  }
  buffer[length] = '\0';
  return buffer;
}

// Nguyen Hai Dang
void SysPrintString(char *buffer, int length)
{
  for (int i = 0; i < length; i++)
  {
    kernel->synchConsoleOut->PutChar(buffer[i]);
  }
}

#endif /* ! __USERPROG_KSYSCALL_H__ */
