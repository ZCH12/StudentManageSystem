#include "menu.h"

//排序菜单
void SortList_M()
{
#if RANDOMCOLOR
	ChangeColor();
#endif
	while (1)
	{
		COMMAND_CLEAR();
		printf(
			DELIMS_LINE
			"                    学生排序\n"
			DELIMS_LINE
		);
		Menu_DisplaySubMenu();
		printf(
			DELIMS_LINE
			" [1].按照姓名排序\n"
			" [2].按照平均成绩排序\n"
			" [3].按照任意单元排序\n"
			" [0].返回主菜单\n"
			DELIMS_LINE
		);

		switch (Event_Input())
		{
		case 1:
			SortByName1();
			break;
		case 2:
			SortByEx1();
			break;
		case 3:
			SortByWhatYouWant();
			break;
		case 4:
			SubMenu_Display();
			break;
		case 0:
			return;
		}

	}
}

//计算任意成绩平均值
void CaluAverage()
{
	int i, t;                       //循环变量
	int UnitNum[20] = { 0 };        //用于保存chart表中unit对应的index
	int returnVal = 0;
	double sum = 0;
	char UnitName[1][32] = { "平均成绩" };     //用于创建新的unit(平均成绩)
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
			"                 计算平均成绩\n"
			DELIMS_LINE\
		);
		Menu_DisplaySubMenu();
		printf(
			DELIMS_LINE\
			" [1].计算平均成绩的科目:"
		);
		for (i = 0; i < tempList.listCount; i++) {
			printf("%s ", ChartHead[CurrentChartIndex]->ChartTitle[tempList.list[i]]);
		}
		printf(
			"\n"
			" Tip:输入对应数字进行输入数据\n"\
			DELIMS_LINE\
			" [2].开始计算\n"\
			" [0].返回上一级\n"\
			DELIMS_LINE
		);
		switch (Event_Input())
		{
		case 1:
			getchar();
			printf(DELIMS_LINE);
			for (i = 4; i < ChartHead[CurrentChartIndex]->TitleCount; i++) {
				printf(" [%d].%s ", i + 1, ChartHead[CurrentChartIndex]->ChartTitle[i]);
			}
			printf(
				"\n"\
				DELIMS_LINE
			);
			fgets(temp, 128, stdin);
			temp[strlen(temp) - 1] = 0;
			GetListFromString(temp, &tempList, ChartHead[CurrentChartIndex]->TitleCount);
			if (tempList.listCount <= 0) {
				printf("输入格式错误\n");
				GETCH();
			}
			break;
		case 2:
			//检查是否输入 计算科目数量
			if (tempList.listCount <= 0) {
				printf("请先选择要进行计算的科目\n");
				GETCH();
				break;
			}

			if (ChartHead&&ChartHead[CurrentChartIndex])
			{
				returnVal = CreateNewUnit(ChartHead[CurrentChartIndex], 1, UnitName, NewTitleLimits);
				if (!returnVal)
				{
					printf("创建新的单元格列成功\n");
				}
				else {
					printf("创建新的单元格失败\n");
					GETCH();
					break;
				}
				NewUnitIndex = SHI(ChartHead[CurrentChartIndex], "平均成绩");
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
			printf("计算平均成绩成功\n");
			GETCH();
			break;
		case 0:
			return;
		}
	}
}

