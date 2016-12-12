#define _CRT_SECURE_NO_WARNINGS
#define OUTSCANFAGAIN(obj, dline, uline) {if(obj<=dline||obj>=uline){printf("输入错误,请重新输入\n");continue;}}

#include <stdlib.h>
#include <stdio.h>
#include "DataBase.h"
#include "HZHfunc.h"



void ReadFromTwoFile_M()
{
	int Again = 0;
	int Pri = 0;
//    请输入读入文件的数量,若输入0则退出
//    1
//    请输入存储各单元名字的文件
//    /Users/wongziihou/Desktop/StudentManageSystem.v2/StudentManageSystem/stu_param.txt
//    请输入存储各单元资料的文件
//    /Users/wongziihou/Desktop/StudentManageSystem.v2/StudentManageSystem/Stu_info.txt
//    请输入保存的表的编号（1—1）
//    1

	int i, Val = 0;
	int ChartId = 1, ReadFileNum=1;
    InfoMap im1 = {0};
    char imps[128]="/Users/wongziihou/Desktop/StudentManageSystem.v2/StudentManageSystem/S_info.txt", impc[128]="/Users/wongziihou/Desktop/StudentManageSystem.v2/StudentManageSystem/C_info.txt";
    char ParamFileName[128]= "/Users/wongziihou/Desktop/StudentManageSystem.v2/StudentManageSystem/stu_param.txt"
    , DataFileName[128] = "/    ";

//	printf("\n请输入读入文件的数量,若输入0则退出\n");
//	scanf("%d", &ReadFileNum);
    
	NewChartSet(ReadFileNum);
	for (i = 0; i < ReadFileNum;)
    {

//		printf("请输入存储各单元名字的文件\n");
//		scanf("%s", ParamFileName);
//		printf("请输入存储各单元资料的文件\n");
//		scanf("%s", DataFileName);
//		printf("请输入保存的表的编号（1—%d）\n", ReadFileNum);
//		scanf("%d", &FileIndex);

		Val = ReadFromTwoFile(ParamFileName, DataFileName, ChartHead[ChartId - 1]);
		if (Val != 0)
        {
            COMMAND_CLEAR();
			printf(
                   DELIMS_LINE
                   "读取文件出现错误\n"
                   " [1].重新输入\n"
                   " [0].返回上级菜单\n"
                   DELIMS_LINE
                   );
            
            scanf("%d", &Again);
            if (Again == 1)
            {
                continue;
            }
        }
        else
        {
            ReadMapFile(imps, &im1);
            Translate(ChartHead[ChartId-1], SearchHeadIndex(ChartHead[ChartId-1], "性别"), &im1);
            ReadMapFile(impc, &im1);
            Translate(ChartHead[ChartId-1], SearchHeadIndex(ChartHead[ChartId-1], "学院名称"), &im1);
            
            COMMAND_CLEAR();
            printf("读入成功\n");
            printf(
                   DELIMS_LINE
                   " [1].输出表格\n"
                   " [0].保存\n"
                   DELIMS_LINE
                   );
            scanf("%d", &Pri);
            if (Pri==1)
            {
                COMMAND_CLEAR();
                Display_Chart(ChartHead[ChartId-1], NULL, NULL, DISPLAY_HIDENUMBER);
            }
            i++;
        }
        

	}
    return;
}


//void ReadFromFile_M() {
//
//
//	int i;
//	int Val, ReadFileNum;
//	char FileName[16];
//
//	printf("请输入所需读取文件的数量,输入0退出\n");
//	while (scanf("%d", &ReadFileNum), ReadFileNum != 0) {
//		
//        NewChartSet(ReadFileNum);
//		printf("请输入文件名字(请使用空格将文件隔开，若文件不在此文件夹，请写上绝对地址。"
//			"如~//username/Desktop/xxx.txt)\n");
//		
//        for (i = 0; i < ReadFileNum;) {
//			
//            printf("表%d:\n", i+1);
//			scanf("%s", FileName);
//			
//            Val = ReadFromFile(FileName, ChartHead[i]);
//			if (Val != 0) {
//				printf("错误代码:%d,读取文件出现错误。重新输入请按1,输入其他键则退出\n", Val);
//				int Again;
//				scanf("%d", &Again);
//				if (Again == 1) {
//					continue;
//				}
//				else
//					return;
//
//			}
//			i++;
//		}
//	}
//	return;
//
//}


