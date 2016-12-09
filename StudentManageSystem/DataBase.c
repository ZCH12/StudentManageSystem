#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "DataBase.h"

/*
数据库库
Create By ZCR
2016-12-04

TODO:存在缺陷
没有初始化函数

*/

/*
初始化一个空表
以已有的表作为模板创建新表
*/

/*
在存档文件中,
第一行第一个数字代表学生的人数n,第二个数字代表每个人的属性的个数unit
第二行有unit组数据,每组数据由2个数据组成,分别是一个字符串(表头)和一个数字(代表这个单元的限制长度)
接下来有n组数据,一直到文件结尾,每组数据分别有unit个数据,他们的值就是表头定义的值
注意表头的长度限制为31个英文字符
*/


//全局变量
int ChartCount;				//已使用的表的个数
int AlloctedChartCount;		//表的指针数组
Chart ** ChartHead=(void*)0;			//已分配的表的个数


/*
从文件读取数据到指定表
File 要读取的文件路径
OperateChart 要用来存储读入的数据的表
//待重写
*/
ErrVal ReadFromFile(char *FileName, Chart *OperateChart)
{
	FILE *File;
	int Count, TitleCount;
	int a, b;				//循环变量
	char temp;				//用于扔掉无用的数据
	char **temp2, ***temp4;	//用于提高性能
	int *temp3;				//用于提高性能

	if (!OperateChart)
		return ERR_ILLEGALCHART;

	File = fopen(FileName, "r");
	if (!File)
		return ERR_OPENFILE;

	if (fscanf(File, "%d%d", &Count, &TitleCount) != 2)		//从文件读取两个参数,分别对应两个
	{
		fclose(File);
		return ERR_NOTSTANDARDFILE;
	}
	if (fgetc(File) != '\n')
		return ERR_NOTSTANDARDFILE;

	//对表进行初始化
	OperateChart->TitleCount = TitleCount;
	OperateChart->UsedLines = Count;
	//OperateChart->AllocatedLines = Count;

	//分配内存
	OperateChart->Chart = (Chart_t)malloc(sizeof(ChartPiece_t)*Count);
	OperateChart->ChartTitle = (ChartPiece_t)malloc(sizeof(ChartPiece_t)*TitleCount);
	OperateChart->ChartLimits = (int*)malloc(sizeof(int)*TitleCount);

	if (!(OperateChart->Chart&&OperateChart->ChartTitle&&OperateChart->ChartLimits))
	{
		fclose(File);
		if (OperateChart->Chart)
			free(OperateChart->Chart);
		if (OperateChart->ChartTitle)
			free(OperateChart->ChartTitle);
		if (OperateChart->ChartLimits)
			free(OperateChart->ChartLimits);
		return ERR_MEMORYNOTENOUGH;
	}

	temp2 = OperateChart->ChartTitle;
	temp3 = OperateChart->ChartLimits;
	for (a = 0; a < TitleCount; a++) {
		*temp2 = (char*)malloc(sizeof(char) * 32);
		if (!*temp2)
		{
			fclose(File);
			temp2--;
			for (a--; a >= 0; a--)
			{
				free(*temp2);
				temp2--;
			}
			free(OperateChart->ChartLimits);
			free(OperateChart->ChartTitle);
			free(OperateChart->Chart);
			return ERR_MEMORYNOTENOUGH;
		}
		//写入标题文字
		if (fscanf(File, "%s%c%d", *temp2, &temp, temp3) != 3)
		{
			fclose(File);
			for (; a >= 0; a--)
			{
				free(*temp2);
				temp2--;
			}
			free(OperateChart->ChartLimits);
			free(OperateChart->ChartTitle);
			free(OperateChart->Chart);
			return ERR_NOTSTANDARDFILE;
		}
		temp2++;
		temp3++;
	}
	if (fgetc(File) != '\n')
		return ERR_NOTSTANDARDFILE;

	//读取数据入表
	temp4 = OperateChart->Chart;
	temp3 = OperateChart->ChartLimits;
	for (a = 0; a < Count; a++) {
		temp4[0] = (ChartPiece_t)malloc(sizeof(char*)*TitleCount);
		if (!temp4[0])
		{
			fclose(File);
			temp2 = OperateChart->ChartTitle;
			for (a = 0; a < TitleCount; a++)
			{
				free(*temp2);
				temp2++;
			}
			free(OperateChart->ChartLimits);
			free(OperateChart->ChartTitle);
			free(OperateChart->Chart);
			return ERR_MEMORYNOTENOUGH;
		}
		for (b = 0; b < TitleCount; b++) {
			temp4[0][b] = (char*)malloc(sizeof(char)*(*temp3 + 1));
			if (!temp4[0][b])
			{
				fclose(File);
				//先释放只分配了一半的数组
				for (b--; b >= 0; b--)
					free(temp4[0][b]);

				//再释放前a轮已分配的数组
				for (temp4--, a--; a >= 0; a--)
				{
					for (b = 0; b < TitleCount; b++)
						free(temp4[0][b]);
					temp4--;
				}
				//释放表头
				temp2 = OperateChart->ChartTitle;
				for (a = 0; a < TitleCount; a++)
				{
					free(*temp2);
					temp2++;
				}
				free(OperateChart->ChartLimits);
				free(OperateChart->ChartTitle);
				free(OperateChart->Chart);
				return ERR_MEMORYNOTENOUGH;
			}

			if (fscanf(File, "%s", temp4[0][b]) != 1)
			{
				fclose(File);
				for (; a >= 0; a--)
				{
					for (b = 0; b < TitleCount; b++)
						free((*temp4)[b]);
					temp4--;
				}
				//释放表头
				temp2 = OperateChart->ChartTitle;
				for (a = 0; a < TitleCount; a++)
				{
					free(*temp2);
					temp2++;
				}
				free(OperateChart->ChartLimits);
				free(OperateChart->ChartTitle);
				free(OperateChart->Chart);
				return ERR_NOTSTANDARDFILE;
			}
		}
		if (fgetc(File) != '\n')
			return ERR_NOTSTANDARDFILE;
		temp4++;
	}
	OperateChart->HadInit = 1;
	fclose(File);
	return SUCCESS;
}

