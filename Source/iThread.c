#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "iThread.h"

const int STACK_SIZE = 1024;
void exiting_iThread()
{
	printf("\nWhat are you gonna to do\n");
}

void create_iThread(struct Thread *thread, void (* start_routine) (void))
{
	thread -> esp = (void *) calloc(STACK_SIZE, sizeof (char)) + STACK_SIZE - 1;
	thread -> ebp = thread -> esp;
	thread -> eip = start_routine;

	thread -> esp = (int *)thread -> esp - 1;
	void **xyz;
	xyz = thread ->esp;
	*xyz = exiting_iThread;
}



void scheduler(struct Thread *prev, struct Thread *next)
{
	printf("\n* Entered in scheduller\n");

/////////////////////////////////////////////////////////
	/*Saving states*/
	asm volatile ("movl (%%ebp), %[prev_ebp]	\t\n"
			"movl 4(%%ebp), %[prev_eip]		\t\n"
			"movl %%ebp, %[prev_esp]	\t\n"
			"addl $8, %[prev_esp]	\t\n"
			:[prev_esp] "=r" (prev->esp),
						[prev_ebp] "=r" (prev->ebp),
						[prev_eip] "=r" (prev->eip)
						:
						:);

	/*Loading states*/
	asm volatile ("movl %[next_esp], %%ebx	\t\n"
			"movl %%ebx, %%esp 		\t\n"
			"movl %[next_ebp], %%ebp	\t\n"
			"jmp *%[next_eip]"
			:
			:[next_esp] "r" (next->esp),
			 [next_ebp] "r" (next->ebp),
			 [next_eip] "r" (next->eip)
			 :
			);
//////////////////////////////////////////////////////////
	printf("Ishan Varade\n");
}
