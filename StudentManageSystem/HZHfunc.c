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
				printf(" [%d].%s ", i+1, ChartHead[CurrentChartIndex]->ChartTitle[i]);
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
		case 3:
			//检查是否输入 计算科目数量
			if (tempList.listCount <= 0) {
				printf("请先选择要进行计算的科目\n");
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
			" [0].返回上一级\n"\
			DELIMS_LINE,
			SortMode ? "降序" : "降序"
		);
		switch (Event_Input())
		{
		case 1:
			SortMode = !SortMode;
			break;
		case 2:
			ReturnVal = SHI(ChartHead[CurrentChartIndex], "姓名");
			if (ReturnVal != -1)
			{
				if (ChartHead&&ChartHead[CurrentChartIndex] && ChartHead[CurrentChartIndex]->UsedLines > 0)
				{
					if (IndexListHeadSet&&IndexListHeadSet[CurrentTitleListIndex] && IndexListHeadSet[CurrentTitleListIndex]->AllocatedList <= 0)
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
			}
			else
				printf("请先读取表\n");
			GETCH();
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
			ReturnVal = SHI(ChartHead[CurrentChartIndex], "平均成绩");
			if (ReturnVal != -1)
			{
				if (ChartHead&&ChartHead[CurrentChartIndex] && ChartHead[CurrentChartIndex]->UsedLines > 0)
				{
					if (IndexListHeadSet&&IndexListHeadSet[CurrentTitleListIndex] && IndexListHeadSet[CurrentTitleListIndex]->AllocatedList <= 0)
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
			}
			else
				printf("请先去高级功能中计算平均成绩\n");
			GETCH();
			break;
		case 0:
			return;

		}
	}
}

//按照任意单元排序
void SortByWhatYouWant()
{
	int i;
	int SortMode = 0;
	int ContentIndex = 0;
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
		printf(
			DELIMS_LINE
			" [1].排序方式:%s\n"
			" [2].排序的内容:", SortMode ? "降序" : "升序");
		for (i = 0; i < ChartHead[CurrentChartIndex]->TitleCount; i++) {
			printf("%s ", ChartHead[CurrentChartIndex]->ChartTitle[i]);
		}
		printf("\n");
		printf(
			" Tip:输入对应数字进行输入数据\n"\
			DELIMS_LINE\
			" [3].开始排序\n"\
			" [0].返回上一级\n"\
			DELIMS_LINE
		);
		Menu_DisplaySubMenu();
		switch (Event_Input())
		{
		case 1:
			SortMode = !SortMode;
			break;
		case 2:
			printf("请选择排序的内容\n");
			for (i = 0; i < ChartHead[CurrentChartIndex]->TitleCount; i++) {
				printf(" [%d].%s\n", i + 1, ChartHead[CurrentChartIndex]->ChartTitle[i]);
			}
			scanf("%d", &ContentIndex);
			if (ContentIndex < 0 || ContentIndex > ChartHead[CurrentChartIndex]->TitleCount) {
				printf("输入错误，请重新输入\n");
			}
			break;
		case 3:
			ReturnVal = Sort(ChartHead[CurrentChartIndex], IndexListHeadSet[CurrentIndexListIndex]
				, ContentIndex, SortMode);
			if (!ReturnVal) {
				printf("排序成功\n");
			}
			else {
				printf("排序失败\n");
			}
			break;
		case 0:
			return;
		}
	}
}