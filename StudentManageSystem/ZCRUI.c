#include "menu.h"
#include "time.h"

//���˵����
void MainMenu()
{
	void SubMenu_Read();
	extern void SubMenu_SortList();
	void SubMenu_Search();
	void SubMenu_Change();
	void SubMenu_Display();
	void SubMenu_SaveToFile();
	void SubMenu_Advantage();

	char a;
	while (1)
	{
#if RANDOMCOLOR
		ChangeColor();
#endif
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
			SubMenu_Read();			//���ļ���ȡ��Ϣ
			break;
		case 2:
			SubMenu_SortList();           //��ѧ����Ϣ����
			break;
		case 3:
			SubMenu_Search();		//����ѧ����Ϣ
			break;
		case 4:
			SubMenu_Change();		//�޸�ѧ����Ϣ
			break;
		case 5:
			SubMenu_Display();		//��ʾѧ����Ϣ
			break;
		case 6:
			SubMenu_SaveToFile();	//������Ϣ
			break;
		case 7:
			SubMenu_Advantage();	//�߼�����
			break;
		case 0:
			printf("ȷ��Ҫ�˳���?(��Y�����˳�)\n����˳�,δ��������ݽ��ᶪʧ\n");
			getchar();
			scanf("%c", &a);
			if (a == 'Y' || a == 'y')
				exit(0);
		}
	}
	return;
}

