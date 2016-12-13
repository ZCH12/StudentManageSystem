#pragma once
#include "menu.h"


void MainMenu()
{

	void SubMenu_Read();
	void SubMenu_Search();
	void SubMenu_Change();
	void SubMenu_Display();

	while (1)
	{
		COMMAND_CLEAR();
		printf(
			DELIMS_LINE\
			"                     主菜单\n"\
			DELIMS_LINE\
		);
		Menu_DisplaySubMenu();

		printf(
			DELIMS_LINE\
			" [1].读取文件\n"\
			" [2].对学生进行排序\n"\
			" [3].查找指定学生\n"\
			" [4].修改学生信息\n"\
			" [5].显示学生信息\n"\
			" [6].保存(导出)信息\n"\
			" [7].高级设置\n"\
			" [0].退出系统\n"\
			DELIMS_LINE
		);
		switch (Event_Input())
		{
		case 1:
			SubMenu_Read();
			break;
		case 2:
			//排序
			break;
		case 3:
			//查找
			SubMenu_Search();
			break;
		case 4:
			SubMenu_Change();
			//修改
			break;
		case 5:
			SubMenu_Display();
			//显示学生信息
			break;
		case 6:
			//保存信息
			break;
		case 7:
			//高级设置
			break;
		case 0:
			exit(0);
		}
	}
	return;
}

