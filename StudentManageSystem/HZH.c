#include "HZH.h"
#include <stdlib.h>

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


