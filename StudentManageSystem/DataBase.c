#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "DataBase.h"

/*
���ݿ��
Create By ZCR
2016-12-10

*/

/*
�ڴ浵�ļ���,
��һ�е�һ�����ִ���ѧ��������n,�ڶ������ִ���ÿ���˵����Եĸ���unit
�ڶ�����unit������,ÿ��������2���������,�ֱ���һ���ַ���(��ͷ)��һ������(���������Ԫ�����Ƴ���)
��������n������,һֱ���ļ���β,ÿ�����ݷֱ���unit������,���ǵ�ֵ���Ǳ�ͷ�����ֵ
ע���ͷ�ĳ�������Ϊ31��Ӣ���ַ�
*/
//���ɵ��ļ��ı�ʶͷ
#ifndef BIN_HEAD
#define BIN_HEAD "DataBaseChartBIN"
#endif

//ȫ�ֱ���
Chart ** ChartHead = NULL;				//�ѷ���ı�ĸ���
int ChartCount = 0;						//��ʹ�õı�ĸ���
int AlloctedChartCount = 0;				//���ָ������

IndexList **IndexListHeadSet = NULL;	//IndexList��ָ������
int IndexListCount = 0;					//��ʹ�õ�IndexList�ĸ���
int AlloctedIndexListCount = 0;			//�ѷ����IndexList�ĸ���

TitleList **TitleListHeadSet = NULL;	//TitleList��ָ������
int TitleListCount = 0;					//��ʹ�õ�TitleList�ĸ���
int AlloctedTitleListCount = 0;			//�ѷ����TitleList�ĸ���

/*
���ļ���ȡ���ݵ�ָ����
//����ȫ,���Ƽ�ʹ�þͺ���
//����д
FileName Ҫ��ȡ���ļ�·��
OperateChart Ҫ�����洢��������ݵı�
*/

