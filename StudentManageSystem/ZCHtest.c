#include <stdio.h>
#include "DataBase.h"

int main()
{
	Chart chart = {0};
	char list[2][32] = { "���","����" };
	int list2[2] = { 1,1 };
	printf("%d\n",ReadFromFile("data.ini", &chart));
	CreateNewUnit(&chart, 2, list, list2);
	strcpy(chart.Chart[0][5], "sd");
	printf("%s  %s  %s  %s  %s  %s\n", chart.Chart[0][0], chart.Chart[0][1], chart.Chart[0][2], chart.Chart[0][3], chart.Chart[0][4], chart.Chart[0][5]);
	
	system("pause");

}