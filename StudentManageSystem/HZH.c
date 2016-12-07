#include "HZH.h"
#include <stdlib.h>

int ChartCount;
Chart ** ChartHead;

//表控制函数
ErrVal NewChart(int CreateCount)
{
	int a;
	Chart** OldChartSet; //原来的表集
	int NewChartCount = ChartCount + CreateCount;
	if (CreateCount <= 0)
		return ERR_ILLEGALPARAM;

	if (NewChartCount <= ChartCount)
		return ERR_ILLEGALPARAM;

	if (ChartCount == 0 || !ChartHead)
	{
		//发现表还没初始化过,进行初始化
		ChartHead = (Chart**)malloc(sizeof(Chart*)*CreateCount);
		if (!ChartHead)
			return ERR_MEMORYNOTENOUGH;

		for (a = 0; a < CreateCount; a++)
		{
			ChartHead[a] = (Chart*)calloc(sizeof(Chart), sizeof(Chart));
			if (!ChartHead[a])
			{
				for (a--; a >= 0; a--)
					free(ChartHead[a]);
				free(ChartHead);
			}
			return ERR_MEMORYNOTENOUGH;
		}
	}
	else {
		OldChartSet = ChartHead;

		ChartHead = (Chart**)malloc(sizeof(Chart*)*NewChartCount);

		if (!ChartHead)
			return ERR_MEMORYNOTENOUGH;

		for (a = 0; a < ChartCount; a++)
			ChartHead[a] = OldChartSet[a];
		for (a = ChartCount; a < NewChartCount; a++)
		{
			ChartHead[a] = (Chart*)calloc(sizeof(Chart), sizeof(Chart));

			if (!ChartHead[a])
			{
				if (a != ChartCount)
					for (a--; a >= ChartCount; a--)
						free(ChartHead[a]);
				free(ChartHead);
			}
		}
	}
	return SUCCESS;
}


