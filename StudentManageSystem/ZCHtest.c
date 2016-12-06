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
	printf("%d\n", SHI(&chart, "µÿ÷∑"));

	//InitList(&il, 15);
	//InitList(&tl, 3);
	//InitList(&ll, 1000);
	WTIA(list3, 3, 0, 1, 2);
	ll.list = list3;
	ll.listCount = 3;
	ll.AllocatedList = 3;

	Display_Piece(&chart, 999, &ll);

	//Sort(&chart, NULL, &ll, 0, 1);

	//Display_Chart(&chart,NULL,NULL,0);

	system("pause");

}