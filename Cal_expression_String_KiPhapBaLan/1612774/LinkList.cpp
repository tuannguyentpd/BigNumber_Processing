#define _CRT_SECURE_NO_WARNINGS
#include"LinkList.h"

Ref getNode(char* data)
{
	Ref p;

	p = (Ref)malloc(sizeof(struct node));
	if (p == NULL)
	{
		printf("Loi - Khong du bo nho cap phat!\n");
	}

	p->data = (char*)malloc(sizeof(char)*(strlen(data) + 1));
	strcpy(p->data, data);
	p->next = NULL;

	return p;
}

void initList(Ref &head, Ref &tail)
{
	head = tail = NULL;
}

void addFirst(Ref &head, Ref &tail, char* data)
{
	Ref p = getNode(data);

	if (p != NULL)
	{
		if (head == NULL)
			head = tail = p;
		else
		{
			p->next = head;
			head = p;
		}
	}
}

void addLast(Ref &head, Ref &tail, char* data)
{
	Ref p = getNode(data);

	if (p != NULL)
	{
		if (head == NULL)
			head = tail = p;
		else
		{
			tail->next = p;
			tail = p;
		}
	}
}

void printList(Ref head, Ref tail)
{
	Ref p;

	if (head == NULL)
	{
		printf("Rong!\n");
		return;
	}

	p = head;
	while (p)
	{
		printf("%s -> ", p->data);
		p = p->next;
	}
}

void destroyNode(Ref &p)
{
	if (p->data != NULL) {
		free(p->data);
	}
	free(p);
}

void destroyList(Ref &head, Ref &tail)
{
	Ref p;

	while (head)
	{
		p = head;
		head = head->next;
		destroyNode(p);
	}
}

void deleteFirst(Ref &head, Ref &tail)
{
	Ref p;

	if (head == NULL)
		return;

	if (head == tail)
	{
		destroyNode(head);
		head = tail = NULL;
	}
	else
	{
		p = head;
		head = head->next;
		destroyNode(p);
	}
}

void deleteEnd(Ref &head, Ref &tail)
{
	Ref p;

	if (head == tail)
	{
		destroyNode(head);
		head = tail = NULL;
	}
	else
	{
		/*	p = head;
		while (p->next->next)
		{
		p = p->next;
		}
		destroyNode(tail);
		tail = p;
		p->next = NULL;*/
		for (p = head; p->next != tail; p = p->next);
		destroyNode(tail);
		tail = p;
		p->next = NULL;
	}
}

char* getDataHead(Ref head, Ref tail)
{
	return head->data;
}

char* getDataTail(Ref head, Ref tail)
{
	return tail->data;
}
