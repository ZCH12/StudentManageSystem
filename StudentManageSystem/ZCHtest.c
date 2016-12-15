//#include <vld.h>
#include <time.h>
#include "menu.h"
/*
//测试内存泄漏用
#define CRTDBG_MAP_ALLOC
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
*/
#if 0
//测试动态创建表
void Demo0()
{
	Chart c;
	IndexList stulist;
	IndexList stulist2;
	IndexList stulist3;
	TitleList titlelist;

	//初始化一个3*5的表
	InitNewChart(&c, 5, 3, "姓名", 5, "班级", 5, "座号", 5);

	//写入数据
	strcpy(c.Chart[0][0], "张三");
	strcpy(c.Chart[1][0], "李四");
	strcpy(c.Chart[2][0], "王五");
	strcpy(c.Chart[3][0], "冯八");
	strcpy(c.Chart[4][0], "张三");
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
	//排序测试
	//按姓名升序排序
	printf("按姓名升序排序\n");
	Sort(&c, &stulist, SHI(&c, "姓名"), SORT_ASCENDING);
	Display_Chart(&c, &stulist, NULL, DISPLAY_HIDENUMBER);			//显示数据
	printf("\n");

	//按座号降序排序
	printf("按座号降序排序\n");
	Sort(&c, &stulist, SHI(&c, "座号"), SORT_DESCENDING);
	Display_Chart(&c, &stulist, NULL, DISPLAY_HIDENUMBER);			//显示数据
	/*********************************************************/
	//筛选查找
	FillList(&stulist2, 10);			//List使用之前要先进行初始化
	FillList(&stulist3, 10);			//List使用之前要先进行初始化

	Search(&c, &stulist, &stulist2, SHI(&c, "姓名"), "张三");

	if (stulist2.listCount > 0) {
		printf("\n找到姓名为张三的学生如下:\n");
		Display_Chart(&c, &stulist2, NULL, DISPLAY_HIDENUMBER);
	}
	else printf("\n没有找到有关学生的信息\n");

	Search(&c, &stulist2, &stulist3, SHI(&c, "班级"), "303");		//在之前搜索结果的基础上再搜索班级为303的学生
	if (stulist3.listCount > 0)
	{
		printf("\n找到姓名为张三的学生如下:\n");
		Display_Chart(&c, &stulist3, NULL, DISPLAY_HIDENUMBER);
	}
	else printf("\n没有找到有关学生的信息\n");
	/**********************************************************/
	//输出的时候如果觉得座号放在后面不合适,没关系,可以进行调整

	printf("\n重新调整列之后的输出\n");
	InitList(&titlelist, 3, SHI(&c, "座号"), SHI(&c, "班级"), SHI(&c, "姓名"));
	Display_Chart(&c, &stulist, &titlelist, DISPLAY_HIDENUMBER);

	printf("\n再按座号升序排序一下\n");
	Sort(&c, &stulist, SHI(&c, "座号"), SORT_ASCENDING);
	Display_Chart(&c, &stulist, &titlelist, DISPLAY_HIDENUMBER);

	//测试完毕后释放内存,防止指针丢失造成内存泄露
	FreeList(&stulist);
	FreeList(&stulist2);
	FreeList(&stulist3);
	FreeList(&titlelist);
	FreeChart(&c);
}

//测试从双文件中读取数据
void demo1()
{
	InfoMap im = { 0 }, im2 = { 0 };
	ReadFromTwoFile("ZCHtestFile\\stu_param.txt", "ZCHtestFile\\Stu_info.txt", ChartHead[0]);

	//翻译学院代码为学院名称
	ReadMapFile("ZCHtestFile\\C_info.txt", &im);
	Translate(ChartHead[0], SHI(ChartHead[0], "学院名称"), &im);
	//翻译性别
	ReadMapFile("ZCHtestFile\\S_info.txt", &im2);
	Translate(ChartHead[0], SHI(ChartHead[0], "性别"), &im2);

	Display_Chart(ChartHead[0], NULL, NULL, DISPLAY_HIDENUMBER);
	printf("%s\n", ChartHead[0]->ChartName);
	FreeMapStruct(&im);
	FreeMapStruct(&im2);

}

//测试CreateNewLine效率
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
	printf("总用时:%ld\n", t3 - t1);
	printf("读取文件用时:%ld\n", t2 - t1);
	printf("分配新行用时:%ld\n", t3 - t2);
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

//测试文件的写入
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
//测试从二进制文件读取数据
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

//加密解密测试
void test7()
{
	ErrVal EncryptChar(const char *ResultString, const char *SourceString, int size, const char* PassWord);
	char str1[100] = "张驰荣";
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
测试显示菜单
*/
void test8()
{
	NewChartSet(5);
	NewListSet(5, LISTTYPE_INDEXLIST);
	NewListSet(5, LISTTYPE_TITLELIST);
	//void Display_M();
	//Display_M();
}

//测试子菜单
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
//实验中的主菜单,将作为主函数
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
	ReadFromTwoFile("Windows测试文件\\stu_param.txt", "Windows测试文件\\stu_info.txt", ChartHead[0]);
	InitList(IndexListHeadSet[0], 12, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, 11);

	Display_Page(ChartHead[0], IndexListHeadSet[0], NULL, DISPLAY_SHOWNUMBER, 4, 0);
	system("pause");
	Display_Page(ChartHead[0], IndexListHeadSet[0], NULL, DISPLAY_SHOWNUMBER, 4, 1);
	system("pause");
	Display_Page(ChartHead[0], IndexListHeadSet[0], NULL, DISPLAY_SHOWNUMBER, 4, 2);
	system("pause");
	Display_Page(ChartHead[0], IndexListHeadSet[0], NULL, DISPLAY_SHOWNUMBER, 4, 3);
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
	test11();
	//FreeChartSet();
	//FreeListSet(0);
	//FreeListSet(1);
	system("pause");

}



