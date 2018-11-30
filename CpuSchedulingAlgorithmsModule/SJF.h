#ifndef __SHORTEST__JOB__FIRST__
#define __SHORTEST__JOB__FIRST__

// Shortest Job First Algorithmd

#include "./Process.h"
#include "./SortingFunction.h"
#include "./PrintTable.h"

void sjf_calculate_time(Process *p, int len)
{
	int i, j;
	int curr_time = 0;
	int min = 0;
	int check = FALSE;

	p[0].completed = TRUE;
	p[0].return_time = p[0].burst;
	p[0].turnaround_time = p[0].burst - p[0].arrive_time;
	p[0].waiting_time = 0;
	curr_time = p[0].burst;

	for(i = 1; i < len; i++)
	{
		for (j = 1; j < len; j++)
		{
			if (p[j].completed == TRUE)
				continue;

			else
			{
				min = j;
				break;
			}
		}

		for (j = i; j < len; j++)
		{
			if ((p[j].completed == FALSE)
					&& (p[j].arrive_time <= curr_time)
						&& (p[j].burst < p[min].burst))
			{
				min = j;
			}
		}


		p[min].waiting_time = curr_time - p[min].arrive_time;
		p[min].completed = TRUE;

		curr_time += p[min].burst;

		p[min].return_time = curr_time;
		p[min].turnaround_time = p[min].return_time - p[min].arrive_time;
	}
}

void sjf_print_gantt_chart(Process *p, int len)
{
	int i, j;

	printf("\t ");

	for (i = 0; i < len; i++)
	{
		for (j = 0; j < p[i].burst; j++)
			printf("--");

		printf(" ");
	}

	printf("\n\t|");

	for (i = 0; i < len; i++)
	{
		for (j = 0; j < p[i].burst - 1; j++)
			printf(" ");

		printf("%s", p[i].id);

		for (j = 0; j < p[i].burst - 1; j++)
			printf(" ");

		printf("|");
	}

	printf("\n\t ");

	for (i = 0; i < len; i++)
	{
		for (j = 0; j < p[i].burst; j++)
			printf("--");

		printf(" ");
	}

	printf("\n\t");

	printf("0");

	for (i = 0; i < len; i++)
	{
		for (j = 0; j < p[i].burst; j++)
			printf("  ");

		if (p[i].turnaround_time > 9)
			printf("\b");

		printf("%d", p[i].return_time);
	}

	printf("\n");
}

void SJF(Process *p, int len)
{
	int i;
	int total_waiting_time = 0;
	int total_turnaround_time = 0;
	int total_return_time = 0;
	int total_response_time = 0;

	process_init(p, len);

	merge_sort_by_arrive_time(p, 0, len);

	sjf_calculate_time(p, len);

	for (i = 0; i < len; i++)
	{
		p[i].return_time = p[i].turnaround_time + p[i].arrive_time;
		p[i].response_time = p[i].waiting_time;

		total_waiting_time += p[i].waiting_time;
		total_turnaround_time += p[i].turnaround_time;
		total_return_time += p[i].return_time;
		total_response_time += p[i].response_time;
	}

	printf("\tSJF Scheduling Algorithms\n\n");

	quick_sort_by_return_time(p, len);

	sjf_print_gantt_chart(p, len);

	printf("\n\tAverage Waiting Time     : %-2.2lf\n", (double)total_waiting_time / (double)len);
	printf("\tAverage Turnaround Time  : %-2.2lf\n", (double)total_turnaround_time / (double)len);
	printf("\tAverage Response Time    : %-2.2lf\n\n", (double)total_response_time / (double)len);

	print_table(p, len);
}

#endif
