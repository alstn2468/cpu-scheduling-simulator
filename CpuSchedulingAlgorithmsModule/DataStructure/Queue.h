#ifndef __QUEUE__
#define __QUEUE__

#include <stdio.h>
#include <stdlib.h>

typedef int element;

typedef struct Node
{
	element item;
	struct Node *link;
} Node;

typedef struct
{
	Node *front;
	Node *rear;
} Queue;

void queue_error(char *messgae)
{
	fprintf(stderr, "%s\n", messgae);
	return ;
}

void queue_init(Queue *q)
{
	q->front = NULL;
	q->rear = NULL;
}

int queue_is_empty(Queue *q)
{
	return (q->front == NULL);
}

void queue_enqueue(Queue *q, element item)
{
	Node *temp = (Node *)malloc(sizeof(Node));

	if (temp == NULL)
		queue_error("MEMORY ALLOCATION ERROR!.\n");

	else
	{
		temp->item = item;
		temp->link = NULL;

		if (queue_is_empty(q))
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

element queue_dequeue(Queue *q)
{
	Node *temp = q->front;
	element item;

	if (queue_is_empty(q))
		queue_error("QUEUE EMPRY ERROR!.\n");

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

element queue_peek(Queue *q)
{
	if (queue_is_empty(q))
		queue_error("큐가 비어있습니다.\n");

	else
		return q->front->item;
}

#endif
