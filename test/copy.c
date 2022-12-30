#include "syscall.h"

#define MAX_LENGTH 255
#define MODE_READWRITE 0
#define MODE_READ 1

#define stdin 0
#define stdout 1

int main() 
{
    char buffer[100];
    char fileName[MAX_LENGTH + 1];
    int length, fileId, read, write;
    int len = 0;

    // Read file 0
    PrintString("Enter file name's length (<=255): ");
    length = ReadNum();

    PrintString("File's name: ");
    ReadString(fileName, length);

    fileId = Open(fileName, MODE_READ);
    //fileId = Open("Test0.txt", MODE_READ);
    read = Read(buffer, 50, fileId);

    while (buffer[len] != '\0') 
        ++len;

    PrintString("Read ");
    PrintNum(len);
    PrintString(" characters: ");
    PrintString(buffer);
    PrintString("\n");
    Close(fileId);

    // Write file 1
    PrintString("Enter file name's length (<=255): ");
    length = ReadNum();

    PrintString("File's name: ");
    ReadString(fileName, length);

    fileId = Open(fileName, MODE_READWRITE);
    //fileId = Open("Test1.txt", MODE_READWRITE);
    write = Write(buffer, len, fileId);

    PrintString("Write ");
    PrintNum(write);
    PrintString(" characters: ");
    PrintString(buffer);
    PrintString("\n");
    Close(fileId);

    Halt();
}