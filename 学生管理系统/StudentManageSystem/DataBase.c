#include "DataBase.h"

/*
Create By ZCR
2016-12-03

TODO:存在缺陷
没有初始化函数
*/

/*
在调用函数时,会要求传入一个*list,
这是一个保存学生在表中的实际存放顺序的下标的数组
它保存的数据是一个个下标,这些数据的顺序不会改变表本身,但是它会关系到显示和保存数据
*/
#define WRONGEXIT(x) {printf("%s,程序将会退出",x);system("pause");exit(1);}
#define ADDITIONAL 10		//一次增加10个学生

/*
在存档文件中,
第一行第一个数字代表学生的人数n,第二个数字代表每个人的属性的个数unit
第二行有unit组数据,每组数据由2个数据组成,分别是一个字符串(表头)和一个数字(代表这个单元的限制长度)
接下来有n组数据,一直到文件结尾,每组数据分别有unit个数据,他们的值就是表头定义的值
注意表头的长度限制为31个英文字符
*/



/*
指向字符串数组的指针
*/
char ***StudentList;
char **UnitHead;			//表头名称的字符串数组
int *UnitHeadlimits;		//单元字符限制(数组)
int UnitCount;
int StudentCount;
int StudentCapacity;		//用于记录StudentList的容量(提高效率,避免多次分配)



/*
从文件读取数据
File 要读取的文件路径
*/
void ReadIni(char *File)
{
	FILE *f;
	int n, unit;
	int a, b;
	char temp;
	f = fopen(File, "r");
	if (!f)
		WRONGEXIT("打开文件失败")
		fscanf(f, "%d%d", &n, &unit);	//从文件中读取两个值
	UnitCount = unit;
	StudentCount = n;
	StudentCapacity = n;
	//初始化表头
	UnitHead = (char**)malloc(sizeof(char*) * unit);
	UnitHeadlimits = (int*)malloc(sizeof(int)*unit);
	if (!(UnitHead&&UnitHeadlimits))
		WRONGEXIT("内存不足");

	for (a = 0; a < unit; a++) {
		*(UnitHead + a) = (char*)malloc(sizeof(char) * 32);
		if (!(*(UnitHead + a)))
			WRONGEXIT("内存不足");
		fscanf(f, "%s%c%d", *(UnitHead + a), &temp, UnitHeadlimits + a);
	}
	//开始初始化表并读取数据
	StudentList = (char***)malloc(sizeof(char**)*n);
	if (!StudentList)
		WRONGEXIT("内存不足");
	for (a = 0; a < n; a++) {
		StudentList[a] = (char**)malloc(sizeof(char*)*unit);
		if (!StudentList[a])
			WRONGEXIT("内存不足");
		for (b = 0; b < unit; b++) {
			StudentList[a][b] = (char*)malloc(sizeof(char)*(UnitHeadlimits[b] + 1));
			if (!StudentList[a][b])
				WRONGEXIT("内存不足");
			fscanf(f, "%s", StudentList[a][b]);
		}
	}
	fclose(f);
}

/*
写入数据到文件
File要进行写入的文件路径,
list 当前正在处理的学生的下标集合
n list中元素的个数
*/
void WriteIni(char* File, int *list, int n)
{
	FILE *f;
	int a, b;
	f = fopen(File, "w+");
	if (!f)
		WRONGEXIT("打开文件失败")
		fprintf(f, "%d %d\n", n, UnitCount);
	for (a = 0; a < UnitCount; a++) {
		fprintf(f, "%s %d ", UnitHead[a], UnitHeadlimits[a]);
	}
	fprintf(f, "\n");
	for (a = 0; a < n; a++) {
		for (b = 0; b < UnitCount; b++)
			fprintf(f, "%s ", StudentList[list[a]][b]);
		fprintf(f, "\n");
	}
	fclose(f);
	return;
}

