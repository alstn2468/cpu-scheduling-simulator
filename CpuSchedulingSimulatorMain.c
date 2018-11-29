#include "CpuSchedulingAlgorithms.h"

int main()
{
	int process_count = 0;
	int i = 0;

	Quantum quantum;
	Process *process;

	FILE *fp = fopen("process.txt", "r");

	if (fp == NULL)
	{
		printf("FILE OPEN ERROR!\n");
		return 0;
	}

	fscanf(fp, " %d", &process_count);

	process = (Process *)malloc(sizeof(Process) * process_count);

	while (i < process_count)
	{
		fscanf(fp, "%s %d %d %d",
			process[i].id, &process[i].arrive_time, &process[i].burst, &process[i].priority);
		i++;
	}

	fscanf(fp, " %d", &quantum);

	puts("┏                                                                                                                       ┓");
	FCFS(process, process_count);
	puts("┗                                                                                                                       ┛\n\n");

	puts("┏                                                                                                                       ┓");
	SJF(process, process_count);
	puts("┗                                                                                                                       ┛\n\n");

	puts("┏                                                                                                                       ┓");
	RR(process, process_count, quantum);
	puts("┗                                                                                                                       ┛\n\n");

	puts("┏                                                                                                                       ┓");
	HRN(process, process_count);
	puts("┗                                                                                                                       ┛\n\n");

	puts("┏                                                                                                                       ┓");
	NPPS(process, process_count);
	puts("┗                                                                                                                       ┛\n\n");

	puts("┏                                                                                                                       ┓");
	PPS(process, process_count);
	puts("┗                                                                                                                       ┛\n\n");

	puts("┏                                                                                                                       ┓");
	SRT(process, process_count);
	puts("┗                                                                                                                       ┛\n\n");

	fclose(fp);
	free(process);

	system("pause");

    return 0;
}
