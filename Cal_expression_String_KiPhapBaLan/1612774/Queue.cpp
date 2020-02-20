#include"LinkList.h"
#include"Queue.h"

void initQueue(Queue &qu)
{
	initList(qu.head, qu.tail);
}

char* popQueue(Queue &qu)
{
	if (qu.head == NULL)
		return qu.head->data;

	Ref result = getNode(qu.tail->data);

	deleteEnd(qu.head, qu.tail);

	return result->data;
}

void pushQueue(Queue &qu, char* data)
{
	addFirst(qu.head, qu.tail, data);
}

void printQueue(Queue qu)
{
	printList(qu.head, qu.tail);
}

bool queueIsEmpty(Queue qu)
{
	return (qu.head == NULL);
}

char* peekQueue(Queue qu)
{
	return qu.tail->data;
}

void destroyQueue(Queue& qu)
{
	destroyList(qu.head, qu.tail);
}