#define _CRT_SECURE_NO_WARNINGS
#include"LinkList.h"
#include"Stack.h"
#include"Queue.h"
#include"File.h"
#include"Expression.h"

void main(int argc, char** argv)
{
	if (argc != 3)
	{
		printf("Tham so khong hop le!\n");
		return;
	}
	tinhBieuThuc(argv[1], argv[2]);
}
