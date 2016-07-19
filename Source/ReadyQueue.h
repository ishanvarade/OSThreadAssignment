/*
 * ReadyQueue.h
 *
 *  Created on: 15-Jul-2016
 *      Author: ishan
 */

#include "iThread.h"
#include <stdlib.h>

#ifndef READYQUEUE_H_
#define READYQUEUE_H_

//#define Ready_queue_size 100

struct Ready_queue
{
	int count;
	int number_of_threads;
	int front_of_queue;
	int end_of_queue;

	struct Thread ** ready_array;
}ready_queue;

void initialize_ready_queue();


void enqueue(struct Thread *thread);
struct Thread * dequeue();

#endif /* READYQUEUE_H_ */
