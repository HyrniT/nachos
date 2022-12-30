#include "syscall.h"
#define MAX_LENGTH 256

int main()
{
     char fileName[MAX_LENGTH];
     int length;

     PrintString("File's name length (<=255): ");
     length = ReadNum();

     PrintString("File's name: ");
     ReadString(fileName, length);

     if(Remove(fileName)==1)
     {
         PrintString("Succeed in removing file ");
         PrintString(fileName);
         PrintString("\n");
     }
      else 
     {
         PrintString("Fail to remove file ");
         PrintString(fileName);
         PrintString("\n");
     }

    Halt();
}