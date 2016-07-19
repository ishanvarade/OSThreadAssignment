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

struct Thread mainThread;
struct Thread thread1;
struct Thread thread2;
void thread_fun();

void thread2_fun()
{
	printf("\nThread2 called 1st time\n");
	scheduler(&thread2, &thread1);
	printf("\nThread2 called 2nd time\n");
}

void thread1_fun()
{
	printf("\nThread1 called 1st time\n");
	scheduler(&thread1, &thread2);
	printf("\nThread1 called 2nd time\n");
	//scheduler(&thread1, &mainThread);
}

int main()
{
	create_iThread(&thread1, thread1_fun);
	create_iThread(&thread2, thread2_fun);
	scheduler(&mainThread, &thread1);
	//justTest(&mainThread);
	//myCall();

	// Creating ready Queue Ready Queue
	printf("\nExiting main\n");
	return 0;
}



void thread_fun()
{
	printf("\nThread called 1st time\n");
	int k = 0;

	while (1)
	{


		//scheduler();
	}

}
