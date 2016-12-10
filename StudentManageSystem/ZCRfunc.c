#include <stdio.h>
#include <stdlib.h>
#include "HZHfunc.h"
//#include "DataBase.h"

#ifdef __APPLE__ && __MACH__
#define COMMAND_CLEAR() system("clear")
#else
#define COMMAND_CLEAR() system("cls")
#endif

#define DELIMS_LINE " ********************************************\n"


/*
暂时的代码
*/

//以上代码将会转移到DataBase中

int CurrentChartIndex=0;
int CurrentIndexListIndex=0;
int CurrentTitleListIndex=0;

void SearchBy(const char* SearchTitle);
void Search_M();
void SearchBy(const char* SearchTitle);


void Search_M()
{
	int Choice=0;
	while(1)
	{
		COMMAND_CLEAR();
		printf(	
			DELIMS_LINE \
			"               查找学生信息\n" \
			DELIMS_LINE \
			"当前操作表:%s\n"\
			"当前操作名单:%s\n"\
			DELIMS_LINE \
			"1.按姓名进行查找\n"\
			"2.按学号进行查找\n"\
			"3.筛选查找\n"\
			"4.输出上一次的查找的结果\n"\
			"4.高级设置\n"\
			"0.返回上级菜单\n"\
			DELIMS_LINE,
			ChartHead[CurrentChartIndex]->ChartName,
			IndexListHeadSet[CurrentIndexListIndex]->ListName
			);
		scanf("%d",&Choice);
		switch(Choice)
		{
		case 1:
			SearchBy("姓名");
			break;
		case 2:
			SearchBy("学号");
			break;
		case 3:
			TitleChoicer();
			break;
		}

	}
}

/*
根据提供的字段进行搜索
*/
void SearchBy(const char* SearchTitle)
{
	static int ShowChartList=0,ShowListList=0;
	int a,b;
	char Choice[3];
	int Choice1;
	char InputBuffer[256];
	while (1){
		COMMAND_CLEAR();
		printf(
			DELIMS_LINE \
			"                查找学生信息\n"
			DELIMS_LINE \
			);
		printf(" %s 选择要进行操作的表:%s(%d)\n",ShowChartList?"-[C]":"+[C]",ChartHead[CurrentChartIndex]->ChartName?ChartHead[CurrentChartIndex]->ChartName:"未命名",CurrentChartIndex);
		if (ShowChartList)
		{
			for (a=0;a<ChartCount;a++)
				printf("   [C#%d]. %s\n",a+1,ChartHead[a]->ChartName);
		}
		printf(" %s 选择要进行操作的名单:%s(%d)\n",ShowListList?"-[L]":"+[L]",IndexListHeadSet[CurrentIndexListIndex]->ListName?IndexListHeadSet[CurrentIndexListIndex]->ListName:"未命名",CurrentIndexListIndex);
		if (ShowListList)
		{
			for (a=0;a<IndexListCount;a++)
				printf("   [L#%d]. %s\n",a+1,IndexListHeadSet[a]->ListName);
		}
		//printf(" %s 选择要进行操作的")
		printf(DELIMS_LINE);
		printf(
			" [1]. 开始查找\n"\
			" [0]. 返回上级菜单\n"\
			);
		printf(DELIMS_LINE);
		scanf("%2s",&Choice);
		switch (Choice[0])
		{
		case 'c':
		case 'C':
			if (Choice[1]=='#')
			{
				scanf("%d",&Choice1);
				if (Choice1>=0&&Choice1<ChartCount)
					CurrentChartIndex=Choice1;
			} else ShowChartList=!ShowChartList;
			break;
		case 'l':
		case 'L':
			if (Choice[1]=='#')
			{
				scanf("%d",&Choice1);
				if (Choice1>=0&&Choice1<IndexListCount)
					CurrentIndexListIndex=Choice1;
			} else ShowListList=!ShowListList;
			break;
		case '0':
			return ;
			break;
		case '1':
			printf("请输入搜索的内容:");
			scanf("%s",InputBuffer);
			a=SaveTo();
			if (!Search(ChartHead[CurrentChartIndex],IndexListHeadSet[CurrentIndexListIndex],IndexListHeadSet[a],SHI(ChartHead[CurrentChartIndex],SearchTitle),InputBuffer));
			printf("%s为%s的结果有:\n",SearchTitle,InputBuffer);
			Display_Chart(ChartHead[CurrentChartIndex],IndexListHeadSet[a],TitleListHeadSet[CurrentTitleListIndex],DISPLAY_HIDENUMBER);
			printf("找到%d个结果\n",IndexListHeadSet[a]->listCount);
			system("pause");
			break;
		}
	}
}

/*
标题选择器
*/
int TitleChoicer()
{
	return 0;
}

/*
用于询问List的保存位置
*/
int SaveTo()
{
	int a,b=-1;
	printf(" 请问你需要在何处存放结果\n");
	printf("请输入一个数字进行选择\n");
	for (a=0;a<IndexListCount;a++)
		printf("  %d. %s\n",a+1,IndexListHeadSet[a]->ListName);
	while (b<1||b>IndexListCount)
	scanf("%d",&b);
	return b-1;
}
