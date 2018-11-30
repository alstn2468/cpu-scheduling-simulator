#ifndef __PRINT__TABLE__
#define __PRINT__TABLE__

// Print Table

/* 사용자 정의 헤더 선언 */
#include "./Process.h"

/**
 * [print_table 프로세스 데이터 테이블 출력 함수]
 * @param p [프로세스 구조체 배열]
 * @param n [프로세스 갯수]
 */
void print_table(Process p[], int n)
{
	int i;
	// 반복문에서 사용할 변수 선언

	puts("\t+-----+------------+-------------+----------+-------------+-----------------+--------------+-----------------+");
	puts("\t| PID | Burst Time | Arrive Time | Priority | Return Time |  Response Time  | Waiting Time | Turnaround Time |");
	puts("\t+-----+------------+-------------+----------+-------------+-----------------+--------------+-----------------+");

	/* 프로세스 갯수만큼 반복하며 포맷을 맞추어 출력 */
	for (i = 0; i < n; i++)
	{
		printf("\t| %3s |     %3d    |     %3d     |    %3d   |     %3d     |      %3d        |      %3d     |        %3d      |\n",
			p[i].id, p[i].burst, p[i].arrive_time, p[i].priority, p[i].return_time, p[i].response_time, p[i].waiting_time, p[i].turnaround_time);

		puts("\t+-----+------------+-------------+----------+-------------+-----------------+--------------+-----------------+");
	}

	puts("\n");
}

#endif
