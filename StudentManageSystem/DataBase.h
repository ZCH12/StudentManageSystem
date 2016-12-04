#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ADDITIONAL 10		//����Ҫ���·����ڴ�ʱ,һ������ʮ����


//�������
#define SUCCESS 0
#define ERR_OPENFILE 1
#define ERR_NOTSTANDARDFILE 2
#define ERR_MEMORYNOTENOUGH 3

//���ͱ���
typedef int ErrVal;
typedef char*** Chart_t;
typedef char** ChartPiece_t;

//����һ����ṹ
typedef struct
{
	//��
	Chart_t Chart;				//�����������׵�ַ

	//����
	int TitleCount;				//�洢����ĸ���
	ChartPiece_t ChartTitle;	//�洢ÿ��������ַ�(ÿ�����ⲻ�ó���31����ĸ)
	int* ChartLimits;			//�洢ÿһ�������µĵ�Ԫ������ַ�������󳤶�

	//��
	int AllocatedLines;			//���ѷ���Ĵ�С(��ֵ���ڵ���UsedLines)(�ѷ��䵫δʹ�õ���δ�����ڴ�)
	int UsedLines;				//�ڱ���ʵ�ʱ�ʹ�õ���
	int HadInit;				//��¼������Ƿ��Ѿ�����ʼ��
} Chart;

//����һ�������ṹ��,����һ����ķ���,����Ԫ�ص���ʾ˳����Chart�������,����������ṹ���е����������˳�������
//ע����ʹ������ṹʱ,listҪ����ƥ���Chartһ��ʹ��,�������ֵò�����Ҫ�Ľ��
//#####Ҫȷ��listCount<UsedLines
typedef struct
{
	int *list;			//����,�����ֵ�洢����ָ�����е�ʵ���е������±�
	int listCount;		//��¼����ĸ���
} IndexList;


ErrVal ReadFromFile(char *FileName, Chart *OperateChart);
ErrVal CreateNewUnit(Chart *OperateChart, int CreateCount, char(*NewTitleSet)[32], int *NewTitleLimits);