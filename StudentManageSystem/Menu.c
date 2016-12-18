#include "menu.h"

/********************************************************************************
����ͨ�ú���
********************************************************************************/
int ShowChartList = 0, ShowListList = 0, ShowTitleList = 0, ShowSearchTitleList = 0;		//����Ϊ����
int ShowPageList = 0;
int CurrentChartIndex = 0;			//����ڲ����ı�ı��
int CurrentIndexListIndex = 0;		//����ڲ�����IndexList�ı��
int CurrentTitleListIndex = 0;		//����ڲ�����TitleList�ı��
int CurrentTitleIndex = 0;			//����ڲ�����Chart���е��еı��
int CurrentPageIndex = 0;			//��ǰ�ڲ�����ҳ

char InputBuffer[256];

/*
����Ԥ��ֵ�����еı������г�ʼ��
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
		strcpy(IndexListHeadSet[a]->ListName, "(δ��ʼ��)");
		FillList(TitleListHeadSet[a], 0);
		strcpy(TitleListHeadSet[a]->ListName, "(δ��ʼ��)");
	}
	system("title ѧ������ϵͳ");
	system("mode con: cols=120 lines=10000");
	system("color F9");

	return;
}

/*
�������ļ���ȡ����
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

	//��
	if (ChartHead[CurrentChartIndex] && ChartHead[CurrentChartIndex]->HadInit != 0) {
		Temp = ChartHead[CurrentChartIndex]->ChartName;
		Temp = Temp ? Temp : "δ����";
	}
	else {
		Temp = NULL;
	}
	printf(" %c[C] ��ǰ���в����ı�:%s(%d)\n", ShowChartList ? '-' : '+', Temp, CurrentChartIndex);
	if (ShowChartList)
	{
		for (a = 0; a < ChartCount; a++)
			if (ChartHead[a] && ChartHead[a]->ChartName)
				printf("   [C#%-2d]. %s\n", a + 1, ChartHead[a]->ChartName);
			else
				printf("   [C#%-2d]. (NULL)\n", a + 1);
	}

	//����
	if (IndexListHeadSet[CurrentIndexListIndex] && IndexListHeadSet[CurrentIndexListIndex]->AllocatedList > 0) {
		Temp = IndexListHeadSet[CurrentIndexListIndex]->ListName;
		Temp = Temp ? Temp : "δ����";
	}
	else {
		Temp = NULL;
	}
	printf(" %c[L] ��ǰ���в���������:%s(%d)\n", ShowListList ? '-' : '+', Temp, CurrentIndexListIndex);
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

	//�������ļ�
	if (TitleListHeadSet[CurrentTitleListIndex] && TitleListHeadSet[CurrentTitleListIndex]->AllocatedList > 0) {
		Temp = TitleListHeadSet[CurrentTitleListIndex]->ListName;
		Temp = Temp ? Temp : "δ����";
	}
	else {
		Temp = NULL;
	}
	printf(" %c[T] ��ǰ���в�����������:%s(%d)\n", ShowTitleList ? '-' : '+', Temp, CurrentTitleListIndex);
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
		Temp = Temp ? Temp : "δ����";
	}
	else {
		Temp = NULL;
	}
	printf(" %s ��ǰ���в������б���:%s(%d)\n", ShowSearchTitleList ? "-[S]" : "+[S]", Temp, CurrentTitleIndex);
	if (ShowSearchTitleList&&ChartHead[CurrentChartIndex])
	{
		for (a = 0; a < ChartHead[CurrentChartIndex]->TitleCount; a++)
			printf("   [S#%-2d]. %s\n", a + 1, ChartHead[CurrentChartIndex]->ChartTitle[a]);
	}
	return Temp;
}
//Display���Ӻ���
void Menu_DisplaySubMenu_Display()
{
	int a;
	if (ChartHead[CurrentIndexListIndex])
	{
		for (a = 0; a < ChartHead[CurrentIndexListIndex]->TitleCount; a++)
			printf("   [%-2d]. %s\n", a + 1, ChartHead[CurrentIndexListIndex]->ChartTitle[a]);
	}
}
//��ҳѡ����
void Menu_DisplaySubMenu_Page()
{
	int a, b;
	printf(" %c[P] ��ǰ���в�����ҳ:%d--%d(%d)\n", ShowSearchTitleList ? '-' : '+', CurrentPageIndex*SIZE_PAGE, (CurrentPageIndex + 1)*SIZE_PAGE, CurrentPageIndex);
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

//��Ӧ�Ӳ˵��¼�
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
//����������,�ǺŻ���
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
