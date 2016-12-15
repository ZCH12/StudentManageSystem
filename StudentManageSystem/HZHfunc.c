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
	int i, t;                       //循环常量
	int CaluUnitCount = 0;          //所需计算平均的科目数量
	int UnitNum[20] = { 0 };          //用于保存chart表中unit对应的index
	int returnVal = 0;
	double sum = 0;
	char UnitName[32] = "平均成绩";     //用于创建新的unit(平均成绩)
	int NewTitleLimits = 8;
	int HadIntputRight = 0;
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
			DELIMS_LINE
			" [1].计算平均成绩的科目数量:%d\n", CaluUnitCount);
		printf(
			" [2].计算平均成绩的科目:"
		);
		for (i = 4; i - 4 < CaluUnitCount; i++) {
			printf("%s ", ChartHead[CurrentChartIndex]->ChartTitle[UnitNum[i - 4]]);
		}
		printf(
			"\n"
			" Tip:输入对应数字进行输入数据\n"
			DELIMS_LINE
			" [3].开始计算"
			" [0].返回上一级"
		);
		switch (Event_Input())
		{
		case 1:
			printf("请输入计算平均成绩的科目数量:\n");
			scanf("%d", &CaluUnitCount);
			if (CaluUnitCount < 0 || CaluUnitCount > ChartHead[CurrentChartIndex]->UsedLines) {
				printf("输入错误，请重新输入\n");
			}
			break;
		case 2:
			if (!CaluUnitCount) {
				printf("输入错误，请优先输入计算平均成绩的科目数量\n");
				break;
			}
			printf("请输入计算平均成绩的科目:\n");
			for (i = 4; i < ChartHead[CurrentChartIndex]->TitleCount; i++) {
				printf(" [%d].%s", i, ChartHead[CurrentChartIndex]->ChartTitle[i]);
			}
			for (i = 0; i < CaluUnitCount;)
			{
				printf("%d.", i);
				scanf("%d", &UnitNum[i]);
				if (UnitNum[i] < 0 && UnitNum[i] > ChartHead[CurrentChartIndex]->TitleCount) {
					printf("第%d个数据输入错误，请重新输入\n", i);
					continue;
				}
				else {
					HadIntputRight++;
				}
				i++;
			}
			break;
		case 3:
			//检查是否输入 计算科目数量
			if (!CaluUnitCount) {
				printf("计算失败，请重新输入所需计算平均的科目数量\n");
				break;
			}
			if (!HadIntputRight) {
				printf("计算失败，请重新输入所需计算的科目\n");
				break;
			}
			returnVal = CreateNewUnit(ChartHead[CurrentChartIndex], 1, &UnitName, &NewTitleLimits);
			for (i = 0; i < ChartHead[CurrentChartIndex]->UsedLines; i++)
			{
				for (t = 0; t < CaluUnitCount; t++)
				{

					sum += atof(ChartHead[CurrentChartIndex]->Chart[i][UnitNum[t]]);
				}
				sprintf(ChartHead[CurrentChartIndex]->Chart[i][SHI(ChartHead[CurrentChartIndex], "平均成绩")], "%.1lf", sum / 10);
                sum = 0;
			}
			if (returnVal == 0) {
				printf("计算成功\n");
			}
			else {
				printf("计算失败\n");
			}
			break;
		case 0:
			return;
		}
	}
}

//按照名字排序
void SortByName1()
{
	int SortMode = 1;               //排序模式
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
			" [1].排序方式:%s\n"
			"\n"
			" Tip:输入对应数字进行输入数据\n"
			DELIMS_LINE
			" [2].开始排序\n"
			" [0].返回上一级\n"
            , SortMode == 1 ? "降序" : "升序"
		);
		switch (Event_Input())
		{
		case 1:
			printf(
				DELIMS_LINE
				"请输入排序方式:\n"
				" [1].降序\n"
				" [2].升序\n"
				DELIMS_LINE
			);
			scanf("%d", &SortMode);
			if (SortMode < 0 || SortMode > 2) {
				printf("输出错误,请重新输入\n");
			}
			break;
		case 2:
			//判断指针 IndexListHeadSet[CurrentChartIndex]是否为空，      (是否已初始化) ||
			//IndexListHeadSet[CurrentChartIndex]中的list数组 是否小于0      (是否已初始化)
			if (!IndexListHeadSet[CurrentChartIndex] || IndexListHeadSet[CurrentChartIndex]->listCount <= 0) {
				//如果 未初始化 则执行初始化函数FillList
				FillList(IndexListHeadSet[CurrentChartIndex], ChartHead[CurrentChartIndex]->UsedLines);
			}
			ReturnVal = Sort(ChartHead[CurrentChartIndex], IndexListHeadSet[CurrentTitleListIndex]
				, SHI(ChartHead[CurrentChartIndex], "姓名"), SortMode);
			if (!ReturnVal) {
				printf("排序成功\n");
			}
			else {
				printf("排序失败\n");
			}
			Display_Chart(ChartHead[CurrentChartIndex], IndexListHeadSet[CurrentTitleListIndex]
				, NULL, DISPLAY_HIDENUMBER);
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
	int SortMode = 1;
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
			" [1].排序方式:%s\n"
			"\n"
			" Tip:输入对应数字进行输入数据\n"
			DELIMS_LINE
			" [2].开始排序\n"
			" [0].返回上一级\n"
			, SortMode == 1 ? "降序" : "升序"
		);
		switch (Event_Input())
		{
		case 1:
			printf(
				DELIMS_LINE
				"请输入排序方式:\n"
				" [1].降序\n"
				" [2].升序\n"
				DELIMS_LINE
			);
			scanf("%d", &SortMode);
			if (SortMode < 0 || SortMode > 2) {
				printf("输出错误,请重新输入\n");
			}
			break;
		case 2:
			ReturnVal = Sort(ChartHead[CurrentChartIndex], IndexListHeadSet[CurrentTitleListIndex - 1]
				, SHI(ChartHead[CurrentChartIndex], "平均成绩"), SortMode);
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

//按照任意单元排序
void SortByWhatYouWant()
{
	int i;
	int SortMode = 1;
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
            " [1].排序方式:%s\n", SortMode == 1 ? "降序" : "升序"
               );
        
       
        printf(
            " [2].排序内容:%s\n", ChartHead[CurrentChartIndex]->ChartTitle[ContentIndex]
               );
        printf("\n");
		printf(
			" Tip:输入对应数字进行输入数据\n"
			DELIMS_LINE
			" [3].开始排序\n"
			" [0].返回上一级\n"
		);
		Menu_DisplaySubMenu();
		switch (Event_Input())
		{
		case 1:
			printf(
				DELIMS_LINE
				"请选择排序方式:\n"
				" [1].降序\n"
				" [2].升序\n"
				DELIMS_LINE
			);
			scanf("%d", &SortMode);
			if (SortMode < 0 || SortMode > 2) {
				printf("输出错误,请重新输入\n");
			}
            
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
