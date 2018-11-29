#ifndef __COMPARE__FUNCTION__
#define __COMPARE__FUNCTION__

// Sorting Function

#include <stdio.h>
#include <stdlib.h>

#include "./Process.h"

int compare_by_return_time(const void *a, const void *b)
{
	Process *ptA = (Process *)a;
	Process *ptB = (Process *)b;

	if (ptA->return_time < ptB->return_time)
		return -1;

	else if (ptA->return_time > ptB->return_time)
		return 1;

	else
		return 0;
}

void quick_sort_by_return_time(Process p[], int len)
{
	qsort(p, len, sizeof(Process), compare_by_return_time);
}

/**
 * [merge 함수]
 * @param arr   [정렬할 배열]
 * @param left  [배열의 가장 왼쪽 인덱스]
 * @param mid   [배열의 가운데 인덱스]
 * @param right [배열의 가장 오른쪽 인덱스]
 */
void merge(Process arr[], int left, int mid, int right)
{
	int fIdx = left;
	// 왼쪽 배열의 시작 인덱스를 저장할 변수 선언 및 초기화
	int rIdx = mid + 1;
	// 오른쪽 배열의 시작 인덱스를 저장할 변수 선언 및 초기화
	int i;
	// 반복문에서 사용할 변수 선언

	Process *sortArr = (Process *)malloc(sizeof(Process) * (right + 1));
	// 정렬된 배열을 저장할 배열 동작 할당
	int sIdx = left;

	/* left부터 mid까지의 블록과 mid + 1부터
	   right까지의 블록을 비교하는 부분 */
	while (fIdx <= mid && rIdx <= right)
	{
		/* left의 데이터가 right값보다 작을 경우 */
		if (arr[fIdx].arrive_time <= arr[rIdx].arrive_time)
			sortArr[sIdx] = arr[fIdx++];
		// left의 데이터를 결과 배열에 복사

		/* 그렇지 않을 경우 */
		else
			sortArr[sIdx] = arr[rIdx++];
		// right의 데이터를 결과 배열에 복사

		sIdx++; // 결과 배열의 인덱스 증가
	}

	/* 오른쪽 배열의 데이터가 남아있는 경우 */
	if (fIdx > mid)
	{
		/* 오른쪽 배열의 남은 데이터 만큼 반복 */
		for (i = rIdx; i <= right; i++, sIdx++)
			sortArr[sIdx] = arr[i];
		// 오른쪽 배열의 데이터를 결과 배열에 복사
	}

	/* 왼쪽 배열의 데이터가 남아있는 경우 */
	else
	{
		/* 왼쪽 배열의 남은 데이터 만큼 반복 */
		for (i = fIdx; i <= mid; i++, sIdx++)
			sortArr[sIdx] = arr[i];
			// 왼쪽 배열의 데이터를 결과 배열에 복사
	}

	/* 배열의 데이터 개수만큼 반복 */
	for (i = left; i <= right; i++)
		arr[i] = sortArr[i]; // 원본 배열에 복사

	free(sortArr); // 배열 메모리 할당 해제
}

/**
 * [merge_sort_by_arrive_time 함수]
 * @param arr   [정렬할 배열]
 * @param left  [배열의 가장 왼쪽 인덱스]
 * @param right [배열의 가장 오른쪽 인덱스]
 */
void merge_sort_by_arrive_time(Process arr[], int left, int right)
{
	int mid;
	// 중간 지점 인덱스를 저장할 변수 선언

	/* left가 right보다 작으면 실행 */
	if (left < right)
	{
		/* 중간 지점을 계산한다 */
		mid = (left + right) / 2;

		/* 둘로 나눠서 각각을 정렬한다 */
		merge_sort_by_arrive_time(arr, left, mid);
		merge_sort_by_arrive_time(arr, mid + 1, right);

		/* 정렬된 두 배열을 병합한다 */
		merge(arr, left, mid, right);
	}
}

#endif
