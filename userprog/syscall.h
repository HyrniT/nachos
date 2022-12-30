/* syscalls.h
 * 	Nachos system call interface.  These are Nachos kernel operations
 * 	that can be invoked from user programs, by trapping to the kernel
 *	via the "syscall" instruction.
 *
 *	This file is included by user programs and by the Nachos kernel.
 *
 * Copyright (c) 1992-1993 The Regents of the University of California.
 * All rights reserved.  See copyright.h for copyright notice and limitation
 * of liability and disclaimer of warranty provisions.
 */

#ifndef SYSCALLS_H
#define SYSCALLS_H

#include "copyright.h"
#include "errno.h"
/* system call codes -- used by the stubs to tell the kernel which system call
 * is being asked for
 */
#define SC_Halt 0
#define SC_Exit 1
#define SC_Exec 2
#define SC_Join 3
#define SC_Create 4
#define SC_Remove 5
#define SC_Open 6
#define SC_Read 7
#define SC_Write 8
#define SC_Seek 9
#define SC_Close 10
#define SC_ThreadFork 11
#define SC_ThreadYield 12
#define SC_ExecV 13
#define SC_ThreadExit 14
#define SC_ThreadJoin 15

#define SC_Add 42
#define SC_ReadNum 43
#define SC_PrintNum 44
#define SC_ReadChar 45
#define SC_PrintChar 46
#define SC_RandomNum 47
#define SC_ReadString 48
#define SC_PrintString 49
#define SC_CreateFile 50
#define SC_CreateSemaphore 51
#define SC_Wait 52
#define SC_Signal 53
#define SC_GetPid 54


#ifndef IN_ASM

#define _ConsoleInput 0
#define _ConsoleOutput 1

/* Stop Nachos, and print out performance stats */
void Halt();

/* This user program is done (status = 0 means exited normally). */
void Exit(int status);

/* A unique identifier for an executing user program (address space) */
typedef int SpaceId;
/* A unique identifier for a thread within a task */
typedef int ThreadId;

/* This can be implemented as a call to ExecV */
SpaceId Exec(char *exec_name);

/* Only return once the user program "id" has finished. Return the exit status */
int Join(SpaceId id);

/* Create a Nachos file, with name "name".
   Return 0 on success, -1 on failure */
int Create(char* name);

/* Remove a Nachos file, with name "name" */
int Remove(char *name);

/* A unique identifier for an open Nachos file. */
typedef int OpenFileId;
/* Open the Nachos file "name", and return an "OpenFileId" */
/* OpenFileId Open(char *name); */
OpenFileId Open(char *name, int type);


/* Read "size" bytes from the open file into "buffer".
Return the number of bytes actually read */
int Read(char *buffer, int size, OpenFileId id);

/* Write "size" bytes from "buffer" to the open file.
   Return the number of bytes actually read on success */
int Write(char *buffer, int size, OpenFileId id);

/* Set the seek position of the open file "id" to the byte "position" */
int Seek(int position, OpenFileId id);

/* Close the file, we're done reading and writing to it.
   Return 1 on success, negative error code on failure */
int Close(OpenFileId id);

/* Fork a thread to run a procedure in the *same* address space as the current thread.
   Return a positive ThreadId on success, negative error code on failure */
ThreadId ThreadFork(void (*func)());

/* Yield the CPU to another runnable thread, whether in this address space or not */
void ThreadYield();

/* Run the executable, stored in the Nachos file "argv[0]".
Return the address space identifier */
SpaceId ExecV(int argc, char *argv[]);

/* Blocks current thread until lokal thread ThreadID exits with ThreadExit.
   Function returns the ExitCode of ThreadExit() of the exiting thread */
int ThreadJoin(ThreadId id);

/* Deletes current thread and returns ExitCode to every waiting lokal thread */
void ThreadExit(int ExitCode);

/* Add the two operants and return the result*/
int Add(int op1, int op2);

/////////////////////////// Nguyen Quang Hien

int ReadNum();

void PrintNum(int num);

/////////////////////////// Nguyen Van Hieu

char ReadChar();

void PrintChar(char character);

int RandomNum();

/////////////////////////// Nguyen Hai Dang

void ReadString(char *buffer, int length);

void PrintString(char *buffer);

//int CreateSemaphore(char *name, int semval);

//int Wait(char *name);

//int Signal(char *name);

















#endif /* IN_ASM */

#endif /* SYSCALL_H */
