#include "menu.h"
#include "time.h"

//主菜单入口
void MainMenu()
{
	void SubMenu_Read();
	void SubMenu_Search();
	void SubMenu_Change();
	void SubMenu_Display();
	void SubMenu_SaveToFile();
	void SubMenu_Advantage();
	extern void SortList_M();
	char a;
	while (1)
	{
#if RANDOMCOLOR
		ChangeColor();
#endif
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
			" [7].高级功能\n"\
			" [0].退出系统\n"\
			DELIMS_LINE
		);
		switch (Event_Input())
		{
		case 1:
			SubMenu_Read();			//从文件读取信息
			break;
		case 2:
			SortList_M();
			break;
		case 3:
			SubMenu_Search();		//查找学生信息
			break;
		case 4:
			SubMenu_Change();		//修改学生信息
			break;
		case 5:
			SubMenu_Display();		//显示学生信息
			break;
		case 6:
			SubMenu_SaveToFile();	//保存信息
			break;
		case 7:
			SubMenu_Advantage();	//高级设置
			break;
		case 0:
			printf("确定要退出吗?(按Y继续退出)\n如果退出,未保存的数据将会丢失\n");
			getchar();
			scanf("%c", &a);
			if (a == 'Y' || a == 'y')
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
#if RANDOMCOLOR
	ChangeColor();
#endif
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
				WriteConfig1(CONFIGFILEPATH1, ParamFilePath, DataFilePath, SexTranslateFilePath, CollegeTranslateFilePath);
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
				WriteConfig2(CONFIGFILEPATH2, FilePath);
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
	extern int ShowPageList;
	int returnVal;
	char temp;
#if RANDOMCOLOR
	ChangeColor();
#endif
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
		Menu_DisplaySubMenu_Page();
		printf(
			DELIMS_LINE\
			" [1].按姓名进行查找\n"\
			" [2].按学号进行查找\n"\
			" [3].按选定信息点进行查找\n"\
			" [4].显示全部结果\n"\
			" [5].分页显示结果\n"\
			" [6].初始化当前名单\n"\
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
			if (IndexListHeadSet&&IndexListHeadSet[CurrentIndexListIndex] && IndexListHeadSet &&IndexListHeadSet[CurrentIndexListIndex]->listCount > 0) {
				if ((IndexListHeadSet[CurrentIndexListIndex]->listCount <= WARNING_TOMUCHITEM) ||
					(ChartHead&&ChartHead[CurrentChartIndex] && ChartHead[CurrentChartIndex]->UsedLines > 0 && ChartHead[CurrentChartIndex]->UsedLines <= WARNING_TOMUCHITEM)) {
					if (Display_Chart(ChartHead[CurrentChartIndex], IndexListHeadSet[CurrentIndexListIndex], TitleListHeadSet[CurrentTitleListIndex], DISPLAY_HIDENUMBER))
						printf("显示信息错误\n");
				}
				else
				{
					printf("预测将要输出的结果数量太大,是否使用分页显示结果?不使用分页显示请输入N,使用分页显示请输入任意字符\n");
					scanf("%c", &temp);
					switch (temp)
					{
					case 'N':
					case 'n':
						if (Display_Chart(ChartHead[CurrentChartIndex], IndexListHeadSet[CurrentIndexListIndex], TitleListHeadSet[CurrentTitleListIndex], DISPLAY_HIDENUMBER))
							printf("显示信息错误\n");
					default:
						ShowPageList = 1;
						if (Display_Page(ChartHead[CurrentChartIndex], IndexListHeadSet[CurrentIndexListIndex], TitleListHeadSet[CurrentTitleListIndex], DISPLAY_HIDENUMBER, SIZE_PAGE, CurrentPageIndex))
							printf("显示信息错误\n");
					}
				}
			}
			GETCH();
			break;
		case 5:
			if (Display_Page(ChartHead[CurrentChartIndex], IndexListHeadSet[CurrentIndexListIndex], TitleListHeadSet[CurrentTitleListIndex], DISPLAY_HIDENUMBER, SIZE_PAGE, CurrentPageIndex))
				printf("显示信息错误\n");
			GETCH();
			break;
		case 6:
			if (IndexListHeadSet&&ChartHead)
				FillList(IndexListHeadSet[CurrentIndexListIndex], ChartHead[CurrentChartIndex]->UsedLines);
			printf("初始化完毕\n");
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
		printf("请输入要搜索的%s:\n", ChartHead[CurrentChartIndex]->ChartTitle[CurrentTitleIndex]);
		scanf("%s", SearchString);
		printf("请选择保存结果的名单:\n");
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
#if RANDOMCOLOR
	ChangeColor();
#endif
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
				if (!IndexListHeadSet[CurrentIndexListIndex] || IndexListHeadSet[CurrentIndexListIndex]->AllocatedList <= 0)
					FillList(IndexListHeadSet[CurrentIndexListIndex], ChartHead[CurrentChartIndex]->UsedLines);
				Display_Chart(ChartHead[CurrentChartIndex], IndexListHeadSet[CurrentIndexListIndex], TitleListHeadSet[CurrentTitleListIndex], DISPLAY_SHOWNUMBER);
				printf(DELIMS_LINE\
					"请通过编号选择学生:\n"
				);
				scanf("%d", &returnVal);
				if (returnVal >= 0 && returnVal < ChartHead[CurrentChartIndex]->UsedLines)
				{
					ChoiceLines = IndexListHeadSet[CurrentIndexListIndex]->list[returnVal];
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
				printf("值已改为：%s、n", ChartHead[CurrentChartIndex]->Chart[ChoiceLines][CurrentTitleIndex]);
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
	extern int ShowPageList;
	char tempChar[100];
	char temp;
#if RANDOMCOLOR
	ChangeColor();
#endif
	while (1)
	{
		COMMAND_CLEAR();
		printf(
			DELIMS_LINE\
			"                    显示信息\n"
			DELIMS_LINE\
		);
		Menu_DisplaySubMenu();
		Menu_DisplaySubMenu_Page();
		printf(
			DELIMS_LINE\
			" [1].单页显示信息\n"\
			" [2].分页显示信息\n"\
			" [3].列配置编辑\n"\
			" [0].返回主菜单\n"
			DELIMS_LINE
		);
		switch (Event_Input())
		{
		case 1:
			if ((IndexListHeadSet&&IndexListHeadSet[CurrentIndexListIndex] && IndexListHeadSet[CurrentIndexListIndex]->listCount > 0 && IndexListHeadSet[CurrentIndexListIndex]->listCount <= WARNING_TOMUCHITEM) ||
				(ChartHead&&ChartHead[CurrentChartIndex] && ChartHead[CurrentChartIndex]->UsedLines > 0 && ChartHead[CurrentChartIndex]->UsedLines <= WARNING_TOMUCHITEM)) {
				if (Display_Chart(ChartHead[CurrentChartIndex], IndexListHeadSet[CurrentIndexListIndex], TitleListHeadSet[CurrentTitleListIndex], DISPLAY_HIDENUMBER))
					printf("显示信息错误\n");
			}
			else
			{
				printf("预测将要输出的结果数量太大,是否使用分页显示结果?不使用分页显示请输入N,使用分页显示请输入任意字符\n");
				scanf("%c", &temp);
				switch (temp)
				{
				case 'N':
				case 'n':
					if (Display_Chart(ChartHead[CurrentChartIndex], IndexListHeadSet[CurrentIndexListIndex], TitleListHeadSet[CurrentTitleListIndex], DISPLAY_HIDENUMBER))
						printf("显示信息错误\n");
				default:
					ShowPageList = 1;
					if (Display_Page(ChartHead[CurrentChartIndex], IndexListHeadSet[CurrentIndexListIndex], TitleListHeadSet[CurrentTitleListIndex], DISPLAY_HIDENUMBER, SIZE_PAGE, CurrentPageIndex))
						printf("显示信息错误\n");
				}
			}
			GETCH();
			break;

		case 2:
			if (ChartHead&&ChartHead[CurrentChartIndex] && IndexListHeadSet&&TitleListHeadSet)
			{
				if (Display_Page(ChartHead[CurrentChartIndex], IndexListHeadSet[CurrentIndexListIndex], TitleListHeadSet[CurrentTitleListIndex], DISPLAY_HIDENUMBER, SIZE_PAGE, CurrentPageIndex))
					printf("显示信息错误\n");
			}
			GETCH();
			break;
		case 3:
			if (ChartHead&&ChartHead[CurrentChartIndex] && ChartHead[CurrentChartIndex]->ChartTitle) {
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

//6保存学生信息
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
			"                    保存信息\n"
			DELIMS_LINE\
		);
		Menu_DisplaySubMenu();
		printf(
			DELIMS_LINE\
			" [1].保存全部数据到文本文件\n"\
			" [2].保存部分数据到文本文件\n"\
			" [3].保存全部数据到二进制文件\n"\
			" [4].保存部分数据到二进制文件\n"\
			" [5].导出数据到*.txt(自动对齐)\n"\
			" [0].返回主菜单\n"\
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
			"                    保存当前表的全部信息到文本文件\n"
			DELIMS_LINE\
		);
		Menu_DisplaySubMenu();
		printf(
			DELIMS_LINE\
			" [1].参数文件的存储位置:%s\n"\
			" [2].数据文件的存储位置:%s\n"\
			, ParamFilePath, DataFilePath);
		printf(
			DELIMS_LINE\
			" [3].保存数据到文本文件\n"\
			" [0].返回主菜单\n"
			DELIMS_LINE
		);
		switch (Event_Input())
		{
		case 1:
			printf("请输入参数文件的存储路径:\n");
			getchar();
			fgets(ParamFilePath, 512, stdin);
			ParamFilePath[strlen(ParamFilePath) - 1] = 0;
			break;
		case 2:
			printf("请输入数据文件的存储路径:\n");
			getchar();
			fgets(DataFilePath, 512, stdin);
			DataFilePath[strlen(DataFilePath) - 1] = 0;
			break;
		case 3:
			//开始输出
			if (ChartHead[CurrentChartIndex] && ChartHead[CurrentChartIndex]->UsedLines > 0) {
				if (!WriteToTwoFile_Chart(ParamFilePath, DataFilePath, ChartHead[CurrentChartIndex])) {
					printf("保存到文件成功\n");
					WriteConfig3(CONFIGFILEPATH3, ParamFilePath, DataFilePath);
				}
				else
					printf("保存到文件失败\n");
			}
			else {
				printf("请先读取文件\n");
			}
			GETCH();
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
			"                    保存当前表的部分信息到文本文件\n"
			DELIMS_LINE\
		);
		Menu_DisplaySubMenu();
		printf(
			DELIMS_LINE\
			" [1].参数文件的存储位置:%s\n"\
			" [2].数据文件的存储位置:%s\n"\
			, ParamFilePath, DataFilePath);
		printf(
			DELIMS_LINE\
			" [3].保存数据到文本文件\n"\
			" [0].返回主菜单\n"
			DELIMS_LINE
		);
		switch (Event_Input())
		{
		case 1:
			printf("请输入参数文件的存储路径:\n");
			getchar();
			fgets(ParamFilePath, 512, stdin);
			ParamFilePath[strlen(ParamFilePath) - 1] = 0;
			break;
		case 2:
			printf("请输入数据文件的存储路径:\n");
			getchar();
			fgets(DataFilePath, 512, stdin);
			DataFilePath[strlen(DataFilePath) - 1] = 0;
			break;
		case 3:
			//开始输出
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
					printf("保存到文件成功\n");
					WriteConfig3(CONFIGFILEPATH3, ParamFilePath, DataFilePath);
				}
				else {
					printf("保存到文件失败\n");
				}
			}
			else {
				printf("请先读取文件\n");
			}
			GETCH();
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
			"                    保存当前表的全部信息到二进制文件\n"
			DELIMS_LINE\
		);
		Menu_DisplaySubMenu();
		printf(
			DELIMS_LINE\
			" [1].二进制文件的存储位置:%s\n"\
			, FilePath);
		printf(
			DELIMS_LINE\
			" [2].保存数据到二进制文件文件\n"\
			" [0].返回主菜单\n"
			DELIMS_LINE
		);
		switch (Event_Input())
		{
		case 1:
			printf("请输入二进制文件的存储位置:\n");
			getchar();
			fgets(FilePath, 512, stdin);
			FilePath[strlen(FilePath) - 1] = 0;
			break;

		case 2:
			//开始输出
			printf("请输入加密的密码(读取时需要此密码,无此密码无法读取)\n");
			scanf("%s", PassWord);
			if (ChartHead[CurrentChartIndex] && ChartHead[CurrentChartIndex]->UsedLines > 0 && IndexListHeadSet&&TitleListHeadSet) {
				if (!WriteToBinFileByList(FilePath, PassWord, ChartHead[CurrentChartIndex], IndexListHeadSet[CurrentIndexListIndex], TitleListHeadSet[CurrentTitleListIndex])) {
					WriteConfig2(CONFIGFILEPATH4, FilePath);
					printf("保存到文件成功\n");
				}
				else
					printf("保存到文件失败\n");
			}
			else {
				printf("请先读取文件\n");
			}
			GETCH();
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
			"                    保存当前表的部分信息到二进制文件\n"
			DELIMS_LINE\
		);
		Menu_DisplaySubMenu();
		printf(
			DELIMS_LINE\
			" [1].二进制文件的存储位置:%s\n"\
			, FilePath);
		printf(
			DELIMS_LINE\
			" [2].保存数据到二进制文件文件\n"\
			" [0].返回主菜单\n"
			DELIMS_LINE
		);
		switch (Event_Input())
		{
		case 1:
			printf("请输入参数文件的存储路径:\n");
			getchar();
			fgets(FilePath, 512, stdin);
			FilePath[strlen(FilePath) - 1] = 0;
			break;
		case 3:
			//开始输出
			printf("请输入加密的密码(读取时需要此密码,无此密码无法读取)\n");
			scanf("%s", PassWord);
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
					printf("保存到文件成功\n");
				}
				else {
					printf("保存到文件失败\n");
				}
			}
			else {
				printf("请先读取文件\n");
			}
			GETCH();
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
			"                    保存当前表的部分信息到文本文件\n"
			DELIMS_LINE\
		);
		Menu_DisplaySubMenu();
		printf(
			DELIMS_LINE\
			" [1].txt文件的存储位置:%s\n"\
			, FilePath);
		printf(
			DELIMS_LINE\
			" [2].保存数据到文本文件\n"\
			" [0].返回主菜单\n"
			DELIMS_LINE
		);
		switch (Event_Input())
		{
		case 1:
			printf("请输入参数文件的存储路径:\n");
			getchar();
			fgets(FilePath, 512, stdin);
			FilePath[strlen(FilePath) - 1] = 0;
			break;
		case 2:
			//开始输出
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
					printf("保存到文件成功\n");
					WriteConfig2(CONFIGFILEPATH5, FilePath);
				}
				else {
					printf("保存到文件失败\n");
				}
			}
			else {
				printf("请先读取文件\n");
			}
			GETCH();
			break;
		case 0:
			return;
		}
	}
}

//7高级功能
void SubMenu_Advantage()
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
			"                    高级功能\n"
			DELIMS_LINE\
		);
		Menu_DisplaySubMenu();
		printf(
			DELIMS_LINE\
			" [1].列配置编辑\n"\
			" [2].计算平均成绩\n"\
			" [0].返回主菜单\n"
		);
		switch (Event_Input())
		{
		case 1:
			if (ChartHead&&ChartHead[CurrentChartIndex] && ChartHead[CurrentChartIndex]->ChartTitle) {
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
		case 2:
			CaluAverage();
			break;
		case 0:
			return;
		}
	}
}


//随机改变颜色
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