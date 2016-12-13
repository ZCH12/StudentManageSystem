#include "menu.h"

/********************************************************************************
窗体通用函数
********************************************************************************/
int ShowChartList = 0, ShowListList = 0, ShowTitleList = 0, ShowSearchTitleList = 0;		//仅作为开关
int CurrentChartIndex = 0;			//最近在操作的表的编号
int CurrentIndexListIndex = 0;		//最近在操作的IndexList的编号
int CurrentTitleListIndex = 0;		//最近在操作的TitleList的编号
int CurrentTitleIndex = 0;			//最近在操作的Chart表中的列的编号

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
		FillList(IndexListHeadSet[a], 0);
		strcpy(IndexListHeadSet[a]->ListName, "(未初始化)");
		FillList(TitleListHeadSet[a], 0);
		strcpy(TitleListHeadSet[a]->ListName, "(未初始化)");
	}
	return;
}

/*
从配置文件读取配置
*/
void ReadConfig1(char *ParamFileName, char * DataFileName, char *SexFileName, char *CollageFileName)
{
	FILE *File = fopen(CONFIGFILEPATH1, "r");
	if (File)
	{
		fgets(ParamFileName, 512, File);
		ParamFileName[strlen(ParamFileName) - 1] = 0;
		fgets(DataFileName, 512, File);
		DataFileName[strlen(DataFileName) - 1] = 0;
		fgets(SexFileName, 512, File);
		SexFileName[strlen(SexFileName) - 1] = 0;
		fgets(CollageFileName, 512, File);
		CollageFileName[strlen(CollageFileName) - 1] = 0;
		fclose(File);
	}
}

void ReadConfig2(char * FileName)
{
	FILE *File = fopen(CONFIGFILEPATH2, "r");
	if (File)
	{
		fgets(FileName, 512, File);
		FileName[strlen(FileName)-1]=0;
		fclose(File);
	}
}

void WriteConfig1(char *ParamFileName, char * DataFileName, char *SexFileName, char *CollageFileName)
{
	FILE *File = fopen(CONFIGFILEPATH1, "w");
	if (File)
	{
		fprintf(File, "%s\n", ParamFileName);
		fprintf(File, "%s\n", DataFileName);
		fprintf(File, "%s\n", SexFileName);
		fprintf(File, "%s\n", CollageFileName);
		fclose(File);
	}
}
void WriteConfig2(char * FileName)
{
	FILE *File = fopen(CONFIGFILEPATH2, "w");
	if (File)
	{
		fprintf(File, "%s\n", FileName);
		fclose(File);
	}
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
	printf(" %s 当前进行操作的列标题:%s(%d)\n", ShowSearchTitleList ? "-[S]" : "+[S]", Temp, CurrentTitleIndex);
	if (ShowSearchTitleList&&ChartHead[CurrentIndexListIndex])
	{
		for (a = 0; a < ChartHead[CurrentIndexListIndex]->TitleCount; a++)
			printf("   [S#%-2d]. %s\n", a + 1, ChartHead[CurrentIndexListIndex]->ChartTitle[a]);
	}
}
//Display的子函数
void Menu_DisplaySubMenu_Display()
{
	int a;
	if (ChartHead[CurrentIndexListIndex])
	{
		for (a = 0; a < ChartHead[CurrentIndexListIndex]->TitleCount; a++)
			printf("   [%-2d]. %s\n", a + 1, ChartHead[CurrentIndexListIndex]->ChartTitle[a]);
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
			scanf("%d", &Choice1);
			if (Choice1 >= 1 && Choice1 <= ChartCount)
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
