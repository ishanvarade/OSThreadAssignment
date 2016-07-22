/*
 * ReadyQueue.c
 *
 *  Created on: 16-Jul-2016
 *      Author: ishan
 */
#include "ReadyQueue.h"
#include <stdlib.h>
#include <stdio.h>

void initialize_ready_queue()
{
		ready_queue.count = 0;
		ready_queue.number_of_threads = 100;
		ready_queue.front_of_queue = -1;
		ready_queue.end_of_queue = -1;
		ready_queue.ready_array = (struct Thread **)calloc(100, sizeof(struct Thread *));
}

void enqueue(struct Thread *thread)
{
	if (0 == ready_queue.count)
	{
		ready_queue.end_of_queue = 0;
		ready_queue.front_of_queue = 0;
	}
	else if (ready_queue.count < ready_queue.number_of_threads)
	{
		ready_queue.end_of_queue = (ready_queue.end_of_queue + 1) %
				ready_queue.number_of_threads;
	}
	else
	{
		printf("E: Queue overflow.\n");
	}

	ready_queue.ready_array[ready_queue.end_of_queue] = thread;
	++ready_queue.count;
}

struct Thread * dequeue()
{
	struct Thread *thread;
	if (ready_queue.count > 0)
	{
		thread = ready_queue.ready_array[ready_queue.front_of_queue];
		ready_queue.front_of_queue = (ready_queue.front_of_queue + 1) %
				ready_queue.number_of_threads;

		--ready_queue.count;
		if (0 == ready_queue.count)
		{
			ready_queue.front_of_queue = -1;
			ready_queue.end_of_queue = -1;
		}

		return thread;
	}

	return NULL;
}
