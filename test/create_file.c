#include "syscall.h"
#define MAX_LENGTH 255

int main()
{
    char fileName[MAX_LENGTH + 1];
    int length;

    PrintString("Enter file name's length (<=255): ");
    length = ReadNum();

    PrintString("File's name: ");
    ReadString(fileName, length);

    if (Create(fileName) == 0)
    {
        PrintString("Succeed in creating file ");
        PrintString(fileName);
        PrintString("\n");
    }
    else 
    {
        PrintString("Fail to create file ");
        PrintString(fileName);
        PrintString("\n");
    }
    Halt();
}