/*
从两个文件中读取信息
ParamFileName	表头与配置文件的路径
DataFileName	表中数据的路径
OperateChart 要用来存储读入的数据的表
*/
ErrVal ReadFromTwoFile(char *ParamFileName, char * DataFileName, Chart *OperateChart)
{
	FILE *File;		//当前正在读取的文件
	const char *Delimer = " \t\n\r";

	//读取操作使用的变量
	char* Line;		//存储一行的信息
	char* Piece;	//存储一个信息点
	int a, b, c;

	//表信息
	int LineCount;
	int TitleCount;
	int LineCharCount;

	//存储操作使用的变量
	ChartPiece_t tempChartPiece;
	int* tempChartTitleLimits;
	Chart_t tempChart;


	if (!OperateChart)
		return ERR_ILLEGALCHART;

	if (OperateChart->HadInit)
	{
		//已经初始化的表先释放
		FreeChart(OperateChart);
	}

	//开始读取表参数文件
	File = fopen(ParamFileName, "r");
	if (!File)
		return ERR_OPENFILE;
	Line = (char*)malloc(sizeof(char) * 20);
	if (!Line)
	{
		fclose(File);
		return ERR_MEMORYNOTENOUGH;
	}

	//读取行数和列数
	fgets(Line, 20, File);
	LineCount = atoi(strtok(Line, Delimer));
	TitleCount = atoi(strtok(NULL, Delimer));
	if (LineCount <= 0 || TitleCount <= 0)
	{
		fclose(File);
		free(Line);
		return ERR_NOTSTANDARDFILE;
	}

	//申请一个用于存放标题的数组
	tempChartPiece = (ChartPiece_t)malloc(sizeof(char*)*TitleCount);
	tempChartTitleLimits = (int*)malloc(sizeof(int)*TitleCount);
	if (!tempChartPiece || !tempChartTitleLimits)
	{
		fclose(File);
		free(Line);
		if (tempChartPiece)
			free(tempChartPiece);
		if (tempChartTitleLimits)
			free(tempChartTitleLimits);
		return ERR_MEMORYNOTENOUGH;
	}
	OperateChart->ChartTitle = tempChartPiece;

	free(Line);
	LineCharCount = 38 * TitleCount;	//计算下一行的最长长度
	Line = malloc(sizeof(char) * LineCharCount);
	fgets(Line, LineCharCount, File);	//读取下一行

	tempChartPiece[0] = (char*)malloc(sizeof(char) * 32);
	if (!tempChartPiece[0])
	{
		fclose(File);
		free(Line);
		free(tempChartPiece);
		free(tempChartTitleLimits);
		return ERR_MEMORYNOTENOUGH;
	}

	//读取第一个标题
	strcpy(tempChartPiece[0], strtok(Line, Delimer));
	tempChartTitleLimits[0] = atoi(strtok(NULL, Delimer));

	for (a = 1; a < TitleCount; a++)	//读取2到第LineCharCount标题
	{
		tempChartPiece[a] = (char*)malloc(sizeof(char) * 32);
		if (!tempChartPiece[a])
		{
			for (a--; a >= 0; a--)
				free(tempChartPiece[a]);
			fclose(File);
			free(Line);
			free(tempChartPiece);
			free(tempChartTitleLimits);
			return ERR_MEMORYNOTENOUGH;
		}
		Piece = strtok(NULL, Delimer);
		if (!Piece)
		{
			for (; a >= 0; a--)
				free(tempChartPiece[a]);
			fclose(File);
			free(Line);
			free(tempChartPiece);
			free(tempChartTitleLimits);
			return ERR_NOTSTANDARDFILE;
		}
		strcpy(tempChartPiece[a], Piece);

		Piece = strtok(NULL, Delimer);
		if (!Piece)
		{
			for (; a >= 0; a--)
				free(tempChartPiece[a]);
			fclose(File);
			free(Line);
			free(tempChartPiece);
			free(tempChartTitleLimits);
			return ERR_NOTSTANDARDFILE;
		}
		tempChartTitleLimits[a] = atoi(Piece);
	}
	free(Line);

	OperateChart->ChartTitle = tempChartPiece;
	OperateChart->ChartLimits = tempChartTitleLimits;

	//标题读取完毕,开始读取表
	LineCharCount = 0;		//开始计算数据行的一行的最长长度
	for (a = 0; a < TitleCount; a++)
		LineCharCount += tempChartTitleLimits[a];
	LineCharCount += TitleCount;

	Line = (char*)malloc(sizeof(char)*LineCharCount);
	if (!Line)
	{
		free(tempChartPiece);
		free(tempChartTitleLimits);
		return ERR_MEMORYNOTENOUGH;
	}

	File = fopen(DataFileName, "r");
	if (!File)
	{
		free(Line);
		free(tempChartPiece);
		free(tempChartTitleLimits);
		return ERR_OPENFILE;
	}

	tempChart = (Chart_t)malloc(sizeof(ChartPiece_t)*LineCount);
	if (!tempChart)
	{
		free(Line);
		fclose(File);
		free(tempChartPiece);
		free(tempChartTitleLimits);
		return ERR_MEMORYNOTENOUGH;
	}

	for (a = 0; a < LineCount; a++)
	{
		tempChart[a] = (ChartPiece_t)malloc(sizeof(char*)*TitleCount);
		if (!tempChart[a])
		{
			for (a--; a >= 0; a--)
			{
				for (b = 0; b < TitleCount; b++)
					free(tempChart[a][b]);
				free(tempChart[a]);
			}
			free(tempChart);
			free(Line);
			fclose(File);
			free(tempChartPiece);
			free(tempChartTitleLimits);
			return ERR_MEMORYNOTENOUGH;
		}
		fgets(Line, LineCharCount, File);

		//写入第一个值
		tempChart[a][0] = (char*)malloc(sizeof(char)*tempChartTitleLimits[0] + 1);
		if (!tempChart[a][0])
		{
			for (a--; a >= 0; a--)
			{
				for (b = 0; b < TitleCount; b++)
				{
					free(tempChart[a][b]);
				}
				free(tempChart[a]);
			}
			free(tempChart);
			free(Line);
			fclose(File);
			free(tempChartPiece);
			free(tempChartTitleLimits);
			return ERR_MEMORYNOTENOUGH;
		}
		Piece = strtok(Line, Delimer);
		if (!Piece)
		{
			for (a--; a >= 0; a--)
			{
				for (b = 0; b < TitleCount; b++)
				{
					free(tempChart[a][b]);
				}
				free(tempChart[a]);
			}
			free(tempChart);
			free(Line);
			fclose(File);
			free(tempChartPiece);
			free(tempChartTitleLimits);
			return ERR_NOTSTANDARDFILE;
		}
		strcpy(tempChart[a][0], Piece);

		//读取第二到第TitleCount个值
		for (b = 1; b < TitleCount; b++)
		{
			tempChart[a][b] = (char*)malloc(sizeof(char)*tempChartTitleLimits[b] + 1);
			Piece = strtok(NULL, Delimer);
			//printf("'%s'\n", Piece);
			if (!tempChart[a][b] || !Piece)
			{
				if (b != 0) {
					if (!tempChart[a][b]) {
						for (b--; b >= 0; b--)
							free(tempChart[a][b]);
					}
					else {
						for (; b >= 0; b--) {
							free(tempChart[a][b]);
						}
					}
					free(tempChart[a]);
				}
				for (a--; a >= 0; a--)
				{
					for (b = 0; b < TitleCount; b++)
					{
						free(tempChart[a][b]);
					}
					free(tempChart[a]);
				}
				free(tempChart);
				free(Line);
				fclose(File);
				free(tempChartPiece);
				free(tempChartTitleLimits);
				if (!Piece)
					return ERR_NOTSTANDARDFILE;
				else
					return ERR_MEMORYNOTENOUGH;
			}

			strcpy(tempChart[a][b], Piece);
		}
	}
	OperateChart->Chart = tempChart;
	fclose(File);
	free(Line);

	OperateChart->UsedLines = LineCount;
	OperateChart->TitleCount = TitleCount;
	OperateChart->HadInit = 1;

	//获取读取的文件的名字
	a = (int)strlen(ParamFileName);
	b = (int)strlen(DataFileName);
	Line = malloc(sizeof(char)*(a + b + 4));
	if (Line) {
		for (c = a - 1; c >= 0; c--)
			if (ParamFileName[c] == '/' || ParamFileName[c] == '\\')
				break;
		a = c + 1;
		for (c = b - 1; c >= 0; c--)
			if (DataFileName[c] == '/' || DataFileName[c] == '\\')
				break;
		b = c + 1;
		c = (int)strlen(ParamFileName + a);
		strcpy(Line, ParamFileName + a);
		strcpy(Line + c, " && ");
		strcpy(Line + c + 4, DataFileName + b);

		Piece = (char*)malloc(sizeof(char)*(strlen(Line) + 1));
		if (Piece) {
			strcpy(Piece, Line);
		}
		free(Line);
		OperateChart->ChartName = Piece;
	}
	else
		OperateChart->ChartName = NULL;

	return SUCCESS;
}

