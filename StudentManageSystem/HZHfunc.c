#include "menu.h"

//����˵�
void SubMenu_SortList()
{
    void Sub_SortListByName();
    void Sub_SortListByAver();
    void Sub_SortListByWhatever();
#if RANDOMCOLOR
	ChangeColor();
#endif
	while (1)
	{
		COMMAND_CLEAR();
		printf(
			DELIMS_LINE
			"                    ѧ������\n"
			DELIMS_LINE
		);
		Menu_DisplaySubMenu();
		printf(
			DELIMS_LINE
			" [1].������������\n"
			" [2].����ƽ���ɼ�����\n"
			" [3].�������ⵥԪ����\n"
			" [0].�������˵�\n"
			DELIMS_LINE
		);

		switch (Event_Input())
		{
		case 1:
			Sub_SortListByName();
			break;
		case 2:
			Sub_SortListByAver();
			break;
		case 3:
			Sub_SortListByWhatever();
			break;
		case 4:
			SubMenu_Display();
			break;
		case 0:
			return;
		}

	}
}

//��������ɼ�ƽ��ֵ
void CaluAverage()
{
	int i, t;                       //ѭ������
	int returnVal = 0;
	double sum = 0;
	char UnitName[1][32] = { "ƽ���ɼ�" };     //���ڴ����µ�unit(ƽ���ɼ�)
	int NewTitleLimits[1] = { 8 };
	char temp[128];
	int NewUnitIndex;
	IndexList tempList = { 0 };
#if RANDOMCOLOR
	ChangeColor();
#endif
	while (1)
	{
		COMMAND_CLEAR();
		printf(
			DELIMS_LINE\
			"                 ����ƽ���ɼ�\n"
			DELIMS_LINE\
		);
		Menu_DisplaySubMenu();
		printf(
			DELIMS_LINE\
			" [1].����ƽ���ɼ��Ŀ�Ŀ:"
		);
		for (i = 0; i < tempList.listCount; i++) {
			printf("%s ", ChartHead[CurrentChartIndex]->ChartTitle[tempList.list[i]]);
		}
		printf(
			"\n"
			" Tip:�����Ӧ���ֽ�����������\n"\
			DELIMS_LINE\
			" [2].��ʼ����\n"\
			" [3].�鿴��Ϣ\n"\
			" [0].������һ��\n"\
			DELIMS_LINE
		);
		switch (Event_Input())
		{
		case 1:
			getchar();
			printf(DELIMS_LINE);
			if (ChartHead&&ChartHead[CurrentChartIndex]) {
				for (i = 4; i < ChartHead[CurrentChartIndex]->TitleCount; i++) {
					printf(" [%d].%s ", i + 1, ChartHead[CurrentChartIndex]->ChartTitle[i]);
				}
				printf(
					"\n"\
					DELIMS_LINE\
					"������Ҫ����ƽ���ֵ���,֧������������\"-\"�������������ֵ\n"
				);
				fgets(temp, 128, stdin);
				temp[strlen(temp) - 1] = 0;
				GetListFromString(temp, ChartHead[CurrentChartIndex]->TitleCount, &tempList, ChartHead[CurrentChartIndex]->TitleCount);
				if (tempList.listCount <= 0) {
					printf("�����ʽ����\n");
					GETCH();
				}
			}
			else {
				printf("���ȶ�ȡ�ļ�\n");
			}
			break;
		case 2:
			//����Ƿ����� �����Ŀ����
			if (tempList.listCount <= 0) {
				printf("����ѡ��Ҫ���м���Ŀ�Ŀ\n");
				GETCH();
				break;
			}

			if (ChartHead && ChartHead[CurrentChartIndex])
			{
				NewUnitIndex = SHI(ChartHead[CurrentChartIndex], "ƽ���ɼ�");
				if (NewUnitIndex == -1) {
					returnVal = CreateNewUnit(ChartHead[CurrentChartIndex], 1, UnitName, NewTitleLimits);
					if (!returnVal)
					{
						printf("�����µĵ�Ԫ���гɹ�\n");
						NewUnitIndex = SHI(ChartHead[CurrentChartIndex], "ƽ���ɼ�");
					}
					else {
						printf("�����µĵ�Ԫ��ʧ��\n");
						GETCH();
						break;
					}

				}
				for (i = 0; i < ChartHead[CurrentChartIndex]->UsedLines; i++)
				{
					sum = 0;
					for (t = 0; t < tempList.listCount; t++)
					{
						sum += atof(ChartHead[CurrentChartIndex]->Chart[i][tempList.list[t]]);
					}
					sprintf(ChartHead[CurrentChartIndex]->Chart[i][NewUnitIndex], "%.1lf", sum / 10);
				}
			}
			printf("����ƽ���ɼ��ɹ�\n");
			GETCH();
			break;
		case 3:
			SubMenu_Display();
			break;
		case 0:
			return;
		}
	}
}

