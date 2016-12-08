#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "DataBase.h"

#define CRTDBG_MAP_ALLOC    
#include <stdlib.h>  
#include <crtdbg.h>

#include "HZHfunc.h"

//测试创建表
void Demo()
{
	Chart c;
	int a;
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
    titlelist.list[0]=1;
    titlelist.list[1]=0;
    titlelist.list[2]=2;
    
	FillList(&stulist, 5);

	Display_Chart(&c,NULL,NULL,DISPLAY_HIDENUMBER);
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

void test1()
{
	InfoMap im = { 0 }, im2 = {0};

	//初始化表
	NewChart(5);
	/*
	InitNewChart(ChartHead[0], 5, 3, "姓名", 5, "班级", 5, "座号", 5);
	//写入数据
	strcpy(ChartHead[0]->Chart[0][0], "张三");
	strcpy(ChartHead[0]->Chart[1][0], "李四");
	strcpy(ChartHead[0]->Chart[2][0], "王五");
	strcpy(ChartHead[0]->Chart[3][0], "冯八");
	strcpy(ChartHead[0]->Chart[4][0], "张三");
	strcpy(ChartHead[0]->Chart[0][1], "303");
	strcpy(ChartHead[0]->Chart[1][1], "302");
	strcpy(ChartHead[0]->Chart[2][1], "303");
	strcpy(ChartHead[0]->Chart[3][1], "301");
	strcpy(ChartHead[0]->Chart[4][1], "301");
	strcpy(ChartHead[0]->Chart[0][2], "1");
	strcpy(ChartHead[0]->Chart[1][2], "2");
	strcpy(ChartHead[0]->Chart[2][2], "3");
	strcpy(ChartHead[0]->Chart[3][2], "4");
	strcpy(ChartHead[0]->Chart[4][2], "5");
	*/
	ReadFromTwoFile("ZCHtestFile\\stu_param.txt", "ZCHtestFile\\Stu_info.txt", ChartHead[0]);

	//翻译学院代码为学院名称
	ReadMapFile("ZCHtestFile\\C_info.txt", &im);
	Translate(ChartHead[0],SHI(ChartHead[0],"学院名称"),&im);

	//翻译性别
	ReadMapFile("ZCHtestFile\\S_info.txt", &im2);
	Translate(ChartHead[0], SHI(ChartHead[0], "性别"), &im2);


	Display_Chart(ChartHead[0], NULL, NULL, DISPLAY_HIDENUMBER);
	printf("%s\n", ChartHead[0]->ChartName);

}

int main()
{
	//Demo();
	test1();
	//int *a=(int*)malloc(sizeof(int)*10);
	//*a=0;
	//int a[10]={1,2,3};
	//printf("%d",*a);

	_CrtDumpMemoryLeaks();
	system("pause");

}