/*
读取映射文件
MapFileName 读取的映射文件的名称
MapStruct 映射信息存储的结构体
映射文件的格式为,直到文件结尾
Val		String
Val		String
...
*/
ErrVal ReadMapFile(char* MapFileName, InfoMap *MapStruct)
{
	FILE *File;
	char temp;
	int a;
	int Count = 0;
	if (!MapStruct)
		return ERR_ILLEGALPARAM;
	File = fopen(MapFileName, "r");
	if (!File)
		return ERR_OPENFILE;
	MapStruct->Val = (char**)malloc(sizeof(char*) * 100);
	MapStruct->String = (char**)malloc(sizeof(char*) * 100);
	if (!(MapStruct->Val&&MapStruct->String))
	{
		if (MapStruct->String)
			free(MapStruct->String);
		if (MapStruct->Val)
			free(MapStruct->Val);
		

		fclose(File);
		return ERR_MEMORYNOTENOUGH;
	}

	for (a = 0; a < 100; a++)
	{
		MapStruct->Val[a] = (char*)malloc(sizeof(char) * 4);
		MapStruct->String[a] = (char*)malloc(sizeof(char) * 20);
		if (!(MapStruct->Val[a] && MapStruct->String[a]))
		{
			fclose(File);
			if (MapStruct->Val[a])
				free(MapStruct->Val[a]);
			for (a--; a >= 0; a--)
			{
				free(MapStruct->Val[a]);
				free(MapStruct->String[a]);
			}
			free(MapStruct->Val);
			free(MapStruct->String);
			return ERR_MEMORYNOTENOUGH;
		}
		if (fscanf(File, "%s%c%s", MapStruct->Val[a], &temp, MapStruct->String[a]) != 3)
		{
			free(MapStruct->Val[a]);
			free(MapStruct->String[a]);
			break;
		}
		else
			Count++;
	}
	MapStruct->Count = Count;
	fclose(File);
	return SUCCESS;
}

ErrVal FreeMapStruct(InfoMap * MapStruct)
{
	int a;
	if (!MapStruct)
		return SUCCESS;
	for (a = 0; a < MapStruct->Count; a++)
	{
		free(MapStruct->String[a]);
		free(MapStruct->Val[a]);
	}
	free(MapStruct->String);
	free(MapStruct->Val);

	return SUCCESS;
}