ErrVal ReadFromFile(const char *FileName, Chart *OperateChart)
{
	FILE *File;
	int Count, TitleCount;
	int a, b;				//ѭ������
	char temp;				//�����ӵ����õ�����
	char **temp2, ***temp4;	//�����������
	int *temp3;				//�����������

	if (!OperateChart)
		return ERR_ILLEGALCHART;

	File = fopen(FileName, "r");
	if (!File)
		return ERR_OPENFILE;

	if (fscanf(File, "%d%d", &Count, &TitleCount) != 2)		//���ļ���ȡ��������,�ֱ��Ӧ����
	{
		fclose(File);
		return ERR_NOTSTANDARDFILE;
	}
	if (fgetc(File) != '\n')
		return ERR_NOTSTANDARDFILE;

	//�Ա���г�ʼ��
	OperateChart->TitleCount = TitleCount;
	OperateChart->UsedLines = Count;
	//OperateChart->AllocatedLines = Count;

	//�����ڴ�
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
		//д���������
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

	//��ȡ�������
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
				//���ͷ�ֻ������һ�������
				for (b--; b >= 0; b--)
					free(temp4[0][b]);

				//���ͷ�ǰa���ѷ��������
				for (temp4--, a--; a >= 0; a--)
				{
					for (b = 0; b < TitleCount; b++)
						free(temp4[0][b]);
					temp4--;
				}
				//�ͷű�ͷ
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
				//�ͷű�ͷ
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
�������ļ��ж�ȡ��Ϣ
ParamFileName   ��ͷ�������ļ���·��
DataFileName    �������ݵ�·��
OperateChart    Ҫ�����洢��������ݵı�
*/
ErrVal ReadFromTwoFile(const char *ParamFileName, const char * DataFileName, Chart *OperateChart)
{
	FILE *File;		//��ǰ���ڶ�ȡ���ļ�
	const char *Delimer = " \t\n\r";

	//��ȡ����ʹ�õı���
	char* Line;		//�洢һ�е���Ϣ
	char* Piece;	//�洢һ����Ϣ��
	int a, b, c;

	//����Ϣ
	int LineCount;
	int TitleCount;
	int LineCharCount;

	//�洢����ʹ�õı���
	ChartPiece_t tempChartPiece;
	int* tempChartTitleLimits;
	Chart_t tempChart;


	if (!OperateChart)
		return ERR_ILLEGALCHART;

	if (OperateChart->HadInit)
	{
		//�Ѿ���ʼ���ı����ͷ�
		FreeChart(OperateChart);
	}

	//��ʼ��ȡ������ļ�
	File = fopen(ParamFileName, "r");
	if (!File)
		return ERR_OPENFILE;
	Line = (char*)malloc(sizeof(char) * 20);
	if (!Line)
	{
		fclose(File);
		return ERR_MEMORYNOTENOUGH;
	}

	//��ȡ����������
	fgets(Line, 20, File);
	LineCount = atoi(strtok(Line, Delimer));
	TitleCount = atoi(strtok(NULL, Delimer));
	if (LineCount <= 0 || TitleCount <= 0)
	{
		fclose(File);
		free(Line);
		return ERR_NOTSTANDARDFILE;
	}

	//����һ�����ڴ�ű��������
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
	LineCharCount = 38 * TitleCount;	//������һ�е������
	Line = (char*)malloc(sizeof(char) * LineCharCount);
	fgets(Line, LineCharCount, File);	//��ȡ��һ��

	tempChartPiece[0] = (char*)malloc(sizeof(char) * 32);
	if (!tempChartPiece[0])
	{
		fclose(File);
		free(Line);
		free(tempChartPiece);
		free(tempChartTitleLimits);
		return ERR_MEMORYNOTENOUGH;
	}

	//��ȡ��һ������
	strcpy(tempChartPiece[0], strtok(Line, Delimer));
	tempChartTitleLimits[0] = atoi(strtok(NULL, Delimer));

	for (a = 1; a < TitleCount; a++)	//��ȡ2����LineCharCount����
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

	//�����ȡ���,��ʼ��ȡ��
	LineCharCount = 0;		//��ʼ���������е�һ�е������
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

		//д���һ��ֵ
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

		//��ȡ�ڶ�����TitleCount��ֵ
		for (b = 1; b < TitleCount; b++)
		{
			tempChart[a][b] = (char*)malloc(sizeof(char)*tempChartTitleLimits[b] + 1);
			Piece = strtok(NULL, Delimer);
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

	//��ȡ��ȡ���ļ�������
	a = (int)strlen(ParamFileName);
	b = (int)strlen(DataFileName);
	Line = (char*)malloc(sizeof(char)*(a + b + 6));
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
�ӱ����򴴽��Ķ������ļ���ȡ��Ϣ
FileName        �������ļ���·��
PassWord        ���ܵ�����
OperateChart    Ҫ���б���ı�
*/
ErrVal ReadFromBinFile(const char *FileName, const char *PassWord, Chart *OperateChart)
{
	ErrVal EncryptChar(const char *ResultString, const char *SourceString, int size, const char* PassWord, int PassWord_len);
	Chart *tempChart = (Chart*)malloc(sizeof(Chart));
	int NewChartLinesCount = 0;
	int NewChartTitleCount = 0;
	int a, b;
	FILE *File;
	char temp[512];
	int PassWord_len = (int)strlen(PassWord);
	if (!OperateChart)
		return ERR_ILLEGALCHART;

	if (!tempChart)
		return ERR_MEMORYNOTENOUGH;

	File = fopen(FileName, "rb");
	if (!File)
		return ERR_OPENFILE;

	fread(temp, sizeof(BIN_HEAD), 1, File);
	fread(temp, sizeof("CHECK"), 1, File);
	EncryptChar(temp, temp, sizeof("CHECK") - 1, PassWord, PassWord_len);
	if (strcmp(temp, "CHECK") != 0) {
		fclose(File);
		return ERR_WRONGPASSWORD;
	}
	fread(&NewChartLinesCount, sizeof(int), 1, File);
	fread(&NewChartTitleCount, sizeof(int), 1, File);

	if (NewChartLinesCount <= 0 || NewChartTitleCount <= 0) {
		fclose(File);
		return ERR_ILLEGALBINFILE;
	}

	tempChart->ChartTitle = (ChartPiece_t)malloc(sizeof(char*)*NewChartTitleCount);
	tempChart->ChartLimits = (int*)malloc(sizeof(int)*NewChartTitleCount);
	if (!tempChart->ChartTitle || !tempChart->ChartLimits)
	{
		if (tempChart->ChartTitle)
			free(tempChart->ChartTitle);
		fclose(File);
		return ERR_MEMORYNOTENOUGH;
	}
	for (a = 0; a < NewChartTitleCount; a++)
	{
		tempChart->ChartTitle[a] = (char*)malloc(sizeof(char) * 32);
		if (!tempChart->ChartTitle[a])
		{
			fclose(File);
			for (a--; a >= 0; a--)
				free(tempChart->ChartTitle[a]);
			free(tempChart->ChartTitle);
			free(tempChart);
			return ERR_MEMORYNOTENOUGH;
		}
		fread(tempChart->ChartTitle[a], sizeof(char), 32, File);
		EncryptChar(tempChart->ChartTitle[a], tempChart->ChartTitle[a], sizeof(char) * 31, PassWord, PassWord_len);
		fread(&tempChart->ChartLimits[a], sizeof(int), 1, File);

	}

	tempChart->Chart = (Chart_t)malloc(sizeof(ChartPiece_t)*NewChartLinesCount);
	if (!tempChart->Chart)
	{
		fclose(File);
		for (a = 0; a < NewChartTitleCount; a++)
			free(tempChart->ChartTitle[a]);
		free(tempChart->ChartTitle);
		free(tempChart->ChartLimits);
		free(tempChart);
		return ERR_MEMORYNOTENOUGH;
	}

	for (a = 0; a < NewChartLinesCount; a++)
	{
		tempChart->Chart[a] = (ChartPiece_t)malloc(sizeof(char*)*NewChartTitleCount);
		if (!tempChart->Chart[a])
		{
			fclose(File);
			for (a--; a >= 0; a--)
			{
				for (b = 0; b < NewChartTitleCount; b++)
				{
					free(tempChart->Chart[a][b]);
				}
				free(tempChart->Chart[a]);
			}
			free(tempChart->Chart);

			for (a = 0; a < NewChartTitleCount; a++)
				free(tempChart->ChartTitle[a]);
			free(tempChart->ChartTitle);
			free(tempChart->ChartLimits);
			free(tempChart);
			return ERR_MEMORYNOTENOUGH;
		}

		for (b = 0; b < NewChartTitleCount; b++)
		{
			tempChart->Chart[a][b] = (char*)malloc(sizeof(char)*(tempChart->ChartLimits[b] + 1));
			if (!tempChart->Chart[a][b])
			{
				fclose(File);
				for (b--; b >= 0; b--)
					free(tempChart->Chart[a][b]);
				free(tempChart->Chart[a]);
				for (a--; a >= 0; a--)
				{
					for (b = 0; b < NewChartTitleCount; b++)
						free(tempChart->Chart[a][b]);
					free(tempChart->Chart[a]);
				}
				free(tempChart->Chart);

				for (a = 0; a < NewChartTitleCount; a++)
					free(tempChart->ChartTitle[a]);
				free(tempChart->ChartTitle);
				free(tempChart->ChartLimits);
				free(tempChart);
				return ERR_MEMORYNOTENOUGH;
			}

			fread(tempChart->Chart[a][b], tempChart->ChartLimits[b] + 1, sizeof(char), File);
			EncryptChar(tempChart->Chart[a][b], tempChart->Chart[a][b], sizeof(char) * tempChart->ChartLimits[b], PassWord, PassWord_len);
		}
	}
	if (OperateChart->HadInit)
		FreeChart(OperateChart);//�Ѿ���ʼ���ı����ͷ�


	OperateChart->Chart = tempChart->Chart;
	OperateChart->ChartLimits = tempChart->ChartLimits;
	OperateChart->ChartName = GetFileName(FileName);
	OperateChart->ChartTitle = tempChart->ChartTitle;
	OperateChart->HadInit = 1;
	OperateChart->TitleCount = NewChartTitleCount;
	OperateChart->UsedLines = NewChartLinesCount;
	free(tempChart);
	return SUCCESS;
}

/*
�����ݵ�����Txt(���Ű�,�ʺ�ֱ���Ķ������)
FileName        Ҫд����ļ���
OperateChart    Ҫд������ݴ�ŵı�
WriteLine       ���Ʊ�����Щ��Ҫ���д洢,�������Ŵ洢˳��
WriteTitle      ��������Щ����Ҫ���,�����������˳��
*/
ErrVal ExportToTxt(const char * FileName, Chart * OperateChart, IndexList * WriteLine, TitleList * WriteTitle)
{
	FILE *File;
	int a, b;

	if (!OperateChart || !OperateChart->HadInit)
		return ERR_UNINITIALIZEDCHART;
	if (OperateChart->TitleCount <= 0 || OperateChart->UsedLines <= 0)
		return ERR_ILLEGALCHART;

	File = fopen(FileName, "w");
	if (!File)
		return ERR_OPENFILE;

	//д�����ͷ��
	for (a = 0; a < WriteTitle->listCount; a++)
		fprintf(File, "%*s ", OperateChart->ChartLimits[WriteTitle->list[a]], OperateChart->ChartTitle[WriteTitle->list[a]]);
	fprintf(File, "\n");

	//��ʼд���������
	for (a = 0; a < WriteLine->listCount; a++)
	{
		for (b = 0; b < WriteTitle->listCount; b++)
			fprintf(File, "%*s ", OperateChart->ChartLimits[WriteTitle->list[b]], OperateChart->Chart[WriteLine->list[a]][WriteTitle->list[b]]);
		fprintf(File, "\n");
	}
	fclose(File);

	return SUCCESS;
}

/*
����д�뵽�����ļ���ȥ
ParamFileName   Ҫд��������ļ�·��
DataFileName    Ҫд��������ݵ��ļ�·��
OperateChart    Ҫд������ݴ�ŵı�
*/
ErrVal WriteToTwoFile_Chart(const char * ParamFileName, const char * DataFileName, Chart * OperateChart)
{
	FILE *File;
	int a, b;

	if (!OperateChart || !OperateChart->HadInit)
		return ERR_UNINITIALIZEDCHART;
	if (OperateChart->TitleCount <= 0 || OperateChart->UsedLines <= 0)
		return ERR_ILLEGALCHART;

	File = fopen(ParamFileName, "w");
	if (!File)
		return ERR_OPENFILE;

	//д�����ͷ��
	fprintf(File, "%d %d\n", OperateChart->UsedLines, OperateChart->TitleCount);
	for (a = 0; a < OperateChart->TitleCount; a++)
		fprintf(File, "%s %d ", OperateChart->ChartTitle[a], OperateChart->ChartLimits[a]);
	fprintf(File, "\n");
	fclose(File);

	//��ʼд���������
	File = fopen(DataFileName, "w");
	if (!File)
		return ERR_OPENFILE;
	for (a = 0; a < OperateChart->UsedLines; a++)
	{
		for (b = 0; b < OperateChart->TitleCount; b++)
			fprintf(File, "%s ", OperateChart->Chart[a][b]);
		fprintf(File, "\n");
	}
	fclose(File);
	return SUCCESS;
}

/*
����List��˳��ѱ�д�뵽�ļ���ȥ,��WriteToTwoFile_Chart()��ͬ�����������֧�ֽ���������д���
ParamFileName   Ҫд��������ļ�·��
DataFileName    Ҫд��������ݵ��ļ�·��
OperateChart    Ҫд������ݴ�ŵı�
WriteLine       ��Ҫ����д����е�����
WriteTitle      ��Ҫ����д����е�����
*/
ErrVal WriteToTwoFileByList(const char * ParamFileName, const char * DataFileName, Chart * OperateChart, IndexList *WriteLine, TitleList *WriteTitle)
{
	FILE *File;
	int a, b;

	if (!OperateChart || !OperateChart->HadInit)
		return ERR_UNINITIALIZEDCHART;
	if (OperateChart->TitleCount <= 0 || OperateChart->UsedLines <= 0)
		return ERR_ILLEGALCHART;

	File = fopen(ParamFileName, "w");
	if (!File)
		return ERR_OPENFILE;

	//д�����ͷ��
	fprintf(File, "%d %d\n", WriteLine->listCount, WriteTitle->listCount);
	for (a = 0; a < WriteTitle->listCount; a++)
		fprintf(File, "%s %d ", OperateChart->ChartTitle[WriteTitle->list[a]], OperateChart->ChartLimits[WriteTitle->list[a]]);
	fprintf(File, "\n");
	fclose(File);

	//��ʼд���������
	File = fopen(DataFileName, "w");
	if (!File)
		return ERR_OPENFILE;
	for (a = 0; a < WriteLine->listCount; a++)
	{
		for (b = 0; b < WriteTitle->listCount; b++)
			fprintf(File, "%s ", OperateChart->Chart[WriteLine->list[a]][WriteTitle->list[b]]);
		fprintf(File, "\n");
	}
	fclose(File);

	return SUCCESS;
}

/*
�����е�����д�뵽��
FileName        Ҫд����ļ���·��
PassWord        ���ܵ�����
OperateChart    Ҫ���б���ı�
*/
ErrVal WriteToBinFile_Chart(const char * FileName, const char * PassWord, Chart * OperateChart)
{
	ErrVal EncryptChar(const char *ResultString, const char *SourceString, int size, const char* PassWord, int PassWord_len);
	FILE *File;
	int a, b;
	char tempStr[512] = "";
	int PassWord_len = (int)strlen(PassWord);

	if (!OperateChart || !OperateChart->HadInit)
		return ERR_UNINITIALIZEDCHART;
	if (OperateChart->TitleCount <= 0 || OperateChart->UsedLines <= 0)
		return ERR_ILLEGALCHART;

	File = fopen(FileName, "wb");
	if (!File)
		return ERR_OPENFILE;

	//д���ͷ
	fwrite(BIN_HEAD, sizeof(BIN_HEAD), 1, File);
	//�����Ƿ�ɹ����ַ���

	EncryptChar(tempStr, "CHECK", sizeof("CHECK") - sizeof(char), PassWord, PassWord_len);
	fwrite(tempStr, sizeof("CHECK"), 1, File);
	fwrite(&OperateChart->UsedLines, sizeof(int), 1, File);
	fwrite(&OperateChart->TitleCount, sizeof(int), 1, File);
	for (a = 0; a < OperateChart->TitleCount; a++)
	{
		EncryptChar(tempStr, OperateChart->ChartTitle[a], sizeof(char) * 31, PassWord, PassWord_len);
		fwrite(tempStr, sizeof(char), 32, File);
		fwrite(&OperateChart->ChartLimits[a], sizeof(int), 1, File);
	}
	for (a = 0; a < OperateChart->UsedLines; a++)
	{
		for (b = 0; b < OperateChart->TitleCount; b++)
		{
			EncryptChar(tempStr, OperateChart->Chart[a][b], OperateChart->ChartLimits[b], PassWord, PassWord_len);
			fwrite(tempStr, sizeof(char), OperateChart->ChartLimits[b] + 1, File);
		}
	}
	fclose(File);
	return SUCCESS;
}

/*
�����е�����д�뵽��
FileName        Ҫд����ļ���·��
PassWord        ���ܵ�����
OperateChart    Ҫ���б���ı�
WriteLine       Ҫд����е�List
WriteTitle      Ҫд����е�List
*/
ErrVal WriteToBinFileByList(const char * FileName, const char * PassWord, Chart * OperateChart, IndexList *WriteLine, TitleList *WriteTitle)
{
	ErrVal EncryptChar(const char *ResultString, const char *SourceString, int size, const char* PassWord, int PassWord_len);
	FILE *File;
	int a, b;
	char tempStr[512] = "";
	int PassWord_len = (int)strlen(PassWord);

	if (!OperateChart || !OperateChart->HadInit)
		return ERR_UNINITIALIZEDCHART;
	if (OperateChart->TitleCount <= 0 || OperateChart->UsedLines <= 0)
		return ERR_ILLEGALCHART;

	if (!WriteLine || WriteLine->listCount <= 0)
	{
		FillList(WriteLine, OperateChart->UsedLines);
		if (!WriteLine)
			return ERR_ILLEGALPARAM;
	}

	if (!WriteTitle || WriteTitle->listCount <= 0)
	{
		FillList(WriteTitle, OperateChart->TitleCount);
		if (!WriteTitle)
			return ERR_ILLEGALPARAM;
	}

	File = fopen(FileName, "wb");
	if (!File)
		return ERR_OPENFILE;

	//д���ͷ
	fwrite(BIN_HEAD, sizeof(BIN_HEAD), 1, File);
	//�����Ƿ�ɹ����ַ���

	EncryptChar(tempStr, "CHECK", sizeof("CHECK") - sizeof(char), PassWord, PassWord_len);
	fwrite(tempStr, sizeof("CHECK"), 1, File);
	fwrite(&WriteLine->listCount, sizeof(int), 1, File);
	fwrite(&WriteTitle->listCount, sizeof(int), 1, File);
	for (a = 0; a < WriteTitle->listCount; a++)
	{
		EncryptChar(tempStr, OperateChart->ChartTitle[WriteTitle->list[a]], sizeof(char) * 31, PassWord, PassWord_len);
		fwrite(tempStr, sizeof(char), 32, File);
		fwrite(&OperateChart->ChartLimits[WriteTitle->list[a]], sizeof(int), 1, File);
	}
	for (a = 0; a < WriteLine->listCount; a++)
	{
		for (b = 0; b < WriteTitle->listCount; b++)
		{
			EncryptChar(tempStr, OperateChart->Chart[WriteLine->list[a]][WriteTitle->list[b]], OperateChart->ChartLimits[WriteTitle->list[b]], PassWord, PassWord_len);
			fwrite(tempStr, sizeof(char), OperateChart->ChartLimits[WriteTitle->list[b]] + 1, File);
		}
	}
	fclose(File);
	return SUCCESS;
}

/*
��ȡӳ���ļ�
MapFileName     ��ȡ��ӳ���ļ�������
MapStruct       ӳ����Ϣ�洢�Ľṹ��
ӳ���ļ��ĸ�ʽΪ,ֱ���ļ���β
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
	MapStruct->MapName = GetFileName(MapFileName);
	fclose(File);
	return SUCCESS;
}

/*
�ͷ�ӳ���ϵ�ṹ��
MapStruct       Ҫ�ͷŵĽṹ��
*/
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
����1�������µı���
OperateChart    Ҫ���в����ı�
CreateCount     Ҫ�����ı�����Ŀ
NewTitleSet     �����ı�����������
NewTitleLimits  �����ı�����������Ƴ���
*/
ErrVal CreateNewUnit(Chart *OperateChart, int CreateCount, char(*NewTitleSet)[32], int *NewTitleLimits)
{
	Chart_t NewChart;
	ChartPiece_t NewChartTitle;
	int* NewChartLimits;
	int LinesCount;
	int UnitCount, NewUnitCount;
	int a, b, c, d;
	char **temp;		//Ϊ���������
	int  *temp3;

	if (CreateCount <= 0)
		return SUCCESS;

	if (!OperateChart)
		return ERR_ILLEGALCHART;
	UnitCount = OperateChart->TitleCount;
	LinesCount = OperateChart->UsedLines;

	if (LinesCount <= 0 || UnitCount <= 0)
		return ERR_UNINITIALIZEDCHART;


	NewUnitCount = OperateChart->TitleCount + CreateCount;

	if (NewUnitCount<=OperateChart->TitleCount)
		return ERR_ILLEGALPARAM;

	//��ʼ�½���ͷ
	NewChartTitle = (ChartPiece_t)malloc(sizeof(char*)*NewUnitCount);
	NewChartLimits = (int*)malloc(sizeof(int)*NewUnitCount);
	if (!NewChartTitle)
		return ERR_MEMORYNOTENOUGH;

	if (!NewChartLimits)
	{
		free(NewChartTitle);
		return ERR_MEMORYNOTENOUGH;
	}
	//�������⵽�µı�ͷ
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
		NewChartLimits[a] = *temp3;
		if (!NewChartTitle[a])
		{
			for (a--; a >= UnitCount; a--)
				free(NewChartTitle[a]);
			free(NewChartTitle);
			free(NewChartLimits);
			return ERR_MEMORYNOTENOUGH;
		}
		strcpy(NewChartTitle[a], *NewTitleSet);
		temp3++;
		NewTitleSet++;

	}

	//��ʼ�½�һ���µı�
	NewChart = (Chart_t)malloc(sizeof(ChartPiece_t)*OperateChart->UsedLines);
	if (!NewChart) {
		for (a = UnitCount; a < NewUnitCount; a++)
			free(NewChartTitle[a]);
		free(NewChartTitle);
		free(NewChartLimits);
		return ERR_MEMORYNOTENOUGH;
	}
	//��ÿ���з��䵥Ԫ��
	for (a = 0; a < LinesCount; a++)
	{
		NewChart[a] = (ChartPiece_t)malloc(sizeof(char*)*NewUnitCount);
		if (!NewChart[a])
		{
			//��������������,������ѷ����ڴ�,����
			for (a--; a >= 0; a--)
				free(NewChart[a]);
			free(NewChart);
			for (a = UnitCount; a < NewUnitCount; a++)
				if (NewChartTitle[a])
					free(NewChartTitle[a]);
			free(NewChartTitle);
			free(NewChartLimits);
			return ERR_MEMORYNOTENOUGH;
		}

		//������Ԫ��
		temp = OperateChart->Chart[a];
		for (b = 0; b < OperateChart->TitleCount; b++)
			NewChart[a][b] = temp[b];

		//�µĵ�Ԫ����з����ڴ�
		//temp2 = OperateChart->TitleCount+CreateCount;
		for (c = 0; c < CreateCount&&b < NewUnitCount; b++, c++)
		{
			d = NewTitleLimits[c] + 1;
			d = sizeof(char)*(d > 2 ? d : 2);
			NewChart[a][b] = (char*)calloc(d, d);
			if (!NewChart[a][b])
			{
				for (b--; b >= 0; b--)			//ɾ����һ�ַ�����ڴ�
					free(NewChart[a][b]);
				free(NewChart[a]);
				for (a--; a >= 0; a--)			//ɾ��ǰ���ַ�����ڴ�
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
	//���е�����,�µı�ͷ������
	//�Ѿɱ��ڴ��ͷŵ�,�����±�,�Ͳ����ɹ���
	for (a = 0; a < OperateChart->UsedLines; a++)		//ɾ���ɱ�,
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
�����еı��д���CreateCount���µ���
OperateChart    Ҫ���в����ı�
CreateCount     ����������
NewList         �����ɵ��е��±�洢���б�
*/
ErrVal CreateNewLine(Chart * OperateChart, int CreateCount, IndexList *NewList)
{
	int NewLine = OperateChart->UsedLines + CreateCount;
	Chart_t tempChart;
	int a, b;

	if (CreateCount <= 0)
		return ERR_ILLEGALPARAM;

	if (!OperateChart || OperateChart->TitleCount <= 0 || OperateChart->UsedLines <= 0 || NewLine <= OperateChart->UsedLines)
		return ERR_ILLEGALCHART;

	/*
	if (NewLine <= OperateChart->AllocatedLines)
	{
	//�ڴ����
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
	//�ڴ治��,��Ҫ���·����ڴ沢����
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
		//Ϊ�б�ֵ
		for (a = OperateChart->UsedLines, b = 0; a < NewLine&&b < NewList->AllocatedList; a++, b++)
			NewList->list[b] = a;
		NewList->listCount = b;
	}
	OperateChart->UsedLines = NewLine;
	return SUCCESS;
}

/*
��ʼ��һ���µı�,������������ݵı���г�ʼ��,�����ƻ�ԭ�������
��ʼ����ı�������
OperateChart	Ҫ���г�ʼ���ı�
LineCount		����
TitleCount		����
TitleList,TitleLimits	�����ʼ���б�(��TitleCount��)
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

	//��ʼ�������б�
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
	strcpy(*tempChartTitle, TitleList);		//д���һ������ 
	*tempChartLimits = TitleLimits;			//д���һ����������ݳ�������

	//�Ե�2-TitleCount�������д���
	va_start(ap, TitleLimits);

	for (a = 1; a < TitleCount; a++)
	{
		tempChartTitle[a] = (char*)malloc(sizeof(char) * 32);
		if (!tempChartTitle[a])
		{
			for (a--; a >= 0; a--)
				free(tempChartTitle[a]);		//�ͷ��Ѿ�������ڴ� 
			free(tempChartLimits);
			free(tempChartTitle);
			return ERR_MEMORYNOTENOUGH;
		}
		strcpy(tempChartTitle[a], va_arg(ap, char*));
		tempChartLimits[a] = va_arg(ap, int);
	}

	//��ʼ���� 
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
	//��ʼ�����������Ϣ
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
�����ִ������Ϊ�ַ���
OperateChart	���в����ı�
TitleIndex		����ת������
MapStruct		�洢ӳ���ϵ�ı�
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
				//ƥ��,���з���
				strcpy(temp, list[b]);
				break;
			}
		}
	}
	return SUCCESS;
}

/*
��Ϊ�ַ����������ִ���
OperateChart	���в����ı�
TitleIndex		����ת������
MapStruct		�洢ӳ���ϵ�ı�
*/
ErrVal UnTranslate(Chart *OperateChart, int TitleIndex, InfoMap *MapStruct)
{
	int a, b;
	char *temp;
	char **list = MapStruct->Val;
	char **Val = MapStruct->String;
	for (a = 0; a < OperateChart->UsedLines; a++)
	{
		temp = OperateChart->Chart[a][TitleIndex];
		for (b = 0; b < MapStruct->Count; b++)
		{
			if (!strcmp(temp, Val[b]))
			{
				//ƥ��,�����淭��
				strcpy(temp, list[b]);
				break;
			}
		}
	}
	return SUCCESS;
}

/*
�ͷ���������ռ���ڴ�
OperateChart    Ҫ�������ٵı�,������֮����δ��ʼ����״̬,��Ҫ���³�ʼ������ʹ��
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
����ShowLines��ShowTitle��˳����ʾ��Ϣ
OperateChart    Ҫ��ʾ�ı�
ShowLines       ��������ʾ˳��Ľṹ��.����ΪNULL,ΪNULL���ձ���ʵ��˳�����
ShowTitle       ��������ʾ˳��Ľṹ��.����ΪNULL,ΪNULL���ձ���ʵ��˳�����
Mode        ������ʾ��һ������(���ڸ��û�����ѡ��)
Mode   1    ���һ�����
Mode   0    ��������
*/
ErrVal Display_Chart(Chart *OperateChart, IndexList *ShowLines, TitleList *ShowTitle, int Mode)
{
	int a, b;
	int *tempLineList, *tempTitleList;
	if (!OperateChart || !OperateChart->HadInit)
		return ERR_UNINITIALIZEDCHART;

	if (ShowLines && ShowLines->listCount <= 0)
	{
		FreeList(ShowLines);
		ShowLines = NULL;
	}

	if (ShowTitle&&ShowTitle->listCount <= 0)
	{
		FreeList(ShowTitle);
		ShowTitle = NULL;
	}

	if (Mode == 1)
		printf("���   ");
	if (!ShowTitle)
	{
		//��ָ�����⽫ʹ��Ĭ��
		for (a = 0; a < OperateChart->TitleCount; a++)
			printf("%-*s ", OperateChart->ChartLimits[a], OperateChart->ChartTitle[a]);
	}
	else {
		tempTitleList = ShowTitle->list;
		for (a = 0; a < ShowTitle->listCount; a++)
		{
			if (*tempTitleList < OperateChart->TitleCount)
				printf("%-*s ", OperateChart->ChartLimits[*tempTitleList], OperateChart->ChartTitle[*tempTitleList]);
			tempTitleList++;
		}
	}
	printf("\n");


	if (ShowLines)
	{
		tempLineList = ShowLines->list;
		//��List����ʾ��Ϣ
		if (ShowTitle)
		{
			//�������������ʾ
			switch (Mode)
			{
			case 0:
				for (a = 0; a < ShowLines->listCount; a++)
				{
					if (*tempLineList < OperateChart->UsedLines) {
						tempTitleList = ShowTitle->list;
						for (b = 0; b < ShowTitle->listCount; b++)
						{
							if (*tempTitleList < OperateChart->TitleCount)
								printf("%-*s ", OperateChart->ChartLimits[*tempTitleList], OperateChart->Chart[*tempLineList][*tempTitleList]);
							tempTitleList++;
						}
						printf("\n");
					}
					tempLineList++;
				}
				break;
			case 1:
				for (a = 0; a < ShowLines->listCount; a++)
				{
					if (*tempLineList < OperateChart->UsedLines) {
						tempTitleList = ShowTitle->list;
						printf("%-7d ", a);
						for (b = 0; b < ShowTitle->listCount; b++)
						{
							if (*tempTitleList < OperateChart->TitleCount)
								printf("%-*s ", OperateChart->ChartLimits[*tempTitleList], OperateChart->Chart[*tempLineList][*tempTitleList]);
							tempTitleList++;
						}
						printf("\n");
					}
					tempLineList++;
				}
				break;
			}
		}
		else {
			//ֻ��IndexList����ʾ
			switch (Mode)
			{
			case 0:
				for (a = 0; a < ShowLines->listCount; a++)
				{
					if (*tempLineList < OperateChart->UsedLines) {
						for (b = 0; b < OperateChart->TitleCount; b++)
							printf("%-*s ", OperateChart->ChartLimits[b], OperateChart->Chart[*tempLineList][b]);
						printf("\n");
					}
					tempLineList++;
				}
				break;
			case 1:
				for (a = 0; a < ShowLines->listCount; a++)
				{
					if (*tempLineList < OperateChart->UsedLines) {
						printf("%-7d ", a);
						for (b = 0; b < OperateChart->TitleCount; b++)
							printf("%-*s ", OperateChart->ChartLimits[b], OperateChart->Chart[*tempLineList][b]);
						printf("\n");
					}
					tempLineList++;
				}
				break;
			}
		}
	}
	else {
		if (ShowTitle)
		{
			//��TitleList���������ʾ
			switch (Mode)
			{
			case 0:
				for (a = 0; a < OperateChart->UsedLines; a++)
				{
					tempTitleList = ShowTitle->list;
					for (b = 0; b < ShowTitle->listCount; b++)
					{
						if (*tempTitleList < OperateChart->TitleCount)
							printf("%-*s ", OperateChart->ChartLimits[*tempTitleList], OperateChart->Chart[a][*tempTitleList]);
						tempTitleList++;
					}
					printf("\n");
				}
				break;
			case 1:
				for (a = 0; a < OperateChart->UsedLines; a++)
				{
					tempTitleList = ShowTitle->list;
					printf("%-7d ", a);
					for (b = 0; b < ShowTitle->listCount; b++)
					{
						if (*tempTitleList < OperateChart->TitleCount)
							printf("%-*s ", OperateChart->ChartLimits[*tempTitleList], OperateChart->Chart[a][*tempTitleList]);
						tempTitleList++;
					}
					printf("\n");
				}
				break;
			}
		}
		else {
			//�����κα���ʾ
			switch (Mode)
			{
			case 0:
				for (a = 0; a < OperateChart->UsedLines; a++)
				{
					for (b = 0; b < OperateChart->TitleCount; b++)
						printf("%-*s ", OperateChart->ChartLimits[b], OperateChart->Chart[a][b]);
					printf("\n");
				}
				break;
			case 1:
				for (a = 0; a < OperateChart->UsedLines; a++)
				{
					printf("%-7d ", a);
					for (b = 0; b < OperateChart->TitleCount; b++)
						printf("%-*s ", OperateChart->ChartLimits[b], OperateChart->Chart[a][b]);
					printf("\n");
				}
				break;
			}
		}
	}
	return SUCCESS;
}

/*
����ShowLines��ShowTitle��˳����ʾ��Ϣ
OperateChart        �������ʾ��Ϣ���ڵı�
OperateLineIndex    ��Chart�����е��±�
ShowTitle           ��������ʾ˳��Ľṹ��.����ΪNULL,ΪNULL���ձ���ʵ��˳�����
*/
ErrVal Display_Piece(Chart *OperateChart, int OperateLineIndex, TitleList *ShowTitle)
{
	int a, b;
	TitleList tempTitlelist = { 0 };
	int temp, temp3;			//�����������
	int *temp2, *temp22, *temp5;	//�����������
	char **temp4;				//�����������

	if (OperateLineIndex >= OperateChart->UsedLines)
		return ERR_ILLEGALPARAM;

	if (!ShowTitle || !ShowTitle->AllocatedList)
	{
		//���ShowTitleΪ��,���ʼ��һ��ShowTitle
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
	temp5 = OperateChart->ChartLimits;		//ȡ�ó������Ƶ�����

	//��ʾ��ͷ
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

	//�ͷ���ʱ������ڴ�
	if (tempTitlelist.list)
		free(tempTitlelist.list);
	return SUCCESS;
}

/*
����ShowLines��ShowTitle��˳����ʾ��Ϣ
OperateChart    Ҫ��ʾ�ı�
ShowLines       ��������ʾ˳��Ľṹ��.����ΪNULL,ΪNULL���ձ���ʵ��˳�����
ShowTitle       ��������ʾ˳��Ľṹ��.����ΪNULL,ΪNULL���ձ���ʵ��˳�����
PageSize        һҳ�Ĵ�С
PageIndex       ҳ�����
Mode        ������ʾ��һ������(���ڸ��û�����ѡ��)
Mode   1    ���һ�����
Mode   0    ��������
*/
ErrVal Display_Page(Chart *OperateChart, IndexList *ShowLines, TitleList *ShowTitle, int Mode, int PageSize, int PageIndex)
{
	int a, b;
	int *tempLineList, *tempTitleList;
	int Start_index, End_index;
	if (!OperateChart || !OperateChart->HadInit)
		return ERR_UNINITIALIZEDCHART;

	if (ShowLines && ShowLines->listCount <= 0)
	{
		FreeList(ShowLines);
		ShowLines = NULL;
	}
	if (PageIndex < 0)
		return ERR_ILLEGALPARAM;

	Start_index = PageSize*PageIndex;
	if (!ShowLines)
	{
		if (Start_index >= OperateChart->UsedLines)
			return ERR_ILLEGALPARAM;
		else
		{
			if (Start_index + PageSize < OperateChart->UsedLines)
			{
				End_index = Start_index + PageSize;
			}
			else {
				End_index = OperateChart->UsedLines;
			}
		}
	}
	else {
		if (PageSize*PageIndex >= ShowLines->listCount)
			return ERR_ILLEGALPARAM;
		else
		{
			if (Start_index + PageSize < ShowLines->listCount)
			{
				End_index = Start_index + PageSize;
			}
			else {
				End_index = ShowLines->listCount;
			}
		}
	}

	if (ShowTitle&&ShowTitle->listCount <= 0)
	{
		FreeList(ShowTitle);
		ShowTitle = NULL;
	}

	if (Mode == 1)
		printf("���   ");
	if (!ShowTitle)
	{
		//��ָ�����⽫ʹ��Ĭ��
		for (a = 0; a < OperateChart->TitleCount; a++)
			printf("%-*s ", OperateChart->ChartLimits[a], OperateChart->ChartTitle[a]);
	}
	else {
		tempTitleList = ShowTitle->list;
		for (a = 0; a < ShowTitle->listCount; a++)
		{
			if (*tempTitleList < OperateChart->TitleCount)
				printf("%-*s ", OperateChart->ChartLimits[*tempTitleList], OperateChart->ChartTitle[*tempTitleList]);
			tempTitleList++;
		}
	}
	printf("\n");

	if (ShowLines)
	{
		tempLineList = ShowLines->list + Start_index;
		//��List����ʾ��Ϣ
		if (ShowTitle)
		{
			//�������������ʾ
			switch (Mode)
			{
			case 0:
				for (a = Start_index; a < End_index; a++)
				{
					if (*tempLineList < OperateChart->UsedLines) {
						tempTitleList = ShowTitle->list;
						for (b = 0; b < ShowTitle->listCount; b++)
						{
							if (*tempTitleList < OperateChart->TitleCount)
								printf("%-*s ", OperateChart->ChartLimits[*tempTitleList], OperateChart->Chart[*tempLineList][*tempTitleList]);
							tempTitleList++;
						}
						printf("\n");
					}
					tempLineList++;
				}
				break;
			case 1:
				for (a = Start_index; a < End_index; a++)
				{
					if (*tempLineList < OperateChart->UsedLines) {
						tempTitleList = ShowTitle->list;
						printf("%-7d ", a);
						for (b = 0; b < ShowTitle->listCount; b++)
						{
							if (*tempTitleList < OperateChart->TitleCount)
								printf("%-*s ", OperateChart->ChartLimits[*tempTitleList], OperateChart->Chart[*tempLineList][*tempTitleList]);
							tempTitleList++;
						}
						printf("\n");
					}
					tempLineList++;
				}
				break;
			}
		}
		else {
			//ֻ��IndexList����ʾ
			switch (Mode)
			{
			case 0:
				for (a = Start_index; a < End_index; a++)
				{
					if (*tempLineList < OperateChart->UsedLines) {
						for (b = 0; b < OperateChart->TitleCount; b++)
							printf("%-*s ", OperateChart->ChartLimits[b], OperateChart->Chart[*tempLineList][b]);
						printf("\n");
					}
					tempLineList++;
				}
				break;
			case 1:
				for (a = Start_index; a < End_index; a++)
				{
					if (*tempLineList < OperateChart->UsedLines) {
						printf("%-7d ", a);
						for (b = 0; b < OperateChart->TitleCount; b++)
							printf("%-*s ", OperateChart->ChartLimits[b], OperateChart->Chart[*tempLineList][b]);
						printf("\n");
					}
					tempLineList++;
				}
				break;
			}
		}
	}
	else {
		if (ShowTitle)
		{
			//��TitleList���������ʾ
			switch (Mode)
			{
			case 0:
				for (a = Start_index; a < End_index; a++)
				{
					tempTitleList = ShowTitle->list;
					for (b = 0; b < ShowTitle->listCount; b++)
					{
						if (*tempTitleList < OperateChart->TitleCount)
							printf("%-*s ", OperateChart->ChartLimits[*tempTitleList], OperateChart->Chart[a][*tempTitleList]);
						tempTitleList++;
					}
					printf("\n");
				}
				break;
			case 1:
				for (a = Start_index; a < End_index; a++)
				{
					tempTitleList = ShowTitle->list;
					printf("%-7d ", a);
					for (b = 0; b < ShowTitle->listCount; b++)
					{
						if (*tempTitleList < OperateChart->TitleCount)
							printf("%-*s ", OperateChart->ChartLimits[*tempTitleList], OperateChart->Chart[a][*tempTitleList]);
						tempTitleList++;
					}
					printf("\n");
				}
				break;
			}
		}
		else {
			//�����κα���ʾ
			switch (Mode)
			{
			case 0:
				for (a = Start_index; a < End_index; a++)
				{
					for (b = 0; b < OperateChart->TitleCount; b++)
						printf("%-*s ", OperateChart->ChartLimits[b], OperateChart->Chart[a][b]);
					printf("\n");
				}
				break;
			case 1:
				for (a = Start_index; a < End_index; a++)
				{
					printf("%-7d ", a);
					for (b = 0; b < OperateChart->TitleCount; b++)
						printf("%-*s ", OperateChart->ChartLimits[b], OperateChart->Chart[a][b]);
					printf("\n");
				}
				break;
			}
		}
	}
	return SUCCESS;
}

/*
�Ա�����������ʼ��
CreateCount     Ҫ�����ı������
*/
ErrVal NewChartSet(int CreateCount)
{

	int a;
	Chart** tempChartSet = NULL; //�µı�
	int NewChartCount;
	if (CreateCount <= 0)
		return ERR_ILLEGALPARAM;

	if (ChartCount < 0)
		ChartCount = 0;

	NewChartCount = ChartCount + CreateCount;
	if (NewChartCount <= ChartCount)
		return ERR_ILLEGALPARAM;

	if (NewChartCount <= 0)
		return ERR_ILLEGALPARAM;

	if (AlloctedChartCount <= 0)
	{
		//ȫ�³�ʼ����
		tempChartSet = (Chart**)malloc(sizeof(Chart*)*CreateCount);
		if (!tempChartSet)
			return ERR_MEMORYNOTENOUGH;
		for (a = 0; a < CreateCount; a++)
		{
			tempChartSet[a] = (Chart*)calloc(sizeof(Chart), sizeof(Chart));
			if (!tempChartSet[a])
			{
				for (a--; a >= 0; a--)
					free(tempChartSet[a]);
				free(tempChartSet);
				return ERR_MEMORYNOTENOUGH;
			}
		}
	}
	else {
		//������ʼ��
		tempChartSet = (Chart**)malloc(sizeof(Chart*)*NewChartCount);
		if (tempChartSet) {
			for (a = 0; a < ChartCount; a++)
				tempChartSet[a] = ChartHead[a];
			for (; a < NewChartCount; a++)
			{
				tempChartSet[a] = (Chart*)calloc(sizeof(Chart), sizeof(Chart));
				if (!tempChartSet[a])
				{
					if (a != ChartCount){
						for (a--; a >= ChartCount; a--)
						{
							free(tempChartSet[a]);
						}
					}
					free(tempChartSet);
					return ERR_MEMORYNOTENOUGH;
				}
			}
		}
		else return ERR_MEMORYNOTENOUGH;
	}
	if (ChartHead)
		free(ChartHead);
	ChartHead = tempChartSet;
	AlloctedChartCount = NewChartCount;
	ChartCount = NewChartCount;
	return SUCCESS;
}

/*
���Ѿ���ʼ���õı�����
!!!�˲�����ͬʱ�������б�
*/
ErrVal FreeChartSet()
{
	int a;
	if (!ChartHead)
		return SUCCESS;

	for (a = 0; a < ChartCount; a++)
	{
		if (ChartHead[a]) {
			FreeChart(ChartHead[a]);		//����ÿһ����
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
����IndexList���н�������
OperateList     ������Chart����lines���±������,������һ���Ϸ���IndexList
Mode   0   ����
Mode   1   ����
*/
#if SORT_ARITHMETIC==0
ErrVal Sort(Chart *OperateChart, IndexList *OperateList, int BaseTitleIndex, int Mode)
{
	int a, b;
	int temp;		//����ʱ���ڴ洢�м�ֵ�ı���

	switch (Mode)
	{
	case 0:
		//����
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
		//����
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
#else
void Swap(int *A, int *B)
{
	int tmp = *A;
	*A = *B;
	*B = tmp;
}

//�Ӵ�С
int QuickSortX(Chart *OperateChart, IndexList *OperateList, int BaseTitleIndex, int Mode, int Low, int High)
{
	int L_p, R_p;
	char *privotKey = OperateChart->Chart[OperateList->list[Low]][BaseTitleIndex];
	int privotIndex = OperateList->list[Low];
	int temp;

	if (High - Low < SORT_CHUNK_SIZE)
		return 0;
	//if (High - Low < 1000)
	//return 0;

	L_p = Low;
	R_p = High;
	while (L_p != R_p) {
		while (StrCmp(OperateChart->Chart[OperateList->list[R_p]][BaseTitleIndex], privotKey) <= 0 && L_p < R_p)
			R_p--;
		while (StrCmp(OperateChart->Chart[OperateList->list[L_p]][BaseTitleIndex], privotKey) >= 0 && L_p < R_p)
			L_p++;
		if (L_p < R_p) {
			temp = OperateList->list[L_p];
			OperateList->list[L_p] = OperateList->list[R_p];
			OperateList->list[R_p] = temp;
		}
	}
	OperateList->list[Low] = OperateList->list[L_p];
	OperateList->list[L_p] = privotIndex;

	if (L_p - 1 > Low)
		QuickSortX(OperateChart, OperateList, BaseTitleIndex, Mode, Low, L_p - 1);
	if (L_p + 1 < High)
		QuickSortX(OperateChart, OperateList, BaseTitleIndex, Mode, L_p + 1, High);
	return L_p;
}

ErrVal Sort(Chart *OperateChart, IndexList *OperateList, int BaseTitleIndex, int Mode)
{
	int a, b;
	int tmp;
	char *tmpchar;
	//���п���
	QuickSortX(OperateChart, OperateList, BaseTitleIndex, Mode, 0, OperateList->listCount - 1);
	/*
	for (a = 1; a < OperateList->listCount; a++)
	{
	if (StrCmp(OperateChart->Chart[OperateList->list[a - 1]][BaseTitleIndex], OperateChart->Chart[OperateList->list[a]][BaseTitleIndex]) < 0)
	{
	tmp = OperateList->list[a];
	tmpchar = OperateChart->Chart[OperateList->list[tmp]][BaseTitleIndex];
	for (b = a - 1; b >= 0 && StrCmp(OperateChart->Chart[OperateList->list[b]][BaseTitleIndex], tmpchar) < 0; b--)
	OperateList->list[b + 1] = OperateList->list[b];
	OperateList->list[b + 1] = tmp;
	}
	}
	*/
	return SUCCESS;
}
#endif


/*
��SearchList�ķ�Χ������������������,�����ظ�ResultList
OperateChart	Ҫ���в��ҵı�
SearchList		Ѱ�ҵķ�Χ,����ΪNULL,���ΪNULL,������������
ResultList		��������صĽṹ��
BaseTitleIndex	���бȽϵĻ�׼(ѡ�����Ǹ�����Ϊ��׼)
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

	if (!ResultList)
		return ERR_ILLEGALPARAM;

	if (!SearchList || SearchList->listCount == 0)
	{
		isNULL = 1;
		//���SearchListΪ��,���ʼ��һ��IndexList
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
���һ��List(����IndexList��TitleList),��0��ʼ���,���Զ���ʼ���ڴ�
OperateList     Ҫ���г�ʼ����list
Count           ��List��ΪIndexListʱһ����Ҫ�������е�����
����ΪTitleListʱһ����Ҫ�������еı��������
OperateList �е�list��Ա�����ָ�������ָ��������Ϊ0
*/
ErrVal FillList(List *OperateList, int Count)
{
	int a;
	//char temp[20];

	if (!OperateList)
		return ERR_ILLEGALCHART;

	if (OperateList->IsOnStack == 1 && (OperateList->list))
		free(OperateList->list);

	if (Count <= 0)
	{
		OperateList->IsOnStack = 0;
		OperateList->listCount = 0;
		OperateList->AllocatedList = 0;
		if (!OperateList->ListName)
			OperateList->ListName = (char*)malloc(sizeof(char) * 32);
		if (OperateList->ListName)
			strcpy(OperateList->ListName, "��List");
		else
			return ERR_MEMORYNOTENOUGH;
		return SUCCESS;
	}

	OperateList->list = (int*)malloc(sizeof(int)*Count);
	if (!OperateList->list)
		return ERR_MEMORYNOTENOUGH;
	OperateList->listCount = Count;
	OperateList->AllocatedList = Count;
	OperateList->IsOnStack = 1;

	for (a = 0; a < Count; a++)
		OperateList->list[a] = a;
	if (!OperateList->ListName)
		OperateList->ListName = (char*)malloc(sizeof(char) * 32);
	if (OperateList->ListName)
		sprintf(OperateList->ListName, "List(0-%d)", Count);
	return SUCCESS;
}

/*
�����ṩ��ֵ��ʼ��һ��List
OperateList     Ҫ���г�ʼ���Ľṹ��
Count           ListData�Ĳ�������
����FillList�Ĳ�������ܷ��ڳ�ʼ��ʱ�Զ���ÿһ��Ԫ��
*/
ErrVal InitList(List *OperateList, int Count, int ListData, ...)
{
	va_list ap;
	int a;
	//char temp[20];
	va_start(ap, ListData);

	if (OperateList->IsOnStack == 1 && (OperateList->list))
		free(OperateList->list);

	if (Count <= 0) {
		OperateList->listCount = 0;
		OperateList->IsOnStack = 0;
		OperateList->AllocatedList = 0;
		if (!OperateList->ListName)
			OperateList->ListName = (char*)malloc(sizeof(char) * 32);
		if (OperateList->ListName)
			strcpy(OperateList->ListName, "δ����");
		return SUCCESS;
	}

	OperateList->list = (int*)malloc(sizeof(int)*Count);
	if (!OperateList->list)
		return ERR_MEMORYNOTENOUGH;

	OperateList->listCount = Count;
	OperateList->AllocatedList = Count;
	OperateList->IsOnStack = 1;
	OperateList->list[0] = ListData;
	for (a = 1; a < Count; a++)
		OperateList->list[a] = va_arg(ap, int);

	if (!OperateList->ListName)
		OperateList->ListName = (char*)malloc(sizeof(char) * 32);
	if (OperateList->ListName)
		sprintf(OperateList->ListName, "List(%d)", Count);
	return SUCCESS;
}
/*
�ͷ�һ��list
*/
ErrVal FreeList(List *OperateList)
{
	if (!OperateList)
		return ERR_EMTYLIST;
	if (!OperateList->IsOnStack)
		return ERR_UNINITIALIZEDLIST;
	if (!OperateList->AllocatedList)
		return ERR_UNINITIALIZEDLIST;
	if (OperateList->ListName)
		free(OperateList->ListName);
	free(OperateList->list);
	return SUCCESS;
}

/*
��ListData����������OperateArray��ֵ
OperateArray	Ҫ���и�ֵ������
n				��ListData�б�����ĸ���(һ��ҪС�ڵ������������)
ListData		ֵ�б�,���б��е�ǰn��ֵ�ḳֵ��OperateArray������
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
�Ա�����������ʼ��
CreateCount     Ҫ�����ı������
ListType        Ҫ���г�ʼ����List����
ListType=0      ��IndexListHeadSet���в���
ListType=1      ��TitleListHeadSet���в���
*/
ErrVal NewListSet(int CreateCount, int ListType)
{
	int a;
	List** tempListSet = NULL;	//�µ�List��
	int NewListCount;
	List** OperateList = NULL;
	int ListCount, AlloctedListCount;

	//����Ϣ��Ӧ��ָ�����͵ı�
	switch (ListType)
	{
	case 0:
		OperateList = IndexListHeadSet;
		ListCount = IndexListCount;
		AlloctedListCount = AlloctedIndexListCount;
		break;
	case 1:
		OperateList = TitleListHeadSet;
		ListCount = TitleListCount;
		AlloctedListCount = AlloctedTitleListCount;
		break;
	default:
		return ERR_ILLEGALPARAM;
		break;
	}

	if (CreateCount <= 0)
		return ERR_ILLEGALPARAM;

	if (ListCount < 0)
		ListCount = 0;

	NewListCount = ListCount + CreateCount;
	if (NewListCount <= ListCount)
		return ERR_ILLEGALPARAM;

	if (AlloctedListCount <= 0)
	{
		//ȫ�³�ʼ��List��
		tempListSet = (List**)malloc(sizeof(List*)*CreateCount);
		if (!tempListSet)
			return ERR_MEMORYNOTENOUGH;
		for (a = 0; a < CreateCount; a++)
		{
			tempListSet[a] = (List*)calloc(sizeof(List), sizeof(List));
			if (!tempListSet[a])
			{
				for (a--; a >= 0; a--)
					free(tempListSet[a]);
				free(tempListSet);
				return ERR_MEMORYNOTENOUGH;
			}
		}
	}
	else {
		//������ʼ��
		tempListSet = (List**)malloc(sizeof(List*)*NewListCount);
		if (!tempListSet)
			return ERR_MEMORYNOTENOUGH;
		for (a = 0; a < ListCount; a++)
			tempListSet[a] = OperateList[a];
		for (; a < NewListCount; a++)
		{
			tempListSet[a] = (List*)calloc(sizeof(List), sizeof(List));
			if (!tempListSet[a])
			{
				if (a != ListCount){
					for (a--; a >= ListCount; a--)
					{
						free(tempListSet[a]);
					}
				}
				free(tempListSet);
				return ERR_MEMORYNOTENOUGH;
			}
		}
	}
	if (OperateList)
		free(OperateList);
	switch (ListType)
	{
	case 0:
		IndexListHeadSet = tempListSet;
		AlloctedIndexListCount = NewListCount;
		IndexListCount = NewListCount;
		break;
	case 1:
		TitleListHeadSet = tempListSet;
		AlloctedTitleListCount = NewListCount;
		TitleListCount = NewListCount;
		break;
	}
	return SUCCESS;
}

/*
�ͷ�List��
�����õ����ж�Ӧ����(IndexList��TitleList)�ı�ʱ,�ɵ��ô˺�����List�������ڴ��ͷ�
ListType        Ҫ�����ͷŵ�List����
ListType=0      ��IndexListHeadSet���в���
ListType=1      ��TitleListHeadSet���в���
*/
ErrVal FreeListSet(int ListType)
{
	int a;
	int ListCount;
	List** OperateList;
	switch (ListType)
	{
	case 0:
		if (!IndexListHeadSet)
			return SUCCESS;
		OperateList = IndexListHeadSet;
		ListCount = IndexListCount;
		break;
	case 1:
		if (!TitleListHeadSet)
			return SUCCESS;
		OperateList = TitleListHeadSet;
		ListCount = TitleListCount;
		break;
	default:
		return ERR_ILLEGALPARAM;
	}

	for (a = 0; a < ListCount; a++)
	{
		if (OperateList[a]) {
			FreeList(OperateList[a]);		//����ÿһ��List
			free(OperateList[a]);
		}
	}
	free(OperateList);
	switch (ListType)
	{
	case 0:
		IndexListHeadSet = NULL;
		IndexListCount = 0;
		AlloctedIndexListCount = 0;
		break;
	case 1:
		TitleListHeadSet = NULL;
		TitleListCount = 0;
		AlloctedTitleListCount = 0;
		break;
	}
	return SUCCESS;
}

/*
��DestList���Ƶ�SourceList
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
�ú�����һ���ַ����е����ֻ����������ȡ����,���list��
��������� ��ʽ����5 4 2 1 3
���Դ��� 1-5 ����������,���ͬ��1 2 3 4 5
n ��������ֵĸ���,�ɳ���,��������,���ϵ���ڴ�ķ���
list �洢��Ŀ��List
MaxIndex ���ƴ������ݵ����ֵ(ֻ��Ϊ�˰�ȫ���),���ֵһ����ָ��Chart���TitleCount
�ַ����е�ֵ�Ǵ�1��ʼ��
*/
ErrVal GetListFromString(char* Input, int n, List *list, int MaxIndex)
{
	int len2;
	char *temp2;
	int a = 0, b;
	char* c1, *c2;
	int temp, temp3;
	const char *Delimer = " \t\n";

	if (n <= 0)
		return ERR_ILLEGALPARAM;
	if (list)
	{
		if (list->AllocatedList <= 0 || !list->list)
		{
			a = FillList(list, n);
			if (a)
			{
				if (a != ERR_MEMORYNOTENOUGH)
					FreeList(list);
				return a;
			}
		}
	}
	else return ERR_ILLEGALPARAM;

	if (!list->list)
		return ERR_EMTYLIST;

	temp2 = strtok(Input, Delimer);
	for (a = 0; temp2 != NULL&&a < list->AllocatedList; )
	{
		len2 = (int)strlen(temp2);
		c1 = temp2;
		c2 = temp2;
		for (b = 0; b < len2 - 1; b++)
		{
			if (temp2[b] == '-')
			{
				c2 = temp2 + b + 1;
				temp2[b] = 0;
				break;
			}
		}
		temp = atoi(c1) - 1;
		temp3 = atoi(c2) - 1;
		for (b = temp; b <= temp3; b++)
		{
			list->list[a] = b;
			if (b >= 0 && b < MaxIndex)
				a++;
		}
		temp2 = strtok(NULL, Delimer);
	}

	list->listCount = a;
	return SUCCESS;
}

/*
�ú�����һ���ַ�����ָ���ĵ�n��Ԫ�ش��ResultList��
����SourceList��List������Ϊ   5 1 2 4 3
Input��ֵΪ1-5(��1 2 3 4 5)
��ResultList�е�ֵΪ 5 1 2 4 3

���Input��ֵΪ 1 3 2 4 5(��1 3 2 4-5)
��ResultList�е�ֵΪ 5 2 1 4 3
���Դ��� 1-5 ����������,���ͬ��1 2 3 4 5
Resultlist �洢��Ŀ��List
SourceList ԴList
*/
ErrVal GetListFromStringViaList(char* Input, int n, List *Resultlist, List *SourceList)
{
	int len2;
	char *temp2;
	int a = 0, b;
	char* c1, *c2;
	int temp, temp3;
	const char *Delimer = " \t\n";

	if (n <= 0)
		return ERR_ILLEGALPARAM;
	if (!SourceList||SourceList->listCount<=0)
		return ERR_EMTYLIST;

	if (Resultlist)
	{
		if (Resultlist->AllocatedList <= 0 || !Resultlist->list)
		{
			a = FillList(Resultlist, n);
			if (a)
			{
				if (a != ERR_MEMORYNOTENOUGH)
					FreeList(Resultlist);
				return a;
			}
		}
	}
	else 
		return ERR_ILLEGALPARAM;

	if (!Resultlist->list)
		return ERR_EMTYLIST;



	temp2 = strtok(Input, Delimer);
	for (a = 0; temp2 != NULL&&a < Resultlist->AllocatedList; )
	{
		len2 = (int)strlen(temp2);
		c1 = temp2;
		c2 = temp2;
		for (b = 0; b < len2 - 1; b++)
		{
			if (temp2[b] == '-')
			{
				c2 = temp2 + b + 1;
				temp2[b] = 0;
				break;
			}
		}
		temp = atoi(c1) - 1;
		temp3 = atoi(c2) - 1;
		for (b = temp; b <= temp3; b++)
		{
			Resultlist->list[a] = SourceList->list[b];
			if (b >= 0 && b < SourceList->listCount)
				a++;
		}
		temp2 = strtok(NULL, Delimer);
	}

	Resultlist->listCount = a;
	return SUCCESS;
}


/*
ErrVal GetListFromString(char* Input, List *list, int MaxIndex)
{
int len = (int)strlen(Input);
char *temp2;
int a = 0;
int temp;
const char *Delimer = " \t";

if (len <= 0)
return ERR_ILLEGALPARAM;
if (list) {
if (list->AllocatedList <= 0 || !list->list) {
a = FillList(list, len);
if (a)
{
if (a != ERR_MEMORYNOTENOUGH)
FreeList(list);
return a;
}

}
}
else return ERR_ILLEGALPARAM;

if (!list->list)
{
return ERR_EMTYLIST;
}

temp2 = strtok(Input, Delimer);
for (a = 0; temp2 != NULL&&a < list->AllocatedList; ) {
temp = atoi(temp2) - 1;
list->list[a] = temp;
if (temp >= 0 && temp < MaxIndex)
a++;
temp2 = strtok(NULL, Delimer);
}

list->listCount = a;
return SUCCESS;
}
*/

/*
�����ַ������бȽ�,���������ַ����Ƚ�
*/
int StrCmp(const char *A, const char *B)
{
	int isNumA = 1, isNumB = 1;
	int lenA = 0, lenB = 0;
	char *A2 = (char*)A, *B2 = (char*)B;

	//���㳤�Ȳ��ж��Ƿ��Ǵ�����
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
		//�������ֽ��бȽ�
		if (lenA != lenB) {
			//����������ֵĳ��Ȳ�ͬ,�򳤵����ִ�
			return lenA - lenB;
		}
		else {
			//������ֳ�����ͬ,���Ӹ�λ����λ���αȽ�
			return strcmp(A, B);
		}
	}
	else {
		//�����ֽ��бȽ�
		return strcmp(A, B);
	}
}

/*
ͨ����ͷ�ı����ҵ���ͷ��Ӧ�ı��
OperateChart        ����Ѱ�ҵı������ڵı�
UnitHeadName        �ַ���"����"
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

/*
��·���ַ����ж�ȡ�ļ�����
*/
char* GetFileName(const char* Path)
{
	int b;
	char *returnVal = NULL;

	for (b = (int)strlen(Path); b >= 0; b--)
		if (Path[b] == '/' || Path[b] == '\\')
			break;
	b++;

	returnVal = (char*)malloc(sizeof(char)*(strlen(Path + b) + 1));
	if (returnVal)
		strcpy(returnVal, Path + b);
	return returnVal;
}


/***********************************�ڲ�����******************************************/
/*
���ַ������м򵥼��ܽ���
*/
ErrVal EncryptChar(const char *ResultString, const char *SourceString, int size, const char* PassWord, int PassWord_len)
{
	int b;
	char *SStr = (char*)SourceString, *RStr = (char*)ResultString;
	for (b = 0, size--; size >= 0; size--, b = (b + 1) % PassWord_len)
		*RStr++ = ((int)(*SStr++)) ^ (PassWord[b] + PassWord_len);
	*RStr = 0;
	return SUCCESS;
}
