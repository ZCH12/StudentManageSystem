//#include <vld.h>
#include <time.h>
#include "menu.h"
/*
//�����ڴ�й©��
#define CRTDBG_MAP_ALLOC
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
*/
#if 0
//���Զ�̬������
void Demo0()
{
	Chart c;
	IndexList stulist;
	IndexList stulist2;
	IndexList stulist3;
	TitleList titlelist;

	//��ʼ��һ��3*5�ı�
	InitNewChart(&c, 5, 3, "����", 5, "�༶", 5, "����", 5);

	//д������
	strcpy(c.Chart[0][0], "����");
	strcpy(c.Chart[1][0], "����");
	strcpy(c.Chart[2][0], "����");
	strcpy(c.Chart[3][0], "���");
	strcpy(c.Chart[4][0], "����");
	strcpy(c.Chart[0][1], "303");
	strcpy(c.Chart[1][1], "302");
	strcpy(c.Chart[2][1], "303");
	strcpy(c.Chart[3][1], "301");
	strcpy(c.Chart[4][1], "301");
	strcpy(c.Chart[0][2], "1");
	strcpy(c.Chart[1][2], "2");
	strcpy(c.Chart[2][2], "3");
	strcpy(c.Chart[3][2], "4");
	strcpy(c.Chart[4][2], "5");

	FillList(&titlelist, 3);
	titlelist.list[0] = 1;
	titlelist.list[1] = 0;
	titlelist.list[2] = 2;

	FillList(&stulist, 5);

	Display_Chart(&c, NULL, NULL, DISPLAY_HIDENUMBER);
	/*********************************************************/
	//�������
	//��������������
	printf("��������������\n");
	Sort(&c, &stulist, SHI(&c, "����"), SORT_ASCENDING);
	Display_Chart(&c, &stulist, NULL, DISPLAY_HIDENUMBER);			//��ʾ����
	printf("\n");

	//�����Ž�������
	printf("�����Ž�������\n");
	Sort(&c, &stulist, SHI(&c, "����"), SORT_DESCENDING);
	Display_Chart(&c, &stulist, NULL, DISPLAY_HIDENUMBER);			//��ʾ����
	/*********************************************************/
	//ɸѡ����
	FillList(&stulist2, 10);			//Listʹ��֮ǰҪ�Ƚ��г�ʼ��
	FillList(&stulist3, 10);			//Listʹ��֮ǰҪ�Ƚ��г�ʼ��

	Search(&c, &stulist, &stulist2, SHI(&c, "����"), "����");

	if (stulist2.listCount > 0) {
		printf("\n�ҵ�����Ϊ������ѧ������:\n");
		Display_Chart(&c, &stulist2, NULL, DISPLAY_HIDENUMBER);
	}
	else printf("\nû���ҵ��й�ѧ������Ϣ\n");

	Search(&c, &stulist2, &stulist3, SHI(&c, "�༶"), "303");		//��֮ǰ��������Ļ������������༶Ϊ303��ѧ��
	if (stulist3.listCount > 0)
	{
		printf("\n�ҵ�����Ϊ������ѧ������:\n");
		Display_Chart(&c, &stulist3, NULL, DISPLAY_HIDENUMBER);
	}
	else printf("\nû���ҵ��й�ѧ������Ϣ\n");
	/**********************************************************/
	//�����ʱ������������ŷ��ں��治����,û��ϵ,���Խ��е���

	printf("\n���µ�����֮������\n");
	InitList(&titlelist, 3, SHI(&c, "����"), SHI(&c, "�༶"), SHI(&c, "����"));
	Display_Chart(&c, &stulist, &titlelist, DISPLAY_HIDENUMBER);

	printf("\n�ٰ�������������һ��\n");
	Sort(&c, &stulist, SHI(&c, "����"), SORT_ASCENDING);
	Display_Chart(&c, &stulist, &titlelist, DISPLAY_HIDENUMBER);

	//������Ϻ��ͷ��ڴ�,��ָֹ�붪ʧ����ڴ�й¶
	FreeList(&stulist);
	FreeList(&stulist2);
	FreeList(&stulist3);
	FreeList(&titlelist);
	FreeChart(&c);
}

//���Դ�˫�ļ��ж�ȡ����
void demo1()
{
	InfoMap im = { 0 }, im2 = { 0 };
	ReadFromTwoFile("ZCHtestFile\\stu_param.txt", "ZCHtestFile\\Stu_info.txt", ChartHead[0]);

	//����ѧԺ����ΪѧԺ����
	ReadMapFile("ZCHtestFile\\C_info.txt", &im);
	Translate(ChartHead[0], SHI(ChartHead[0], "ѧԺ����"), &im);
	//�����Ա�
	ReadMapFile("ZCHtestFile\\S_info.txt", &im2);
	Translate(ChartHead[0], SHI(ChartHead[0], "�Ա�"), &im2);

	Display_Chart(ChartHead[0], NULL, NULL, DISPLAY_HIDENUMBER);
	printf("%s\n", ChartHead[0]->ChartName);
	FreeMapStruct(&im);
	FreeMapStruct(&im2);

}