//按照名字排序
void SortByName1()
{
	int SortMode = 0;               //排序模式
	int ReturnVal = 0;
#if RANDOMCOLOR
	ChangeColor();
#endif
	while (1)
	{
		COMMAND_CLEAR();
		printf(
			DELIMS_LINE\
			"                 按照姓名排序\n"
			DELIMS_LINE\
		);
		Menu_DisplaySubMenu();
		printf(
			DELIMS_LINE
			" [1].排序方式:%s\n"\
			"\n"\
			" Tip:输入对应数字进行输入数据\n"\
			DELIMS_LINE\
			" [2].开始排序\n"\
			" [3].显示结果\n"\
			" [0].返回上一级\n"\
			DELIMS_LINE,
			SortMode ? "降序" : "升序"
		);
		switch (Event_Input())
		{
		case 1:
			SortMode = !SortMode;
			break;
		case 2:
			if (ChartHead&&ChartHead[CurrentChartIndex]) {
				ReturnVal = SHI(ChartHead[CurrentChartIndex], "姓名");
				if (ReturnVal != -1)
				{
					if (ChartHead&&ChartHead[CurrentChartIndex] && ChartHead[CurrentChartIndex]->UsedLines > 0)
					{
						if (IndexListHeadSet) {
							if (IndexListHeadSet[CurrentTitleListIndex] && IndexListHeadSet[CurrentTitleListIndex]->AllocatedList <= 0)
							{
								FillList(IndexListHeadSet[CurrentTitleListIndex], ChartHead[CurrentChartIndex]->UsedLines);
							}
							ReturnVal = Sort(ChartHead[CurrentChartIndex], IndexListHeadSet[CurrentTitleListIndex], ReturnVal, SortMode);

							if (!ReturnVal) {
								printf("排序成功\n");
							}
							else {
								printf("排序失败\n");
							}
						}
						else printf("请先初始化表\n");
					}
				}
				else
					printf("请先读取表\n");
			}
			else printf("请先读取表\n");
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

//按照平均成绩排序
void SortByEx1()
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
			"                 按照平均成绩排序\n"
			DELIMS_LINE
		);
		Menu_DisplaySubMenu();
		printf(
			DELIMS_LINE
			" [1].排序方式:%s\n"\
			"\n"\
			" Tip:输入对应数字进行输入数据\n"\
			DELIMS_LINE\
			" [2].开始排序\n"\
			" [3].显示结果\n"\
			" [0].返回上一级\n"\
			DELIMS_LINE
			, SortMode ? "降序" : "升序"
		);
		switch (Event_Input())
		{
		case 1:
			SortMode = !SortMode;
			break;
		case 2:
			if (ChartHead) {
				ReturnVal = SHI(ChartHead[CurrentChartIndex], "平均成绩");
				if (ReturnVal != -1)
				{
					if (ChartHead&&ChartHead[CurrentChartIndex] && ChartHead[CurrentChartIndex]->UsedLines > 0)
					{
						if (IndexListHeadSet) {
							if (IndexListHeadSet[CurrentTitleListIndex] && IndexListHeadSet[CurrentTitleListIndex]->AllocatedList <= 0)
							{
								FillList(IndexListHeadSet[CurrentTitleListIndex], ChartHead[CurrentChartIndex]->UsedLines);
							}
							ReturnVal = Sort(ChartHead[CurrentChartIndex], IndexListHeadSet[CurrentTitleListIndex], ReturnVal, SortMode);
							if (!ReturnVal) {
								printf("排序成功\n");
							}
							else {
								printf("排序失败\n");
							}
						}
						else printf("请先初始化List集\n");
					}
				}
				else
					printf("请先去高级功能中计算平均成绩\n");
			}
			else printf("请先读取信息\n");
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

//按照任意单元排序
void SortByWhatYouWant()
{
	int SortMode = 0;
	int ReturnVal = 0;
#if RANDOMCOLOR
	ChangeColor();
#endif
	while (1)
	{
		COMMAND_CLEAR();
		printf(
			DELIMS_LINE
			"                 按照任意单元排序\n"
			DELIMS_LINE
		);
		Menu_DisplaySubMenu();
		Menu_DisplaySubMenu_Search();
		printf(
			DELIMS_LINE
			" [1].排序方式:%s\n",
			SortMode ? "降序" : "升序"
		);
		printf(
			" Tip:输入对应数字进行输入数据\n"\
			DELIMS_LINE\
			" [2].开始排序\n"\
			" [3].显示结果\n"\
			" [0].返回上一级\n"\
			DELIMS_LINE
		);

		switch (Event_Input())
		{
		case 1:
			SortMode = !SortMode;
			break;
		case 2:
			if (ChartHead&&ChartHead[CurrentChartIndex] && ChartHead[CurrentChartIndex]->HadInit != 0) {
				if (IndexListHeadSet) {
					if (!IndexListHeadSet[CurrentIndexListIndex] || IndexListHeadSet[CurrentIndexListIndex]->listCount < 0)
						FillList(IndexListHeadSet[CurrentIndexListIndex], ChartHead[CurrentChartIndex]->UsedLines);
					ReturnVal = Sort(ChartHead[CurrentChartIndex], IndexListHeadSet[CurrentIndexListIndex], CurrentTitleIndex, SortMode);
					if (!ReturnVal) {
						printf("排序成功\n");
					}
					else {
						printf("排序失败\n");
					}
				}
				else printf("请先初始化List集\n");
			}
			else printf("请先对表进行初始化\n");
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