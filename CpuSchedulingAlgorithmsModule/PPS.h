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
	int *count = (int *)malloc(sizeof(int)*len);
	int current_time = 0;
	int total_burst_time = 0;
	int priority;
	int k = 0;

	for (int i = 0; i < len; i++)
	{
		count[i] = 0;
		remain_burst_time[i] = p[i].burst;
		total_burst_time += p[i].burst;
		p[i].completed = FALSE;
	}

	while (current_time < total_burst_time)
	{
		priority = INT_MAX;

		if (current_time <= p[len - 1].arrive_time)
		{
			for (int i = 0; i < len; i++)
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
			for (int i = 0; i < len; i++)
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

		if (count[k] == 0)
		{
			count[k]++;
			p[k].response_time = current_time;
		}

		remain_burst_time[k]--;
		current_time++;

		if (remain_burst_time[k] == 0)
		{
			p[k].completed = TRUE;
			p[k].waiting_time = current_time - p[k].burst - p[k].arrive_time;
			p[k].return_time = current_time;
		}
	}
}

void pps_print_gantt_chart(Process *p, int len)
{
	int i, j;
	int *count = (int *)malloc(sizeof(int)*len);
	int total_burst_time = 0;
	int current_time = 0, previous_time = 0;
	int *remain_burst_time = (int *)malloc(sizeof(int)*len);
	int *running_time;
	int k, pre_k = 0;
	int priority;
	int num;

	for (i = 0; i < len; i++)
	{
		remain_burst_time[i] = p[i].burst;
		total_burst_time += p[i].burst;
		p[i].completed = FALSE;
		count[i] = 0;
	}

	running_time = (int *)malloc(sizeof(int)*total_burst_time);

	for (j = 0; j < total_burst_time; j++)
		running_time[j] = -1;

	printf(" ");

	while (current_time < total_burst_time)
	{
		priority = INT_MAX;

		if (current_time <= p[len - 1].arrive_time)
		{
			for (i = 0; i < len; i++)
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
			for (i = 0; i < len; i++)
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

		if (pre_k != k)
			printf(" ");

		printf("--");
		remain_burst_time[k]--;
		current_time++;
		pre_k = k;

		if (remain_burst_time[k] == 0)
			p[k].completed = TRUE;

	}

	//간트차트 프로세스 이름 출력
	for (i = 0; i < len; i++)
	{
		remain_burst_time[i] = p[i].burst;
		p[i].completed = FALSE;
	}

	current_time = 0;
	printf("\n|");

	while (current_time < total_burst_time)
	{

		priority = INT_MAX;

		if (current_time <= p[len - 1].arrive_time)
		{
			for (i = 0; i < len; i++)
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
			for (i = 0; i < len; i++)
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

		if (current_time == 0)
		{
			count[k]++;
			printf("  ");
		}

		else
		{
			if (pre_k != k)
			{
				running_time[current_time] = current_time;
				num = count[pre_k] + 1;
				count[pre_k] = 0;
				count[k]++;

				for (int a = 0; a < num; a++)
					printf("\b");

				printf("%2s", p[pre_k].id);

				for (int b = 0; b < num - 2; b++)
					printf(" ");

				printf("|  ");
			}

			else
			{
				count[k]++;
				printf("  ");
				if (current_time == total_burst_time - 1)
				{
					num = count[pre_k] + 1;
					count[pre_k] = 0;
					count[k]++;

					for (int a = 0; a < num; a++)
						printf("\b");

					printf("%2s", p[pre_k].id);

					for (int b = 0; b < num - 2; b++)
						printf(" ");
				}
			}

		}
		pre_k = k;
		remain_burst_time[k]--;
		current_time++;

		if (remain_burst_time[k] == 0)
			p[k].completed = TRUE;
	}

	//간트차트 마지막
	for (i = 0; i < len; i++)
	{
		remain_burst_time[i] = p[i].burst;
		p[i].completed = FALSE;
	}

	current_time = 0;
	printf("|\n");

	while (current_time < total_burst_time)
	{
		priority = INT_MAX;

		if (current_time <= p[len - 1].arrive_time)
		{
			for (i = 0; i < len; i++)
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
			for (i = 0; i < len; i++)
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

		if (pre_k != k)
			printf(" ");

		printf("--");

		remain_burst_time[k]--;
		current_time++;
		pre_k = k;

		if (remain_burst_time[k] == 0)
			p[k].completed = TRUE;
	}

	for (i = 0; i < len; i++)
	{
		remain_burst_time[i] = p[i].burst;
		p[i].completed = FALSE;
	}

	current_time = 0;
	num = 0;
	printf("\n");

	while (current_time <= total_burst_time)
	{
		if (total_burst_time != current_time)
		{
			priority = INT_MAX;

			if (current_time <= p[len - 1].arrive_time)
			{
				for (i = 0; i < len; i++)
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
				for (i = 0; i < len; i++)
				{
					if (p[i].completed == FALSE && priority > p[i].priority)
					{
						priority = p[i].priority;
						k = i;
					}
				}
			}


			if (pre_k != k)
			{
				for (i = 0; i < num && current_time != 0; i++)
					printf("  ");

				if (current_time != 0)
					printf(" ");

				printf("%-2d", current_time);
				num = 0;

				previous_time = current_time;

			}

			else
				num++;

			remain_burst_time[k]--;
			current_time++;
			pre_k = k;

			if (remain_burst_time[k] == 0)
				p[k].completed = TRUE;
		}

		else
		{
			for (i = 0; i < current_time - previous_time - 1; i++)
				printf("  ");
			printf(" ");

			printf("%-2d", current_time);

			break;
		}
	}
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

	for (i = 0; i < len; i++)
	{
		p[i].turnaround_time = p[i].return_time - p[i].arrive_time;
		total_waiting_time += p[i].waiting_time;
		total_turnaround_time += p[i].turnaround_time;
		total_response_time += p[i].response_time;
	}

	printf("Preemptive Priority Scheduling Algorithm\n\n");

	pps_print_gantt_chart(p, len);

	printf("\n\nAverage Waiting Time     : %-2.2lf\n", (double)total_waiting_time / (double)len);
	printf("Average Turnaround Time  : %-2.2lf\n", (double)total_turnaround_time / (double)len);
	printf("Average Response Time    : %-2.2lf\n\n", (double)total_response_time / (double)len);

	print_table(p, len);
}
#endif