/*
新增1个或多个新的标题
OperateChart 要进行操作的表
CreateCount 要新增的标题数目
NewTitleSet 新增的标题名称数组
NewTitleLimits 新增的标题的内容限制长度
*/
ErrVal CreateNewUnit(Chart *OperateChart, int CreateCount, char(*NewTitleSet)[32], int *NewTitleLimits)
{
	Chart_t NewChart;
	ChartPiece_t NewChartTitle;
	int* NewChartLimits;
	int LinesCount = OperateChart->UsedLines;
	int UnitCount = OperateChart->TitleCount, NewUnitCount;
	int a, b, c, d;
	char **temp;		//为了提高性能
	int  *temp3;

	if (CreateCount <= 0)
		return SUCCESS;

	if (!OperateChart)
		return ERR_ILLEGALCHART;

	if (LinesCount <= 0 || UnitCount <= 0)
		return ERR_UNINITIALIZEDCHART;

	NewUnitCount = OperateChart->TitleCount + CreateCount;

	//开始新建表头
	NewChartTitle = (ChartPiece_t)malloc(sizeof(char*)*NewUnitCount);
	NewChartLimits = (int*)malloc(sizeof(int)*NewUnitCount);
	if (!NewChartTitle)
		return ERR_MEMORYNOTENOUGH;

	if (!NewChartLimits)
	{
		free(NewChartTitle);
		return ERR_MEMORYNOTENOUGH;
	}
	//拷贝标题到新的表头
	temp = OperateChart->ChartTitle;
	temp3 = OperateChart->ChartLimits;
	for (a = 0; a < UnitCount; a++)
	{
		NewChartTitle[a] = *temp;
		NewChartLimits[a] = *temp3;
		temp++;
		temp3++;
	}

	temp3 = NewTitleLimits;
	for (a = UnitCount; a < NewUnitCount; a++)
	{
		NewChartTitle[a] = (char*)malloc(sizeof(char) * 32);
		if (!NewChartTitle[a])
		{
			for (a--; a >= UnitCount; a--)
				free(NewChartTitle[a]);
			free(NewChartTitle);
			free(NewChartLimits);
			return ERR_MEMORYNOTENOUGH;
		}
		NewChartLimits[a] = *temp3;
		strcpy(NewChartTitle[a], *NewTitleSet);
		temp3++;
		NewTitleSet++;
	}

	//开始新建一个新的表
	NewChart = (Chart_t)malloc(sizeof(ChartPiece_t)*OperateChart->UsedLines);
	if (!NewChart) {
		for (a = UnitCount; a < NewUnitCount; a++)
			free(NewChartTitle[a]);
		free(NewChartTitle);
		free(NewChartLimits);
		return ERR_MEMORYNOTENOUGH;
	}
	//对每个行分配单元格
	for (a = 0; a < LinesCount; a++)
	{
		NewChart[a] = (ChartPiece_t)malloc(sizeof(char*)*NewUnitCount);
		if (!NewChart[a])
		{
			//如果分配出现问题,则回收已分配内存,返回
			for (a--; a >= 0; a--)
				free(NewChart[a]);
			free(NewChart);
			for (a = UnitCount; a < NewUnitCount; a++)
				free(NewChartTitle[a]);
			free(NewChartTitle);
			free(NewChartLimits);
			return ERR_MEMORYNOTENOUGH;
		}

		//拷贝单元格
		temp = OperateChart->Chart[a];
		for (b = 0; b < OperateChart->TitleCount; b++)
			NewChart[a][b] = temp[b];

		//新的单元格进行分配内存
		//temp2 = OperateChart->TitleCount+CreateCount;
		for (c = 0; c < CreateCount&&b < NewUnitCount; b++, c++)
		{
			d = NewTitleLimits[c] + 1;
			d = sizeof(char)*(d > 2 ? d : 2);
			NewChart[a][b] = (char*)calloc(d, d);
			if (!NewChart[a][b])
			{
				for (b--; b >= 0; b--)			//删除这一轮分配的内存
					free(NewChart[a][b]);
				free(NewChart[a]);
				for (a--; a >= 0; a--)			//删除前几轮分配的内存
				{
					for (b = UnitCount; b < NewUnitCount; b++)
						free(NewChart[a][b]);
					free(NewChart[a]);
				}
				free(NewChart);

				for (a = UnitCount; a < NewUnitCount; a++)
					free(NewChartTitle[a]);
				free(NewChartTitle);
				free(NewChartLimits);
				return ERR_MEMORYNOTENOUGH;
			}
		}
	}
	//运行到这里,新的表就分配好了
	//把旧表内存释放掉,放入新表,就操作成功了
	for (a = 0; a < OperateChart->UsedLines; a++)		//删除旧表,
		free(OperateChart->Chart[a]);
	free(OperateChart->Chart);
	free(OperateChart->ChartTitle);
	free(OperateChart->ChartLimits);

	OperateChart->TitleCount = NewUnitCount;
	OperateChart->Chart = NewChart;
	OperateChart->ChartTitle = NewChartTitle;
	OperateChart->ChartLimits = NewChartLimits;
	return SUCCESS;
}

/*
在已有的表中创建CreateCount个新的行
OperateChart 要进行操作的表
CreateCount 新增的行数
NewList		新生成的行的下标存储的列表
*/
ErrVal CreateNewLine(Chart * OperateChart, int CreateCount, IndexList *NewList)
{
	int NewLine = OperateChart->UsedLines + CreateCount;
	Chart_t tempChart;
	int a, b;

	if (CreateCount <= 0)
		return ERR_ILLEGALPARAM;

	if (!OperateChart || OperateChart->TitleCount <= 0 || OperateChart->UsedLines <= 0||NewLine<=OperateChart->UsedLines)
		return ERR_ILLEGALCHART;

	/*
	if (NewLine <= OperateChart->AllocatedLines)
	{
		//内存充足
		tempChart = OperateChart->Chart;
		for (a = OperateChart->UsedLines; a < NewLine; a++)
		{
			for (b = 0; b < OperateChart->TitleCount; b++)
			{
				tempChart[a][b] = (char*)malloc(sizeof(char)*OperateChart->ChartLimits[b]);
				if (!tempChart[a][b])
				{
					for (b--; b >= 0; b--)
						free(tempChart[a][b]);
					free(tempChart[a]);

					for (a--; a >= 0; a--)
					{
						for (b = 0; b < OperateChart->TitleCount; b++)
							free(tempChart[a][b]);
						free(tempChart[a]);
					}
					return ERR_MEMORYNOTENOUGH;
				}

			}
		}
	}
	else
	{
		*/
		//内存不够,需要重新分配内存并复制
	tempChart = (Chart_t)malloc(sizeof(ChartPiece_t)*NewLine);
	if (!tempChart)
		return ERR_MEMORYNOTENOUGH;

	for (a = 0; a < OperateChart->UsedLines; a++)
		tempChart[a] = OperateChart->Chart[a];
	for (; a < NewLine; a++)
	{
		tempChart[a] = (ChartPiece_t)malloc(sizeof(ChartPiece_t)*OperateChart->TitleCount);
		if (!tempChart[a])
		{
			if (a != OperateChart->UsedLines) {
				for (a--; a >= OperateChart->UsedLines; a--)
				{
					for (b = 0; b < OperateChart->TitleCount; b++)
						free(tempChart[a][b]);
					free(tempChart[a]);
				}

			}
			free(tempChart);
			return ERR_MEMORYNOTENOUGH;
		}
		for (b = 0; b < OperateChart->TitleCount; b++)
		{
			tempChart[a][b] = (char*)calloc(sizeof(char)*OperateChart->ChartLimits[b], sizeof(char)*OperateChart->ChartLimits[b]);
			if (!tempChart[a][b])
			{
				for (b--; b >= 0; b--)
					free(tempChart[a][b]);
				if (a != OperateChart->UsedLines) {
					for (a--; a >= OperateChart->UsedLines; a--)
					{
						for (b = 0; b < OperateChart->TitleCount; b++)
							free(tempChart[a][b]);
						free(tempChart[a]);
					}
					free(tempChart);
					return ERR_MEMORYNOTENOUGH;
				}

			}
		}
	}
	free(OperateChart->Chart);
	OperateChart->Chart = tempChart;

	if (NewList)
	{
		//为列表赋值
		for (a = OperateChart->UsedLines, b = 0; a < NewLine&&b < NewList->AllocatedList; a++, b++)
			NewList->list[b] = a;
		NewList->listCount = b;
	}
	OperateChart->UsedLines = NewLine;
	return SUCCESS;
}

