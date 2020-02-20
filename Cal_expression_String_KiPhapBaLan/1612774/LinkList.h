#pragma once

#include<stdio.h>
#include<math.h>
#include<malloc.h>
#include<string.h>

typedef struct node* Ref;
struct  node
{
	char* data;
	Ref next;
};

void initList(Ref &, Ref &);
Ref getNode(char*);
void addFirst(Ref &, Ref &, char*);
void addLast(Ref &, Ref &, char*);
void printList(Ref, Ref);
void destroyNode(Ref &);
void destroyList(Ref &, Ref &);
void deleteFirst(Ref &, Ref &);
void deleteEnd(Ref &, Ref &);
char* getDataHead(Ref, Ref);
char* getDataTail(Ref, Ref);
