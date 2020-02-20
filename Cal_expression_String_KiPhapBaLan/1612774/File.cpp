#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include"File.h"

void readFile(char* filename, char* &s)
{
	FILE* f = fopen(filename, "r");

	if (f)
	{
		fseek(f, 0L, SEEK_END);
		int cuoiFile = ftell(f);
		fseek(f, 0L, SEEK_SET);

		int len = cuoiFile + 1;
		s = (char*)malloc(sizeof(char)*(len + 1));
		fgets(s, len, f);

		fclose(f);
	}
	else
		printf("Loi! Khong the doc file\n");
}

void writeFile(char* filename, char* s)
{
	FILE* f = fopen(filename, "w");

	if (f)
	{
		fputs(s, f);

		fclose(f);
	}
	else
		printf("Loi! Khong the ghi vao file!\n");
}