//������������
void Sub_SortListByName()
{
	int SortMode = 0;               //����ģʽ
	int ReturnVal = 0;
#if RANDOMCOLOR
	ChangeColor();
#endif
	while (1)
	{
		COMMAND_CLEAR();
		printf(
			DELIMS_LINE\
			"                 ������������\n"
			DELIMS_LINE\
		);
		Menu_DisplaySubMenu();
		printf(
			DELIMS_LINE
			" [1].����ʽ:%s\n"\
			"\n"\
			" Tip:�����Ӧ���ֽ�����������\n"\
			DELIMS_LINE\
			" [2].��ʼ����\n"\
			" [3].��ʾ��Ϣ\n"\
			" [0].������һ��\n"\
			DELIMS_LINE,
			SortMode ? "����" : "����"
		);
		switch (Event_Input())
		{
		case 1:
			SortMode = !SortMode;
			break;
		case 2:
			if (ChartHead&&ChartHead[CurrentChartIndex]) {
				ReturnVal = SHI(ChartHead[CurrentChartIndex], "����");
				if (ReturnVal != -1)
				{
					if (ChartHead&&ChartHead[CurrentChartIndex] && ChartHead[CurrentChartIndex]->UsedLines > 0)
					{
						if (IndexListHeadSet) {
							if (IndexListHeadSet[CurrentTitleListIndex] && IndexListHeadSet[CurrentTitleListIndex]->AllocatedList <= 0)
							{
								FillList(IndexListHeadSet[CurrentTitleListIndex], ChartHead[CurrentChartIndex]->UsedLines);
							}
							printf("��������,�����ĵȴ�...\n");
							ReturnVal = Sort(ChartHead[CurrentChartIndex], IndexListHeadSet[CurrentTitleListIndex], ReturnVal, SortMode);

							if (!ReturnVal) {
								printf("����ɹ�\n");
							}
							else {
								printf("����ʧ��\n");
							}
						}
						else printf("���ȳ�ʼ����\n");
					}
				}
				else
					printf("���ȶ�ȡ��\n");
			}
			else printf("���ȶ�ȡ��\n");
			GETCH();
			break;
		case 3:
			SubMenu_Display();
			break;
		case 0:
			return;
		}
	}
}

