#include <stdio.h>
#include "DataBase.h"

int main()
{
	Chart chart = {0};
	char list[2][32] = { "班级","地址" };
	int list2[2];
	int list3[5];
	IndexList il = { 0 };
	TitleList tl = { 0 };
	IndexList ll = { 0 };

	printf("%d\n",ReadFromFile("data.ini", &chart));
	WirteToIntArray(list2, 2, 20, 20);
	CreateNewUnit(&chart, 2, list, list2);
	FillList(&ll, 1000);
	InitList(&tl, 4, 1, 0, 2, 3, 4, 5);
	//Display_Piece(&chart, 999, &ll);
	Search(&chart, &ll, &ll, 3, "99");
	//Search(&chart, &ll, &ll, 2, "99");
	//Sort(&chart,&ll, SHI(&chart, "姓名"), SORT_ASCENDING);
	Display_Chart(&chart,&ll,&tl,0);
	FreeList(&ll);
	FreeList(&tl);
	system("pause");




}

Chart **charthead;

ErrVal CreatNewChart() {
	Chart *creat;
	static int had_creat_chart_num = 0;             //静态变量 已创建的表格数量
	int creatchartnum;                              //所需创建的表格数量
	printf("请输入所需创建表的数量\n");
	scanf("%d", &creatchartnum);


	charthead = (Chart **)malloc(sizeof(Chart *));
	if (charthead == NULL) {
		return ERR_MEMORYNOTENOUGH;
	}
	for (had_creat_chart_num = 0; had_creat_chart_num < creatchartnum; had_creat_chart_num++) {
		creat = (Chart *)malloc(sizeof(Chart));
		if (creat == NULL) {
			return ERR_MEMORYNOTENOUGH;
		}
		charthead[had_creat_chart_num] = creat;
	}


	printf("表已创建完成\n");
	//free(creat);
	return SUCCESS;
}


void Test1()
{
	
}