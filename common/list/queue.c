#include "queue.h"

Queue *initQueue(int value)
{
	Queue *q;
	Num *n;
	n = malloc(sizeof(Num));
	q = malloc(sizeof(Queue));
	n->num = value;
	q->init = n;
	q->end = n;
	q->end->next = NULL;
	return q;
}

void printQueue(Queue *q)
{
	Num *n; 
	for (n = q->init; n != NULL; n = n->next)
	{
		printf("%d - ", n->num);
	}
}

void freeQueue(Queue *q)
{
	while(q->init!=NULL)
	{
		removeQueue(q);
	}	

	free(q);
}

void insertQueue(Queue *q, int value)
{
	Num *v;
	v = malloc(sizeof(Num));
	v->num = value;
	v->next = NULL;
	q->end->next = v;
	q->end = v;
}

int removeQueue(Queue *q)
{
	Num *remove = q->init;
	int value = q->init->num;
	q->init = q->init->next;
	free(remove);
	return value;
}

int emptyQueue(Queue *q)
{
	if(q->init == NULL)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
