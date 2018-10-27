#ifndef __COMPARE__FUNCTION__
#define __COMPARE__FUNCTION__

// Compare Function

#include <stdio.h>

#include "./Process.h"

int compare_by_arrive_time(const void *a, const void *b)
{
	Process *ptA = (Process *)a;
	Process *ptB = (Process *)b;

	if (ptA->arrive_time < ptB->arrive_time)
		return -1;

	else if (ptA->arrive_time > ptB->arrive_time)
		return 1;

	else
		return 0;
}

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

#endif
