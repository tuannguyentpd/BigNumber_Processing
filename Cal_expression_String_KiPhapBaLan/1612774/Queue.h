#pragma once

#include"LinkList.h"

struct Queue
{
	Ref head;
	Ref tail;
};

void initQueue(Queue &);
char* popQueue(Queue &);
void pushQueue(Queue &, char*);
void printQueue(Queue);
bool queueIsEmpty(Queue);
char* peekQueue(Queue);
void destroyQueue(Queue&);