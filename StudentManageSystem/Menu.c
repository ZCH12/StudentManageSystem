
#include <stdio.h>
#include <stdlib.h>
#include "menu.h"


int ShowChartList = 0, ShowListList = 0, ShowTitleList = 0, ShowSearchTitleList = 0;		//仅作为开关
int CurrentChartIndex = 0;
int CurrentIndexListIndex = 0;
int CurrentTitleListIndex = 0;
int CurrentTitleIndex = 0;


//int Choice1;
char InputBuffer[256];

/*
根据预设值将所有的变量进行初始化
*/
void InitALL()
{
	int a;
	NewChartSet(5);
	NewListSet(5, LISTTYPE_INDEXLIST);
	NewListSet(5, LISTTYPE_TITLELIST);
	for (a = 0; a < 5; a++)
	{
		//IndexListHeadSet[a] = NULL;
		//TitleListHeadSet[a] = NULL;
		FillList(IndexListHeadSet[a], 0);
		strcpy(IndexListHeadSet[a]->ListName, "(未初始化)");
		FillList(TitleListHeadSet[a], 0);
		strcpy(TitleListHeadSet[a]->ListName, "(未初始化)");
	}
	return;
}

void FreeAll()
{
	FreeChartSet();
	FreeListSet(LISTTYPE_INDEXLIST);
	FreeListSet(LISTTYPE_TITLELIST);
	return;
}

void Menu_DisplaySubMenu() {
	int a;
	char* Temp;

	//表
	if (ChartHead[CurrentChartIndex] && ChartHead[CurrentChartIndex]->HadInit != 0) {
		Temp = ChartHead[CurrentChartIndex]->ChartName;
		Temp = Temp ? Temp : "未命名";
	}
	else {
		Temp = NULL;
	}
	printf(" %c[C] 当前进行操作的表:%s(%d)\n", ShowChartList ? '-' : '+', Temp, CurrentChartIndex);
	if (ShowChartList)
	{
		for (a = 0; a < ChartCount; a++)
			if (ChartHead[a] && ChartHead[a]->ChartName)
				printf("   [C#%-2d]. %s\n", a + 1, ChartHead[a]->ChartName);
			else
				printf("   [C#%-2d]. (NULL)\n", a + 1);
	}

	//名单
	if (IndexListHeadSet[CurrentIndexListIndex] && IndexListHeadSet[CurrentIndexListIndex]->AllocatedList > 0) {
		Temp = IndexListHeadSet[CurrentIndexListIndex]->ListName;
		Temp = Temp ? Temp : "未命名";
	}
	else {
		Temp = NULL;
	}
	printf(" %c[L] 当前进行操作的名单:%s(%d)\n", ShowListList ? '-' : '+', Temp, CurrentIndexListIndex);
	if (ShowListList)
	{
		for (a = 0; a < IndexListCount; a++)
			if (IndexListHeadSet[a] && IndexListHeadSet[a]->ListName)
				printf("   [L#%-2d]. %s\n", a + 1, IndexListHeadSet[a]->ListName);
			else
				printf("   [L#%-2d]. (NULL)\n", a + 1);
	}

	//列配置文件
	if (TitleListHeadSet[CurrentTitleListIndex] && TitleListHeadSet[CurrentTitleListIndex]->AllocatedList > 0) {
		Temp = TitleListHeadSet[CurrentTitleListIndex]->ListName;
		Temp = Temp ? Temp : "未命名";
	}
	else {
		Temp = NULL;
	}
	printf(" %c[T] 当前进行操作的列配置:%s(%d)\n", ShowTitleList ? '-' : '+', Temp, CurrentTitleListIndex);
	if (ShowTitleList)
	{
		for (a = 0; a < TitleListCount; a++)
			if (TitleListHeadSet[a] && TitleListHeadSet[a]->ListName)
				printf("   [T#%-2d]. %s\n", a + 1, TitleListHeadSet[a]->ListName);
			else
				printf("   [T#%-2d]. (NULL)\n", a + 1);
	}
	return;
}
void Menu_DisplaySubMenu_Search()
{
	int a;
	char* Temp;
	if (ChartHead[CurrentIndexListIndex] && ChartHead[CurrentIndexListIndex]->HadInit != 0) {
		Temp = ChartHead[CurrentIndexListIndex]->ChartTitle[CurrentTitleIndex];
		Temp = Temp ? Temp : "未命名";
	}
	else {
		Temp = NULL;
	}
	printf(" %s 当前进行搜索的列标题:%s(%d)\n", ShowSearchTitleList ? "-[S]" : "+[S]", Temp, CurrentTitleIndex);
	if (ShowSearchTitleList)
	{
		for (a = 0; a < ChartHead[CurrentIndexListIndex]->TitleCount; a++)
			printf("   [S#%-2d]. %s\n", a + 1, ChartHead[CurrentIndexListIndex]->ChartTitle[a]);
	}
}





//响应子菜单事件
int Event_Input()
{
	char Choice[5];
	int Choice1;
	scanf("%2s", Choice);
	switch (Choice[0])
	{
	case 'c':
	case 'C':
		if (Choice[1] == '#')
		{
			scanf("%d", &Choice);
			if (Choice >= 1 && Choice1 <= ChartCount)
				CurrentChartIndex = Choice1 - 1;
		}
		else ShowChartList = !ShowChartList;
		break;
	case 'l':
	case 'L':
		if (Choice[1] == '#')
		{
			scanf("%d", &Choice1);
			if (Choice1 >= 1 && Choice1 <= IndexListCount)
				CurrentIndexListIndex = Choice1 - 1;
		}
		else ShowListList = !ShowListList;
		break;
	case 't':
	case 'T':
		if (Choice[1] == '#')
		{
			scanf("%d", &Choice1);
			if (Choice1 >= 1 && Choice1 <= TitleListCount)
				CurrentTitleListIndex = Choice1 - 1;
		}
		else ShowTitleList = !ShowTitleList;
		break;
	case 's':
	case 'S':
		if (Choice[1] == '#')
		{
			scanf("%d", &Choice1);
			if (Choice1 >= 1 && Choice1 <= ChartHead[CurrentIndexListIndex]->TitleCount)
				CurrentTitleIndex = Choice1 - 1;
		}
		else ShowSearchTitleList = !ShowSearchTitleList;
		break;

	default:
		if (Choice[0] >= '0'&&Choice[0] <= '9')
			return atoi(Choice);
		break;
	}
	return -1;
}