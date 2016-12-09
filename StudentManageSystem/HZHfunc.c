﻿#define _CRT_SECURE_NO_WARNINGS
#define OUTSCANFAGAIN(obj, dline, uline) {if(obj<=dline||obj>=uline){printf("输入错误,请重新输入\n");continue;}}


#include <stdlib.h>
#include <stdio.h>
#include "DataBase.h"
#include "HZHfunc.h"



int ChartCount;
int AlloctedChartCount;
Chart ** ChartHead;

//表控制函数
ErrVal NewChart(int CreateCount)
{
    
	int a;
	Chart** NewChartSet; //原来的表集
	int NewChartCount = ChartCount + CreateCount;
	if (CreateCount <= 0)
		return ERR_ILLEGALPARAM;

	if (NewChartCount <= ChartCount)
		return ERR_ILLEGALPARAM;

	if (AlloctedChartCount <= 0)
	{
		//全新初始化表
		NewChartSet = (Chart**)malloc(sizeof(Chart*)*CreateCount);
		if (!NewChartSet)
			return ERR_MEMORYNOTENOUGH;
		for (a = 0; a < CreateCount; a++)
		{
			NewChartSet[a] = (Chart*)calloc(sizeof(Chart), sizeof(Chart));
			if (!NewChartSet[a])
			{
				for (a--; a >= 0; a--)
					free(NewChartSet[a]);
				free(NewChartSet);
				return ERR_MEMORYNOTENOUGH;
			}
		}
	}
	else if (NewChartCount <= AlloctedChartCount)
	{
		//已分配空间新建表
		NewChartSet = (Chart**)malloc(sizeof(Chart*)*NewChartCount);
		if (!NewChartSet)
			return ERR_MEMORYNOTENOUGH;
		for (a = 0; a < ChartCount; a++)
		{
			NewChartSet[a] = ChartHead[a];
		}
		for (a = ChartCount; a < NewChartCount; a++)
		{
			NewChartSet[a] = (Chart*)calloc(sizeof(Chart), sizeof(Chart));
			if (!NewChartSet[a])
			{
				if (a != ChartCount)
					for (a--; a >= ChartCount; a--)
						free(NewChartSet[a]);
				free(NewChartSet);
				return ERR_MEMORYNOTENOUGH;;
			}
		}
	}
	else {
		//增量初始化
		NewChartSet = (Chart**)malloc(sizeof(Chart*)*NewChartCount);
		if (!NewChartSet)
			return ERR_MEMORYNOTENOUGH;
		for (a = 0; a < ChartCount; a++)
		{
			NewChartSet[a] = ChartHead[a];
		}
		for (; a < NewChartCount; a++)
		{
			NewChartSet[a] = (Chart*)malloc(sizeof(Chart));
			if (!NewChartSet[a])
			{
				if (a != ChartCount)
					for (a--; a >= ChartCount; a--)
					{
						free(NewChartSet[a]);
					}
				free(NewChartSet);
				return ERR_MEMORYNOTENOUGH;
			}
		}
	}
	free(ChartHead);
	ChartHead = NewChartSet;
	AlloctedChartCount = NewChartCount;
	ChartCount = NewChartCount;
	return SUCCESS;
}

void ReadFromTwoFile_M() {

    
    int i, Val;
    int Fileindex, ReadFileNum = 1;
    char ParamFileName[32], DataFileName[32];
    

    printf("请输入读入文件的数量,若输入0则退出\n");
    scanf("%d", &ReadFileNum);
    NewChart(ReadFileNum);
    for (i = 0; i<ReadFileNum; i++) {
        
        printf("请输入存储各单元名字的文件\n");
        scanf("%s", ParamFileName);
        printf("请输入存储各单元资料的文件\n");
        scanf("%s", DataFileName);
        printf("请输入保存的表的编号（1—%d）\n", ReadFileNum);
        scanf("%d", &Fileindex);
        
        Val = ReadFromTwoFile(ParamFileName, DataFileName, ChartHead[Fileindex-1]);
        if (Val != 0) {
            printf("错误代码:%d,读入失败\n", Val);
            return;
        }
        printf("读入成功\n");
        return;
    }
}


void ReadFromFile_M() {
    
    
    int i;
    int Val, ReadFileNum;
    char FileName[16];
    
    printf("请输入所需读取文件的数量,输入0退出\n");
    while(scanf("%d", &ReadFileNum), ReadFileNum!=0) {
        NewChart(ReadFileNum);
        
        printf("请输入文件名字(请使用空格将文件隔开，若文件不在此文件夹，请写上绝对地址。"
               "如~//username/Desktop/xxx.txt)\n");
        
        for (i = 0; i < ReadFileNum;) {
            printf("表%d:\n", i+1);
            scanf("%s", FileName);
            
            Val = ReadFromFile(FileName, ChartHead[i]);
            if (Val != 0) {
                printf("错误代码:%d,读取文件出现错误。重新输入请按1,输入其他键则退出\n", Val);
                int Again;
                scanf("%d", &Again);
                if (Again == 1) {
                    continue;
                }
                else
                    return;
                    
            }
            i++;
        }
    }
    return;
    
}


void SortList_M() {
    int Mode = 0, SortMode = 1, ChartId;
    int i;
    int k;
    
    printf("1.按照姓名排序\n"
           "2.按照平均成绩排序\n"
           "3.按照任意条件排序\n"
           "0.退出\n");
    while(scanf("%d", &Mode),
          Mode != 0) {
        if (Mode<=0||Mode>=3) {
            printf("输入错误\n");
            continue;
        }
        printf("请输入所需排序的表格\n");
        
        
        scanf("%d", &ChartId);
        printf("排序方法:\n"
               "1.升序\n"
               "2.降序\n");
        scanf("%d", &SortMode);
        for (i = 0; i<ChartCount; i++) {
            printf("%d.%s\n", i, ChartHead[ChartId]->ChartTitle[i]);
        }
        scanf("%d", &k);
        
        
        switch (Mode) {
            case 1:
                Sort(ChartHead[ChartId], NULL, SHI(ChartHead[ChartId], ChartHead[ChartId]->ChartTitle[k]), SortMode-1);
                break;

//            case 2:
////                Sort(ChartHead[ChartId], <#IndexList *OperateList#>, <#int BaseTitleIndex#>, <#int Mode#>);
//                break;
//
//            case 3:
//                <#statements#>
//                break;
            
//            case 0:
//                <#statements#>
//                break;
        }
        
        
    }
    
    
}


//for (i = 0; i<ChartHead[0]->TitleCount; i++) {
//    atoi(ChartHead[0]->Chart[0][SHI(ChartHead[0],"成绩1")]);//第一个表里 的第一个同学的第一个成绩
//}





