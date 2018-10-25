#ifndef __SHORTEST__JOB__FIRST__
#define __SHORTEST__JOB__FIRST__

// Shortest Job First Algorithm

#include <stdio.h>
#include <stdlib.h>

#include "./Process.h"
#define TRUE 1
#define FALSE 0

void sjf_calculate_waiting_time(Process *p, int len)
{
	int i, j;
	int complete = 0, t = 0, minm = INT_MAX;
	int shortest = 0, finish_time;
	int check = FALSE;

	int *remain_time = (int *)malloc(sizeof(int) * len);

	for (i = 0; i < len; i++)
		remain_time[i] = p[i].burst;

	while (complete != len)
	{
		for (j = 0; j < len; j++)
		{
			if ((p[j].arrive_time <= t)
				&& (remain_time[j] < minm) && (remain_time[j] > 0))
			{
				minm = remain_time[j];
				shortest = j;
				check = TRUE;
			}
		}

		if (check == FALSE)
		{
			t++;
			continue;
		}

		remain_time[shortest]--;

		minm = remain_time[shortest];

		if (minm == 0)
			minm = INT_MAX;

		if (remain_time[shortest] == 0)
		{
			complete++;
			check = FALSE;

			finish_time = t + 1;

			p[shortest].waiting_time =
				finish_time - p[shortest].burst - p[shortest].arrive_time;

			if (p[shortest].waiting_time < 0)
				p[shortest].waiting_time = 0;
		}

		t++;
	}
}

void sjf_calculate_turnaround_time(Process *p, int len)
{
	int i;

	for (i = 0; i < len; i++)
		p[i].turnaround_time = p[i].burst + p[i].waiting_time;
}

int compare_by_turnaround_time(const void *a, const void *b)
{
	Process *ptA = (Process *)a;
	Process *ptB = (Process *)b;

	if (ptA->turnaround_time < ptB->turnaround_time)
		return -1;

	else if (ptA->turnaround_time > ptB->turnaround_time)
		return 1;

	else
		return 0;
}

void sjf_print_gantt_chart(Process *p, int len)
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

		if (p[i].turnaround_time > 9)
			printf("\b");

		printf("%d", p[i].turnaround_time + p[i].arrive_time);

	}

	printf("\n\n\n");
}

void SJF(Process *p, int len)
{
	int i;
	int total_waiting_time = 0;
	int total_turnaround_time = 0;

	sjf_calculate_waiting_time(p, len);
	sjf_calculate_turnaround_time(p, len);

	for (i = 0; i < len; i++)
	{
		total_waiting_time += p[i].waiting_time;
		total_turnaround_time += p[i].turnaround_time;
	}

	qsort(p, len, sizeof(Process), compare_by_turnaround_time);

	printf("SJF Scheduling Algorithms\n");
	print_table(p, len);
	printf("\n");

	printf("Average Waiting Time     : %-2.2lf\n", (double)total_waiting_time / (double)len);
	printf("Average Turnaround Time  : %-2.2lf\n\n", (double)total_turnaround_time / (double)len);

	sjf_print_gantt_chart(p, len);
}

#endif
