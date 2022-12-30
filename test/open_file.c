#include "syscall.h"
#define MAX_LENGTH 255

int main() 
{
    int length, fileId;
    char fileName[MAX_LENGTH + 1];

    PrintString("Enter file name's length (<=255): ");
    length = ReadNum();

    PrintString("Enter file name: ");
    ReadString(fileName, length);
    
    if ((fileId = Open(fileName, 0)) != -1) 
    {
        PrintString("File ");
        PrintString(fileName);
        PrintString(" opened successfully!\n");
        PrintString("File Id: ");
        PrintNum(fileId);
        PrintString("\n");
        Close(fileId);
    } 
     else
    {
        PrintString("Fail to open file ");
        PrintString(fileName);
        PrintString("\n");
    }
    Halt();
}