//����CreateNewLineЧ��
void test2()
{
	clock_t t1, t2, t3;
	t1 = clock();
	ReadFromTwoFile("ZCHtestFile\\stu_param2.txt", "ZCHtestFile\\Stu_info2.txt", ChartHead[0]);
	t2 = clock();
	CreateNewLine(ChartHead[0], 5, NULL);
	CreateNewLine(ChartHead[0], 5, NULL);
	CreateNewLine(ChartHead[0], 5, NULL);
	t3 = clock();
	printf("����ʱ:%ld\n", t3 - t1);
	printf("��ȡ�ļ���ʱ:%ld\n", t2 - t1);
	printf("����������ʱ:%ld\n", t3 - t2);
	//Display_Chart(ChartHead[0], NULL, NULL, DISPLAY_HIDENUMBER);

}

void test3()
{
	//void SearchBy(const char* SearchTitle);
	//void Search_M();
	//void SearchBy(const char* SearchTitle);
	//printf("%s",GetFileName("C:\\456\\123.txt"));
	NewChartSet(1);

	//ReadFromTwoFile("ZCHtestFile\\stu_param2.txt", "ZCHtestFile\\Stu_info2.txt", ChartHead[0]);

	printf("%d", ReadFromTwoFile("ZCHtestFile\\123_p.txt", "ZCHtestFile\\123_data.txt", ChartHead[0]));
	NewListSet(5, LISTTYPE_INDEXLIST);
	NewListSet(5, LISTTYPE_TITLELIST);
	FillList(TitleListHeadSet[0], 5);
	FillList(IndexListHeadSet[0], ChartHead[0]->UsedLines);
	FillList(IndexListHeadSet[1], ChartHead[0]->UsedLines);

	WriteToTwoFile_Chart("123_p.txt", "123_data.txt", ChartHead[0]);
	//Search_M();
}

//�����ļ���д��
void test4()
{
	NewChartSet(5);
	printf("%d", ReadFromTwoFile("ZCHtestFile\\123_p.txt", "ZCHtestFile\\123_data.txt", ChartHead[0]));
	NewListSet(5, LISTTYPE_INDEXLIST);
	NewListSet(5, LISTTYPE_TITLELIST);
	FillList(IndexListHeadSet[0], 20);
	FillList(TitleListHeadSet[0], 8);
	WriteToTwoFileByList("123_p.txt", "123_data.txt", ChartHead[0], IndexListHeadSet[0], TitleListHeadSet[0]);
}

void test5()
{
	NewChartSet(5);
	printf("%d\n", ReadFromTwoFile("ZCHtestFile\\123_p.txt", "ZCHtestFile\\123_data.txt", ChartHead[0]));
	NewListSet(5, LISTTYPE_INDEXLIST);
	NewListSet(5, LISTTYPE_TITLELIST);
	FillList(IndexListHeadSet[0], 20);
	FillList(TitleListHeadSet[0], 8);
	WriteToBinFile_Chart("1.dat", "1234", ChartHead[0]);
	FreeChart(ChartHead[0]);
	//ReadFromBinFile("1.dat", " ", ChartHead[1]);
	//Display_Chart(ChartHead[1], IndexListHeadSet[0], TitleListHeadSet[0], DISPLAY_HIDENUMBER);
}
//���ԴӶ������ļ���ȡ����
void test6()
{
	NewChartSet(5);
	printf("%d\n", ReadFromBinFile("1.dat", "1234", ChartHead[0]));
	NewListSet(5, LISTTYPE_INDEXLIST);
	NewListSet(5, LISTTYPE_TITLELIST);
	FillList(IndexListHeadSet[0], 20);
	FillList(TitleListHeadSet[0], 8);
	Display_Chart(ChartHead[0], IndexListHeadSet[0], TitleListHeadSet[0], DISPLAY_HIDENUMBER);
}

//���ܽ��ܲ���
void test7()
{
	ErrVal EncryptChar(const char *ResultString, const char *SourceString, int size, const char* PassWord);
	char str1[100] = "�ų���";
	char str2[100] = "";
	printf("%s'%d\n", str1, strlen(str1));
	EncryptChar(str2, str1, strlen(str1), "123");
	printf("%s'%d\n", str2, strlen(str2));
	EncryptChar(str2, str2, strlen(str1), "123");
	printf("%s'%d\n", str2, strlen(str2));
	/*
	Encrypt(&a1, &a2,sizeof(int), "123");
	printf("%d\n",a1);
	Encrypt(&a1, &a1, sizeof(int),"123");
	printf("%d\n", a1);*/
}

