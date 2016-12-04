#include <stdio.h>
#include "DataBase.h"

int main()
{
	Chart chart = {0};
	char list[2][32] = { "±àºÅ","ĞÕÃû" };
	int list2[2] = { 5,5 };
	//printf("%d\n",ReadFromFile("data.ini", &chart));
	CreateNewUnit(&chart, 1, list, list2);
	//printf("%s  %s  %s\n", chart.Chart[0][0], chart.Chart[0][1], chart.Chart[0][1]);
	
	system("pause");

}