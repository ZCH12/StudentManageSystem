#include <stdlib.h>
#include <stdio.h>
#include "DataBase.h"




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

void ReadFromFile_M() {
    
    int i;
    int val, ReadFileNum;
    char FileName[16];
    
    printf("请输入所需读取文件的数量\n");
    scanf("%d", &ReadFileNum);
    NewChart(ReadFileNum);
    
    printf("请输入文件名字(请使用空格将文件隔开，若文件不在此文件夹，请写上绝对地址。如~//username/Desktop/xxx.txt)\n");
    
    
    for (i = 0; i < ReadFileNum;) {
        printf("表%d:", i+1);
        scanf("%s", FileName);
        val = ReadFromFile(FileName, ChartHead[i]);
        if (val != 0) {
            printf("%d,读取文件出现错误。重新输入请按1,输入其他键则退出\n",val);
            int again;
            scanf("%d", &again);
            if (again == 1) {
                continue;
            }
        }
        i++;
    }
    return;
}



//for (i = 0; i<ChartHead[0]->TitleCount; i++) {
//    atoi(ChartHead[0]->Chart[0][SHI(ChartHead[0],"成绩1")]);//第一个表里 的第一个同学的第一个成绩
//}





