#include <stdio.h>
#include "DataBase.h"

int main()
{
	Chart chart = {0};
	char list[2][32] = { "∞‡º∂","µÿ÷∑" };
	int list2[2];
	int list3[5];
	IndexList il = { 0 };
	TitleList tl = { 0 };
	IndexList ll = { 0 };

	printf("%d\n",ReadFromFile("data.ini", &chart));
	WirteToIntArray(list2, 2, 20, 20);
	CreateNewUnit(&chart, 2, list, list2);

	//InitList(&il, 15);
	//InitList(&tl, 3);
	InitList(&ll, 1000);

	//Display_Piece(&chart, 999, &ll);

	Sort(&chart,&ll, SHI(&chart, "–’√˚"), SORT_ASCENDING);
	Display_Chart(&chart,&ll,NULL,0);

	system("pause");

}