//1读取数据子菜单
void SubMenu_Read()
{
	void Sub_ChoiceFileToRead1();
	void Sub_ChoiceFileToRead2();
	while (1)
	{
		COMMAND_CLEAR();
		printf(
			DELIMS_LINE\
			"                    读取文件\n"
			DELIMS_LINE\
		);
		Menu_DisplaySubMenu();
		printf(
			DELIMS_LINE\
			" [1].从文本文件读取\n"\
			" [2].从二进制文件读取\n"\
			" [0].返回主菜单\n"
			DELIMS_LINE
		);
		switch (Event_Input())
		{
		case 1:
			//从文本读取数据
			Sub_ChoiceFileToRead1();
			break;
		case 2:
			//从二进制文件读取数据
			Sub_ChoiceFileToRead2();
			break;
		case 0:
			return;
		}
	}
}
//从文本读取数据
void Sub_ChoiceFileToRead1()
{
	char ParamFilePath[512] = "";
	char DataFilePath[512] = "";
	char SexTranslateFilePath[512] = "";
	char CollegeTranslateFilePath[512] = "";
	int returnVal;
	InfoMap im;
	ReadConfig1(ParamFilePath, DataFilePath, SexTranslateFilePath, CollegeTranslateFilePath);

	while (1)
	{
		COMMAND_CLEAR();
		printf(
			DELIMS_LINE\
			"                 选择要读取的文件\n"
			DELIMS_LINE\
		);
		Menu_DisplaySubMenu();

		printf(
			DELIMS_LINE\
			" [1].参数列表文件路径:%s\n"\
			" [2].数据文件路径:%s\n"\
			" [3].性别映射文件路径:%s\n"\
			" [4].学院信息映射文件路径:%s\n"
			"\n"\
			" Tip:输入对应数字进行输入数据\n",
			ParamFilePath, DataFilePath, SexTranslateFilePath, CollegeTranslateFilePath
		);
		printf(
			DELIMS_LINE\
			" [5].开始读取\n"\
			" [0].返回上一级\n"
			DELIMS_LINE
		);
		switch (Event_Input())
		{
		case 1:
			printf("请输入参数列表文件路径:\n");
			getchar();
			fgets(ParamFilePath, 512, stdin);
			ParamFilePath[strlen(ParamFilePath) - 1] = 0;
			break;
		case 2:
			printf("请输入数据文件路径:\n");
			getchar();
			fgets(DataFilePath, 512, stdin);
			DataFilePath[strlen(DataFilePath) - 1] = 0;
			break;
		case 3:
			printf("请输入性别映射文件路径:\n");
			getchar();
			fgets(SexTranslateFilePath, 512, stdin);
			SexTranslateFilePath[strlen(SexTranslateFilePath) - 1] = 0;
			break;
		case 4:
			printf("请输入学院信息映射文件路径:\n");
			getchar();
			fgets(CollegeTranslateFilePath, 512, stdin);
			CollegeTranslateFilePath[strlen(CollegeTranslateFilePath) - 1] = 0;
			break;
		case 5:
			returnVal = ReadFromTwoFile(ParamFilePath, DataFilePath, ChartHead[CurrentChartIndex]);
			if (!returnVal)
			{
				printf("读取数据文件成功\n");
				//继续翻译
				returnVal = SHI(ChartHead[CurrentChartIndex], "性别");
				if (returnVal != -1) {
					ReadMapFile(SexTranslateFilePath, &im);
					Translate(ChartHead[CurrentChartIndex], returnVal, &im);
					FreeMapStruct(&im);
				}
				returnVal = SHI(ChartHead[CurrentChartIndex], "学院名称");
				if (returnVal != -1) {
					ReadMapFile(CollegeTranslateFilePath, &im);
					Translate(ChartHead[CurrentChartIndex], returnVal, &im);
					FreeMapStruct(&im);
				}
				WriteConfig1(ParamFilePath, DataFilePath, SexTranslateFilePath, CollegeTranslateFilePath);
			}
			else if (returnVal == ERR_OPENFILE) {
				printf("读取文件失败,请确认路径是否正确,");
			}
			else if (returnVal == ERR_NOTSTANDARDFILE) {
				printf("目标文件不符合标准,请换一个文件再试\n");
			}
			GETCH();
			//读取数据
			break;
		case 0:
			return;
		}
	}
}
//从二进制文件读取数据
void Sub_ChoiceFileToRead2()
{
	char FilePath[512] = "";
	char PassWord[32] = "";
	int returnVal;
	ReadConfig2(FilePath);
	while (1)
	{
		COMMAND_CLEAR();
		printf(
			DELIMS_LINE\
			"                 选择要读取的文件\n"
			DELIMS_LINE\
		);
		Menu_DisplaySubMenu();
		printf(
			DELIMS_LINE
			" [1].二进制文件存放路径:%s\n"\
			"\n"\
			" Tip:输入对应数字进行输入数据\n",
			FilePath
		);
		printf(
			DELIMS_LINE\
			" [2].开始读取\n"\
			" [0].返回上一级\n"
			DELIMS_LINE
		);
		switch (Event_Input())
		{
		case 1:
			printf("请输入二进制文件存放路径:\n");
			getchar();
			fgets(FilePath, 512, stdin);
			FilePath[strlen(FilePath) - 1] = 0;
			break;
		case 2:
			printf("请输入文件密码密码:\n");
			scanf("%s", PassWord);
			returnVal = ReadFromBinFile(FilePath, PassWord, ChartHead[CurrentChartIndex]);
			if (!returnVal) {
				WriteConfig2(FilePath);
				printf("读取文件成功\n");
			}
			else if (returnVal == ERR_WRONGPASSWORD)
				printf("密码错误,无法读取文件\n");
			else if (returnVal == ERR_OPENFILE)
				printf("文件路径错误\n");
			GETCH();
			break;
		case 0:
			return;
		}
	}
}


