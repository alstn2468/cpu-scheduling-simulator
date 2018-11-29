#ifndef __NON__PREEMPTIVE__PRIORITY__SCHEDULING__
#define __NON__PREEMPTIVE__PRIORITY__SCHEDULING__

// Non-preemptive Priority Scheduling Algorithm

#include "./Process.h"
#include "./SortingFunction.h"
#include "./PrintTable.h"

void npps_calculate(Process *p, int len)
{
	int i, j;
	int check, min;
	int time = 0;

	p[0].return_time = p[0].burst;
	p[0].turnaround_time = p[0].return_time - p[0].arrive_time;
	p[0].response_time = 0;
	p[0].completed = TRUE;

	time = p[0].burst;

	while (TRUE)
	{
		min = INT_MAX;
		check = FALSE;

		for (i = 1; i < len; i++)
		{
			if ((p[min].priority > p[i].priority)
				&& (p[i].completed == FALSE)
					&& (p[i].arrive_time <= time))
			{
				min = i;
				check = TRUE;
			}
		}

		if (check == FALSE)
			break;

		p[min].response_time = time - p[min].arrive_time;
		p[min].return_time = time + p[min].burst;
		p[min].turnaround_time = p[min].return_time - p[min].arrive_time;
		p[min].waiting_time = time - p[min].arrive_time;
		p[min].completed = TRUE;

		time += p[min].burst;
	}
}

void npps_print_gantt_chart(Process *p, int len)
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

		if (p[i].return_time > 9)
			printf("\b");

		printf("%d", p[i].return_time);
	}

	printf("\n");
}

void NPPS(Process *p, int len)
{
	int i;
	int total_waiting_time = 0;
	int total_turnaround_time = 0;
	int total_return_time = 0;
	int total_response_time = 0;

	process_init(p, len);

	merge_sort_by_arrive_time(p, 0, len);

	npps_calculate(p, len);

	for (i = 0; i < len; i++)
	{
		total_waiting_time += p[i].waiting_time;
		total_turnaround_time += p[i].turnaround_time;
		total_return_time += p[i].return_time;
		total_response_time += p[i].response_time;
	}

	quick_sort_by_return_time(p, len);

	printf("\tNon-preemptive Priority Scheduling Algorithm\n\n");

	npps_print_gantt_chart(p, len);

	printf("\n\tAverage Waiting Time     : %-2.2lf\n", (double)total_waiting_time / (double)len);
	printf("\tAverage Turnaround Time  : %-2.2lf\n", (double)total_turnaround_time / (double)len);
	printf("\tAverage Response Time    : %-2.2lf\n\n", (double)total_response_time / (double)len);

	print_table(p, len);
}

#endif
