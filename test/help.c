/* halt.c
 *	Simple program to test whether running a user program works.
 *	
 *	Just do a "syscall" that shuts down the OS.
 *
 * 	NOTE: for some reason, user programs with global data structures 
 *	sometimes haven't worked in the Nachos environment.  So be careful
 *	out there!  One option is to allocate data structures as 
 * 	automatics within a procedure, but if you do this, you have to
 *	be careful to allocate a big enough stack to hold the automatics!
 */

#include "syscall.h"

int
main()
{
    PrintString("-------DANH SACH THANH VIEN NHOM-------\n");
    PrintString("20120049 - Nguyen Hai Dang\n");
    PrintString("20120077 - Nguyen Quang Hien\n");
    PrintString("20120084 - Nguyen Van Hieu\n");
    PrintString("-------MO TA NGAN GON-------\n");
    PrintString("ascii: Chuong trinh ascii se in ra cac ki tu co the hien thi duoc.\n");
    PrintString("sort: Sap xep cac so theo 1 thu tu nao do bang thuat toan bubble sort.\n");
    Halt();
    /* not reached */
}