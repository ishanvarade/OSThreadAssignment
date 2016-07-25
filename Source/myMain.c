/*
 * myMain.c
 *
 *  Created on: 15-Jul-2016
 *      Author: ishan
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "iThread.h"
#include "ReadyQueue.h"

void thread_fun();

void thread2_fun()
{
	printf("\nThread2 called 1st time\n");
	//scheduler(&thread2, &thread1);
	printf("\nThread2 called 2nd time\n");
}

void thread1_fun()
{
	printf("\nThread1 called 1st time\n");
	//scheduler(&thread1, &thread2);
	printf("\nThread1 called 2nd time\n");
	//scheduler(&thread1, &mainThread);
}

int main()
{
	initialize_ready_queue();

	set_running_thread(&mainThread);

//	struct Thread thread1;
//	struct Thread thread2;
//
//	create_iThread(&thread1, thread_fun);
//	create_iThread(&thread2, thread_fun);

	const int n = 3;

	for (int i = 0; i < n; i++)
	{
		struct Thread *thread = (struct Thread *)malloc(sizeof (struct Thread));
		create_iThread(thread, thread_fun);
	}

	scheduler();

	printf("\nExiting main\n");
	return 0;
}



void thread_fun()
{
	//printf("\nThread called 1st time\n");
	for (int i = 1; i <= 10; i++)
	{
		print_running_thread_id();
		printf("Thread fun : %d", i);
		scheduler();
	}
}
