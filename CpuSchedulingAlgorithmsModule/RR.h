#ifndef __Round__ROBIN__
#define __Round__ROBIN__

// Round Robin Scheduling

/* 사용자 정의 헤더 선언 */
#include "./Process.h"
#include "./SortingFunction.h"
#include "./PrintTable.h"

/**
 * [rr_calculate_waiting_time RR 알고리즘 대기 시간 계산 함수]
 * @param p   [description]
 * @param len [description]
 * @param q   [description]
 */
void rr_calculate_waiting_time(Process *p, int len, Quantum q)
{
	int i;
	// 반복문에서 사용할 변수 선언
	int curr_time = 0;
	// 현재 시간을 저장할 변수 선언 및 초기화

	/* 각 프로세스 별 남은 실행 시간을 저장할 배열 동적 할당 */
	int *remain_burst_time = (int *)malloc(sizeof(int) * len);
	/* 응답 시간을 확인하는데 사용할 배열 동적 할당 */
	int *calc_response_time = (int *)malloc(sizeof(int) * len);

	/* 프로세스의 갯수만큼 반복 */
	for (i = 0; i < len; i++)
	{
		remain_burst_time[i] = p[i].burst;
		// 남은 실행 시간 저장 배열 초기화
		calc_response_time[i] = FALSE;
		// 응답시간 계산 확인 배열 초기화
	}

	/* 모든 프로세스가 완료될때 까지 반복 */
	while (TRUE)
	{
		int check = TRUE;
		// check 변수 초기화

		/* 프로세스의 갯수만큼 반복 */
		for (i = 0; i < len; i++)
		{
			/* 실행시간이 남아있을 경우 */
			if (remain_burst_time[i] > 0)
			{
				check = FALSE;
				// check 변수 FALSE 처리

				/* 아직 응답 시간이 계산되지 않았을 경우 */
				if (calc_response_time[i] == FALSE)
				{
					p[i].response_time = curr_time - p[i].arrive_time;
					// 응답 시간 계산 후 저장
					calc_response_time[i] = TRUE;
					// 응답 시간 계산 처리
				}

				/* 남은 시간이 시간 할당량보다 클 경우 */
				if (remain_burst_time[i] > q)
				{
					curr_time += q;
					// 현재 시간 시간 할당량만큼 증가
					remain_burst_time[i] -= q;
					// 현재 실행 중 프로세스의 남은 시간 감소
				}

				/* 남은 시간이 시간 할당량보다 작을 경우 */
				else
				{
					curr_time += remain_burst_time[i];
					// 현재 시간 남은 시간만큼 증가
					p[i].waiting_time = curr_time - p[i].burst;
					// 대기 시간 계산
					remain_burst_time[i] = 0;
					// 남은 시간을 0으로 바꾸어줌
				}
			}
		}

		/* 모든 프로세스가 완료되었을 경우 */
		if (check == TRUE)
			break;
			// 무한 루프 탈출
	}

	free(remain_burst_time);
	// 동적 할당한 배열 메모리 할당 해제
}

/**
 * [rr_calculate_turnaround_time 턴어라운드 타임 계산 함수]
 * @param p   [프로세스 구조체 배열]
 * @param len [프로세스 갯수]
 */
void rr_calculate_turnaround_time(Process *p, int len)
{
	int i;
	// 반복문에서 사용할 변수 선언

	/* 프로세스의 갯수만큼 반복 */
	for (i = 0; i < len; i++)
		p[i].turnaround_time = p[i].burst + p[i].waiting_time - p[i].arrive_time;
		// 턴어라운드 타임 계산 후 저장
}

/**
 * [rr_print_gantt_chart 라운드 로빈 간트 차트 출력 함수]
 * @param p   [프로세스 구조체 배열]
 * @param len [프로세스 갯수]
 * @param q   [시간 할당량]
 */