/*
������ʾ�˵�
*/
void test8()
{
	NewChartSet(5);
	NewListSet(5, LISTTYPE_INDEXLIST);
	NewListSet(5, LISTTYPE_TITLELIST);
	//void Display_M();
	//Display_M();
}

//�����Ӳ˵�
void test9()
{
	//InitALL();
	NewChartSet(5);
	printf("%d\n", ReadFromBinFile("1.dat", "1234", ChartHead[0]));
	NewListSet(5, LISTTYPE_INDEXLIST);
	NewListSet(5, LISTTYPE_TITLELIST);
	FillList(IndexListHeadSet[0], 20);
	FillList(TitleListHeadSet[0], 8);
	while (1) {
		COMMAND_CLEAR();
		printf(DELIMS_LINE);
		Menu_DisplaySubMenu();
		Menu_DisplaySubMenu_Search();
		printf(DELIMS_LINE);
		Event_Input();
	}
	system("pause");
}
#endif
//ʵ���е����˵�,����Ϊ������
void testmain()
{
	InitALL();
	MainMenu();
	FreeAll();
}

void test10()
{
	//void SubMenu_Search();
	//InitALL();
	//ReadFromBinFile("1.dat", "1234", ChartHead[0]);

	//SubMenu_Display();

	//printf("%s", IndexListHeadSet[0]->ListName);
	//FillList(IndexListHeadSet[0],50);
	FreeAll();
}

void test11()
{
	NewChartSet(5);
	NewListSet(5, LISTTYPE_INDEXLIST);
	NewListSet(5, LISTTYPE_TITLELIST);
	ReadFromTwoFile("Windows�����ļ�\\stu_param.txt", "Windows�����ļ�\\stu_info.txt", ChartHead[0]);
	InitList(IndexListHeadSet[0], 12, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, 11);

	Display_Page(ChartHead[0], IndexListHeadSet[0], NULL, DISPLAY_SHOWNUMBER, 4, 0);
	system("pause");
	Display_Page(ChartHead[0], IndexListHeadSet[0], NULL, DISPLAY_SHOWNUMBER, 4, 1);
	system("pause");
	Display_Page(ChartHead[0], IndexListHeadSet[0], NULL, DISPLAY_SHOWNUMBER, 4, 2);
	system("pause");
	Display_Page(ChartHead[0], IndexListHeadSet[0], NULL, DISPLAY_SHOWNUMBER, 4, 3);
}

//��������
/*
void test12()
{
	int Part(Chart *OperateChart, IndexList *OperateList, int BaseTitleIndex, int Mode, int Low, int High);
	NewChartSet(5);
	NewListSet(5, LISTTYPE_INDEXLIST);
	//NewListSet(5, LISTTYPE_TITLELIST);
	
	ReadFromTwoFile("Windows�����ļ�\\stu_param2.txt", "Windows�����ļ�\\stu_info2.txt", ChartHead[0]);
	FillList(IndexListHeadSet[0], ChartHead[0]->UsedLines);

	for (int a = 0; a < IndexListHeadSet[0]->listCount; a++)
	{
		printf("%d ", IndexListHeadSet[0]->list[a]);
	}
	printf("\n\n");

	Sort(ChartHead[0], IndexListHeadSet[0], 0, 1);

	for (int a = 0; a < IndexListHeadSet[0]->listCount; a++)
	{
		printf("%d ", IndexListHeadSet[0]->list[a]);
	}
	printf("\n");

	Display_Chart(ChartHead[0], IndexListHeadSet[0], NULL, 1);
	system("pause");
}
*/

//����GetListFromStringViaList
void test13()
{
	char str[] = "1-3 5 4";
	NewListSet(3, LISTTYPE_INDEXLIST);
	InitList(IndexListHeadSet[0], 5, 3, 2, 1, 4, 6);
	FillList(IndexListHeadSet[1], 5);
	GetListFromStringViaList(str,5, IndexListHeadSet[1], IndexListHeadSet[0]);
	for (int a = 0; a < 5; a++)
	{
		printf("%d ", IndexListHeadSet[1]->list[a]);
	}
	printf("\n");

}

int main()
{
	//_CrtSetBreakAlloc(65);
	//_CrtSetDbgFlag(_CRTDBG_CHECK_ALWAYS_DF |_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//NewChartSet(5);

	//char *ss = malloc(sizeof(char) * 10);
	//ss[-1] = 45;


	//Demo();
	//test1();
	//test2();
	//test3();
	//test4();
	//test5();
	//test6();
	//test7();
	//test8();
	//test9();
	//testmain();
	//test10();
	//test11();
	//test12();
	test13();
	//FreeChartSet();
	//FreeListSet(0);
	//FreeListSet(1);
	system("pause");

}



