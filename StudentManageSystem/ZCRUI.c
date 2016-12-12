#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "ZCRUI.h"

void MainMenu()
{
	void SubMenu_Read();
	void SubMenu_Search();

	while (1)
	{
		COMMAND_CLEAR();
		printf(
			DELIMS_LINE\
			"                     ���˵�\n"\
			DELIMS_LINE\
		);
		Menu_DisplaySubMenu();

		printf(
			DELIMS_LINE\
			" [1].��ȡ�ļ�\n"\
			" [2].��ѧ����������\n"\
			" [3].����ָ��ѧ��\n"\
			" [4].�޸�ѧ����Ϣ\n"\
			" [5].��ʾѧ����Ϣ\n"\
			" [6].����(����)��Ϣ\n"\
			" [7].�߼�����\n"\
			" [0].�˳�ϵͳ\n"\
			DELIMS_LINE
		);
		switch (Event_Input())
		{
		case 1:
			SubMenu_Read();
			break;
		case 2:
			//����
			break;
		case 3:
			//����
			SubMenu_Search();
			break;
		case 4:
			//�޸�
			break;
		case 5:
			//��ʾѧ����Ϣ
			break;
		case 6:
			//������Ϣ
			break;
		case 7:
			//�߼�����
			break;
		case 0:
			exit(0);
		}
	}
	return 0;
}

//��ȡ�����Ӳ˵�
void SubMenu_Read()
{
	void Sub_ChoiceFileToRead1();
	void Sub_ChoiceFileToRead2();
	while (1)
	{
		COMMAND_CLEAR();
		printf(
			DELIMS_LINE\
			"                    ��ȡ�ļ�\n"
			DELIMS_LINE\
		);
		Menu_DisplaySubMenu();
		printf(
			DELIMS_LINE\
			" [1].���ı��ļ���ȡ\n"\
			" [2].�Ӷ������ļ���ȡ\n"\
			" [0].�������˵�\n"
			DELIMS_LINE
		);
		switch (Event_Input())
		{
		case 1:
			//���ı���ȡ����
			Sub_ChoiceFileToRead1();
			break;
		case 2:
			//�Ӷ������ļ���ȡ����
			Sub_ChoiceFileToRead2();
			break;
		case 0:
			return;
		}
	}
}
//���ı���ȡ����
void Sub_ChoiceFileToRead1()
{
	char ParamFilePath[512] = "";
	char DataFilePath[512] = "";
	char SexTranslateFilePath[512] = "";
	char CollegeTranslateFilePath[512] = "";
	int returnVal;
	InfoMap im;
	while (1)
	{
		COMMAND_CLEAR();
		printf(
			DELIMS_LINE\
			"                 ѡ��Ҫ��ȡ���ļ�\n"
			DELIMS_LINE\
		);
		Menu_DisplaySubMenu();

		printf(
			DELIMS_LINE\
			" [1].�����б��ļ�·��:%s\n"\
			" [2].�����ļ�·��:%s\n"\
			" [3].�Ա�ӳ���ļ�·��:%s\n"\
			" [4].ѧԺ��Ϣӳ���ļ�·��:%s\n"
			" Tip:�����Ӧ���ֽ�����������\n",
			ParamFilePath, DataFilePath, SexTranslateFilePath, CollegeTranslateFilePath
		);
		printf(
			DELIMS_LINE\
			" [5].��ʼ��ȡ\n"\
			" [0].������һ��\n"
			DELIMS_LINE
		);
		switch (Event_Input())
		{
		case 1:
			printf("����������б��ļ�·��:\n");
			scanf("%s", ParamFilePath);
			break;
		case 2:
			printf("�����������ļ�·��:\n");
			scanf("%s", DataFilePath);
			break;
		case 3:
			printf("�������Ա�ӳ���ļ�·��:\n");
			scanf("%s", SexTranslateFilePath);
			break;
		case 4:
			printf("������ѧԺ��Ϣӳ���ļ�·��:\n");
			scanf("%s", CollegeTranslateFilePath);
			break;
		case 5:
			returnVal = ReadFromTwoFile(ParamFilePath, DataFilePath, ChartHead[CurrentChartIndex]);
			if (!returnVal)
			{
				printf("��ȡ�����ļ��ɹ�\n");
				//��������
				returnVal = SHI(ChartHead[CurrentChartIndex], "�Ա�");
				if (returnVal != -1) {
					ReadMapFile(SexTranslateFilePath, &im);
					Translate(ChartHead[CurrentChartIndex], returnVal, &im);
					FreeMapStruct(&im);
				}
				returnVal = SHI(ChartHead[CurrentChartIndex], "ѧԺ����");
				if (returnVal != -1) {
					ReadMapFile(CollegeTranslateFilePath, &im);
					Translate(ChartHead[CurrentChartIndex], returnVal, &im);
					FreeMapStruct(&im);
				}
			}
			else if (returnVal == ERR_OPENFILE) {
				printf("��ȡ�ļ�ʧ��,��ȷ��·���Ƿ���ȷ,");
			}
			else if (returnVal == ERR_NOTSTANDARDFILE) {
				printf("Ŀ���ļ������ϱ�׼,�뻻һ���ļ�����\n");
			}
			getch();
			//��ȡ����
			break;
		case 0:
			return 0;
		}
	}
}
//�Ӷ������ļ���ȡ����
void Sub_ChoiceFileToRead2()
{
	char FilePath[512] = "";
	char PassWord[32] = "";
	int returnVal;
	while (1)
	{
		COMMAND_CLEAR();
		printf(
			DELIMS_LINE\
			"                 ѡ��Ҫ��ȡ���ļ�\n"
			DELIMS_LINE\
		);
		Menu_DisplaySubMenu();
		printf(
			DELIMS_LINE
			" [1].�������ļ����·��:%s\n"\
			" Tip:�����Ӧ���ֽ�����������\n",
			FilePath
		);
		printf(
			DELIMS_LINE\
			" [2].��ʼ��ȡ\n"\
			" [0].������һ��\n"
			DELIMS_LINE
		);
		switch (Event_Input())
		{
		case 1:
			printf("������������ļ����·��:\n");
			scanf("%s", FilePath);
			break;
		case 2:
			printf("�������ļ���������:\n");
			scanf("%s", PassWord);
			returnVal = ReadFromBinFile(FilePath, PassWord, ChartHead[CurrentChartIndex]);
			if (!returnVal)
				printf("��ȡ�ļ��ɹ�\n");
			else if (returnVal == ERR_WRONGPASSWORD)
				printf("�������,�޷���ȡ�ļ�\n");
			else if (returnVal == ERR_OPENFILE)
				printf("�ļ�·������\n");
			getch();
			break;
		case 0:
			return 0;
		}
	}
}


