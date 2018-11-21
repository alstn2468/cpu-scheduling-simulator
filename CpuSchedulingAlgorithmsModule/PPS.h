#ifndef __PREEMPTIVE__PRIORITY__SCHEDULING__
#define __PREEMPTIVE__PRIORITY__SCHEDULING__

// Preemptive Priority Scheduling Algorithm

#include <stdio.h>
#include <stdlib.h>

#include "./Process.h"
#include "./PrintTable.h"

#define TRUE 1
#define FALSE 0

void pps_calculate_waiting_time(Process *p, int len)
{
	int *remain_burst_time = (int *)malloc(sizeof(int)*len);
	int current_time = 0;
	int total_burst_time = 0;
	int priority;
	int k = 0;

	for (int i = 0;i < len;i++) 
	{
		remain_burst_time[i] = p[i].burst;
		total_burst_time += p[i].burst;
		p[i].completed = FALSE;
	}

	while (current_time <= total_burst_time)
	{
		priority = INT_MAX;

		if (current_time <= p[len - 1].arrive_time)
		{
			for (int i = 0;i < len;i++)
			{
				if (p[i].completed == FALSE && p[i].arrive_time <= current_time)
				{
					if (priority > p[i].priority) 
					{
						priority = p[i].priority;
						k = i;
					}
				}
			}
		}

		else
		{
			for (int i = 0;i < len;i++)
			{
				if (p[i].completed == FALSE)
				{
					if (priority > p[i].priority) 
					{
						priority = p[i].priority;
						k = i;
					}
				}
			}
		}

		remain_burst_time[k]--;
		current_time++;

		if (remain_burst_time[k] == 0) 
		{
			p[k].completed = TRUE;
			p[k].waiting_time = current_time - p[k].burst - p[k].arrive_time;
		}
	}
}

void pps_calculate_turnaround_time(Process *p, int len)
{
	int i;
	for (i = 0;i < len;i++)
	{
		p[i].turnaround_time = p[i].burst + p[i].waiting_time - p[i].arrive_time;
	}
}

void pps_print_gantt_chart(Process *p, int len)
{

}

void PPS(Process *p, int len)
{
	int i;
	int total_waiting_time = 0;
	int total_turnaround_time = 0;
	int total_return_time = 0;
	int total_response_time = 0;

	qsort(p, len, sizeof(Process), compare_by_arrive_time);

	pps_calculate_waiting_time(p, len);

	print_table(p, len);
}
#endif
