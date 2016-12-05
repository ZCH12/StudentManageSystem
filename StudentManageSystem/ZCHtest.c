#include <stdio.h>
#include "DataBase.h"

int main()
{
	Chart chart = {0};
	char list[2][32] = { "∞‡º∂","µÿ÷∑" };
	int list2[2] = { 6,20 };
	IndexList il = { 0 };
	TitleList tl = { 0 };
	IndexList ll = { 0 };

	printf("%d\n",ReadFromFile("data.ini", &chart));
	CreateNewUnit(&chart, 2, list, list2);

	InitList(&il, 15);
	InitList(&tl, 3);
	InitList(&ll, 1000);

	Sort(&chart, NULL, &ll, 0, 1);

	Display_Chart(&chart,&ll,&tl,0);

	system("pause");

}