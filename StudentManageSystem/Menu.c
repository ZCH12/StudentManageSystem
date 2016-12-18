#include "menu.h"

/********************************************************************************
窗体通用函数
********************************************************************************/
int ShowChartList = 0, ShowListList = 0, ShowTitleList = 0, ShowSearchTitleList = 0;		//仅作为开关
int ShowPageList = 0;
int CurrentChartIndex = 0;			//最近在操作的表的编号
int CurrentIndexListIndex = 0;		//最近在操作的IndexList的编号
int CurrentTitleListIndex = 0;		//最近在操作的TitleList的编号
int CurrentTitleIndex = 0;			//最近在操作的Chart表中的列的编号
int CurrentPageIndex = 0;			//当前在操作的页

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
	system("title 学生管理系统");
	system("mode con: cols=120 lines=10000");
	system("color F9");

	return;
}

/*
从配置文件读取配置
*/
void ReadConfig1(char *ConfigFile, char *ParamFileName, char * DataFileName, char *SexFileName, char *CollageFileName)
{
	FILE *File = fopen(ConfigFile, "r");
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
void ReadConfig2(char *ConfigFile, char * FileName)
{
	FILE *File = fopen(ConfigFile, "r");
	if (File)
	{
		fgets(FileName, 512, File);
		FileName[strlen(FileName) - 1] = 0;
		fclose(File);
	}
}
void ReadConfig3(char * ConfigFile, char * ParamFileName, char * DataFileName)
{
	FILE *File = fopen(ConfigFile, "r");
	if (File)
	{
		fgets(ParamFileName, 512, File);
		ParamFileName[strlen(ParamFileName) - 1] = 0;
		fgets(DataFileName, 512, File);
		DataFileName[strlen(DataFileName) - 1] = 0;
		fclose(File);
	}
}

void WriteConfig1(char *ConfigFile, char *ParamFileName, char * DataFileName, char *SexFileName, char *CollageFileName)
{
	FILE *File = fopen(ConfigFile, "w");
	if (File)
	{
		fprintf(File, "%s\n", ParamFileName);
		fprintf(File, "%s\n", DataFileName);
		fprintf(File, "%s\n", SexFileName);
		fprintf(File, "%s\n", CollageFileName);
		fclose(File);
	}
}
void WriteConfig2(char *ConfigFile, char * FileName)
{
	FILE *File = fopen(ConfigFile, "w");
	if (File)
	{
		fprintf(File, "%s\n", FileName);
		fclose(File);
	}
}
void WriteConfig3(char * ConfigFile, char * ParamFileName, char * DataFileName)
{
	FILE *File = fopen(ConfigFile, "w");
	if (File)
	{
		fprintf(File, "%s\n", ParamFileName);
		fprintf(File, "%s\n", DataFileName);
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
		if (IndexListHeadSet)
			for (a = 0; a < IndexListCount; a++)
                if (IndexListHeadSet[a]){
                    if (IndexListHeadSet[a]->ListName){
                        printf("   [L#%-2d]. %s{%d}\n", a + 1, IndexListHeadSet[a]->ListName, IndexListHeadSet[a]->listCount);
                    }
                    else {
                        printf("   [L#%-2d]. (NULL){%d}\n", a + 1, IndexListHeadSet[a]->listCount);
                    }
                }
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
		if (TitleListHeadSet)
			for (a = 0; a < TitleListCount; a++)
                if (TitleListHeadSet[a]){
                    if (TitleListHeadSet[a]->ListName){
                        printf("   [T#%-2d]. %s{%d}\n", a + 1, TitleListHeadSet[a]->ListName, TitleListHeadSet[a]->listCount);
                    }
                    else {
                        printf("   [T#%-2d]. (NULL){%d}\n", a + 1, TitleListHeadSet[a]->listCount);
                    }
                }
	}
	return;
}
char* Menu_DisplaySubMenu_Search()
{
	int a;
	char* Temp;
	if (ChartHead[CurrentChartIndex] && ChartHead[CurrentChartIndex]->HadInit != 0) {
		Temp = ChartHead[CurrentChartIndex]->ChartTitle[CurrentTitleIndex];
		Temp = Temp ? Temp : "未命名";
	}
	else {
		Temp = NULL;
	}
	printf(" %s 当前进行操作的列标题:%s(%d)\n", ShowSearchTitleList ? "-[S]" : "+[S]", Temp, CurrentTitleIndex);
	if (ShowSearchTitleList&&ChartHead[CurrentChartIndex])
	{
		for (a = 0; a < ChartHead[CurrentChartIndex]->TitleCount; a++)
			printf("   [S#%-2d]. %s\n", a + 1, ChartHead[CurrentChartIndex]->ChartTitle[a]);
	}
	return Temp;
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
//多页选择器
void Menu_DisplaySubMenu_Page()
{
	int a, b;
	printf(" %c[P] 当前进行操作的页:%d--%d(%d)\n", ShowSearchTitleList ? '-' : '+', CurrentPageIndex*SIZE_PAGE, (CurrentPageIndex + 1)*SIZE_PAGE, CurrentPageIndex);
	if (ShowPageList) {
		if (IndexListHeadSet&&IndexListHeadSet[CurrentIndexListIndex] && IndexListHeadSet[CurrentIndexListIndex]->AllocatedList > 0)
		{
			for (a = 1, b = 0; b + SIZE_PAGE <= IndexListHeadSet[CurrentIndexListIndex]->listCount; a++, b += SIZE_PAGE)
				printf("   [P#%-2d]. %d--%d\n", a, b, b + SIZE_PAGE);
		}
		else {
			if (ChartHead&&ChartHead[CurrentChartIndex] && ChartHead[CurrentChartIndex]->UsedLines)
				for (a = 1, b = 0; b + SIZE_PAGE <= ChartHead[CurrentChartIndex]->UsedLines; a++, b += SIZE_PAGE)
					printf("   [P#%-2d]. %d--%d\n", a, b, b + SIZE_PAGE);
		}
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
	case 'p':
	case 'P':
		if (Choice[1] == '#')
		{
			scanf("%d", &Choice1);
			CurrentPageIndex = Choice1 - 1;
		}
		else ShowPageList = !ShowPageList;
		break;
	default:
		if (Choice[0] >= '0'&&Choice[0] <= '9')
			return atoi(Choice);
		break;
	}
	return -1;
}

#if GETPASSWORD==1
//密码输入器,星号回显
int InputPassWord(char *PassWord, int MaxSize)
{
	char tempchar;
	int a;
	if (MaxSize <= 0)
		return 0;
	for (a = 0; a < MaxSize;)
	{
		tempchar = _getch();
		switch (tempchar)
		{
		case '\r':
			PassWord[a] = 0;
			printf("\n");
			return a;
		case '\b':
			if (a > 0) {
				a--;
				printf("\b \b");
			}
			break;
		default:
			PassWord[a] = tempchar;
			printf("*");
			a++;
			break;
		}
	}
	return a;
}
#else
int InputPassWord(char *PassWord, int MaxSize)
{
	getchar();
	fgets(PassWord,MaxSize,stdin);
	PassWord[strlen(PassWord)-1]=0;
	return (int )strlen(PassWord);
}
#endif
