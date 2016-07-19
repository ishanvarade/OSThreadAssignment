/*
 * iThread.h
 *
 *  Created on: 15-Jul-2016
 *      Author: ishan
 */

#ifndef ITHREAD_H_
#define ITHREAD_H_


/* Thread Control Block */
struct Thread
{
	void *esp;
	void *eip;
	void *ebp;
	//bool isExit;
};

void scheduler(struct Thread *previousThread, struct Thread * nextThread);
void create_iThread(struct Thread *thread, void (* start_routine) (void));



#endif /* ITHREAD_H_ */
