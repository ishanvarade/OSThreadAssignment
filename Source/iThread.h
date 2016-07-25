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
	enum {
		ready_status,
		running_status,
		block_status,
		exit_status
	} status;
	void *esp;
	void *eip;
	void *ebp;

	void *stack;
	//bool isExit;
};

struct Thread mainThread;

void set_running_thread(struct Thread * thread);
void print_running_thread_id();
void scheduler();
void create_iThread(struct Thread *thread, void (* start_routine) (void));



#endif /* ITHREAD_H_ */
