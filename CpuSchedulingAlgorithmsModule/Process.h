#ifndef __PROCESS__
#define __PROCESS__
#define ID_LEN 20

// Process Structure Header

typedef struct _process
{
	char id[ID_LEN];
	int arrive_time;
	int waiting_time;
	int return_time;
	int response_time;
	int turnaround_time;
	int burst;
	int priority;
	int completed;
} Process;

typedef int Quantum;

#endif