/*
新增一个表列
title新增列的表头
UnitLimits 新增数据长度限制
Default 表中的初始值,必须为非空白字符
*/
void NewUnit(char *title, int UnitLimits, char Default)
{
	char **temp;
	int *temp2;
	int a, b;
	int newUnitCount;
	newUnitCount = UnitCount + 1;

	if (UnitLimits < 1)		//确保UnitLimits能够存储下"0"
		UnitLimits = 1;

	//创建表头
	temp = (char**)malloc(sizeof(char*)*newUnitCount);
	if (!temp)
		WRONGEXIT("内存不足");
	for (a = 0; a < UnitCount; a++)
		temp[a] = UnitHead[a];
	temp[a] = (char*)malloc(sizeof(char) * 32);
	if (!temp[a])
		WRONGEXIT("内存不足");
	strcpy(temp[a], title);
	free(UnitHead);
	UnitHead = temp;

	temp2 = (int*)malloc(sizeof(int)*newUnitCount);
	if (!temp2)
		WRONGEXIT("内存不足");
	for (a = 0; a < UnitCount; a++)
		temp2[a] = UnitHeadlimits[a];
	temp2[a] = UnitLimits;
	free(UnitHeadlimits);
	UnitHeadlimits = temp2;

	//为每个学生的相应属性分配内存
	for (a = 0; a < StudentCount; a++) {
		temp = (char**)malloc(sizeof(char*)*newUnitCount);
		if (!temp)
			WRONGEXIT("内存不足");
		for (b = 0; b < UnitCount; b++)
			temp[b] = StudentList[a][b];
		temp[b] = (char*)malloc(sizeof(char)*(UnitLimits + 1));
		if (!temp[b])
			WRONGEXIT("内存不足");
		temp[b][0] = Default;
		temp[b][1] = 0;
		free(StudentList[a]);
		StudentList[a] = temp;
	}
	UnitCount++;
	return;
}

/*
加入一个新的学生
list 当前正在处理的学生的下标集合
n list中元素的个数
*/
int NewStudent(int *list, int *n)
{
	char ***temp;
	int a;
	//确定是否有空间保存数据
	if (StudentCapacity <= StudentCount) {
		StudentCapacity = StudentCount + ADDITIONAL;
		temp = (char***)malloc(sizeof(char**)*StudentCapacity);
		if (!temp)
			WRONGEXIT("内存不足");
		for (a = 0; a < StudentCount; a++)
			temp[a] = StudentList[a];
		free(StudentList);
		StudentList = temp;
	}
	//对最后一个元素进行写入,到这里可以确定StudentList[StudentCount]一定可以保存数据
	if (UnitCount > 0) {
		StudentList[StudentCount] = (char**)malloc(sizeof(char*)*UnitCount);
		if (!StudentList[StudentCount])
			WRONGEXIT("内存不足");
		for (a = 0; a < UnitCount; a++) {
			if (UnitHeadlimits[a] < 1) {
				UnitHeadlimits[a] = 1;
			}
			StudentList[StudentCount][a] = (char*)malloc(sizeof(char)*(UnitHeadlimits[a] + 1));
			if (!StudentList[StudentCount][a])
				WRONGEXIT("内存不足");
			StudentList[StudentCount][a][0] = '0';		//初始化单元格数据
			StudentList[StudentCount][a][1] = 0;
		}
	}

	list[*n] = StudentCount;//把新的学生的下标传递给名单
	*n += 1;
	StudentCount++;
	return *n;
}

/*
删除指定列
Unit要删除的列的下标
*/
void DeleteUnit(int Unit)
{
	int a, b, c;
	for (a = 0, b = 0; a < UnitCount; a++)
	{
		UnitHead[b] = UnitHead[a];
		UnitHeadlimits[b] = UnitHeadlimits[a];
		if (a != Unit)
			b++;
		else
			free(UnitHead[a]);
	}
	for (a = 0; a < StudentCount; a++)
	{
		for (b = 0, c = 0; b < UnitCount; b++)
		{
			StudentList[a][c] = StudentList[a][b];
			if (b != Unit)
				c++;
			else
				free(StudentList[a][b]);
		}
	}
	UnitCount--;
}

/*
从名单中剔除某个学生(此函数不会对表进行改动)
list是要进行修改的表
n是list表的长度
StudentNumber是学生在表中的实际编号
mode是删除模式 0表示删除后取最后一个元素来填补空缺(效率高) 1表示将按原来的顺序
*/
void DeleteStudentInList(int *list, int *n, int StudentNumber, int mode)
{
	int a, b = 0;
	switch (mode)
	{
	case 0:
		//删除指定学生之后用最后一个学生信息填充
		for (a = 0; a < *n; a++)
		{
			if (list[a] == StudentNumber)
			{
				list[a] = list[*n - 1];
				*n -= 1;
				return;
			}
		}
		break;
	case 1:
		//删除指定学生之后,空位之后的学生上移,以此填补空位
		for (a = 0; a < *n; a++)
		{
			list[b] = list[a];
			if (list[a] != StudentNumber)
				b++;
		}
		*n -= 1;
		return;
	}
}

/*
当学生表不再需要时,调用它可以释放内存,但是释放内存之后不能再对表进行操作,除非重新读取表信息
*/
void DestroyStudentList()
{
	int a, b, c;
	for (a = 0; a < StudentCount; a++)
	{
		for (b = 0; b < UnitCount; b++)
		{
			free(StudentList[a][b]);
		}
		free(StudentList[a]);
	}
	free(StudentList);
	StudentList = NULL;
}


