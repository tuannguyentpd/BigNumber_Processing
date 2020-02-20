#pragma once

#include"LinkList.h"

struct Stack
{
	Ref head;
	Ref tail;
};

void initStack(Stack &);
char* popStack(Stack &);
void pushStack(Stack &, char*);
void printStack(Stack);
bool stackIsEmpty(Stack);
char* peekStack(Stack);
void destroyStack(Stack&);