//3搜索数据子菜单
void SubMenu_Search()
{
	void Sub_Search1();
	int returnVal;
	while (1)
	{
		COMMAND_CLEAR();
		printf(
			DELIMS_LINE\
			"                     搜索信息\n"\
			DELIMS_LINE\
		);
		Menu_DisplaySubMenu();
		Menu_DisplaySubMenu_Search();
		printf(
			DELIMS_LINE\
			" [1].按姓名进行查找\n"\
			" [2].按学号进行查找\n"\
			" [3].按选定信息点进行查找\n"\
			" [4].显示结果\n"\
			" [0].返回主菜单\n"\
			DELIMS_LINE
		);
		switch (Event_Input())
		{
		case 1:
			returnVal = SHI(ChartHead[0], "姓名");
			if (returnVal != -1)
			{
				CurrentTitleIndex = returnVal;
				Sub_Search1();
			}
			else
			{
				printf("本表没有姓名字段\n");
			}
			GETCH();
			//按姓名进行查找
			break;
		case 2:
			returnVal = SHI(ChartHead[0], "学号");
			if (returnVal != -1)
			{
				CurrentTitleIndex = returnVal;
				Sub_Search1();
			}
			else
			{
				printf("本表没有学号字段\n");
			}
			GETCH();
			break;
		case 3:
			Sub_Search1();
			GETCH();
			break;
		case 4:

			if (Display_Chart(ChartHead[CurrentChartIndex], IndexListHeadSet[CurrentIndexListIndex], TitleListHeadSet[CurrentTitleListIndex], DISPLAY_HIDENUMBER))
			{
				printf("显示失败\n");
			}
			GETCH();
			break;
		case 0:
			return;
		}
	}
}
//Sub_Search1的子功能
void Sub_Search1()
{
	int WhichListSaveTo();
	int returnVal, SaveIndex;
	char SearchString[512];
	if (CurrentChartIndex >= 0 && CurrentChartIndex < ChartHead[CurrentChartIndex]->TitleCount) {
		printf("请输入要搜索的%s:\n", ChartHead[CurrentChartIndex]->ChartTitle[CurrentTitleIndex]);
		scanf("%s", SearchString);
		printf("请选择保存结果的名单:\n");
		SaveIndex = WhichListSaveTo();
		if (!IndexListHeadSet[SaveIndex] || IndexListHeadSet[SaveIndex]->AllocatedList == 0)
			if (IndexListHeadSet[CurrentIndexListIndex] && IndexListHeadSet[CurrentIndexListIndex]->listCount > 0)
				FillList(IndexListHeadSet[SaveIndex], IndexListHeadSet[CurrentIndexListIndex]->listCount);
			else
				FillList(IndexListHeadSet[SaveIndex], ChartHead[CurrentChartIndex]->UsedLines);

		returnVal = Search(ChartHead[CurrentChartIndex], IndexListHeadSet[CurrentIndexListIndex], IndexListHeadSet[SaveIndex], CurrentTitleIndex, SearchString);
		if (!returnVal)
		{
			if (IndexListHeadSet[SaveIndex] && IndexListHeadSet[SaveIndex]->listCount > 0) {
				printf("成功找到以下数据\n");
				Display_Chart(ChartHead[0], IndexListHeadSet[SaveIndex], TitleListHeadSet[CurrentTitleListIndex], DISPLAY_HIDENUMBER);
				CurrentTitleIndex = SaveIndex;
				printf("共找到%d个结果\n", IndexListHeadSet[SaveIndex]->listCount);
			}
			else
				printf("没有找到相关数据\n");
		}
		else if (returnVal == ERR_ILLEGALCHART) {
			printf("错误的表,可能没有读取过文件\n");
		}
	}
	else
		printf("操作失败\n");
}
//Sub_Search1的子功能
int WhichListSaveTo()
{
	int a, b = -1;
	printf(" 请问你需要在哪个名单中存放结果\n");
	printf("请输入一个数字进行选择\n");
	for (a = 0; a < IndexListCount; a++)
		if (IndexListHeadSet[a] && IndexListHeadSet[a]->ListName)
			printf("  [%d]. %s\n", a + 1, IndexListHeadSet[a]->ListName);
		else
			printf("  [%d]. 未命名\n", a + 1);
	while (b<1 || b>IndexListCount)
		scanf("%d", &b);
	return b - 1;
}