//���������Ӳ˵�
void SubMenu_Search()
{
	void Sub_Search1();
	int returnVal;
	while (1)
	{
		COMMAND_CLEAR();
		printf(
			DELIMS_LINE\
			"                     ������Ϣ\n"\
			DELIMS_LINE\
		);
		Menu_DisplaySubMenu();
		Menu_DisplaySubMenu_Search();
		printf(
			DELIMS_LINE\
			" [1].���������в���\n"\
			" [2].��ѧ�Ž��в���\n"\
			" [3].��ѡ����Ϣ����в���\n"\
			" [4].��ʾ���\n"\
			" [0].�������˵�\n"\
			DELIMS_LINE
		);
		switch (Event_Input())
		{
		case 1:
			returnVal = SHI(ChartHead[0], "����");
			if (returnVal != -1)
			{
				CurrentTitleIndex = returnVal;
				Sub_Search1();
			}
			getch();
			//���������в���
			break;
		case 2:
			returnVal = SHI(ChartHead[0], "ѧ��");
			if (returnVal != -1)
			{
				CurrentTitleIndex = returnVal;
				Sub_Search1();
			}
			getch();
			break;
		case 3:
			Sub_Search1();
			getch();
			break;
		case 4:
			Display_Chart(ChartHead[CurrentChartIndex], IndexListHeadSet[CurrentIndexListIndex], TitleListHeadSet[CurrentTitleListIndex], DISPLAY_HIDENUMBER);
			getch();
			break;
		case 0:
			return;
		}
	}
}
//Sub_Search1���ӹ���
void Sub_Search1()
{
	int WhichListSaveTo();
	int returnVal, SaveIndex;
	char SearchString[512];
	if (CurrentChartIndex >= 0 && CurrentChartIndex < ChartHead[CurrentChartIndex]->TitleCount) {
		printf("������Ҫ������%s:\n", ChartHead[CurrentChartIndex]->ChartTitle[CurrentTitleIndex]);
		scanf("%s", SearchString);
		printf("��ѡ�񱣴���������:\n");
		SaveIndex = WhichListSaveTo();
		if (!IndexListHeadSet[SaveIndex] || IndexListHeadSet[SaveIndex]->AllocatedList == 0)
			if (IndexListHeadSet[CurrentIndexListIndex] && IndexListHeadSet[CurrentIndexListIndex]->listCount > 0)
				FillList(IndexListHeadSet[SaveIndex], IndexListHeadSet[CurrentIndexListIndex]->list);
			else
				FillList(IndexListHeadSet[SaveIndex], ChartHead[CurrentChartIndex]->UsedLines);
		returnVal = Search(ChartHead[CurrentChartIndex], IndexListHeadSet[CurrentIndexListIndex], IndexListHeadSet[SaveIndex], CurrentTitleIndex, SearchString);
		if (!returnVal)
		{
			if (IndexListHeadSet[SaveIndex]->listCount > 0) {
				printf("�ɹ��ҵ���������\n");
				Display_Chart(ChartHead[0], IndexListHeadSet[SaveIndex], TitleListHeadSet[CurrentTitleListIndex], DISPLAY_HIDENUMBER);
				CurrentTitleIndex = SaveIndex;
				printf("���ҵ�%d�����\n", IndexListHeadSet[SaveIndex]->listCount);
			}
			else
				printf("û���ҵ��������\n");
		}
		else if (returnVal == ERR_ILLEGALCHART) {
			printf("����ı�,����û�ж�ȡ���ļ�\n");
		}
	}
	else
		printf("����ʧ��\n");
}
//Sub_Search1���ӹ���
int WhichListSaveTo()
{
	int a, b = -1;
	printf(" ��������Ҫ���ĸ������д�Ž��\n");
	printf("������һ�����ֽ���ѡ��\n");
	for (a = 0; a < IndexListCount; a++)
		if (IndexListHeadSet[a] && IndexListHeadSet[a]->ListName)
			printf("  [%d]. %s\n", a + 1, IndexListHeadSet[a]->ListName);
		else
			printf("  [%d]. δ����\n", a + 1);
	while (b<1 || b>IndexListCount)
		scanf("%d", &b);
	return b - 1;
}