/*
初始化一个新的表,如果对已有内容的表进行初始化,将会破坏原表的内容
初始化后的表无内容
OperateChart	要进行初始化的表
LineCount		行数
TitleCount		列数
TitleList,TitleLimits	标题初始化列表(有TitleCount组)
*/
ErrVal InitNewChart(Chart *OperateChart, int LinesCount, int TitleCount, char* TitleList, int TitleLimits, ...)
{
	Chart_t tempChart = NULL;
	int* tempChartLimits;
	ChartPiece_t tempChartTitle = NULL;
	int a, b;
	va_list ap;
	int* temp;

	if (!OperateChart)
		return ERR_ILLEGALPARAM;
	if (LinesCount <= 0 || TitleCount <= 0)
		return ERR_ILLEGALPARAM;

	FreeChart(OperateChart);

	//初始化标题列表
	tempChartTitle = (ChartPiece_t)malloc(sizeof(char*)*TitleCount);
	if (!tempChartTitle)
		return ERR_MEMORYNOTENOUGH;
	tempChartLimits = (int*)malloc(sizeof(int)*TitleCount);
	if (!tempChartLimits)
	{
		free(tempChartTitle);
		return ERR_MEMORYNOTENOUGH;
	}
	*tempChartTitle = (char*)malloc(sizeof(char) * 32);
	if (!*tempChartTitle)
	{
		free(tempChartLimits);
		free(tempChartTitle);
		return ERR_MEMORYNOTENOUGH;
	}
	strcpy(*tempChartTitle, TitleList);		//写入第一个标题 
	*tempChartLimits = TitleLimits;			//写入第一个标题的内容长度限制

	//对第2-TitleCount个数进行处理
	va_start(ap, TitleLimits);

	for (a = 1; a < TitleCount; a++)
	{
		tempChartTitle[a] = (char*)malloc(sizeof(char) * 32);
		if (!tempChartTitle[a])
		{
			for (a--; a >= 0; a--)
				free(tempChartTitle[a]);		//释放已经分配的内存 
			free(tempChartLimits);
			free(tempChartTitle);
			return ERR_MEMORYNOTENOUGH;
		}
		strcpy(tempChartTitle[a], va_arg(ap, char*));
		tempChartLimits[a] = va_arg(ap, int);
	}

	//初始化表 
	tempChart = (Chart_t)malloc(sizeof(ChartPiece_t)*LinesCount);
	if (!tempChart)
	{
		for (a = 0; a < TitleCount; a++)
			free(tempChartTitle[a]);
		free(tempChartTitle);
		free(tempChartLimits);
		return ERR_MEMORYNOTENOUGH;
	}
	for (a = 0; a < LinesCount; a++)
	{
		tempChart[a] = (ChartPiece_t)malloc(sizeof(char*)*TitleCount);
		if (!tempChart[a])
		{
			for (a--; a >= 0; a--) {
				for (b = 0; b < TitleCount; b++)
					free(tempChart[a][b]);
				free(tempChart[a]);
			}
			free(tempChart);
			for (a = 0; a < TitleCount; a++)
				free(tempChartTitle[a]);
			free(tempChartTitle);
			free(tempChartLimits);
			return ERR_MEMORYNOTENOUGH;
		}
		temp = tempChartLimits;
		for (b = 0; b < TitleCount; b++)
		{
			tempChart[a][b] = (char*)calloc(sizeof(char)*(*temp), sizeof(char)*(*temp));
			if (!tempChart[a][b])
			{
				for (b--; b >= 0; b--)
					free(tempChart[a][b]);
				for (a--; a >= 0; a--) {
					for (b = 0; b < TitleCount; b++)
						free(tempChart[a][b]);
					free(tempChart[a]);
				}
				free(tempChart);
				for (a = 0; a < TitleCount; a++)
					free(tempChartTitle[a]);
				free(tempChartTitle);
				free(tempChartLimits);
				return ERR_MEMORYNOTENOUGH;
			}
			temp++;
		}
	}
	//初始化表的其他信息
	OperateChart->ChartName = NULL;
	OperateChart->Chart = tempChart;
	OperateChart->ChartLimits = tempChartLimits;
	OperateChart->ChartTitle = tempChartTitle;
	OperateChart->TitleCount = TitleCount;
	//OperateChart->AllocatedLines = LinesCount;
	OperateChart->UsedLines = LinesCount;
	OperateChart->HadInit = 1;

	return SUCCESS;
}

/*
把数字代码解释为字符串
OperateChart	进行操作的表
TitleIndex		进行转换的列
MapStruct		存储映射关系的表
*/
ErrVal Translate(Chart *OperateChart, int TitleIndex, InfoMap *MapStruct)
{
	int a, b;
	char *temp;
	char **list = MapStruct->String;
	char **Val = MapStruct->Val;
	for (a = 0; a < OperateChart->UsedLines; a++)
	{
		temp = OperateChart->Chart[a][TitleIndex];
		for (b = 0; b < MapStruct->Count; b++)
		{
			if (!strcmp(temp, Val[b]))
			{
				//匹配,进行翻译
				strcpy(temp, list[b]);
				break;
			}
		}
	}
	return SUCCESS;
}

/*
释放整个表所占的内存
OperateChart 要进行销毁的表,表销毁之后处于未初始化的状态,需要重新初始化才能使用
*/
ErrVal FreeChart(Chart *OperateChart)
{
	int a, b;
	if (!OperateChart)
	{
		return ERR_UNINITIALIZEDCHART;
	}
	if (OperateChart->HadInit != 1)
	{
		return ERR_UNINITIALIZEDCHART;
	}
	for (b = 0; b < OperateChart->TitleCount; b++)
	{
		free(OperateChart->ChartTitle[b]);
	}
	free(OperateChart->ChartTitle);

	for (a = 0; a < OperateChart->UsedLines; a++)
	{
		for (b = 0; b < OperateChart->TitleCount; b++)
		{
			free(OperateChart->Chart[a][b]);
		}
		free(OperateChart->Chart[a]);
	}
	if (OperateChart->ChartName)
		free(OperateChart->ChartName);
	free(OperateChart->Chart);
	free(OperateChart->ChartLimits);
	OperateChart->HadInit = 0;
	return SUCCESS;
}