//4修改学生信息
void SubMenu_Change()
{
	int returnVal;
	int ChoiceLines = 0;
	char *temp;
	while (1)
	{
		COMMAND_CLEAR();
		printf(
			DELIMS_LINE\
			"                     修改信息\n"\
			DELIMS_LINE\
		);
		Menu_DisplaySubMenu();
		Menu_DisplaySubMenu_Search();
		if (ChartHead&&ChartHead[CurrentChartIndex]) {
			returnVal = SHI(ChartHead[CurrentChartIndex], "姓名");
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
		printf(" 当前选择的学生:%s\n", temp);
		printf(
			DELIMS_LINE\
			" [1].选择修改的学生\n"\
			" [2].查看已选择的学生的信息\n"\
			" [3].开始修改\n"\
			" [0].返回主菜单\n"\
			DELIMS_LINE
		);
		switch (Event_Input())
		{
		case 1:
			if (ChartHead&&ChartHead[CurrentChartIndex] && ChoiceLines >= 0 && ChoiceLines < ChartHead[CurrentChartIndex]->UsedLines)
			{
				printf(DELIMS_LINE);
				Display_Chart(ChartHead[CurrentChartIndex], IndexListHeadSet[CurrentIndexListIndex], TitleListHeadSet[CurrentTitleListIndex], DISPLAY_SHOWNUMBER);
				printf(DELIMS_LINE\
					"请通过编号选择学生:\n"
				);
				scanf("%d", &returnVal);
				if (returnVal >= 0 && returnVal < ChartHead[CurrentChartIndex]->UsedLines)
				{
					ChoiceLines = returnVal;
					printf("选择成功\n");
				}
				else {
					printf("输入有误\n");
				}
			}
			else printf("请先正确选择学生\n");
			GETCH();
			break;
		case 2:
			if (ChartHead&&ChartHead[CurrentChartIndex] && ChoiceLines >= 0 && ChoiceLines < ChartHead[CurrentChartIndex]->UsedLines)
				Display_Piece(ChartHead[CurrentChartIndex], ChoiceLines, TitleListHeadSet[CurrentTitleListIndex]);
			else
				printf("请先正确选择操作学生\n");
			GETCH();
			break;
		case 3:
			if (ChartHead&&ChartHead[CurrentChartIndex] && ChartHead[CurrentChartIndex]->Chart&&
				ChoiceLines >= 0 && ChoiceLines < ChartHead[CurrentChartIndex]->UsedLines&&ChartHead[CurrentChartIndex]->Chart[ChoiceLines]
				&& CurrentTitleIndex >= 0 && CurrentTitleIndex < ChartHead[CurrentChartIndex]->TitleCount) {
				printf(
					" 请输入【%s】的【%s】的值:\n"\
					"原来的值为:%s\n",
					temp,
					ChartHead[CurrentChartIndex]->ChartTitle[CurrentTitleIndex],
					ChartHead[CurrentChartIndex]->Chart[ChoiceLines][CurrentTitleIndex]
				);
				scanf("%s", ChartHead[CurrentChartIndex]->Chart[ChoiceLines][CurrentTitleIndex]);
			}
			else {
				printf("请先正确选择学生\n");
			}
			GETCH();
			break;
		case 0:
			return;
		}
	}
}

//5显示学生信息
void SubMenu_Display()
{
	extern int ShowTitleList;
	char tempChar[100];
	while (1)
	{
		COMMAND_CLEAR();
		printf(
			DELIMS_LINE\
			"                    显示信息\n"
			DELIMS_LINE\
		);
		Menu_DisplaySubMenu();
		printf(
			DELIMS_LINE\
			" [1].显示信息\n"\
			" [2].列配置编辑\n"\
			" [0].返回主菜单\n"
			DELIMS_LINE
		);
		switch (Event_Input())
		{
		case 1:
			if (Display_Chart(ChartHead[CurrentChartIndex], IndexListHeadSet[CurrentIndexListIndex], TitleListHeadSet[CurrentTitleListIndex], DISPLAY_HIDENUMBER))
			{
				printf("显示信息错误\n");
			}
			GETCH();
			break;
		case 2:
			if (ChartHead&&ChartHead[CurrentChartIndex]&&ChartHead[CurrentChartIndex]->ChartTitle) {
				printf(DELIMS_LINE);
				Menu_DisplaySubMenu_Display();
				printf(DELIMS_LINE);
				printf("请输入要显示的标题的序号,各个序号之间用空格隔开,用回车结束输入:\n");
				getchar();
				fgets(tempChar, 100, stdin);
				GetListFromString(tempChar, TitleListHeadSet[CurrentTitleListIndex], ChartHead[CurrentChartIndex]->TitleCount);
				printf("编辑成功\n");
			}
			else {
				printf("请先读取或创建表\n");
			}
			GETCH();
			break;
		case 0:
			return;
		}
	}
}
