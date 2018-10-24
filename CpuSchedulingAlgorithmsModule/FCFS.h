#ifndef __FIRST__COME__FIRST__SERVED__
#define __FIRST__COME__FIRST__SERVED__

// FCFS Algorithm

#include <stdio.h>
#include <stdlib.h>

#include "./Process.h"

int compare(const void *a, const void *b)
{
	Process *ptA = (Process *)a;
	Process *ptB = (Process *)b;

	if (ptA->arrive_time < ptB->arrive_time)
		return -1;

	else if (ptA->arrive_time > ptB->arrive_time)
		return 1;

	else
		return 0;
}

void print_table(Process p[], int n)
{
	int i;

	puts("+-----+------------+--------------+-----------------+");
	puts("| PID | Burst Time | Waiting Time | Turnaround Time |");
	puts("+-----+------------+--------------+-----------------+");

	for (i = 0; i < n; i++) {
		printf("| %3s |     %3d    |      %3d     |        %3d      |\n"
			, p[i].id, p[i].burst, p[i].waiting_time, p[i].turnaround_time);

		puts("+-----+------------+--------------+-----------------+");
	}

}

void print_gantt_chart(Process p[], int n)
{
	int i, j;

	printf(" ");

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < p[i].burst; j++)
			printf("--");

		printf(" ");
	}

	printf("\n|");

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < p[i].burst - 1; j++)
			printf(" ");

		printf("%s", p[i].id);

		for (j = 0; j < p[i].burst - 1; j++)
			printf(" ");

		printf("|");
	}

	printf("\n ");

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < p[i].burst; j++)
			printf("--");

		printf(" ");
	}

	printf("\n");

	printf("0");

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < p[i].burst; j++)
			printf("  ");

		if (p[i].turnaround_time > 9)
			printf("\b");

		printf("%d", p[i].turnaround_time);

	}

	printf("\n");

}

void FCFS(Process *p, int len)
{
	int i;
	int total_waiting_time = 0;
	int total_turnaround_time = 0;

	qsort(p, len, sizeof(Process), compare);

	for (i = 0; i < len; i++)
	{
		p[i].waiting_time = 0;
		p[i].turnaround_time = 0;

	}

	p[0].turnaround_time = p[0].burst;

	for (i = 1; i < len; i++)
	{
		p[i].waiting_time = p[i - 1].waiting_time + p[i - 1].burst;
		p[i].turnaround_time = p[i].waiting_time + p[i].burst;

		total_waiting_time += p[i].waiting_time;
		total_turnaround_time += p[i].turnaround_time;
	}

	printf("\n");
	print_table(p, len);
	printf("\n");

	printf("Average Waiting Time     : %-2.2lf\n", (double)total_waiting_time / (double)len);
	printf("Average Turnaround Time  : %-2.2lf\n\n", (double)total_turnaround_time / (double)len);

	printf("┌───────────────────────────────┐\n");
	printf("│          GANTT CHART          │\n");
	printf("└───────────────────────────────┘\n");
	print_gantt_chart(p, len);
}

#endif
