#define _CRTDBG_MAP_ALLOC
#include <stdio.h>
#include <stdlib.h>
#include <crtdbg.h>
#include "DataBase.h"

int main()
{
	void SearchBy(const char* SearchTitle);
	void Search_M();
	void SearchBy(const char* SearchTitle);
	//printf("%s",GetFileName("C:\\456\\123.txt"));
	NewChartSet(1);
	
	ReadFromTwoFile("ZCHtestFile\\stu_param2.txt", "ZCHtestFile\\Stu_info2.txt", ChartHead[0]);

	NewListSet(5,1);
	NewListSet(5,0);
	FillList(TitleListHeadSet[0],5);
	FillList(IndexListHeadSet[0],ChartHead[0]->UsedLines);
	FillList(IndexListHeadSet[1],ChartHead[0]->UsedLines);
	Search_M();
	_CrtDumpMemoryLeaks();
}