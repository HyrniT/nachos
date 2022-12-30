/* sort.c 
 *    Test program to sort a large number of integers.
 *
 *    Intention is to stress virtual memory system.
 *
 *    Ideally, we could read the unsorted array off of the file system,
 *	and store the result back to the file system!
 */


/*
#define UNIX
#define UNIX_DEBUG
*/


#include "syscall.h"

#define SIZE (100)

int A[SIZE];	/* size of physical memory; with code, we'll run out of space!*/

int
main()
{
    int i, j, tmp, n, o;
    do {
        PrintString("Enter n: ");
        n = ReadNum();
        if (n < 0 || n > 100)
        PrintString("Sorry, n must be 0 <= n <= 100, try again please: ");
    } while (n < 0 || n > 100);
    /* first initialize the array, in reverse sorted order */

    for (i = 0; i < n; i++) {
        PrintString("a[");
        PrintNum(i);
        PrintString("]: ");
        A[i] = ReadNum();
    }

    do {
        PrintString("Your sort order (1: increasing, 2: decreasing) is: ");
        o = ReadNum();
        if (o != 1 && o != 2)
            PrintString("Only 1 or 2, try agian please: \n");
    } while (o != 1 && o != 2);


    /* then sort! */
    for (i = 0; i < n; i++) {
        for (j = 0; j < (n-1); j++) {
            if (o == 1) {
                if (A[j] > A[j + 1]) {	/* out of order -> need to swap ! */
                tmp = A[j];
                A[j] = A[j + 1];
                A[j + 1] = tmp;
                }
            }
            else if (o == 2) {
                if (A[j] < A[j + 1]) {	/* out of order -> need to swap ! */
                tmp = A[j];
                A[j] = A[j + 1];
                A[j + 1] = tmp;
                }
            }
        }
    }
    PrintString("Day so sau khi sap xep la: ");
    for (i = 0; i < n; i++) {
        PrintNum(A[i]);
        PrintChar(' ');
    }
    PrintChar('\n');
    Halt();
}