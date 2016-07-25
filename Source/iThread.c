#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "iThread.h"
#include "ReadyQueue.h"


#define switch_to(prev, next) 								\
{															\
		asm volatile ("movl (%%ebp), %[prev_ebp]	\t\n"	\
				"movl 4(%%ebp), %[prev_eip]		\t\n"		\
				"movl %%ebp, %[prev_esp]	\t\n"			\
				"addl $8, %[prev_esp]	\t\n"				\
				:[prev_esp] "=r" (prev->esp),				\
				 [prev_ebp] "=r" (prev->ebp),				\
				 [prev_eip] "=r" (prev->eip)				\
				 :											\
				 :);										\
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

/*
	if (prev -> status == exit_status)					\
    {														\
    	free(prev -> stack);								\
    	printf("\nFREE STACK\n");							\
    }														\
    */

const int STACK_SIZE = 1048579; // 1Mb
struct Thread *running_thread;

void set_running_thread(struct Thread * thread)
{
	running_thread = thread;
	thread -> status = running_status;
}

void print_running_thread_id()
{
	printf("* Thread Running: %p ", running_thread);
}

void exiting_iThread()
{
	printf("\nExiting Thread: %p\n", running_thread);
	running_thread -> status = exit_status;
	scheduler();
}

void create_iThread(struct Thread *thread, void (* start_routine) (void))
{
	thread -> stack = (void *) calloc(STACK_SIZE, sizeof (char));
	thread -> esp = thread -> stack + STACK_SIZE - 1;
	thread -> ebp = thread -> esp;
	thread -> eip = start_routine;

	thread -> esp = (int *)thread -> esp - 1;

	void **exiting_function;
	exiting_function = thread ->esp;
	*exiting_function = exiting_iThread;

	thread -> status = ready_status;
	enqueue(thread);

}



void scheduler()
{
	printf("\n* Entered in scheduller\n");
	struct Thread *prev;
	//struct Thread *next;

	prev = running_thread;

	if (prev -> status == running_status && prev != &mainThread)
	{
		enqueue(prev);
		prev -> status = ready_status;
	}

	if (ready_queue.count)
	{
		running_thread = dequeue();
		if (running_thread -> status == exit_status)
		{
			printf("\nXYS\n");
		}
		printf("Next Thread: %p\n\n", running_thread);
	}
	else
	{
		running_thread = &mainThread;
		printf("Next Thread: %p <Main Thread>\n\n", running_thread);
	}


	running_thread -> status = running_status;
	switch_to(prev, running_thread);

	printf("Ishan Varade\n");
}
