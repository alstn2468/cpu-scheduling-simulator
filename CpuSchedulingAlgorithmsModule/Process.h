#ifndef __PROCESS__
#define __PROCESS__
#define ID_LEN 20
#define TRUE 1
#define FALSE 0

// Process Structure Header

typedef struct _process
{
	char id[ID_LEN];
	int arrive_time;
	int waiting_time;
	int return_time;
	int turnaround_time;
	int response_time;
	int burst;
	int priority;
	int completed;
} Process;

typedef int Quantum;

void process_init(Process p[], int len)
{
	int i;

	for (i = 0; i < len; i++)
	{
		p[i].waiting_time = 0;
		p[i].return_time = 0;
		p[i].response_time = 0;
		p[i].completed = FALSE;
	}
}

#endif
