#ifndef __FIRST__COME__FIRST__SERVED__
#define __FIRST__COME__FIRST__SERVED__

// FCFS Algorithm

#include <stdio.h>
#include <stdlib.h>

#include "./Process.h"
#include "./CompareFunction.h"
#include "./PrintTable.h"

void fcfs_print_gantt_chart(Process *p, int len)
{
	int i, j;

	printf(" ");

	for (i = 0; i < len; i++)
	{
		for (j = 0; j < p[i].burst; j++)
			printf("--");

		printf(" ");
	}

	printf("\n|");

	for (i = 0; i < len; i++)
	{
		for (j = 0; j < p[i].burst - 1; j++)
			printf(" ");

		printf("%s", p[i].id);

		for (j = 0; j < p[i].burst - 1; j++)
			printf(" ");

		printf("|");
	}

	printf("\n ");

	for (i = 0; i < len; i++)
	{
		for (j = 0; j < p[i].burst; j++)
			printf("--");

		printf(" ");
	}

	printf("\n");

	printf("0");

	for (i = 0; i < len; i++)
	{
		for (j = 0; j < p[i].burst; j++)
			printf("  ");

		if (p[i].return_time > 9)
			printf("\b");

		printf("%d", p[i].return_time);

	}

	printf("\n\n\n");
}

void FCFS(Process *p, int len)
{
	int i;
	int total_waiting_time = 0;
	int total_turnaround_time = 0;
	int total_return_time = 0;

	qsort(p, len, sizeof(Process), compare_by_arrive_time);

	for (i = 0; i < len; i++)
	{
		p[i].waiting_time = 0;
		p[i].return_time = 0;
	}

	p[0].return_time = p[0].burst;
	p[0].turnaround_time = p[0].return_time - p[0].arrive_time;
	total_return_time = p[0].burst;

	for (i = 1; i < len; i++)
	{
		p[i].waiting_time = total_return_time - p[i].arrive_time;
		p[i].return_time = total_return_time + p[i].burst;
		p[i].turnaround_time = p[i].return_time - p[i].arrive_time;

		total_return_time += p[i].burst;
		total_waiting_time += p[i].waiting_time;
		total_turnaround_time += p[i].turnaround_time;
	}

	printf("\nFCFS Scheduling Algorithm\n");
	fcfs_print_gantt_chart(p, len);

	printf("Average Waiting Time     : %-2.2lf\n", (double)total_waiting_time / (double)len);
	printf("Average Return Time      : %-2.2lf\n", (double)total_return_time / (double)len);
	printf("Average Turnaround Time  : %-2.2lf\n\n", (double)total_turnaround_time / (double)len);

	print_table(p, len);
}

#endif