void rr_print_gantt_chart(Process *p, int len, Quantum q)
{
	int i, j;
	// 반복문에서 사용할 변수 선언
	int curr_time = 0, total_burst_time = 0;
	// 현재 시간과 총 실행 시간을 저장할 변수 선언 및 초기화
	int temp_total_burst_time = 0;
	// 임시로 값을 저장할 변수 선언 및 초기화

	/* 각 프로세스 별 남은 실행 시간을 저장할 배열 동적 할당 */
	int *remain_burst_time = (int *)malloc(sizeof(int) * len);

	/* 프로세스의 갯수만큼 반복 */
	for (i = 0; i < len; i++)
	{
		remain_burst_time[i] = p[i].burst;
		// 남은 시간 저장 배열  초기화
		total_burst_time += p[i].burst;
		// 총 실행 시간 계산
	}

	printf("\t");

	/* 대기 시간 계산 알고리즘과 동일 상단 바 출력 */
	while (TRUE)
	{
		int check = TRUE;

		for (i = 0; i < len; i++)
		{
			if (remain_burst_time[i] > 0)
			{
				check = FALSE;

				if (remain_burst_time[i] < q)
				{
					printf(" ");
					for (j = 0; j < remain_burst_time[i]; j++)
						printf("--");
				}

				else
				{
					printf(" ");
					for (j = 0; j <= q; j++)
						printf("--");
				}

				if (remain_burst_time[i] > q)
				{
					curr_time += q;
					remain_burst_time[i] -= q;
				}

				else
				{
					curr_time += remain_burst_time[i];
					p[i].waiting_time = curr_time - p[i].burst;
					remain_burst_time[i] = 0;
				}


			}
		}

		if (check == TRUE)
			break;
	}

	printf(" \n\t");

	for (i = 0; i < len; i++)
	{
		remain_burst_time[i] = p[i].burst;
	}

	/* 프로세스 아이디 출력 */
	while (TRUE)
	{
		int check = TRUE;

		for (i = 0; i < len; i++)
		{
			if (remain_burst_time[i] > 0)
			{
				check = FALSE;

				if (remain_burst_time[i] < q)
				{
					printf("|");

					if (remain_burst_time[i] != 1)
					{
						for (j = 0; j <= remain_burst_time[i] / 2; j++)
							printf(" ");

						printf("%2s", p[i].id);

						for (j = 0; j <= remain_burst_time[i] / 2; j++)
							printf(" ");
					}

					else
						printf("%2s", p[i].id);
				}

				else
				{
					printf("|");

					for (j = 0; j < q; j++)
						printf(" ");

					printf("%2s", p[i].id);

					for (j = 0; j < q; j++)
						printf(" ");
				}

				if (remain_burst_time[i] > q)
				{
					curr_time += q;
					remain_burst_time[i] -= q;
				}

				else
				{
					curr_time += remain_burst_time[i];
					p[i].waiting_time = curr_time - p[i].burst;
					remain_burst_time[i] = 0;
				}


			}
		}

		if (check == TRUE)
			break;
	}

	printf("|\n\t");

	for (i = 0; i < len; i++)
	{
		remain_burst_time[i] = p[i].burst;
	}

	/* 하단 바 출력 */
	while (TRUE)
	{
		int check = TRUE;

		for (i = 0; i < len; i++)
		{
			if (remain_burst_time[i] > 0)
			{
				check = FALSE;

				if (remain_burst_time[i] < q)
				{
					printf(" ");
					for (j = 0; j < remain_burst_time[i]; j++)
						printf("--");
				}

				else
				{
					printf(" ");
					for (j = 0; j <= q; j++)
						printf("--");
				}

				if (remain_burst_time[i] > q)
				{
					curr_time += q;
					remain_burst_time[i] -= q;
				}

				else
				{
					curr_time += remain_burst_time[i];
					p[i].waiting_time = curr_time - p[i].burst;
					remain_burst_time[i] = 0;
				}


			}
		}

		if (check == TRUE)
			break;
	}

	printf("\n\t");

	for (i = 0; i < len; i++)
		remain_burst_time[i] = p[i].burst;

	curr_time = 0;

	/* 프로세스 시간 출력 */
	while (TRUE)
	{
		int check = TRUE;

		for (i = 0; i < len; i++)
		{
			if (remain_burst_time[i] > 0)
			{
				check = FALSE;

				if (remain_burst_time[i] < q)
				{
					printf("%-2d", curr_time);

					for (j = 0; j < remain_burst_time[i] - 1; j++)
						printf("  ");

					printf(" ");
				}

				else
				{
					printf("%-2d", curr_time);

					for (j = 0; j < q; j++)
						printf("  ");

					printf(" ");
				}

				if (remain_burst_time[i] > q)
				{
					curr_time += q;
					remain_burst_time[i] -= q;
				}

				else
				{
					curr_time += remain_burst_time[i];
					p[i].waiting_time = curr_time - p[i].burst;
					remain_burst_time[i] = 0;
				}
			}
		}

		if (check == TRUE)
			break;
	}

	printf("%-3d\n", total_burst_time);

	printf("\n");

	free(remain_burst_time);
	// 동적 할당한 배열의 메모리 할당 해제
}

/**
 * [RR RR 알고리즘 실행 함수]
 * @param p       [프로세스 구조체 배열]
 * @param len     [프로세스 갯수]
 * @param quantum [시간 할당량]
 */
void RR(Process *p, int len, Quantum quantum)
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

	rr_calculate_waiting_time(p, len, quantum);
	// rr_calculate_waiting_time 함수 호출로 대기 시간, 응답 시간 계산

	rr_calculate_turnaround_time(p, len);
	// rr_calculate_turnaround_time 함수 호출로 턴어라운드 타임 계산

	/* 프로세스의 갯수만큼 반복 */
	for (i = 0; i < len; i++)
	{
		p[i].waiting_time = p[i].turnaround_time - p[i].burst;
		// 대기 시간 계산 후 저장
		p[i].return_time = p[i].arrive_time + p[i].burst + p[i].waiting_time;
		// 반환 시간 계산 후 저장

		total_waiting_time += p[i].waiting_time;
		// 총 대기 시간 증가
		total_turnaround_time += p[i].turnaround_time;
		// 총 턴어라운드 타임 증가
		total_response_time += p[i].response_time;
		// 총 응답 시간 증가
	}

	printf("\tRound Robin Scheduling Algorithm ( Quantum : %d )\n\n", quantum);

	rr_print_gantt_chart(p, len, quantum);
	// rr_print_gantt_chart 함수 호출로 간트 차트 출력

	/* 평균 대기시간, 턴어라운드 타임, 응답 시간 출력 */
	printf("\n\tAverage Waiting Time     : %-2.2lf\n", (double)total_waiting_time / (double)len);
	printf("\tAverage Turnaround Time  : %-2.2lf\n", (double)total_turnaround_time / (double)len);
	printf("\tAverage Response Time    : %-2.2lf\n\n", (double)total_response_time / (double)len);

	print_table(p, len);
	// print_table 함수 호출로 데이터 표 출력
}

#endif
