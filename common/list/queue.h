#include "list.h"
#include <stdio.h>

typedef struct queue Queue;
struct queue
{
	Num *init;
	Num *end;
};

Queue *initQueue(int value);
void insertQueue(Queue *q, int value);
int removeQueue(Queue *q);
int emptyQueue(Queue *q);
void printQueue(Queue *q); 
void freeQueue(Queue *q);