/*
两个字符串进行比较,兼容数字比较
*/
int StrCmp(const char *A, const char *B)
{
	int isNumA = 1, isNumB = 1;
	int lenA = 0, lenB = 0;
	char *A2 = (char*)A, *B2 = (char*)B;
	//计算长度并判断是否是纯数字
	while (*A2) {
		if (isNumA && (*A2<'0' || *A2>'9'))
			isNumA = 0;
		lenA++;
		A2++;
	}
	while (*B2) {
		if (isNumB && (*B2<'0' || *B2>'9'))
			isNumB = 0;
		lenB++;
		B2++;
	}
	if (isNumA*isNumB == 1) {
		//两个数字进行比较
		if (lenA != lenB) {
			//如果两个数字的长度不同,则长的数字大
			return lenA - lenB;
		}
		else {
			//如果数字长度相同,怎从高位到低位依次比较
			return strcmp(A, B);
		}
	}
	else {
		//非数字进行比较
		return strcmp(A, B);
	}
}

/*
通过表头的标题找到表头对应的编号
*/
int SearchHeadIndex(const char *UnitHeadName)
{
	int a;
	for (a = 0; a < UnitCount; a++) {
		if (!strcmp(UnitHead[a], UnitHeadName))
			return a;
	}
	return -1;
}

/*
传入一个下标数组,存储学生按指定的基准进行排序后新的顺序,list中仅储存这个学生在数据库中的实际顺序
list 当前正在处理的学生的下标集合
n list中元素的个数
Order==0 升序排序
Order==1 降序排序
*/
void Sort(int *list, int n, int sortBase, int Order)
{
	int j, k;
	int temp;
	switch (Order) {
	case 0:
		for (j = 0; j < n; j++) {
			for (k = j; k < n; k++) {
				if (StrCmp(StudentList[list[j]][sortBase], StudentList[list[k]][sortBase]) > 0) {
					temp = list[j];
					list[j] = list[k];
					list[k] = temp;
				}
			}
		}
		break;
	case 1:
		for (j = 0; j < n; j++) {
			for (k = j; k < n; k++) {
				if (StrCmp(StudentList[list[j]][sortBase], StudentList[list[k]][sortBase]) < 0) {
					temp = list[j];
					list[j] = list[k];
					list[k] = temp;
				}
			}
		}
		break;
	}
	return;
}

/*
查找符合条件的学生
返回值为找到的学生数
Sourcelist 当前正在处理的学生的下标集合
n list中元素的个数
Resultlist 处理之后返回的学生的下标集合(允许与Sourcelist一样)
destin 寻找的目标字符串
*/
int Search(int *Sourcelist, int n, int *Resultlist, int SearchUnit, const char *destin)
{
	int a;
	int list_p = 0;
	for (a = 0; a < n; a++) {
		if (!strcmp(StudentList[Sourcelist[a]][SearchUnit], destin)) {
			Resultlist[list_p++] = Sourcelist[a];
		}
	}
	return list_p;
}

/*
取得整张表的原理就是把所有索引都传递出去
list用于返回学生名单
n返回学生数
*/
void GetList(int *list, int *n)
{
	int a;
	*n = StudentCount;
	for (a = 0; a < StudentCount; a++) {
		list[a] = a;
	}
	return;
}

/*
根据list显示学生信息
mode=1 显示编号
mode=0 不显示编号
*/
void display(int *list, int n, int mode)
{
	int a, b;
	if (mode == 1)
		printf("编号 ");
	for (a = 0; a < UnitCount; a++) {
		printf("%-*s ", UnitHeadlimits[a], UnitHead[a]);
	}
	printf("\n");
	if (mode == 0) {
		for (a = 0; a < n; a++) {
			for (b = 0; b < UnitCount; b++) {
				printf("%-*s ", UnitHeadlimits[b], StudentList[list[a]][b]);
			}
			printf("\n");
		}
	}
	else {
		for (a = 0; a < n; a++) {
			printf("%-4d ", a);
			for (b = 0; b < UnitCount; b++) {
				printf("%-*s ", UnitHeadlimits[b], StudentList[list[a]][b]);
			}
			printf("\n");
		}
	}
	return;
}

/*
该函数取得指定学生的指定信息的指针
可以用于显示它的值或修改它的值
list 名单
list_ID 学生在名单中的位置(从0开始计)
GetUnit 表头的
*/
char* GetString(int *list, int list_ID, int GetUnit)
{
	return StudentList[list[list_ID]][GetUnit];
}

/*
返回第Unit个单元的名称
*/
char* GetUnitTittle(int Unit)
{
	return UnitHead[Unit];
}
