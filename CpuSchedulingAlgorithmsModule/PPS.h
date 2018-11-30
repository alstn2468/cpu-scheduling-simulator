#ifndef __PREEMPTIVE__PRIORITY__SCHEDULING__
#define __PREEMPTIVE__PRIORITY__SCHEDULING__

// Preemptive Priority Scheduling Algorithm

#include "./Process.h"
#include "./SortingFunction.h"
#include "./PrintTable.h"

void pps_calculate_time(Process *p, int len)
{
	int i;
	int priority;
	int current_time = 0;
	int total_burst_time = 0;
	int k = 0;

	int *remain_burst_time = (int *)malloc(sizeof(int) * len);
	int *count = (int *)malloc(sizeof(int) * len);

	for (i = 0; i < len; i++)
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
			for (i = 0; i < len; i++)
			{
				if ((p[i].completed == FALSE)
						&& (p[i].arrive_time <= current_time))
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

	free(remain_burst_time);
	free(count);
}

void pps_print_gantt_chart(Process *p, int len)
{
	int i;
	int total_burst_time = 0;
	int current_time = 0, previous_time = 0;
	int k, pre_k = 0;
	int priority, num;

	int *count = (int *)malloc(sizeof(int) * len);
	int *remain_burst_time = (int *)malloc(sizeof(int) * len);

	for (i = 0; i < len; i++)
	{
		remain_burst_time[i] = p[i].burst;
		total_burst_time += p[i].burst;
		p[i].completed = FALSE;
		count[i] = 0;
	}

	printf("\t ");

	while (current_time < total_burst_time)
	{
		priority = INT_MAX;

		if (current_time <= p[len - 1].arrive_time)
		{
			for (i = 0; i < len; i++)
			{
				if ((p[i].completed == FALSE)
						&& (p[i].arrive_time <= current_time))
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

	printf("\n\t|");
	current_time = 0;

	while (current_time < total_burst_time)
	{
		priority = INT_MAX;

		if (current_time <= p[len - 1].arrive_time)
		{
			for (i = 0; i < len; i++)
			{
				if ((p[i].completed == FALSE)
						&& (p[i].arrive_time <= current_time))
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
				num = count[pre_k] + 1;
				count[pre_k] = 0;
				count[k]++;

				for (i= 0; i < num; i++)
					printf("\b");

				printf("%2s", p[pre_k].id);

				for (i = 0; i < num - 2; i++)
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

					for (i = 0; i < num; i++)
						printf("\b");

					printf("%2s", p[pre_k].id);

					for (i = 0; i < num - 2; i++)
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

	for (i = 0; i < len; i++)
	{
		remain_burst_time[i] = p[i].burst;
		p[i].completed = FALSE;
	}

	printf("|\n\t");
	current_time = 0;

	while (current_time < total_burst_time)
	{
		priority = INT_MAX;

		if (current_time <= p[len - 1].arrive_time)
		{
			for (i = 0; i < len; i++)
			{
				if ((p[i].completed == FALSE)
						&& (p[i].arrive_time <= current_time))
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
	printf("\n\t");

	while (current_time <= total_burst_time)
	{
		if (total_burst_time != current_time)
		{
			priority = INT_MAX;

			if (current_time <= p[len - 1].arrive_time)
			{
				for (i = 0; i < len; i++)
				{
					if ((p[i].completed == FALSE)
							&& (p[i].arrive_time <= current_time))
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
					if ((p[i].completed == FALSE)
							&& (priority > p[i].priority))
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

	printf("\n");

	free(count);
	free(remain_burst_time);
}

void PPS(Process *p, int len)
{
	int i;
	int total_waiting_time = 0;
	int total_turnaround_time = 0;
	int total_return_time = 0;
	int total_response_time = 0;

	process_init(p, len);

	merge_sort_by_arrive_time(p, 0, len);

	pps_calculate_time(p, len);

	for (i = 0; i < len; i++)
	{
		p[i].turnaround_time = p[i].return_time - p[i].arrive_time;
		total_waiting_time += p[i].waiting_time;
		total_turnaround_time += p[i].turnaround_time;
		total_response_time += p[i].response_time;
	}

	printf("\tPreemptive Priority Scheduling Algorithm\n\n");

	pps_print_gantt_chart(p, len);

	printf("\n\tAverage Waiting Time     : %-2.2lf\n", (double)total_waiting_time / (double)len);
	printf("\tAverage Turnaround Time  : %-2.2lf\n", (double)total_turnaround_time / (double)len);
	printf("\tAverage Response Time    : %-2.2lf\n\n", (double)total_response_time / (double)len);

	print_table(p, len);
}

#endif
