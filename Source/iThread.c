#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "iThread.h"
#include "ReadyQueue.h"


#define switch_to(prev, next) 								\
{															\
	if (prev)												\
	{														\
		asm volatile ("movl (%%ebp), %[prev_ebp]	\t\n"	\
				"movl 4(%%ebp), %[prev_eip]		\t\n"		\
				"movl %%ebp, %[prev_esp]	\t\n"			\
				"addl $8, %[prev_esp]	\t\n"				\
				:[prev_esp] "=r" (prev->esp),				\
				 [prev_ebp] "=r" (prev->ebp),				\
				 [prev_eip] "=r" (prev->eip)				\
				 :											\
				 :);										\
	}														\
	/*Loading states*/										\
	asm volatile ("movl %[next_esp], %%ebx	\t\n"			\
			"movl %%ebx, %%esp 		\t\n"					\
			"movl %[next_ebp], %%ebp	\t\n"				\
			"jmp *%[next_eip]"								\
			:												\
			:[next_esp] "r" (next->esp),					\
			 [next_ebp] "r" (next->ebp),					\
			 [next_eip] "r" (next->eip)						\
			 :												\
	);														\
}															\

const int STACK_SIZE = 1024;
struct Thread *running_thread;

void set_running_thread(struct Thread * thread)
{
	running_thread = thread;
}

void print_running_thread_id()
{
	printf("\n* Thread Running: %p \n", running_thread);
}

void exiting_iThread()
{
	printf("\nExiting Thread\n");
	running_thread = NULL;
	scheduler();
}

void create_iThread(struct Thread *thread, void (* start_routine) (void))
{
	thread -> esp = (void *) calloc(STACK_SIZE, sizeof (char)) + STACK_SIZE - 1;
	thread -> ebp = thread -> esp;
	thread -> eip = start_routine;

	thread -> esp = (int *)thread -> esp - 1;

	void **exiting_function;
	exiting_function = thread ->esp;
	*exiting_function = exiting_iThread;

	enqueue(thread);

}



void scheduler()
{
	printf("\n* Entered in scheduller\n");
	struct Thread *prev;
	//struct Thread *next;

	prev = running_thread;

	if (prev && prev != &mainThread)
	{
		enqueue(prev);
	}


	if (ready_queue.count)
	{
		running_thread = dequeue();
	}
	else
	{
		running_thread = &mainThread;
	}

	switch_to(prev, running_thread);

	/////////////////////////////////////////////////////////
	/*Saving states*/
//	if (prev)
//	{
//		asm volatile ("movl (%%ebp), %[prev_ebp]	\t\n"
//				"movl 4(%%ebp), %[prev_eip]		\t\n"
//				"movl %%ebp, %[prev_esp]	\t\n"
//				"addl $8, %[prev_esp]	\t\n"
//				:[prev_esp] "=r" (prev->esp),
//				 [prev_ebp] "=r" (prev->ebp),
//				 [prev_eip] "=r" (prev->eip)
//				 :
//				 :);
//	}
//
//	/*Loading states*/
//	asm volatile ("movl %[next_esp], %%ebx	\t\n"
//			"movl %%ebx, %%esp 		\t\n"
//			"movl %[next_ebp], %%ebp	\t\n"
//			"jmp *%[next_eip]"
//			:
//			:[next_esp] "r" (next->esp),
//			 [next_ebp] "r" (next->ebp),
//			 [next_eip] "r" (next->eip)
//			 :
//	);
	//////////////////////////////////////////////////////////
	printf("Ishan Varade\n");
}