//1��ȡ�����Ӳ˵�
void SubMenu_Read()
{
	void Sub_ChoiceFileToRead1();
	void Sub_ChoiceFileToRead2();
#if RANDOMCOLOR
	ChangeColor();
#endif
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
void Sub_ChoiceFileToRead1()
{
	char ParamFilePath[512] = "";
	char DataFilePath[512] = "";
	char SexTranslateFilePath[512] = "";
	char CollegeTranslateFilePath[512] = "";
	int returnVal;
	InfoMap im;
	ReadConfig1(CONFIGFILEPATH1, ParamFilePath, DataFilePath, SexTranslateFilePath, CollegeTranslateFilePath);
#if RANDOMCOLOR
	ChangeColor();
#endif
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
			"\n"\
			" Tip:�����Ӧ���ֽ�����������\n",
			ParamFilePath, DataFilePath, SexTranslateFilePath, CollegeTranslateFilePath
		);
		printf(
			DELIMS_LINE\
			" [5].��ʼ��ȡ\n"\
			" [6].��ʾ��Ϣ\n"\
			" [0].������һ��\n"
			DELIMS_LINE
		);
		switch (Event_Input())
		{
		case 1:
			printf("����������б��ļ�·��:\n");
			getchar();
			fgets(ParamFilePath, 512, stdin);
			ParamFilePath[strlen(ParamFilePath) - 1] = 0;
			break;
		case 2:
			printf("�����������ļ�·��:\n");
			getchar();
			fgets(DataFilePath, 512, stdin);
			DataFilePath[strlen(DataFilePath) - 1] = 0;
			break;
		case 3:
			printf("�������Ա�ӳ���ļ�·��:\n");
			getchar();
			fgets(SexTranslateFilePath, 512, stdin);
			SexTranslateFilePath[strlen(SexTranslateFilePath) - 1] = 0;
			break;
		case 4:
			printf("������ѧԺ��Ϣӳ���ļ�·��:\n");
			getchar();
			fgets(CollegeTranslateFilePath, 512, stdin);
			CollegeTranslateFilePath[strlen(CollegeTranslateFilePath) - 1] = 0;
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
				WriteConfig1(CONFIGFILEPATH1, ParamFilePath, DataFilePath, SexTranslateFilePath, CollegeTranslateFilePath);
			}
			else if (returnVal == ERR_OPENFILE) {
				printf("��ȡ�ļ�ʧ��,��ȷ��·���Ƿ���ȷ,");
			}
			else if (returnVal == ERR_NOTSTANDARDFILE) {
				printf("Ŀ���ļ������ϱ�׼,�뻻һ���ļ�����\n");
			}
			GETCH();
			//��ȡ����
			break;
		case 6:
			SubMenu_Display();
			break;
		case 0:
			return;
		}
	}
}
void Sub_ChoiceFileToRead2()
{
	char FilePath[512] = "";
	char PassWord[32] = "";
	int returnVal;
	ReadConfig2(CONFIGFILEPATH2, FilePath);
#if RANDOMCOLOR
	ChangeColor();
#endif
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
			"\n"\
			" Tip:�����Ӧ���ֽ�����������\n",
			FilePath
		);
		printf(
			DELIMS_LINE\
			" [2].��ʼ��ȡ\n"\
			" [3].��ʾ��Ϣ\n"\
			" [0].������һ��\n"
			DELIMS_LINE
		);
		switch (Event_Input())
		{
		case 1:
			printf("������������ļ����·��:\n");
			getchar();
			fgets(FilePath, 512, stdin);
			FilePath[strlen(FilePath) - 1] = 0;
			break;
		case 2:
			printf("�������ļ���������:\n");
			//scanf("%s", PassWord);
			InputPassWord(PassWord, 32);
			returnVal = ReadFromBinFile(FilePath, PassWord, ChartHead[CurrentChartIndex]);
			if (!returnVal) {
				WriteConfig2(CONFIGFILEPATH2, FilePath);
				printf("��ȡ�ļ��ɹ�\n");
			}
			else if (returnVal == ERR_WRONGPASSWORD)
				printf("�������,�޷���ȡ�ļ�\n");
			else if (returnVal == ERR_OPENFILE)
				printf("�ļ�·������\n");
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

//3���������Ӳ˵�
void SubMenu_Search()
{
	void Sub_Search1();
	extern int ShowPageList;
	int returnVal;
#if RANDOMCOLOR
	ChangeColor();
#endif
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
		Menu_DisplaySubMenu_Page();
		printf(
			DELIMS_LINE\
			" [1].���������в���\n"\
			" [2].��ѧ�Ž��в���\n"\
			" [3].��ѡ����Ϣ����в���\n"\
			" [4].��ʾ��Ϣ\n"\
			" [5].��ʼ����ǰ����\n"\
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
			else
			{
				printf("����û�������ֶ�\n");
			}
			GETCH();
			//���������в���
			break;
		case 2:
			returnVal = SHI(ChartHead[0], "ѧ��");
			if (returnVal != -1)
			{
				CurrentTitleIndex = returnVal;
				Sub_Search1();
			}
			else
			{
				printf("����û��ѧ���ֶ�\n");
			}
			GETCH();
			break;
		case 3:
			Sub_Search1();
			GETCH();
			break;
		case 4:
			SubMenu_Display();
			break;
		case 5:
			if (IndexListHeadSet&&ChartHead)
				FillList(IndexListHeadSet[CurrentIndexListIndex], ChartHead[CurrentChartIndex]->UsedLines);
			printf("��ʼ�����\n");
			GETCH();
			break;
		case 0:
			return;
		}
	}
}
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
		{
			if (IndexListHeadSet[CurrentIndexListIndex] && IndexListHeadSet[CurrentIndexListIndex]->listCount > 0)
			{
				FillList(IndexListHeadSet[SaveIndex], IndexListHeadSet[CurrentIndexListIndex]->listCount);
			}
			else
			{
				FillList(IndexListHeadSet[SaveIndex], ChartHead[CurrentChartIndex]->UsedLines);
			}
		}
		returnVal = Search(ChartHead[CurrentChartIndex], IndexListHeadSet[CurrentIndexListIndex], IndexListHeadSet[SaveIndex], CurrentTitleIndex, SearchString);
		if (!returnVal)
		{
			if (IndexListHeadSet[SaveIndex] && IndexListHeadSet[SaveIndex]->listCount > 0) {
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
int WhichListSaveTo()
{
	int a, b = -1;
	printf(" ��������Ҫ���ĸ������д�Ž��\n");
	printf("������һ�����ֽ���ѡ��\n");
	printf(DELIMS_LINE);
	for (a = 0; a < IndexListCount; a++)
		if (IndexListHeadSet[a] && IndexListHeadSet[a]->ListName)
			printf("  [%d]. %s\n", a + 1, IndexListHeadSet[a]->ListName);
		else
			printf("  [%d]. δ����\n", a + 1);
	printf(DELIMS_LINE);
	while (b<1 || b>IndexListCount)
		scanf("%d", &b);
	return b - 1;
}

//4�޸�ѧ����Ϣ
void SubMenu_Change()
{
	int returnVal;
	int ChoiceLines = 0;
	char *temp;
#if RANDOMCOLOR
	ChangeColor();
#endif
	while (1)
	{
		COMMAND_CLEAR();
		printf(
			DELIMS_LINE\
			"                     �޸���Ϣ\n"\
			DELIMS_LINE\
		);
		Menu_DisplaySubMenu();
		Menu_DisplaySubMenu_Search();
		if (ChartHead&&ChartHead[CurrentChartIndex]) {
			returnVal = SHI(ChartHead[CurrentChartIndex], "����");
			if (returnVal != -1) {
				if (ChartHead&&ChartHead[CurrentChartIndex] && ChartHead[CurrentChartIndex]->Chart&&ChartHead[CurrentChartIndex]->Chart[ChoiceLines] && ChartHead[CurrentChartIndex]->Chart[ChoiceLines][returnVal])
					temp = ChartHead[CurrentChartIndex]->Chart[ChoiceLines][returnVal];
				else {
					returnVal = 0;
					temp = NULL;
				}
			}
			else temp = NULL;
		}
		else temp = NULL;
		printf(" ��ǰѡ���ѧ��:%s\n", temp);
		printf(
			DELIMS_LINE\
			" [1].ѡ���޸ĵ�ѧ��\n"\
			" [2].�鿴��ѡ���ѧ������Ϣ\n"\
			" [3].��ʼ�޸�\n"\
			" [4].�鿴��Ϣ\n"\
			" [0].�������˵�\n"\
			DELIMS_LINE
		);
		switch (Event_Input())
		{
		case 1:
			if (ChartHead&&ChartHead[CurrentChartIndex] && ChoiceLines >= 0 && ChoiceLines < ChartHead[CurrentChartIndex]->UsedLines)
			{
				printf(DELIMS_LINE);
				if (IndexListHeadSet) {
					if (!IndexListHeadSet[CurrentIndexListIndex] || IndexListHeadSet[CurrentIndexListIndex]->AllocatedList <= 0)
						if (FillList(IndexListHeadSet[CurrentIndexListIndex], ChartHead[CurrentChartIndex]->UsedLines))
						{
							printf("����ʧ��\n");
							GETCH();
							break;
						}
					Display_Chart(ChartHead[CurrentChartIndex], IndexListHeadSet[CurrentIndexListIndex], TitleListHeadSet[CurrentTitleListIndex], DISPLAY_SHOWNUMBER);
					printf(DELIMS_LINE\
						"��ͨ�����ѡ��ѧ��:\n"
					);
					scanf("%d", &returnVal);
					if (returnVal >= 0 && returnVal < ChartHead[CurrentChartIndex]->UsedLines)
					{
						if (IndexListHeadSet[CurrentIndexListIndex]) {
							ChoiceLines = IndexListHeadSet[CurrentIndexListIndex]->list[returnVal];
							printf("ѡ��ɹ�\n");
						}
						else printf("���ȳ�ʼ��List\n");
					}
					else {
						printf("��������\n");
					}
				}
				else
				{
					printf("���ȳ�ʼ��List��\n");
				}

			}
			else printf("������ȷѡ��ѧ��\n");
			GETCH();
			break;
		case 2:
			if (ChartHead&&ChartHead[CurrentChartIndex] && ChoiceLines >= 0 && ChoiceLines < ChartHead[CurrentChartIndex]->UsedLines)
				Display_Piece(ChartHead[CurrentChartIndex], ChoiceLines, TitleListHeadSet[CurrentTitleListIndex]);
			else
				printf("������ȷѡ�����ѧ��\n");
			GETCH();
			break;
		case 3:
			if (ChartHead&&ChartHead[CurrentChartIndex] && ChartHead[CurrentChartIndex]->Chart&&
				ChoiceLines >= 0 && ChoiceLines < ChartHead[CurrentChartIndex]->UsedLines&&ChartHead[CurrentChartIndex]->Chart[ChoiceLines]
				&& CurrentTitleIndex >= 0 && CurrentTitleIndex < ChartHead[CurrentChartIndex]->TitleCount) {
				printf(
					" �����롾%s���ġ�%s����ֵ:\n"\
					"ԭ����ֵΪ:%s\n",
					temp,
					ChartHead[CurrentChartIndex]->ChartTitle[CurrentTitleIndex],
					ChartHead[CurrentChartIndex]->Chart[ChoiceLines][CurrentTitleIndex]
				);
				scanf("%s", ChartHead[CurrentChartIndex]->Chart[ChoiceLines][CurrentTitleIndex]);
				printf("ֵ�Ѹ�Ϊ��%s��n", ChartHead[CurrentChartIndex]->Chart[ChoiceLines][CurrentTitleIndex]);
			}
			else {
				printf("������ȷѡ��ѧ��\n");
			}
			GETCH();
			break;
		case 4:
			SubMenu_Display();
			break;
		case 0:
			return;
		}
	}
}

//5��ʾѧ����Ϣ
void SubMenu_Display()
{
    void SubMenu_Advantage();
	extern int ShowTitleList;
	extern int ShowPageList;
	static int ShowNumber = 0;
	char temp;
#if RANDOMCOLOR
	ChangeColor();
#endif
	while (1)
	{
		COMMAND_CLEAR();
		printf(
			DELIMS_LINE\
			"                    ��ʾ��Ϣ\n"
			DELIMS_LINE\
		);
		Menu_DisplaySubMenu();
		Menu_DisplaySubMenu_Page();
		printf(
			DELIMS_LINE\
			" [1].��ʾ���:%s\n"\
			" [2].��ҳ��ʾ��Ϣ\n"\
			" [3].��ҳ��ʾ��Ϣ\n"\
			" [4].��ת���߼�����\n"\
			" [0].������һ��\n"
			DELIMS_LINE,
			ShowNumber ? "��" : "��"
		);
		switch (Event_Input())
		{
		case 1:
			ShowNumber = !ShowNumber;
			break;
		case 2:
			if ((IndexListHeadSet&&IndexListHeadSet[CurrentIndexListIndex] && IndexListHeadSet[CurrentIndexListIndex]->listCount > 0 && IndexListHeadSet[CurrentIndexListIndex]->listCount <= WARNING_TOMUCHITEM) ||
				(ChartHead&&ChartHead[CurrentChartIndex] && ChartHead[CurrentChartIndex]->UsedLines > 0 && ChartHead[CurrentChartIndex]->UsedLines <= WARNING_TOMUCHITEM))
			{
				if (IndexListHeadSet&&TitleListHeadSet)
					if (Display_Chart(ChartHead[CurrentChartIndex], IndexListHeadSet[CurrentIndexListIndex], TitleListHeadSet[CurrentTitleListIndex], ShowNumber))
						printf("��ʾ��Ϣ����\n");
			}
			else
			{
				printf("Ԥ�⽫Ҫ����Ľ������̫��,�Ƿ�ʹ�÷�ҳ��ʾ���?��ʹ�÷�ҳ��ʾ������N,ʹ�÷�ҳ��ʾ�����������ַ�\n");
				getchar();
				scanf("%c", &temp);
				switch (temp)
				{
				case 'N':
				case 'n':
					if (ChartHead&&ChartHead[CurrentChartIndex]) {
						if (IndexListHeadSet&&TitleListHeadSet) {
							if (Display_Chart(ChartHead[CurrentChartIndex], IndexListHeadSet[CurrentIndexListIndex], TitleListHeadSet[CurrentTitleListIndex], ShowNumber))
								printf("��ʾ��Ϣ����\n");
						}
						else
							printf("Listû�г�ʼ��\n");
					}
					else
						printf("���ȶ�ȡ��Ϣ\n");
				default:
					ShowPageList = 1;
					if (ChartHead&&ChartHead[CurrentChartIndex]) {
						if (IndexListHeadSet&&TitleListHeadSet) {
							if (Display_Page(ChartHead[CurrentChartIndex], IndexListHeadSet[CurrentIndexListIndex], TitleListHeadSet[CurrentTitleListIndex], ShowNumber, SIZE_PAGE, CurrentPageIndex))
								printf("��ʾ��Ϣ����\n");
						}
						else
							printf("Listû�г�ʼ��\n");
					}
					else
						printf("���ȶ�ȡ��Ϣ\n");
				}
			}
			GETCH();
			break;

		case 3:
			if (ChartHead&&ChartHead[CurrentChartIndex] && IndexListHeadSet&&TitleListHeadSet)
			{
				if (Display_Page(ChartHead[CurrentChartIndex], IndexListHeadSet[CurrentIndexListIndex], TitleListHeadSet[CurrentTitleListIndex], DISPLAY_HIDENUMBER, SIZE_PAGE, CurrentPageIndex))
					printf("��ʾ��Ϣ����\n");
			}
			GETCH();
			break;
		case 4:
			SubMenu_Advantage();
			break;
		case 0:
			return;
		}
	}
}

//6����ѧ����Ϣ
void SubMenu_SaveToFile()
{
	void Sub_Save1();
	void Sub_Save2();
	void Sub_Save3();
	void Sub_Save4();
	void Sub_Save5();
#if RANDOMCOLOR
	ChangeColor();
#endif
	while (1)
	{
		COMMAND_CLEAR();
		printf(
			DELIMS_LINE\
			"                    ������Ϣ\n"
			DELIMS_LINE\
		);
		Menu_DisplaySubMenu();
		printf(
			DELIMS_LINE\
			" [1].����ȫ�����ݵ��ı��ļ�\n"\
			" [2].���沿�����ݵ��ı��ļ�\n"\
			" [3].����ȫ�����ݵ��������ļ�\n"\
			" [4].���沿�����ݵ��������ļ�\n"\
			" [5].�������ݵ�*.txt(�Զ�����)\n"\
			" [6].��ʾ��Ϣ\n"\
			" [0].�������˵�\n"\
			DELIMS_LINE
		);
		switch (Event_Input())
		{
		case 1:
			Sub_Save1();
			break;
		case 2:
			Sub_Save2();
			break;
		case 3:
			Sub_Save3();
			break;
		case 4:
			Sub_Save4();
			break;
		case 5:
			Sub_Save5();
			break;
		case 6:
			SubMenu_Display();
			break;
		case 0:
			return;
		}
	}
}
void Sub_Save1()
{
	char ParamFilePath[512] = { 0 };
	char DataFilePath[512] = { 0 };
	ReadConfig3(CONFIGFILEPATH3, ParamFilePath, DataFilePath);
#if RANDOMCOLOR
	ChangeColor();
#endif
	while (1) {
		COMMAND_CLEAR();
		printf(
			DELIMS_LINE\
			"                    ���浱ǰ���ȫ����Ϣ���ı��ļ�\n"
			DELIMS_LINE\
		);
		Menu_DisplaySubMenu();
		printf(
			DELIMS_LINE\
			" [1].�����ļ��Ĵ洢λ��:%s\n"\
			" [2].�����ļ��Ĵ洢λ��:%s\n"\
			, ParamFilePath, DataFilePath);
		printf(
			DELIMS_LINE\
			" [3].�������ݵ��ı��ļ�\n"\
			" [4].�鿴��Ϣ\n"\
			" [0].�������˵�\n"
			DELIMS_LINE
		);
		switch (Event_Input())
		{
		case 1:
			printf("����������ļ��Ĵ洢·��:\n");
			getchar();
			fgets(ParamFilePath, 512, stdin);
			ParamFilePath[strlen(ParamFilePath) - 1] = 0;
			break;
		case 2:
			printf("�����������ļ��Ĵ洢·��:\n");
			getchar();
			fgets(DataFilePath, 512, stdin);
			DataFilePath[strlen(DataFilePath) - 1] = 0;
			break;
		case 3:
			//��ʼ���
			if (ChartHead[CurrentChartIndex] && ChartHead[CurrentChartIndex]->UsedLines > 0) {
				if (!WriteToTwoFile_Chart(ParamFilePath, DataFilePath, ChartHead[CurrentChartIndex])) {
					printf("���浽�ļ��ɹ�\n");
					WriteConfig3(CONFIGFILEPATH3, ParamFilePath, DataFilePath);
				}
				else
					printf("���浽�ļ�ʧ��\n");
			}
			else {
				printf("���ȶ�ȡ�ļ�\n");
			}
			GETCH();
			break;
		case 4:
			SubMenu_Display();
			break;
		case 0:
			return;
		}
	}
}
void Sub_Save2()
{
	char ParamFilePath[512] = "";
	char DataFilePath[512] = "";
	ReadConfig3(CONFIGFILEPATH3, ParamFilePath, DataFilePath);
#if RANDOMCOLOR
	ChangeColor();
#endif
	while (1) {
		COMMAND_CLEAR();
		printf(
			DELIMS_LINE\
			"                    ���浱ǰ��Ĳ�����Ϣ���ı��ļ�\n"
			DELIMS_LINE\
		);
		Menu_DisplaySubMenu();
		printf(
			DELIMS_LINE\
			" [1].�����ļ��Ĵ洢λ��:%s\n"\
			" [2].�����ļ��Ĵ洢λ��:%s\n"\
			, ParamFilePath, DataFilePath);
		printf(
			DELIMS_LINE\
			" [3].�������ݵ��ı��ļ�\n"\
			" [4].��ʾ��Ϣ\n"\
			" [0].�������˵�\n"
			DELIMS_LINE
		);
		switch (Event_Input())
		{
		case 1:
			printf("����������ļ��Ĵ洢·��:\n");
			getchar();
			fgets(ParamFilePath, 512, stdin);
			ParamFilePath[strlen(ParamFilePath) - 1] = 0;
			break;
		case 2:
			printf("�����������ļ��Ĵ洢·��:\n");
			getchar();
			fgets(DataFilePath, 512, stdin);
			DataFilePath[strlen(DataFilePath) - 1] = 0;
			break;
		case 3:
			//��ʼ���
			if (ChartHead[CurrentChartIndex] && ChartHead[CurrentChartIndex]->UsedLines > 0)
			{
				if (!IndexListHeadSet[CurrentIndexListIndex] || IndexListHeadSet[CurrentIndexListIndex]->listCount <= 0)
				{
					FillList(IndexListHeadSet[CurrentIndexListIndex], ChartHead[CurrentChartIndex]->UsedLines);
				}
				if (!TitleListHeadSet[CurrentTitleListIndex] || TitleListHeadSet[CurrentTitleListIndex]->listCount <= 0)
				{
					FillList(TitleListHeadSet[CurrentTitleListIndex], ChartHead[CurrentChartIndex]->TitleCount);
				}
				if (!WriteToTwoFileByList(ParamFilePath, DataFilePath, ChartHead[CurrentChartIndex],
					IndexListHeadSet[CurrentIndexListIndex], TitleListHeadSet[CurrentTitleListIndex]))
				{
					printf("���浽�ļ��ɹ�\n");
					WriteConfig3(CONFIGFILEPATH3, ParamFilePath, DataFilePath);
				}
				else {
					printf("���浽�ļ�ʧ��\n");
				}
			}
			else {
				printf("���ȶ�ȡ�ļ�\n");
			}
			GETCH();
			break;
		case 4:
			SubMenu_Display();
			break;
		case 0:
			return;
		}
	}
}
void Sub_Save3()
{
	char FilePath[512] = { 0 };
	char PassWord[32] = { 0 };
	ReadConfig2(CONFIGFILEPATH4, FilePath);
#if RANDOMCOLOR
	ChangeColor();
#endif
	while (1) {
		COMMAND_CLEAR();
		printf(
			DELIMS_LINE\
			"                    ���浱ǰ���ȫ����Ϣ���������ļ�\n"
			DELIMS_LINE\
		);
		Menu_DisplaySubMenu();
		printf(
			DELIMS_LINE\
			" [1].�������ļ��Ĵ洢λ��:%s\n"\
			, FilePath);
		printf(
			DELIMS_LINE\
			" [2].�������ݵ��������ļ��ļ�\n"\
			" [3].��ʾ��Ϣ\n"\
			" [0].�������˵�\n"
			DELIMS_LINE
		);
		switch (Event_Input())
		{
		case 1:
			printf("������������ļ��Ĵ洢λ��:\n");
			getchar();
			fgets(FilePath, 512, stdin);
			FilePath[strlen(FilePath) - 1] = 0;
			break;

		case 2:
			//��ʼ���
			printf("��������ܵ�����(��ȡʱ��Ҫ������,�޴������޷���ȡ)\n");
			//scanf("%s", PassWord);
			InputPassWord(PassWord, 32);
			if (ChartHead[CurrentChartIndex] && ChartHead[CurrentChartIndex]->UsedLines > 0 && IndexListHeadSet&&TitleListHeadSet) {
				if (!WriteToBinFileByList(FilePath, PassWord, ChartHead[CurrentChartIndex], IndexListHeadSet[CurrentIndexListIndex], TitleListHeadSet[CurrentTitleListIndex])) {
					WriteConfig2(CONFIGFILEPATH4, FilePath);
					printf("���浽�ļ��ɹ�\n");
				}
				else
					printf("���浽�ļ�ʧ��\n");
			}
			else {
				printf("���ȶ�ȡ�ļ�\n");
			}
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
void Sub_Save4()
{
	char FilePath[512] = { 0 };
	char PassWord[32] = { 0 };
	ReadConfig2(CONFIGFILEPATH4, FilePath);
#if RANDOMCOLOR
	ChangeColor();
#endif
	while (1) {
		COMMAND_CLEAR();
		printf(
			DELIMS_LINE\
			"                    ���浱ǰ��Ĳ�����Ϣ���������ļ�\n"
			DELIMS_LINE\
		);
		Menu_DisplaySubMenu();
		printf(
			DELIMS_LINE\
			" [1].�������ļ��Ĵ洢λ��:%s\n"\
			, FilePath);
		printf(
			DELIMS_LINE\
			" [2].�������ݵ��������ļ��ļ�\n"\
			" [3].��ʾ��Ϣ\n"\
			" [0].�������˵�\n"
			DELIMS_LINE
		);
		switch (Event_Input())
		{
		case 1:
			printf("����������ļ��Ĵ洢·��:\n");
			getchar();
			fgets(FilePath, 512, stdin);
			FilePath[strlen(FilePath) - 1] = 0;
			break;
		case 2:
			//��ʼ���
			printf("��������ܵ�����(��ȡʱ��Ҫ������,�޴������޷���ȡ)\n");
			//scanf("%s", PassWord);
			InputPassWord(PassWord, 32);
			if (ChartHead[CurrentChartIndex] && ChartHead[CurrentChartIndex]->UsedLines > 0)
			{
				if (!IndexListHeadSet[CurrentIndexListIndex] || IndexListHeadSet[CurrentIndexListIndex]->listCount <= 0)
				{
					FillList(IndexListHeadSet[CurrentIndexListIndex], ChartHead[CurrentChartIndex]->UsedLines);
				}
				if (!TitleListHeadSet[CurrentTitleListIndex] || TitleListHeadSet[CurrentTitleListIndex]->listCount <= 0)
				{
					FillList(TitleListHeadSet[CurrentTitleListIndex], ChartHead[CurrentChartIndex]->TitleCount);
				}
				if (!WriteToBinFileByList(FilePath, PassWord, ChartHead[CurrentChartIndex],
					IndexListHeadSet[CurrentIndexListIndex], TitleListHeadSet[CurrentTitleListIndex]))
				{
					WriteConfig2(CONFIGFILEPATH4, FilePath);
					printf("���浽�ļ��ɹ�\n");
				}
				else {
					printf("���浽�ļ�ʧ��\n");
				}
			}
			else {
				printf("���ȶ�ȡ�ļ�\n");
			}
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
void Sub_Save5()
{
	char FilePath[512] = "";
	ReadConfig2(CONFIGFILEPATH5, FilePath);
#if RANDOMCOLOR
	ChangeColor();
#endif
	while (1) {
		COMMAND_CLEAR();
		printf(
			DELIMS_LINE\
			"                    ���浱ǰ��Ĳ�����Ϣ���ı��ļ�\n"
			DELIMS_LINE\
		);
		Menu_DisplaySubMenu();
		printf(
			DELIMS_LINE\
			" [1].txt�ļ��Ĵ洢λ��:%s\n"\
			, FilePath);
		printf(
			DELIMS_LINE\
			" [2].�������ݵ��ı��ļ�\n"\
			" [3].��ʾ��Ϣ\n"\
			" [0].�������˵�\n"
			DELIMS_LINE
		);
		switch (Event_Input())
		{
		case 1:
			printf("����������ļ��Ĵ洢·��:\n");
			getchar();
			fgets(FilePath, 512, stdin);
			FilePath[strlen(FilePath) - 1] = 0;
			break;
		case 2:
			//��ʼ���
			if (ChartHead[CurrentChartIndex] && ChartHead[CurrentChartIndex]->UsedLines > 0)
			{
				if (!IndexListHeadSet[CurrentIndexListIndex] || IndexListHeadSet[CurrentIndexListIndex]->listCount <= 0)
				{
					FillList(IndexListHeadSet[CurrentIndexListIndex], ChartHead[CurrentChartIndex]->UsedLines);
				}
				if (!TitleListHeadSet[CurrentTitleListIndex] || TitleListHeadSet[CurrentTitleListIndex]->listCount <= 0)
				{
					FillList(TitleListHeadSet[CurrentTitleListIndex], ChartHead[CurrentChartIndex]->TitleCount);
				}
				if (!ExportToTxt(FilePath, ChartHead[CurrentChartIndex],
					IndexListHeadSet[CurrentIndexListIndex], TitleListHeadSet[CurrentTitleListIndex]))
				{
					printf("���浽�ļ��ɹ�\n");
					WriteConfig2(CONFIGFILEPATH5, FilePath);
				}
				else {
					printf("���浽�ļ�ʧ��\n");
				}
			}
			else {
				printf("���ȶ�ȡ�ļ�\n");
			}
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

//7�߼�����
void SubMenu_Advantage()
{
	void Sub_TitleList();
	void Sub_IndexList();
	void CaluAverage();
#if RANDOMCOLOR
	ChangeColor();
#endif
	while (1)
	{
		COMMAND_CLEAR();
		printf(
			DELIMS_LINE\
			"                    �߼�����\n"
			DELIMS_LINE\
		);
		Menu_DisplaySubMenu();
		printf(
			DELIMS_LINE\
			" [1].����������\n"\
			" [2].�����༭\n"\
			" [3].��ʾ��Ϣ\n"\
			" [4].����ƽ���ɼ�\n"\
			" [0].�������˵�\n"\
			DELIMS_LINE
		);
		switch (Event_Input())
		{
		case 1:
			Sub_TitleList();
			break;
		case 2:
			Sub_IndexList();
			break;
		case 3:
			SubMenu_Display();
			break;
		case 4:
			CaluAverage();
			break;
		case 0:
			return;
		}
	}
}
void Sub_TitleList()
{
	char tempChar[100];
#if RANDOMCOLOR
	ChangeColor();
#endif
	while (1)
	{
		COMMAND_CLEAR();
		printf(
			DELIMS_LINE\
			"                    ����������\n"
			DELIMS_LINE\
		);
		Menu_DisplaySubMenu();
		printf(
			DELIMS_LINE\
			" [1].�����ñ༭\n"\
			" [2].��ʼ��������\n"\
			" [3].�Ե�ǰ�����ø���\n"\
			" [4].��ʾ��Ϣ\n"\
			" [0].������һ��\n"\
			DELIMS_LINE
		);
		switch (Event_Input())
		{
		case 1:
			if (ChartHead&&ChartHead[CurrentChartIndex] && ChartHead[CurrentChartIndex]->ChartTitle) {
				printf(DELIMS_LINE);
				Menu_DisplaySubMenu_Display();
				printf(DELIMS_LINE);
				printf("������Ҫ��ʾ�ı������Ż��������,�������(����)֮���ÿո����,�ûس���������:\n");
				getchar();
				fgets(tempChar, 100, stdin);
				if (GetListFromString(tempChar, ChartHead[CurrentChartIndex]->TitleCount, TitleListHeadSet[CurrentTitleListIndex], ChartHead[CurrentChartIndex]->TitleCount))
					printf("�༭ʧ��\n");
				else
					printf("�༭�ɹ�\n");
			}
			else {
				printf("���ȶ�ȡ�򴴽���\n");
			}
			GETCH();
			break;
		case 2:
			if (ChartHead&&ChartHead[CurrentChartIndex])
			{
				if (TitleListHeadSet&&TitleListHeadSet[CurrentTitleListIndex])
				{
					if (FillList(TitleListHeadSet[CurrentTitleListIndex], ChartHead[CurrentChartIndex]->TitleCount))
						printf("��ʼ��ʧ��\n");
					else
						printf("��ʼ���ɹ�\n");
				}
			}
			else
				printf("���ȶԱ���г�ʼ��\n");
			GETCH();
			break;
		case 3:
			if (TitleListHeadSet&&TitleListHeadSet[CurrentTitleListIndex] && TitleListHeadSet[CurrentTitleListIndex]->listCount > 0)
			{
				if (TitleListHeadSet[CurrentTitleListIndex]->ListName) {
					scanf("%s", TitleListHeadSet[CurrentTitleListIndex]->ListName);
					printf("�޸ĳɹ�\n");
				}
				else printf("���ȶ������ý��г�ʼ��\n");
			}
			else printf("���ȶ������ý��г�ʼ��\n");
			GETCH();
			break;
		case 4:
			SubMenu_Display();
			break;
		case 0:
			return;
		}
	}
}

void Sub_IndexList()
{
	char tempChar[512];
#if RANDOMCOLOR
	ChangeColor();
#endif
	while (1)
	{
		COMMAND_CLEAR();
		printf(
			DELIMS_LINE\
			"                    �����༭\n"
			DELIMS_LINE\
		);
		Menu_DisplaySubMenu();
		printf(
			DELIMS_LINE\
			" [1].��������ѡȡѧ��\n"\
			" [2].��ʼ����ǰѡ�������\n"\
			" [3].�Ե�ǰ��������\n"\
			" [4].��ʾ��Ϣ\n"\
			" [0].������һ��\n"\
			DELIMS_LINE
		);
		switch (Event_Input())
		{
		case 1:
			if (ChartHead&&ChartHead[CurrentChartIndex] && ChartHead[CurrentChartIndex]->UsedLines > 0) {
				printf(
					"������Ҫ��ʾ��ѧ���ı�Ż�������,�������(����)֮���ÿո����,�ûس���������:\n"
					"Tip:��ſ���ͨ����ʾ��Ϣ����,����ʾ��ſ��ؽ��л�ȡ\n"
				);
				getchar();
				fgets(tempChar, 512, stdin);
				if (GetListFromStringViaList(tempChar, ChartHead[CurrentChartIndex]->UsedLines, IndexListHeadSet[WhichListSaveTo()], IndexListHeadSet[CurrentIndexListIndex]))
					printf("�༭ʧ��\n");
				else
					printf("�༭�ɹ�\n");
			}
			else {
				printf("���ȶ�ȡ�򴴽���\n");
			}
			GETCH();
			break;
		case 2:
			if (ChartHead&&ChartHead[CurrentChartIndex])
			{
				if (IndexListHeadSet&&IndexListHeadSet[CurrentIndexListIndex])
				{
					if (FillList(IndexListHeadSet[CurrentIndexListIndex], ChartHead[CurrentChartIndex]->UsedLines))
						printf("��ʼ��ʧ��\n");
					else
						printf("��ʼ���ɹ�\n");
				}
			}
			else
				printf("���ȶԱ���г�ʼ��\n");
			GETCH();
			break;
		case 3:
			if (IndexListHeadSet&&IndexListHeadSet[CurrentIndexListIndex] && IndexListHeadSet[CurrentIndexListIndex]->listCount > 0)
			{
				if (IndexListHeadSet[CurrentIndexListIndex]->ListName) {
					scanf("%s", IndexListHeadSet[CurrentIndexListIndex]->ListName);
					printf("�����ɹ�\n");
				}
				else printf("����δ��ʼ��\n");
			}
			else printf("���ȶԵ�ǰ�������г�ʼ��\n");
			GETCH();
			break;
		case 4:
			SubMenu_Display();
			break;
		case 0:
			return;
		}
	}
}

//����ı���ɫ
void ChangeColor()
{
	srand((int)time(NULL));
	switch (rand() % 8)
	{
	case 0:
		system("color F1");
		break;
	case 1:
		system("color F2");
		break;
	case 2:
		system("color F3");
		break;
	case 3:
		system("color F4");
		break;
	case 4:
		system("color F5");
		break;
	case 5:
		system("color F6");
		break;
	case 6:
		system("color FC");
		break;
	case 7:
		system("color FD");
		break;
	}
}
