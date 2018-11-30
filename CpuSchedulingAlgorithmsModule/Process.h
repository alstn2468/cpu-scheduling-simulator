#ifndef __PROCESS__
#define __PROCESS__

// Process

/* 프로그램에서 사용할 헤더파일 선언 */
#include <stdio.h>
#include <stdlib.h>

/* 프로그램에서 사용할 기호상수 정의 */
#define ID_LEN 20
#define TRUE 1
#define FALSE 0

/* 프로세스 구조체 */
typedef struct _process
{
    char id[ID_LEN];       // 프로세스 ID 필드
    int arrive_time;       // 도착 시간 필드
    int waiting_time;      // 대기 시간 필드
    int return_time;       // 반환 시간 필드
    int turnaround_time;   // 턴어라운드 타임 필드
    int response_time;     // 등답 시간 필드
    int burst;             // 실행 시간 필드
    int priority;          // 우선순위 필드
    int completed;         // 완료 상태 필드
} Process; // Process 키워드로 사용 가능

typedef int Quantum; // 시간 할당량 Quantum 키워드 사용

/**
 * [process_init 프로세스 초기화 함수]
 * @param p   [프로세스 구조체 배열]
 * @param len [프로세스 갯수]
 */
void process_init(Process p[], int len)
{
    int i;

    /* 프로세스의 갯수만큼 반복 */
    for (i = 0; i < len; i++)
    {
        p[i].waiting_time = 0;   // 대기 시간 초기화
        p[i].return_time = 0;    // 반환 시간 초기화
        p[i].response_time = 0;  // 응답 시간 초기화
        p[i].completed = FALSE;  // 완료 상태 초기화
    }
}

#endif
