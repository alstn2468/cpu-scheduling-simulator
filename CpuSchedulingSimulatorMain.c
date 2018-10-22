#include <stdio.h>
#include <stdlib.h>

#include "CpuSchedulingAlgorithms.h"
#include "PrintGanttChart.h"

int main()
{
	int process_count = 0;
	int i = 0;

	Quantum quantum;
	Process *process;

	FILE *fp = fopen("data.txt", "r");

	if (fp == NULL)
	{
		printf("FILE OPEN ERROR!\n");
		return 0;
	}

	fscanf(fp, "%d", &process_count);

	process = (Process *)malloc(sizeof(Process) * process_count);

	while (!feof(fp) || i < process_count)
	{
		fscanf(fp, "%s %d %d %d", 
			process[i].id, &process[i].arriveTime, &process[i].burst, &process[i].priority);
	}

	fscanf(fp, " %d", &quantum);

	fclose(fp);
	free(process);

    return 0;
}