void SortList_M() {
    
    
    int Mode = 0;
    int SortMode = 0;
    int ChartId = 0;
	int i;
    
    while (
           COMMAND_CLEAR(),
           printf(
                  DELIMS_LINE
                  " [1].按照姓名排序\n"
                  " [2].按照平均成绩排序\n"
                  " [3].按照任意条件排序\n"
                  " [0].返回主菜单\n"
                  DELIMS_LINE
                  ),
           scanf("%d", &Mode),
           Mode != 0
           )
    {
            COMMAND_CLEAR();
		if (Mode <= 0 || Mode >= 3) {
			printf("输入错误\n");
			continue;
		}
        for (i = 0; i<ChartCount; i++) {
            printf("%d.%s\n", i+1, ChartHead[i]->ChartName);
        }
		printf("请输入所需排序的表格\n");
		scanf("%d", &ChartId);
		printf(
               DELIMS_LINE
               " [1].升序排序\n"
               " [2].降序排序\n"
               DELIMS_LINE
               );
		scanf("%d", &SortMode);
		switch (Mode)
        {
		case 1:
                FillList(IndexListHeadSet[ChartId-1], ChartHead[ChartId-1]->UsedLines);
                Sort(ChartHead[ChartId-1], IndexListHeadSet[ChartId-1], SearchHeadIndex(ChartHead[ChartId-1], "学号"), SORT_ASCENDING);
                Display_Chart(ChartHead[ChartId-1], IndexListHeadSet[ChartId-1], NULL, DISPLAY_HIDENUMBER);
                continue;
                
        case 2:
                
                FillList(IndexListHeadSet[ChartId-1], ChartHead[ChartId-1]->UsedLines);
                Average(ChartId);
                Sort(ChartHead[ChartId-1], IndexListHeadSet[ChartId-1], SHI(ChartHead[ChartId-1], "平均成绩"), SORT_ASCENDING);
                Display_Chart(ChartHead[ChartId-1], IndexListHeadSet[ChartId-1], NULL, DISPLAY_HIDENUMBER);
                continue;
                
//			            case 3:
//			                
//			                break;
			//            case 0:
			//                <#statements#>
			//                break;
		}


	}


}


//for (i = 0; i<ChartHead[0]->TitleC<#statements#>ount; i++) {
//    atoi(ChartHead[0]->Chart[0][SHI(ChartHead[0],"成绩1")]);//第一个表里 的第一个同学的第一个成绩
//}

void Average(int ChartId) {
    int i, t;
    char NewUnitName[32] = "";
    int TitleLimits = 0;
    double sum;
    int Int;
    //我要写的是按照成绩排序，然后我需要吧新建单元独立出来。,
    //average创建一个新的单元，计算之前的平均成绩
    while (1) {
        COMMAND_CLEAR();
        printf(DELIMS_LINE
               "                 新增单元"
               DELIMS_LINE);
        Menu_DisplaySubMenu();
        printf(
               DELIMS_LINE
               " [1].新增单元数量:%d\n"
               " [2].新增单元名字:%s\n"
               " [3].选择计算平均成绩的对象:"
               " Tip:输入对应数字进行输入数据\n"
               DELIMS_LINE
               " [4].开始计算\n"
               " [0].返回上一级\n"
               ,TitleLimits, NewUnitName);
        switch (Event_Input()) {
            case 1:
                printf("请输入新增单元数量\n");
                scanf("%d", &TitleLimits);
                break;
            case 2:
                printf("请输入新增单元名字\n");
                for (i=0; i<TitleLimits; i++) {
                    printf("%d.",i+1);
                    scanf("%s", NewUnitName);
                }
                break;
            case 3:
                break;
            case 4:
                CreateNewUnit(ChartHead[ChartId-1], 1, &NewUnitName, &TitleLimits);
                for (i = 0; i < ChartHead[ChartId-1]->UsedLines; i++) {
                    for (t = 4, sum = 0; t < ChartHead[ChartId-1]->TitleCount-1; t++) {
                        sum += atof(ChartHead[ChartId-1]->Chart[i][t]);
                    }
                    sprintf(ChartHead[ChartId-1]->Chart[i][t], "%.1lf", sum/10);
                }
                
                
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
                scanf("%s", ParamFilePath);
                break;
            case 2:
                printf("请输入数据文件路径:\n");
                scanf("%s", DataFilePath);
                break;
            case 3:
                printf("请输入性别映射文件路径:\n");
                scanf("%s", SexTranslateFilePath);
                break;
            case 4:
                printf("请输入学院信息映射文件路径:\n");
                scanf("%s", CollegeTranslateFilePath);
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
                return ;
        }
    }
}



