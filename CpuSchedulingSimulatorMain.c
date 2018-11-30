/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Operating System Term Project                         *
 * CPU Scheduling Algorithm                              *
 *                                                       *
 * @author 김민수                                        *
 * @author 김혜린                                        *
 * @author 배서형                                        *
 *                                                       *
 * [Repository]                                          *
 * https://github.com/alstn2468/CPU_Scheduling_Simulator *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* 사용자 정의 헤더파일 선언 */
#include "CpuSchedulingAlgorithms.h"

int main()
{
    int process_count = 0;
    // 프로세스 갯수를 저장할 변수 선언 및 초기화
    int i = 0;
    // 반복문에서 사용할 변수 선언 및 초기화

    Quantum quantum;
    // 시간 할당량을 저장할 변수 선언
    Process *process;
    // 프로세스 구조체 배열을 동적 할당할 포인터 변수 선언

    /* 파일포인터 fp선언 및 process.txt를 읽기모드로 연다. */
    FILE *fp = fopen("process.txt", "r");

    /* 파일을 여는데 실패했을 경우 */
    if (fp == NULL)
    {
        printf("FILE OPEN ERROR!\n");
        return 0; // 예외 출력 후 메인 함수 종료
    }

    fscanf(fp, " %d", &process_count);
    // 파일에서 정수형 데이터를 읽어와 process_count에 저장

    /* process_count 갯수만큼 프로세스 구조체 배열 동적 할당 */
    process = (Process *)malloc(sizeof(Process) * process_count);

    /* 프로세스 갯수만큼 반복 */
    while (i < process_count)
    {
        fscanf(fp, "%s %d %d %d",
                process[i].id, &process[i].arrive_time, &process[i].burst, &process[i].priority);
        // 파일에서 프로세스 데이터를 읽어와 배열에 저장
        i++;
        // 다음 배열로 이동
    }

    fscanf(fp, " %d", &quantum);
    // 파일에서 정수형 데이터를 읽어와 quantum에 저장

    /* FCFS 함수 호출로 First Come First Served 알고리즘 실행 */
    puts("┏                                                                                                                             ┓\n\n");
    FCFS(process, process_count);
    puts("┗                                                                                                                             ┛\n\n");

    /* SJF 함수 호출로 Shortest Job First 알고리즘 실행 */
    puts("┏                                                                                                                             ┓\n\n");
    SJF(process, process_count);
    puts("┗                                                                                                                             ┛\n\n");

    /* RR 함수 호출로 Round Robin 알고리즘 실행 */
    puts("┏                                                                                                                             ┓\n\n");
    RR(process, process_count, quantum);
    puts("┗                                                                                                                             ┛\n\n");

    /* HRN 함수 호출로 Highest Response Ratio Next 알고리즘 실행 */
    puts("┏                                                                                                                             ┓\n\n");
    HRN(process, process_count);
    puts("┗                                                                                                                             ┛\n\n");

    /* NPPS 함수 호출로 Non-Preemptive Priority Scheduling 알고리즘 실행 */
    puts("┏                                                                                                                             ┓\n\n");
    NPPS(process, process_count);
    puts("┗                                                                                                                             ┛\n\n");

    /* PPS 함수 호출로 Preemptive Priority Scheduling 알고리즘 실행 */
    puts("┏                                                                                                                             ┓\n\n");
    PPS(process, process_count);
    puts("┗                                                                                                                             ┛\n\n");

    /* SRT 함수 호출로 Shortes Remaining Time 알고리즘 실행 */
    puts("┏                                                                                                                             ┓\n\n");
    SRT(process, process_count);
    puts("┗                                                                                                                             ┛\n\n");

    fclose(fp);
    // 열어준 파일포인터 fp를 닫아준다.

    free(process);
    // 메모리 할당을 해준 프로세스 구조체 배열 할당 해제

    system("pause");
    // 콘솔 창이 꺼지지 않도록 중지

    return 0;
    // 메인 함수 종료
}
