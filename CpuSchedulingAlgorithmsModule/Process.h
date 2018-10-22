#ifndef __PROCESS__
#define __PROCESS__
#define ID_LEN 20

// Process Structure Header

typedef struct _process
{
    char id[ID_LEN];
    int arriveTime;
    int burst;
    int priority;
} Process

typedef int quantum

#endif
