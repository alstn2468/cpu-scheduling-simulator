#ifndef __CIRCULAR__QUEUE__
#define __CIRCULAR__QUEUE__

#include <stdio.h>
#include <stdlib.h>

typedef int element;

typedef struct
{
	element *queue;
	int front;
	int rear;
} QueueType;

void error(char *message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

void init(QueueType *q, int count)
{
    q->queue = (element *)malloc(sizeof(element) * count);
	q->front = q->rear = 0;
}

int is_empty(QueueType *q)
{
	return  (q->front == q->rear);
}

int is_full(QueueType *q)
{
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

void enqueue(QueueType *q, element item)
{
	if (is_full(q))
		error("QUEUE FULL ERROR!\n");

	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->queue[q->rear] = item;
}

element dequeue(QueueType *q)
{
	if (is_empty(q))
		error("QUEUE EMPTY ERROR!.\n");

	q->front = (q->front + 1) % MAX_QUEUE_SIZE;

	return q->queue[q->front];
}

element peek(QueueType *q)
{
	if (is_empty(q))
		error("QUEUE EMPTY ERROR!.\n");

	return q->queue[(q->front + 1) % MAX_QUEUE_SIZE];
}


#endif
