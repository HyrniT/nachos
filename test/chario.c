#include "syscall.h"

int
main()
{
  PrintChar(ReadChar());
  Halt();
  /* not reached */
}