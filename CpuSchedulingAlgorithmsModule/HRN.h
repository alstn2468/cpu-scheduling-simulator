#ifndef __HIGHEST__RESPONSE__RATIO__NEXT__
#define __HIGHEST__RESPONSE__RATIO__NEXT__

// HRN Algorithm

/* 사용자 정의 헤더 선언 */
#include "./Process.h"
#include "./SortingFunction.h"
#include "./PrintTable.h"

/**
 * [hrn_print_gantt_chart 간트 차트 출력 함수]
 * @param p   [프로세스 구조체 배열]
 * @param len [프로세스 갯수]
 */
void hrn_print_gantt_chart(Process *p, int len)
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
 * [HRN HRN 알고리즘 실행 함수]
 * @param p   [프로세스 구조체 배열]
 * @param len [프로세스 갯수]
 */
void HRN(Process *p, int len)
{
	int i, j;
	// 반복문에서 사용할 변수 선언
	int time, loc;
	// 현재 시간과 프로세스 위치를 저장할 변수 선언
	int total_burst_time = 0;
	// 총 실행 시간을 저장할 변수 선언 및 초기화
	int total_waiting_time = 0;
	// 총 대기 시간을 저장할 변수 선언 및 초기화
	int total_turnaround_time = 0;
	// 총 턴어라운드 타임을 저장할 변수 선언 및 초기화
	int total_response_time = 0;
	// 총 응답 시간을 저장할 변수 선언 및 초기화

	float hrr, temp;
	// hrr 알고리즘의 우선 순위를 저장할 변수 선언

	process_init(p, len);
	// process_init 함수 호출로 프로세스 초기화

	/* 프로세스의 갯수만큼 반복 */
	for (i = 0; i < len; i++)
	{
		total_burst_time += p[i].burst;
		// 총 실행 시간을 계산
	}

	merge_sort_by_arrive_time(p, 0, len);
	// merge_sort_by_arrive_time 함수 호출로 도착 시간을 기준으로 정렬

	/* 현재 시간이 총 실행 시간이 같아질 때까지 반복 */
	for (time = p[0].arrive_time; time < total_burst_time;)
	{
		hrr = -9999;
		// 우선순위를 -9999으로 초기화

		/* 프로세스의 갯수만큼 반복 */
		for (i = 0; i < len; i++)
		{
			/* 이미 도착한 프로세스이면서 완료되지 않은 프로세스인 경우 */
			if ((p[i].arrive_time <= time)
					&& (p[i].completed != TRUE))
			{
				temp = (p[i].burst + (time - p[i].arrive_time)) / p[i].burst;
				// (실행시간 + 대기시간) / 실행시간 으로 우선순위 계산

				/* 우선순위가 더 클 경우 */
				if (hrr < temp)
				{
					hrr = temp;
					// 우선순위 값 갱신
					loc = i;
					// 인덱스 갱신
				}
			}
		}

		time += p[loc].burst;
		// 실행한 프로세스 시간 만큼 현재 시간 증가

		/* 실행 한 프로세스 시간 정보 계산 */
		p[loc].waiting_time = time - p[loc].arrive_time - p[loc].burst;
		p[loc].turnaround_time = time - p[loc].arrive_time;
		p[loc].return_time = p[loc].turnaround_time + p[loc].arrive_time;
		p[loc].response_time = p[loc].waiting_time;
		p[loc].completed = TRUE;

		total_waiting_time += p[loc].waiting_time;
		// 총 대기 시간 증가
		total_turnaround_time += p[loc].turnaround_time;
		// 총 턴어라운드 타임 증가
		total_response_time += p[loc].response_time;
		// 총 응답 시간 증가
	}

	quick_sort_by_return_time(p, len);
	// quick_sort_by_return_time 함수 호출로 반환 시간으로 정렬

	printf("\tHighest Response Ratio Next Scheduling Algorithm\n\n");

	hrn_print_gantt_chart(p, len);
	// hrn_print_gantt_chart 함수 호출로 간트 차트 출력

	/* 평균 대기시간, 턴어라운드 타임, 응답 시간 출력 */
	printf("\n\tAverage Waiting Time     : %-2.2lf\n", (double)total_waiting_time / (double)len);
	printf("\tAverage Turnaround Time  : %-2.2lf\n", (double)total_turnaround_time / (double)len);
	printf("\tAverage Response Time    : %-2.2lf\n\n", (double)total_response_time / (double)len);

	print_table(p, len);
	// print_table 함수 호출로 데이터 표 출력
}

#endif
