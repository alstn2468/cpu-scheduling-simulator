#ifndef __PRINT__TABLE__
#define __PRINT__TABLE__

// Print Table

#include "./Process.h"

void print_table(Process p[], int n)
{
	int i;

	puts("\t+-----+------------+-------------+----------+-------------+-----------------+--------------+-----------------+");
	puts("\t| PID | Burst Time | Arrive Time | Priority | Return Time |  Response Time  | Waiting Time | Turnaround Time |");
	puts("\t+-----+------------+-------------+----------+-------------+-----------------+--------------+-----------------+");

	for (i = 0; i < n; i++) {
		printf("\t| %3s |     %3d    |     %3d     |    %3d   |     %3d     |      %3d        |      %3d     |        %3d      |\n",
			p[i].id, p[i].burst, p[i].arrive_time, p[i].priority, p[i].return_time, p[i].response_time, p[i].waiting_time, p[i].turnaround_time);

		puts("\t+-----+------------+-------------+----------+-------------+-----------------+--------------+-----------------+");
	}

	puts("\n\n");
}

#endif
