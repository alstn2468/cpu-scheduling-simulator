#ifndef __HIGHEST__RESPONSE__RATIO__NEXT__
#define __HIGHEST__RESPONSE__RATIO__NEXT__

// HRN Algorithm

#include <stdio.h>
#include <stdlib.h>

#include "./Process.h"

int calculate_priority(Process *p, int len)
{
	return (p->waiting_time + p->burst) / (p->burst);
}

void hrn_print_gantt_chart(Process *p, int len)
{

}

void HRN(Process *p, int len)
{

}

#endif
