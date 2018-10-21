#ifndef __QUEUE__
#define __QUEUE__

#include <stdio.h>
#include <stdlib.h>

typedef int element;

typedef struct QueueNode
{
	element item;
	struct QueueNode *link;
} QueueNode;

typedef struct
{
	QueueNode *front;
	QueueNode *rear;
} QueueType;

void error(char *messgae)
{
	fprintf(stderr, "%s\n", messgae);
	exit(1);
}

void init(QueueType *q)
{
	q->front = NULL;
	q->rear = NULL;
}

int is_empty(QueueType *q)
{
	return (q->front == NULL);
}

void enqueue(QueueType *q, element item)
{
	QueueNode *temp = (QueueNode *)malloc(sizeof(QueueNode));

	if (temp == NULL)
		error("MEMORY ALLOCATION ERROR!.\n");

	else
	{
		temp->item = item;
		temp->link = NULL;

		if (is_empty(q))
		{
			q->front = temp;
			q->rear = temp;
		}

		else
		{
			q->rear->link = temp;
			q->rear = temp;
		}
	}
}

element dequeue(QueueType *q)
{
	QueueNode *temp = q->front;
	element item;

	if (is_empty(q))
		error("QUEUE EMPRY ERROR!.\n");

	else
	{
		item = temp->item;
		q->front = q->front->link;

		if (q->front == NULL)
			q->rear = NULL;

		free(temp);

		return item;
	}
}

element peek(QueueType *q)
{
	if (is_empty(q))
		error("큐가 비어있습니다.\n");

	else
		return q->front->item;
}

#endif