/*
按照ShowLines和ShowTitle的顺序显示信息
ShowLines 包含在Chart表中lines的下标的数组,允许为NULL,将输出所有的行(按表中顺序)
ShowTitle 包含在Chart表中ShowTitle的下标的数组,允许为NULL,将输出所有的列(按表中顺序)
Mode是控制显示的一个参数
	Mode=1 输出一个编号(用于给用户进行选择)
	Mode=0 不输出编号
*/
ErrVal Display_Chart(Chart *OperateChart, IndexList *ShowLines, TitleList *ShowTitle, int Mode)
{
	int a, b;
	IndexList tempLinelist = { 0 };
	TitleList tempTitlelist = { 0 };
	int temp, temp3;			//用于提高性能
	int *temp2, *temp22, *temp5;	//用于提高性能
	char ***temp4;				//用于提高性能

	if (!ShowLines)
	{
		//如果ShowLines为空,则初始化一个IndexList
		temp = OperateChart->UsedLines;
		tempLinelist.listCount = temp;
		tempLinelist.list = (int*)malloc(sizeof(int)*temp);
		if (!tempLinelist.list)
			return ERR_MEMORYNOTENOUGH;

		temp2 = tempLinelist.list;
		for (a = 0; a < temp; a++) {
			*temp2 = a;
			temp2++;
		}
		ShowLines = &tempLinelist;
	}
	if (!ShowTitle)
	{
		//如果ShowTitle为空,则初始化一个ShowTitle
		temp = OperateChart->TitleCount;
		tempTitlelist.listCount = temp;
		tempTitlelist.list = (int*)malloc(sizeof(int)*temp);
		if (!tempTitlelist.list) {
			free(tempLinelist.list);
			return ERR_MEMORYNOTENOUGH;
		}
		temp2 = tempTitlelist.list;
		for (a = 0; a < temp; a++) {
			*temp2 = a;
			temp2++;
		}
		ShowTitle = &tempTitlelist;
	}

	temp = ShowLines->listCount;
	temp3 = ShowTitle->listCount;
	temp5 = OperateChart->ChartLimits;		//取得长度限制的数组

	//显示表头
	if (Mode == 1)
		printf("编号   ");
	temp2 = ShowTitle->list;
	for (a = 0; a < temp3; a++)
	{
		if (*temp2 < OperateChart->TitleCount)
			printf("%-*s ", temp5[*temp2], OperateChart->ChartTitle[*temp2]);
		temp2++;
	}
	printf("\n");

	temp4 = OperateChart->Chart;
	temp5 = OperateChart->ChartLimits;
	temp2 = ShowLines->list;

	//显示信息
	switch (Mode)
	{
	case 0:
		for (a = 0; a < temp; a++)
		{
			temp22 = ShowTitle->list;
			if (*temp2 < OperateChart->UsedLines)
				for (b = 0; b < temp3; b++)
				{
					if (*temp22 < OperateChart->TitleCount)
						printf("%-*s ", temp5[*temp22], temp4[*temp2][*temp22]);
					temp22++;
				}
			printf("\n");
			temp2++;
		}
		break;
	case 1:
		for (a = 0; a < temp; a++)
		{
			temp22 = ShowTitle->list;
			printf("%-7d ", a);
			for (b = 0; b < temp3; b++)
			{
				printf("%-*s ", temp5[*temp22], temp4[*temp2][*temp22]);
				temp22++;
			}
			printf("\n");
			temp2++;
		}
		break;
	}

	//释放临时申请的内存
	if (tempTitlelist.list)
		free(tempTitlelist.list);
	if (tempLinelist.list)
		free(tempLinelist.list);
	return SUCCESS;
}

/*
按照ShowLines和ShowTitle的顺序显示信息
OperateLineIndex 在Chart表中行的下标
ShowTitle 包含在Chart表中ShowTitle的下标的数组,允许为NULL,将输出所有的列(按表中顺序)
*/
ErrVal Display_Piece(Chart *OperateChart, int OperateLineIndex, TitleList *ShowTitle)
{
	int a, b;
	TitleList tempTitlelist = { 0 };
	int temp, temp3;			//用于提高性能
	int *temp2, *temp22, *temp5;	//用于提高性能
	char **temp4;				//用于提高性能

	if (OperateLineIndex >= OperateChart->UsedLines)
		return ERR_ILLEGALPARAM;

	if (!ShowTitle)
	{
		//如果ShowTitle为空,则初始化一个ShowTitle
		temp = OperateChart->TitleCount;
		tempTitlelist.listCount = temp;
		tempTitlelist.list = (int*)malloc(sizeof(int)*temp);
		if (!tempTitlelist.list) {
			return ERR_MEMORYNOTENOUGH;
		}
		temp2 = tempTitlelist.list;
		for (a = 0; a < temp; a++) {
			*temp2 = a;
			temp2++;
		}
		ShowTitle = &tempTitlelist;
	}
	temp3 = ShowTitle->listCount;
	temp5 = OperateChart->ChartLimits;		//取得长度限制的数组

	//显示表头
	temp2 = ShowTitle->list;
	for (a = 0; a < temp3; a++)
	{
		if (*temp2 < OperateChart->TitleCount)
			printf("%-*s ", temp5[*temp2], OperateChart->ChartTitle[*temp2]);
		temp2++;
	}
	printf("\n");

	temp4 = OperateChart->Chart[OperateLineIndex];
	temp5 = OperateChart->ChartLimits;

	temp22 = ShowTitle->list;
	for (b = 0; b < temp3; b++)
	{
		if (*temp22 < OperateChart->TitleCount)
			printf("%-*s ", temp5[*temp22], temp4[*temp22]);
		temp22++;
	}
	printf("\n");

	//释放临时申请的内存
	if (tempTitlelist.list)
		free(tempTitlelist.list);
	return SUCCESS;
}

/*
对表集进行扩充或初始化
CreateCount 要新增的表的数量
*/
ErrVal NewChartSet(int CreateCount)
{

	int a;
	Chart** NewChartSet=NULL; //新的表集
	int NewChartCount;
	if (CreateCount <= 0)
		return ERR_ILLEGALPARAM;

	if (ChartCount < 0)
		ChartCount = 0;

	NewChartCount = ChartCount + CreateCount;
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
			NewChartSet[a] = ChartHead[a];
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
	if (ChartHead)
		free(ChartHead);
	ChartHead = NewChartSet;
	AlloctedChartCount = NewChartCount;
	ChartCount = NewChartCount;
	return SUCCESS;
}

