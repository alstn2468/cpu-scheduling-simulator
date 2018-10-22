#ifndef __CIRCULAR__QUEUE__
#define __CIRCULAR__QUEUE__

#include <stdio.h>
#include <stdlib.h>

typedef int element;

typedef struct _queue
{
	element *queue;
	int front;
	int rear;
	int size;
} CircularQueue;

void cqueue_error(char *message)
{
	fprintf(stderr, "%s\n", message);
	return ;
}

void cqueue_init(CircularQueue *q, int count)
{
    q->queue = (element *)malloc(sizeof(element) * count);
	q->front = q->rear = 0;
	q->size = 0;
}

int cqueue_is_empty(CircularQueue *q)
{
	return  (q->front == q->rear);
}

int cqueue_is_full(CircularQueue *q)
{
	return ((q->rear + 1) % q->size == q->front);
}

void cqueue_enqueue(CircularQueue *q, element item)
{
	if (cqueue_is_full(q))
		cqueue_error("QUEUE FULL ERROR!\n");

	q->rear = (q->rear + 1) % q->size;
	q->queue[q->rear] = item;
}

element cqueue_dequeue(CircularQueue *q)
{
	if (cqueue_is_empty(q))
		cqueue_error("QUEUE EMPTY ERROR!.\n");

	q->front = (q->front + 1) % q->size;

	return q->queue[q->front];
}

element cqueue_peek(CircularQueue *q)
{
	if (cqueue_is_empty(q))
		cqueue_error("QUEUE EMPTY ERROR!.\n");

	return q->queue[(q->front + 1) % q->size];
}

#endif
