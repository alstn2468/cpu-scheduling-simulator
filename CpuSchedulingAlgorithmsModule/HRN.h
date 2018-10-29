#ifndef __HIGHEST__RESPONSE__RATIO__NEXT__
#define __HIGHEST__RESPONSE__RATIO__NEXT__

// HRN Algorithm

#include <stdio.h>
#include <stdlib.h>

#include "./Process.h"
#include "./CompareFunction.h"
#include "./PrintTable.h"

#define TRUE 1
#define FALSE 0

void hrn_print_gantt_chart(Process *p, int len)
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

	printf("\n");
}

void HRN(Process *p, int len)
{
	int i, j;
	int time, loc;
	int total_burst_time = 0;
	int total_waiting_time = 0;
	int total_turnaround_time = 0;
	int total_return_time = 0;
	int total_response_time = 0;

	float hrr, temp;

	for (i = 0; i < len; i++)
	{
		total_burst_time += p[i].burst;
		p[i].completed = FALSE;
	}

	qsort(p, len, sizeof(Process), compare_by_arrive_time);

	for (time = p[0].arrive_time; time < total_burst_time;)
	{

		hrr = -9999;

		for (i = 0; i < len; i++)
		{
			if (p[i].arrive_time <= time && p[i].completed != TRUE)
			{
				temp = (p[i].burst + (time - p[i].arrive_time)) / p[i].burst;

				if (hrr < temp)
				{
					hrr = temp;
					loc = i;
				}
			}
		}

		time += p[loc].burst;

		p[loc].waiting_time = time - p[loc].arrive_time - p[loc].burst;
		p[loc].turnaround_time = time - p[loc].arrive_time;
		p[loc].return_time = p[loc].turnaround_time + p[loc].arrive_time;
		p[loc].response_time = p[loc].arrive_time + p[loc].waiting_time;
		p[loc].completed = TRUE;

		total_turnaround_time += p[loc].turnaround_time;
		total_waiting_time += p[loc].waiting_time;
		total_return_time += p[loc].return_time;
		total_response_time += p[loc].response_time;
	}

	qsort(p, len, sizeof(Process), compare_by_return_time);

	printf("Highest Response Ratio Next Scheduling Algorithm\n\n");

	hrn_print_gantt_chart(p, len);

	printf("\nAverage Waiting Time     : %-2.2lf\n", (double)total_waiting_time / (double)len);
	printf("Average Turnaround Time  : %-2.2lf\n", (double)total_turnaround_time / (double)len);
	printf("Average Return Time      : %-2.2lf\n", (double)total_return_time / (double)len);
	printf("Average Response Time    : %-2.2lf\n\n", (double)total_response_time / (double)len);

	print_table(p, len);
}

#endif
