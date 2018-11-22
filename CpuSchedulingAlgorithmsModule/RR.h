#ifndef __Round__ROBIN__
#define __Round__ROBIN__

// Round Robin Scheduling

#include <stdio.h>
#include <stdlib.h>

#include "./Process.h"
#include "./CompareFunction.h"
#include "./PrintTable.h"

#define TRUE 1
#define FALSE 0

void rr_calculate_waiting_time(Process *p, int len, Quantum q)
{
	int i;
	int curr_time = 0;
	int *remain_burst_time = (int *)malloc(sizeof(int) * len);

	for (i = 0; i < len; i++)
		remain_burst_time[i] = p[i].burst;

	while (TRUE)
	{
		int check = TRUE;

		for (i = 0; i < len; i++)
		{
			if (remain_burst_time[i] > 0)
			{
				check = FALSE;

				if (remain_burst_time[i] > q)
				{
					curr_time += q;
					remain_burst_time[i] -= q;
				}

				else
				{
					curr_time += remain_burst_time[i];
					p[i].waiting_time = curr_time - p[i].burst;
					remain_burst_time[i] = 0;
				}
			}
		}

		if (check == TRUE)
			break;
	}
}

void rr_calculate_turnaround_time(Process *p, int len)
{
	int i;

	for (i = 0; i < len; i++)
		p[i].turnaround_time = p[i].burst + p[i].waiting_time - p[i].arrive_time;
}

void rr_print_gantt_chart(Process *p, int len, Quantum q)
{
	int i, j;
	int curr_time = 0, total_burst_time = 0;
	int temp_total_burst_time = 0;
	int *remain_burst_time = (int *)malloc(sizeof(int) * len);

	for (i = 0; i < len; i++)
	{
		remain_burst_time[i] = p[i].burst;
		total_burst_time += p[i].burst;
	}

	while (TRUE)
	{
		int check = TRUE;

		for (i = 0; i < len; i++)
		{
			if (remain_burst_time[i] > 0)
			{
				check = FALSE;

				if (remain_burst_time[i] < q)
				{
					printf(" --");
				}

				else
				{
					printf(" ----");
				}

				if (remain_burst_time[i] > q)
				{
					curr_time += q;
					remain_burst_time[i] -= q;
				}

				else
				{
					curr_time += remain_burst_time[i];
					p[i].waiting_time = curr_time - p[i].burst;
					remain_burst_time[i] = 0;
				}


			}
		}

		if (check == TRUE)
			break;
	}

	printf(" \n");

	for (i = 0; i < len; i++)
	{
		remain_burst_time[i] = p[i].burst;
	}

	while (TRUE)
	{
		int check = TRUE;

		for (i = 0; i < len; i++)
		{
			if (remain_burst_time[i] > 0)
			{
				check = FALSE;

				if (remain_burst_time[i] < q)
				{

					printf("|%2s", p[i].id);
				}

				else
				{
					printf("| %2s", p[i].id);

					for (j = 0; j < q / 2; j++)
						printf(" ");
				}

				if (remain_burst_time[i] > q)
				{
					curr_time += q;
					remain_burst_time[i] -= q;
				}

				else
				{
					curr_time += remain_burst_time[i];
					p[i].waiting_time = curr_time - p[i].burst;
					remain_burst_time[i] = 0;
				}


			}
		}

		if (check == TRUE)
			break;
	}

	printf("|\n");

	for (i = 0; i < len; i++)
	{
		remain_burst_time[i] = p[i].burst;
	}

	while (TRUE)
	{
		int check = TRUE;

		for (i = 0; i < len; i++)
		{
			if (remain_burst_time[i] > 0)
			{
				check = FALSE;

				if (remain_burst_time[i] < q)
				{
					printf(" --");
				}

				else
				{
					printf(" ----");
				}

				if (remain_burst_time[i] > q)
				{
					curr_time += q;
					remain_burst_time[i] -= q;
				}

				else
				{
					curr_time += remain_burst_time[i];
					p[i].waiting_time = curr_time - p[i].burst;
					remain_burst_time[i] = 0;
				}


			}
		}

		if (check == TRUE)
			break;
	}

	printf("\n");

	for (i = 0; i < len; i++)
		remain_burst_time[i] = p[i].burst;

	curr_time = 0;

	while (TRUE)
	{
		int check = TRUE;

		for (i = 0; i < len; i++)
		{
			if (remain_burst_time[i] > 0)
			{
				check = FALSE;

				if (remain_burst_time[i] < q)
				{
					printf("%-2d ", curr_time);
				}

				else
				{
					printf("%-3d  ", curr_time);
				}

				if (remain_burst_time[i] > q)
				{
					curr_time += q;
					remain_burst_time[i] -= q;
				}

				else
				{
					curr_time += remain_burst_time[i];
					p[i].waiting_time = curr_time - p[i].burst;
					remain_burst_time[i] = 0;
				}
			}
		}

		if (check == TRUE)
			break;
	}

	printf("%-3d\n", total_burst_time);

	printf("\n");
}

void RR(Process *p, int len, Quantum quantum)
{
	int i;
	int total_waiting_time = 0;
	int total_turnaround_time = 0;
	int total_return_time = 0;
	int total_response_time = 0;

	qsort(p, len, sizeof(Process), compare_by_arrive_time);

	rr_calculate_waiting_time(p, len, quantum);
	rr_calculate_turnaround_time(p, len);

	for (i = 0; i < len; i++)
	{
		p[i].waiting_time = p[i].turnaround_time - p[i].burst;
		p[i].return_time = p[i].arrive_time + p[i].burst + p[i].waiting_time;

		if (i == 0)
			p[i].response_time = 0;

		else
			p[i].response_time = p[i - 1].response_time + quantum;

		total_turnaround_time += p[i].turnaround_time;
		total_waiting_time += p[i].waiting_time;
		total_return_time += p[i].return_time;
		total_response_time += p[i].response_time;
	}

	printf("Round Robin Scheduling Algorithm ( Quantum : %d )\n\n", quantum);

	rr_print_gantt_chart(p, len, quantum);

	printf("\nAverage Waiting Time     : %-2.2lf\n", (double)total_waiting_time / (double)len);
	printf("Average Turnaround Time  : %-2.2lf\n", (double)total_turnaround_time / (double)len);
	printf("Average Response Time    : %-2.2lf\n\n", (double)total_response_time / (double)len);

	print_table(p, len);
}

#endif
