#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ADDITIONAL 10		//当需要重新分配内存时,一次增加十个行


//错误代码
#define SUCCESS 0
#define ERR_OPENFILE 1
#define ERR_NOTSTANDARDFILE 2
#define ERR_MEMORYNOTENOUGH 3

//类型别名
typedef int ErrVal;
typedef char*** Chart_t;
typedef char** ChartPiece_t;

//定义一个表结构
typedef struct
{
	//表
	Chart_t Chart;				//整个表的入口首地址

	//标题
	int TitleCount;				//存储标题的个数
	ChartPiece_t ChartTitle;	//存储每个标题的字符(每个标题不得超过31个字母)
	int* ChartLimits;			//存储每一个标题下的单元格里的字符串的最大长度

	//行
	int AllocatedLines;			//表已分配的大小(此值大于等于UsedLines)(已分配但未使用的行未申请内存)
	int UsedLines;				//在表中实际被使用的行
	int HadInit;				//记录这个表是否已经被初始化
} Chart;


/*
IndexList是一个索引结构体,它里面的list是一个int数组,数组的每一个元素是单元行在Chart表中的实际顺序的下标(从0开始计数),在调用display时,影响数据输出的顺序的是list中下标的顺序,而与行在数组的位置无关
Title也是一个索引结构体,它里面的list是一个int数组,数组的每一个元素是标题在Chart表中的下标,在调用display时,此索引也同样可以影响display显示的标题和顺序
警告:在使用时一定要与相应的表匹配,否则结果不正确.
*/
//#####要确保listCount<UsedLines
typedef struct
{
	int *list;			//数组,里面的值存储的是指定表中的实际行(或列)的数组下标
	int listCount;		//记录数组的个数
} IndexList,TitleList;


ErrVal ReadFromFile(char *FileName, Chart *OperateChart);
ErrVal CreateNewUnit(Chart *OperateChart, int CreateCount, char(*NewTitleSet)[32], int *NewTitleLimits);
ErrVal Display_Chart(Chart *OperateChart, IndexList *ShowLines, TitleList *ShowTitle, int Mode);

/*
以下函数未实现
*/
//ErrVal InitChart(Chart *OperateChart,int LinesCount,int TitleCount);
//
//ErrVal Display_Piece(Chart *OperateChart, int ShowLineIndex, TitleList ShowTitle);
