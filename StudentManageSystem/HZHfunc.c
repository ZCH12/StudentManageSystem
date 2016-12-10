#define _CRT_SECURE_NO_WARNINGS
#define OUTSCANFAGAIN(obj, dline, uline) {if(obj<=dline||obj>=uline){printf("输入错误,请重新输入\n");continue;}}


#include <stdlib.h>
#include <stdio.h>
#include "DataBase.h"
#include "HZHfunc.h"

void ReadFromTwoFile_M()
{
	int Again;
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
    , DataFileName[128] = "/Users/wongziihou/Desktop/StudentManageSystem.v2/StudentManageSystem/Stu_info.txt";

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
			printf("\n*****************************\n"
                   "读取文件出现错误\n"
                   "1.重新输入\n"
                   "0.退出\n"
                   "*****************************\n");
            
            scanf("%d", &Again);
            if (Again == 1)
            {
                continue;
            }
        }
        else
        {
            printf("读入成功\n");
            
            printf("\n*****************************\n"
                   "1.输出表格\n"
                   "0.保存\n"
                   "*****************************\n");
            scanf("%d", &Pri);
            if (Pri==1)
            {
                ReadMapFile(imps, &im1);
                Translate(ChartHead[ChartId-1], SearchHeadIndex(ChartHead[ChartId-1], "性别"), &im1);
                ReadMapFile(impc, &im1);
                Translate(ChartHead[ChartId-1], SearchHeadIndex(ChartHead[ChartId-1], "学院名称"), &im1);
                Display_Chart(ChartHead[ChartId-1], NULL, NULL, 0);
            }
            i++;
        }
	}
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
	int Mode = 0, SortMode = 1, ChartId;
	int i;
	int k;

	printf("\n*****************************\n"
           "1.按照姓名排序\n"
		"2.按照平均成绩排序\n"
		"3.按照任意条件排序\n"
		"0.退出\n"
           "*****************************\n");
	while (scanf("%d", &Mode),
		Mode != 0) {
		if (Mode <= 0 || Mode >= 3) {
			printf("输入错误\n");
			continue;
		}
        for (i = 0; i<ChartCount; i++) {
            printf("%d.%s\n", i+1, ChartHead[i]->ChartName);
        }
		printf("请输入所需排序的表格\n");
        


		scanf("%d", &ChartId);
		printf("\n*****************************\n"
			"1.升序\n"
			"2.降序\n"
               "*****************************\n");
		scanf("%d", &SortMode);
		for (i = 0; i < ChartCount; i++) {
			printf("%d.%s\n", i+1, ChartHead[ChartId-1]->ChartTitle[i]);
		}
		scanf("%d", &k);

		switch (Mode) {
		case 1:
			Sort(ChartHead[ChartId-1], NULL, SHI(ChartHead[ChartId-1], "学号"), SortMode - 1);
                Display_Chart(ChartHead[ChartId], NULL, NULL, 1);

			break;


			//            case 2:
			////                Sort(ChartHead[ChartId], <#IndexList *OperateList#>, <#int BaseTitleIndex#>, <#int Mode#>);
			//                break;
			//
			//            case 3:
			//                <#statements#>
			//                break;

			//            case 0:
			//                <#statements#>
			//                break;
		}


	}


}


//for (i = 0; i<ChartHead[0]->TitleCount; i++) {
//    atoi(ChartHead[0]->Chart[0][SHI(ChartHead[0],"成绩1")]);//第一个表里 的第一个同学的第一个成绩
//}