//����ƽ���ɼ�����
void Sub_SortListByAver()
{
	int ReturnVal = 0;
	int SortMode = 0;
#if RANDOMCOLOR
	ChangeColor();
#endif
	while (1)
	{
		COMMAND_CLEAR();
		printf(
			DELIMS_LINE
			"                 ����ƽ���ɼ�����\n"
			DELIMS_LINE
		);
		Menu_DisplaySubMenu();
		printf(
			DELIMS_LINE
			" [1].����ʽ:%s\n"\
			"\n"\
			" Tip:�����Ӧ���ֽ�����������\n"\
			DELIMS_LINE\
			" [2].��ʼ����\n"\
			" [3].��ʾ��Ϣ\n"\
			" [0].������һ��\n"\
			DELIMS_LINE
			, SortMode ? "����" : "����"
		);
		switch (Event_Input())
		{
		case 1:
			SortMode = !SortMode;
			break;
		case 2:
			if (ChartHead) {
				ReturnVal = SHI(ChartHead[CurrentChartIndex], "ƽ���ɼ�");
				if (ReturnVal != -1)
				{
					if (ChartHead&&ChartHead[CurrentChartIndex] && ChartHead[CurrentChartIndex]->UsedLines > 0)
					{
						if (IndexListHeadSet) {
							if (IndexListHeadSet[CurrentTitleListIndex] && IndexListHeadSet[CurrentTitleListIndex]->AllocatedList <= 0)
							{
								FillList(IndexListHeadSet[CurrentTitleListIndex], ChartHead[CurrentChartIndex]->UsedLines);
							}
							printf("��������,�����ĵȴ�...\n");
							ReturnVal = Sort(ChartHead[CurrentChartIndex], IndexListHeadSet[CurrentTitleListIndex], ReturnVal, SortMode);
							if (!ReturnVal) {
								printf("����ɹ�\n");
							}
							else {
								printf("����ʧ��\n");
							}
						}
						else printf("���ȳ�ʼ��List��\n");
					}
				}
				else
					printf("����ȥ�߼������м���ƽ���ɼ�\n");
			}
			else printf("���ȶ�ȡ��Ϣ\n");
			GETCH();
			break;
		case 3:
			SubMenu_Display();
			break;
		case 0:
			return;

		}
	}
}

//�������ⵥԪ����
void Sub_SortListByWhatever()
{
	int SortMode = 0;
	int ReturnVal = 0;
	char* temp;
#if RANDOMCOLOR
	ChangeColor();
#endif
	while (1)
	{
		COMMAND_CLEAR();
		printf(
			DELIMS_LINE
			"                 �������ⵥԪ����\n"
			DELIMS_LINE
		);
		Menu_DisplaySubMenu();
		temp = Menu_DisplaySubMenu_Search();
		printf(
			DELIMS_LINE
			" [1].����ʽ:%s\n",
			SortMode ? "����" : "����"
		);

		printf(
			" Tip:�����Ӧ���ֽ�����������\n"\
			DELIMS_LINE\
			" [2].��\"%s\"%s����\n"\
			" [3].��ʾ��Ϣ\n"\
			" [0].������һ��\n"\
			DELIMS_LINE,
			temp,
			SortMode ? "����" : "����"
		);

		switch (Event_Input())
		{
		case 1:
			SortMode = !SortMode;
			break;
		case 2:
			if (ChartHead && ((ChartHead[CurrentChartIndex] && ChartHead[CurrentChartIndex]->HadInit != 0) || (!ChartHead[CurrentChartIndex]))) {
				if (IndexListHeadSet) {
					if (!IndexListHeadSet[CurrentIndexListIndex] || IndexListHeadSet[CurrentIndexListIndex]->listCount <= 0)
						FillList(IndexListHeadSet[CurrentIndexListIndex], ChartHead[CurrentChartIndex]->UsedLines);
					if (IndexListHeadSet[CurrentIndexListIndex]->listCount > 0) {
						printf("��������,�����ĵȴ�...\n");
						ReturnVal = Sort(ChartHead[CurrentChartIndex], IndexListHeadSet[CurrentIndexListIndex], CurrentTitleIndex, SortMode);
						if (!ReturnVal) {
							printf("����ɹ�\n");
						}
						else {
							printf("����ʧ��\n");
						}
					}
					else {
						printf("��ʼ��Listʧ��\n");
					}
				}
				else printf("���ȳ�ʼ��List��\n");
			}
			else printf("���ȶԱ���г�ʼ��\n");
			GETCH();
			break;
		case 3:
			SubMenu_Display();
			break;
		case 0:
			return;
		}
	}
}
