#define _CRT_SECURE_NO_WARNINGS
#include"LinkList.h"
#include"Stack.h"

void initStack(Stack &st)
{
	initList(st.head, st.tail);
}

char* popStack(Stack &st)
{
	if (st.head == NULL)
		return NULL;

	Ref result = getNode(st.tail->data);

	deleteEnd(st.head, st.tail);

	return result->data;
}

void pushStack(Stack &st, char* data)
{
	addLast(st.head, st.tail, data);
}

void printStack(Stack st)
{
	printList(st.head, st.tail);
}

bool stackIsEmpty(Stack st)
{
	return (st.head == NULL);
}

char* peekStack(Stack st)
{
	return st.tail->data;
}

void destroyStack(Stack&st)
{
	destroyList(st.head, st.tail);
}