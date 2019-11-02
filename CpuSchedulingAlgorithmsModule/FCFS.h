#ifndef __FIRST__COME__FIRST__SERVED__
#define __FIRST__COME__FIRST__SERVED__

// FCFS Algorithm

/* 사용자 정의 헤더 선언 */
#include "./Process.h"
#include "./SortingFunction.h"
#include "./PrintTable.h"

/**
 * [fcfs_print_gantt_chart 간트 차트 출력 함수]
 * @param p   [프로세스 구조체 배열]
 * @param len [프로세스 갯수]
 */
void fcfs_print_gantt_chart(Process *p, int len)
{
	int i, j;
	// 반복문에서 사용할 변수 선언

	printf("\t ");

	/* 상단 바 출력 */
	for (i = 0; i < len; i++)
	{
		for (j = 0; j < p[i].burst; j++)
			printf("--");

		printf(" ");
	}

	printf("\n\t|");

	/* 프로세스 이름 출력 */
	for (i = 0; i < len; i++)
	{
		for (j = 0; j < p[i].burst - 1; j++)
			printf(" ");

		printf("%s", p[i].id);

		for (j = 0; j < p[i].burst - 1; j++)
			printf(" ");

		printf("|");
	}

	printf("\n\t ");

	/* 하단 바 출력 */
	for (i = 0; i < len; i++)
	{
		for (j = 0; j < p[i].burst; j++)
			printf("--");

		printf(" ");
	}

	printf("\n\t");

	/* 프로세스 시간 출력 */
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

/**
 * [FCFS FCFS 알고리즘 실행 함수]
 * @param p   [프로세스 구조체 배열]
 * @param len [프로세스 갯수]
 */
void FCFS(Process *p, int len)
{
	int i;
	// 반복문에서 사용할 변수 선언
	int total_waiting_time = 0;
	// 총 대기 시간을 저장할 변수 선언 및 초기화
	int total_turnaround_time = 0;
	// 총 턴어라운드 타임을 저장할 변수 선언 및 초기화
	int total_response_time = 0;
	// 총 응답 시간을 저장할 변수 선언 및 초기화
	int total_return_time = 0;
	// 총 반환 시간을 저장할 변수 선언 및 초기화

	process_init(p, len);
	// process_init 함수 호출로 프로세스 초기화

	merge_sort_by_arrive_time(p, 0, len);
	// merge_sort_by_arrive_time 함수 호출로 도착 시간을 기준으로 정렬

	/* 맨 처음 들어온 프로세스 실행 */
	p[0].return_time = p[0].burst;
	p[0].turnaround_time = p[0].return_time - p[0].arrive_time;
	p[0].response_time = 0;
	p[0].waiting_time = 0;

	/* 실행된 프로세스만큼 합 증가 */
	total_response_time += p[0].response_time;
	total_waiting_time += p[0].waiting_time;
	total_turnaround_time += p[0].turnaround_time;
	total_return_time += p[0].burst;

	/* 다음 프로레스 부터 순차적으로 계산 */
	for (i = 1; i < len; i++)
	{
		/* 각 프로세스 맴버 계산 */
		p[i].waiting_time = total_return_time - p[i].arrive_time;
		p[i].return_time = total_return_time + p[i].burst;
		p[i].turnaround_time = p[i].return_time - p[i].arrive_time;
		p[i].response_time = p[i].waiting_time;

		/* 실행된 프로세스만큼 증가 */
		total_return_time += p[i].burst;
		total_waiting_time += p[i].waiting_time;
		total_turnaround_time += p[i].turnaround_time;
		total_response_time += p[i].response_time;
	}

	printf("\n\tFCFS Scheduling Algorithm\n\n");

	fcfs_print_gantt_chart(p, len);
	// fcfs_print_gantt_chart 함수 호출로 간트 차트 출력

	/* 평균 대기시간, 턴어라운드 타임, 응답 시간 출력 */
	printf("\n\tAverage Waiting Time     : %-2.2lf\n", (double)total_waiting_time / (double)len);
	printf("\tAverage Turnaround Time  : %-2.2lf\n", (double)total_turnaround_time / (double)len);
	printf("\tAverage Response Time    : %-2.2lf\n\n", (double)total_response_time / (double)len);

	print_table(p, len);
	// print_table 함수 호출로 데이터 표 출력
}

#endif