/*
把已经初始化好的表集销毁
!!!此操作会同时销毁所有表
*/
ErrVal FreeChartSet()
{
	int a;
	if (!ChartHead)
		return SUCCESS;
	
	for (a = 0; a < ChartCount; a++)
	{
		if (ChartHead[a]) {
			FreeChart(ChartHead[a]);		//销毁每一个表
			free(ChartHead[a]);
		}
	}
	free(ChartHead);
	ChartHead = NULL;
	ChartCount = 0;
	AlloctedChartCount = 0;
	return SUCCESS;
}

/*
按照IndexList对行进行排序
SourceLines 包含在Chart表中lines的下标的数组,允许为NULL,将排序所有的行(按表中顺序)
Mode 0升序
Mode 1降序
*/
ErrVal Sort(Chart *OperateChart, IndexList *OperateList, int BaseTitleIndex, int Mode)
{
	int a, b;
	int temp;		//交换时用于存储中间值的变量

	switch (Mode)
	{
	case 0:
		//升序
		for (a = 0; a < OperateList->listCount; a++)
		{
			for (b = a; b < OperateList->listCount; b++)
			{
				if (StrCmp(OperateChart->Chart[OperateList->list[a]][BaseTitleIndex], OperateChart->Chart[OperateList->list[b]][BaseTitleIndex]) > 0)
				{
					temp = OperateList->list[a];
					OperateList->list[a] = OperateList->list[b];
					OperateList->list[b] = temp;
				}
			}
		}
		break;
	case 1:
		//降序
		for (a = 0; a < OperateList->listCount; a++)
		{
			for (b = a; b < OperateList->listCount; b++)
			{
				if (StrCmp(OperateChart->Chart[OperateList->list[a]][BaseTitleIndex], OperateChart->Chart[OperateList->list[b]][BaseTitleIndex]) < 0)
				{
					temp = OperateList->list[a];
					OperateList->list[a] = OperateList->list[b];
					OperateList->list[b] = temp;
				}
			}
		}
		break;
	}
	return SUCCESS;
}

/*
在SearchList的范围内搜索符合条件的行,并返回给ResultList
OperateChart	要进行查找的表
SearchList		寻找的范围,允许为NULL,如果为NULL,将查找整个表
ResultList		将结果返回的结构体
BaseTitleIndex	进行比较的基准(选择以那个列作为基准)
*/
ErrVal Search(Chart *OperateChart, IndexList *SearchList, IndexList *ResultList, int BaseTitleIndex, char * DestinString)
{
	int a;
	int list_p = 0;
	int temp, *temp2;
	IndexList tempLinelist = { 0 };
	int isNULL = 0;

	if (!OperateChart)
		return ERR_ILLEGALPARAM;

	if (BaseTitleIndex >= OperateChart->TitleCount)
		return ERR_ILLEGALPARAM;

	if (!SearchList)
	{
		isNULL = 1;
		//如果ShowLines为空,则初始化一个IndexList
		temp = OperateChart->UsedLines;
		if (!temp)
		{
			ResultList->listCount = 0;
			return SUCCESS;
		}
		tempLinelist.listCount = temp;
		tempLinelist.list = (int*)malloc(sizeof(int)*temp);
		if (!tempLinelist.list)
			return ERR_MEMORYNOTENOUGH;

		temp2 = tempLinelist.list;
		for (a = 0; a < temp; a++) {
			*temp2 = a;
			temp2++;
		}
		SearchList = &tempLinelist;
	}
	if (SearchList->listCount > 0)
		for (a = 0; a < SearchList->listCount; a++) {
			if ((SearchList->list[a] < OperateChart->UsedLines) && (!strcmp(OperateChart->Chart[SearchList->list[a]][BaseTitleIndex], DestinString))) {
				ResultList->list[list_p++] = SearchList->list[a];
			}
		}
	ResultList->listCount = list_p;
	if (isNULL)
		free(tempLinelist.list);

	return SUCCESS;
}

/*
填充一个List(包含IndexList和TitleList),从0开始填充,会自动初始化内存
Count 在List作为IndexList时一定不要超过表中的行数
		在作为TitleList时一定不要超过表中的标题的数量
OperateList 中的list成员如果是指向数组的指针请设置为0
*/
ErrVal FillList(List *OperateList, int Count)
{
	int a;

	if (Count <= 0)
		return ERR_ILLEGALPARAM;

	if (OperateList->IsOnStack == 1 && (OperateList->list))
		free(OperateList->list);

	OperateList->list = (int*)malloc(sizeof(int)*Count);
	if (!OperateList->list)
		return ERR_MEMORYNOTENOUGH;
	OperateList->listCount = Count;
	OperateList->AllocatedList = Count;
	OperateList->IsOnStack = 1;

	for (a = 0; a < Count; a++)
		OperateList->list[a] = a;
	return SUCCESS;
}

/*
按照提供的值初始化一个List
OperateList 要进行初始化的结构体
Count ListData的参数个数
它与FillList的差别在于能否在初始化时自定义每一个元素
*/
ErrVal InitList(List *OperateList, int Count, int ListData, ...)
{
	va_list ap;
	int a;
	va_start(ap, ListData);

	if (Count <= 0)
		return ERR_ILLEGALPARAM;

	if (OperateList->IsOnStack == 1 && (OperateList->list))
		free(OperateList->list);


	OperateList->list = (int*)malloc(sizeof(int)*Count);
	if (!OperateList->list)
		return ERR_MEMORYNOTENOUGH;

	OperateList->listCount = Count;
	OperateList->AllocatedList = Count;
	OperateList->IsOnStack = 1;
	OperateList->list[0] = ListData;
	for (a = 1; a < Count; a++)
		OperateList->list[a] = va_arg(ap, int);
	return SUCCESS;
}

/*
释放一个List
*/
ErrVal FreeList(List *OperateList)
{
	if (!OperateList)
		return ERR_EMTYLIST;
	if (!OperateList->IsOnStack)
		return ERR_UNINITIALIZEDLIST;
	if (!OperateList->AllocatedList)
		return ERR_UNINITIALIZEDLIST;
	free(OperateList->list);
	return SUCCESS;
}

