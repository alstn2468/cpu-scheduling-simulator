#ifndef __NON__PREEMPTIVE__PRIORITY__SCHEDULING__
#define __NON__PREEMPTIVE__PRIORITY__SCHEDULING__

// Non-preemptive Priority Scheduling Algorithm

/* 사용자 정의 헤더 선언 */
#include "./Process.h"
#include "./SortingFunction.h"
#include "./PrintTable.h"

/**
 * [npps_calculate NPPS 알고리즘 시간 계산 함수]
 * @param p   [프로세스 구조체 배열]
 * @param len [프로세스 갯수]
 */
void npps_calculate(Process *p, int len)
{
	int i, j;
	// 반복문에서 사용할 변수 선언
	int check;
	// 모든 프로세스가 완료되었는지 확인할 변수 선언
	int min;
	// 우선순위가 가장 높은 인덱스를 저장할 변수 선언
	int time = 0;
	// 현재 시간을 저장할 변수 선언 및 초기화

	/* 가장 먼저 들어온 프로세스 실행 및 시간 계산 */
	p[0].return_time = p[0].burst;
	p[0].turnaround_time = p[0].return_time - p[0].arrive_time;
	p[0].response_time = 0;
	p[0].completed = TRUE;

	time = p[0].burst;
	// 실행된 프로세스 시간만큼 현재 시간 증가

	/* 모든 프로세스가 완료될때 까지 반복 */
	while (TRUE)
	{
		min = INT_MAX;
		// 최솟값을 저장할 변수 초기화
		check = FALSE;
		// 모든 프로세스 완료 확인 변수 초기화

		/* 프로세스의 갯수 -1 만큼 반복 */
		for (i = 1; i < len; i++)
		{
			/* 현재 우선순위 보다 작은 우선순위를 갖으며
			   아직 실행되지 않았고 이미 도착한 프로세스인 경우 */
			if ((p[min].priority > p[i].priority)
				&& (p[i].completed == FALSE)
					&& (p[i].arrive_time <= time))
			{
				min = i;
				// 최소 우선순위 프로세스 인덱스 갱신
				check = TRUE;
				// 실행할 프로세스가 남았음을 표시
			}
		}

		/* 모든 프로세스가 완료되었을 경우 */
		if (check == FALSE)
			break;
			// 반복문 탈출

		/* 선택된 프로세스 시간 계산 */
		p[min].response_time = time - p[min].arrive_time;
		p[min].return_time = time + p[min].burst;
		p[min].turnaround_time = p[min].return_time - p[min].arrive_time;
		p[min].waiting_time = time - p[min].arrive_time;
		p[min].completed = TRUE;

		time += p[min].burst;
		// 실행된 프로세스 시간 만큼 현재 시간 증가
	}
}

/**
 * [npps_print_gantt_chart 간트 차트 출력 함수]
 * @param p   [프로세스 구조체 배열]
 * @param len [프로세스 갯수]
 */
void npps_print_gantt_chart(Process *p, int len)
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
 * [NPPS NPPS 알고리즘 실행 함수]
 * @param p   [프로세스 구조체 배열]
 * @param len [프로세스 갯수]
 */
void NPPS(Process *p, int len)
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

	npps_calculate(p, len);
	// npps_calculate 함수 호출로 시간 계산

	/* 프로세스의 갯수 만큼 반복 */
	for (i = 0; i < len; i++)
	{
		total_waiting_time += p[i].waiting_time;
		// 총 대기 시간 증가
		total_turnaround_time += p[i].turnaround_time;
		// 총 턴어라운드 타임 증가
		total_response_time += p[i].response_time;
		// 총 응답 시간 증가
	}

	quick_sort_by_return_time(p, len);
	// quick_sort_by_return_time 함수 호출로 반환 시간으로 정렬

	printf("\tNon-preemptive Priority Scheduling Algorithm\n\n");

	npps_print_gantt_chart(p, len);
	// npps_print_gantt_chart 함수 호출로 간트 차트 출력

	/* 평균 대기시간, 턴어라운드 타임, 응답 시간 출력 */
	printf("\n\tAverage Waiting Time     : %-2.2lf\n", (double)total_waiting_time / (double)len);
	printf("\tAverage Turnaround Time  : %-2.2lf\n", (double)total_turnaround_time / (double)len);
	printf("\tAverage Response Time    : %-2.2lf\n\n", (double)total_response_time / (double)len);

	print_table(p, len);
	// print_table 함수 호출로 데이터 표 출력
}

#endif
