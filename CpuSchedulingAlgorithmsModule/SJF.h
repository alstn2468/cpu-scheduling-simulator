#ifndef __SHORTEST__JOB__FIRST__
#define __SHORTEST__JOB__FIRST__

// Shortest Job First Algorithmd

/* 사용자 정의 헤더 선언 */
#include "./Process.h"
#include "./SortingFunction.h"
#include "./PrintTable.h"

/**
 * [sjf_calculate_time SJF 알고리즘 시간 계산 함수]
 * @param p   [프로세스 구조체 배열]
 * @param len [프로세스 갯수]
 */
void sjf_calculate_time(Process *p, int len)
{
	int i, j;
	// 반복문에서 사용할 변수 선언
	int curr_time = 0;
	// 현재 시간을 저장할 변수 선언 및 초기화
	int min = 0;
	// 최소 시간을 갖는 인덱스를 저장할 변수 선언 및 초기화

	/* 맨 처음에 실행되는 프로세스 시간 계산 */
	p[0].completed = TRUE;
	p[0].return_time = p[0].burst;
	p[0].turnaround_time = p[0].burst - p[0].arrive_time;
	p[0].waiting_time = 0;
	curr_time = p[0].burst;
	// 현재 시간 완료된 프로세스 시간 만큼 증가

	/* 프로세스의 갯수 -1 만큼 반복 */
	for(i = 1; i < len; i++)
	{
		/* 프로세스의 갯수 -1 만큼 반복 */
		for (j = 1; j < len; j++)
		{
			/* 이미 완료된 프로세스일 경우 */
			if (p[j].completed == TRUE)
				continue;
				// 다음 루프로 이동

			/* 아직 완료되지 않은 프로세스일 경우 */
			else
			{
				min = j;
				// min 변수 초기화
				break;
				// 반복문 탈출
			}
		}

		/* 프로세스의 갯수 -1 만큼 반복 */
		for (j = 1; j < len; j++)
		{
			/* 최소 작업 시간을 갖는 조건에 맞는 프로세스 탐색 */
			if ((p[j].completed == FALSE)
					&& (p[j].arrive_time <= curr_time)
						&& (p[j].burst < p[min].burst))
			{
				min = j;
				// 최소 작업 프로세스 갱신
			}
		}

		p[min].waiting_time = curr_time - p[min].arrive_time;
		// 실행할 프로세스 대기 시간 계산
		p[min].completed = TRUE;
		// 실행 프로세스 완료 상태 변경

		curr_time += p[min].burst;
		// 현재 시간 프로세스의 실행 시간만큼 증가

		p[min].return_time = curr_time;
		// 프로세스 반환 시간 계산
		p[min].turnaround_time = p[min].return_time - p[min].arrive_time;
		// 프로세스 턴어라운드 타임 계산
	}
}

/**
 * [sjf_print_gantt_chart 간트 차트 출력 함수]
 * @param p   [프로세스 구조체 배열]
 * @param len [프로세스 갯수]
 */
void sjf_print_gantt_chart(Process *p, int len)
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

	/* 프로세스 ID 출력 */
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

	printf("0");

	/* 프로세스 실행 시간 출력 */
	for (i = 0; i < len; i++)
	{
		for (j = 0; j < p[i].burst; j++)
			printf("  ");

		if (p[i].turnaround_time > 9)
			printf("\b");

		printf("%d", p[i].return_time);
	}

	printf("\n");
}

/**
 * [SJF SJF 알고리즘 실행 함수]
 * @param p   [프로세스 구조체 배열]
 * @param len [프로세스 갯수]
 */
void SJF(Process *p, int len)
{
	int i;
	// 반복문에서 사용할 변수 선언
	int total_waiting_time = 0;
	// 총 대기 시간을 저장할 변수 선언 및 초기화
	int total_turnaround_time = 0;
	// 총 턴어라운드 타임을 저장할 변수 선언 및 초기화
	int total_response_time = 0;
	// 총 응답 시간을 저장할 변수 선언 및 초기화

	process_init(p, len);
	// process_init 함수 호출로 프로세스 초기화

	merge_sort_by_arrive_time(p, 0, len);
	// merge_sort_by_arrive_time 함수 호출로 도착 시간을 기준으로 정렬

	sjf_calculate_time(p, len);
	// sjf_calculate_time 함수 호출로 프로세스 시간 계산

	/* 프로세스의 갯수 만큼 반복 */
	for (i = 0; i < len; i++)
	{
		p[i].return_time = p[i].turnaround_time + p[i].arrive_time;
		// 프로세스의 반환 시간 계산 후 저장
		p[i].response_time = p[i].waiting_time;
		// 프로세스의 응답 시간 저장

		total_waiting_time += p[i].waiting_time;
		// 총 대기 시간 증가
		total_turnaround_time += p[i].turnaround_time;
		// 총 턴어라운드 타임 증가
		total_response_time += p[i].response_time;
		// 총 응답 시간 증가
	}

	printf("\tSJF Scheduling Algorithms\n\n");

	quick_sort_by_return_time(p, len);
	// quick_sort_by_return_time 함수 호출로 반환 시간으로 정렬

	sjf_print_gantt_chart(p, len);
	// sjf_print_gantt_chart 함수 호출로 간트 차트 출력

	/* 평균 대기시간, 턴어라운드 타임, 응답 시간 출력 */
	printf("\n\tAverage Waiting Time     : %-2.2lf\n", (double)total_waiting_time / (double)len);
	printf("\tAverage Turnaround Time  : %-2.2lf\n", (double)total_turnaround_time / (double)len);
	printf("\tAverage Response Time    : %-2.2lf\n\n", (double)total_response_time / (double)len);

	print_table(p, len);
	// print_table 함수 호출로 데이터 표 출력
}

#endif