/*
用ListData参数表来给OperateArray赋值
OperateArray	要进行赋值的数组
n				被ListData列表参数的个数(一定要小于等于数组的容量)
ListData		值列表,该列表中的前n个值会赋值到OperateArray数组中
*/
ErrVal WirteToIntArray(int* OperateArray, int n, int ListData, ...)
{
	va_list ap;
	int a;
	va_start(ap, ListData);

	if (n <= 0)
		return ERR_ILLEGALPARAM;

	OperateArray[0] = ListData;
	for (a = 1; a < n; a++)
		OperateArray[a] = va_arg(ap, int);
	return SUCCESS;
}

/*
将DestList表复制到SourceList
*/
ErrVal CopyList(List *SourceList, List *DestList)
{
	int a;
	if (!SourceList->listCount)
		return ERR_ILLEGALPARAM;
	if (DestList->listCount < SourceList->listCount)
		FillList(DestList, SourceList->listCount);

	for (a = 0; a < SourceList->listCount; a++)
		DestList->list[a] = SourceList->list[a];
	DestList->listCount = SourceList->listCount;
	return SUCCESS;
}

/*
两个字符串进行比较,兼容数字字符串比较
*/
int StrCmp(const char *A, const char *B)
{
	int isNumA = 1, isNumB = 1;
	int lenA = 0, lenB = 0;
	char *A2 = (char*)A, *B2 = (char*)B;

	//计算长度并判断是否是纯数字
	while (*A2) {
		if (isNumA && (*A2<'0' || *A2>'9'))
			isNumA = 0;
		lenA++;
		A2++;
	}
	while (*B2) {
		if (isNumB && (*B2<'0' || *B2>'9'))
			isNumB = 0;
		lenB++;
		B2++;
	}

	if (isNumA*isNumB == 1) {
		//两个数字进行比较
		if (lenA != lenB) {
			//如果两个数字的长度不同,则长的数字大
			return lenA - lenB;
		}
		else {
			//如果数字长度相同,怎从高位到低位依次比较
			return strcmp(A, B);
		}
	}
	else {
		//非数字进行比较
		return strcmp(A, B);
	}
}

/*
通过表头的标题找到表头对应的编号
*/
int SearchHeadIndex(Chart *OperateChart, const char *UnitHeadName)
{
	int a;
	char **temp = OperateChart->ChartTitle;
	for (a = 0; a < OperateChart->TitleCount; a++) {
		if (!strcmp(*temp, UnitHeadName))
			return a;
		temp++;
	}
	return -1;
}

/*****************************分割线*******************************/
/**************************以下代码作废****************************/

#if (0)
/*
写入数据到文件
File要进行写入的文件路径,
list 当前正在处理的学生的下标集合
n list中元素的个数
*/
void WriteIni(char* File, int *list, int n)
{
	FILE *f;
	int a, b;
	f = fopen(File, "w+");
	if (!f)
		WRONGEXIT("打开文件失败")
		fprintf(f, "%d %d\n", n, UnitCount);
	for (a = 0; a < UnitCount; a++) {
		fprintf(f, "%s %d ", UnitHead[a], UnitHeadlimits[a]);
	}
	fprintf(f, "\n");
	for (a = 0; a < n; a++) {
		for (b = 0; b < UnitCount; b++)
			fprintf(f, "%s ", StudentList[list[a]][b]);
		fprintf(f, "\n");
	}
	fclose(f);
	return;
}


/*
加入一个新的学生
list 当前正在处理的学生的下标集合
n list中元素的个数
*/
int NewStudent(int *list, int *n)
{
	char ***temp;
	int a;
	//确定是否有空间保存数据
	if (StudentCapacity <= StudentCount) {
		StudentCapacity = StudentCount + ADDITIONAL;
		temp = (char***)malloc(sizeof(char**)*StudentCapacity);
		if (!temp)
			WRONGEXIT("内存不足");
		for (a = 0; a < StudentCount; a++)
			temp[a] = StudentList[a];
		free(StudentList);
		StudentList = temp;
	}
	//对最后一个元素进行写入,到这里可以确定StudentList[StudentCount]一定可以保存数据
	if (UnitCount > 0) {
		StudentList[StudentCount] = (char**)malloc(sizeof(char*)*UnitCount);
		if (!StudentList[StudentCount])
			WRONGEXIT("内存不足");
		for (a = 0; a < UnitCount; a++) {
			if (UnitHeadlimits[a] < 1) {
				UnitHeadlimits[a] = 1;
			}
			StudentList[StudentCount][a] = (char*)malloc(sizeof(char)*(UnitHeadlimits[a] + 1));
			if (!StudentList[StudentCount][a])
				WRONGEXIT("内存不足");
			StudentList[StudentCount][a][0] = '0';		//初始化单元格数据
			StudentList[StudentCount][a][1] = 0;
		}
	}

	list[*n] = StudentCount;//把新的学生的下标传递给名单
	*n += 1;
	StudentCount++;
	return *n;
}

/*
删除指定列
Unit要删除的列的下标
*/
void DeleteUnit(int Unit)
{
	int a, b, c;
	for (a = 0, b = 0; a < UnitCount; a++)
	{
		UnitHead[b] = UnitHead[a];
		UnitHeadlimits[b] = UnitHeadlimits[a];
		if (a != Unit)
			b++;
		else
			free(UnitHead[a]);
	}
	for (a = 0; a < StudentCount; a++)
	{
		for (b = 0, c = 0; b < UnitCount; b++)
		{
			StudentList[a][c] = StudentList[a][b];
			if (b != Unit)
				c++;
			else
				free(StudentList[a][b]);
		}
	}
	UnitCount--;
}

/*
从名单中剔除某个学生(此函数不会对表进行改动)
list是要进行修改的表
n是list表的长度
StudentNumber是学生在表中的实际编号
mode是删除模式 0表示删除后取最后一个元素来填补空缺(效率高) 1表示将按原来的顺序
*/
void DeleteStudentInList(int *list, int *n, int StudentNumber, int mode)
{
	int a, b = 0;
	switch (mode)
	{
	case 0:
		//删除指定学生之后用最后一个学生信息填充
		for (a = 0; a < *n; a++)
		{
			if (list[a] == StudentNumber)
			{
				list[a] = list[*n - 1];
				*n -= 1;
				return;
			}
		}
		break;
	case 1:
		//删除指定学生之后,空位之后的学生上移,以此填补空位
		for (a = 0; a < *n; a++)
		{
			list[b] = list[a];
			if (list[a] != StudentNumber)
				b++;
		}
		*n -= 1;
		return;
	}
}



#endif
