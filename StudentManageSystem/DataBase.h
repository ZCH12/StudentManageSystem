#pragma once
/*
Create By ZCR
2016-12-10
*/

//错误代码
#define SUCCESS					0		//操作成功
#define ERR_OPENFILE			1		//打开文件失败
#define ERR_NOTSTANDARDFILE		2		//不是一个本程序可读的文件
#define ERR_MEMORYNOTENOUGH		3		//内存不足,无法分配内存
#define ERR_ILLEGALCHART		4		//非法的表
#define ERR_UNINITIALIZEDCHART	5		//未初始化的表
#define ERR_ILLEGALPARAM		6		//非法的参数
#define ERR_EMTYLIST			7		//空List
#define ERR_UNINITIALIZEDLIST	8		//未初始化的表
#define ERR_WRONGPASSWORD		9		//错误的密码
#define ERR_ILLEGALBINFILE		10		//错误的二进制文件

//助记常量
#define SORT_ASCENDING	0		//按升序进行排序
#define SORT_DESCENDING	1		//按降序进行排序
#define DISPLAY_HIDENUMBER	0	//隐藏编号
#define DISPLAY_SHOWNUMBER	1	//显示编号
#define LISTTYPE_INDEXLIST	0	//指定为IndexList类型的结构体
#define LISTTYPE_TITLELIST	1	//指定为TitleList类型的结构体

//函数短名
#define WTIA WirteToIntArray
#define SHI SearchHeadIndex

//编译开关
#define SORT_ARITHMETIC 0		//排序算法编译控制

//编译期常量
#define SORT_CHUNK_SIZE 8		//排序算法改用插入排序的临界个数

//类型别名
typedef int ErrVal;
typedef char*** Chart_t;
typedef char** ChartPiece_t;

//定义一个表结构
typedef struct
{
	//表
	Chart_t Chart;				//整个表的入口首地址
	char *ChartName;			//这个表的名称

	//标题
	int TitleCount;				//存储标题的个数
	ChartPiece_t ChartTitle;	//存储每个标题的字符串(每个标题不得超过31个字母)
	int *ChartLimits;			//存储每一个标题下的单元格里的字符串的最大长度

	//行
	//int AllocatedLines;			//表已分配的大小(此值大于等于UsedLines)(已分配但未使用的行未申请内存)
	int UsedLines;				//在表中实际被使用的行
	int HadInit;				//记录这个表是否已经被初始化
} Chart;


/*
IndexList是一个索引结构体,它里面的list是一个int数组,数组的每一个元素是单元行在Chart表中的实际顺序的下标(从0开始计数),在调用display时,影响数据输出的顺序的是list中下标的顺序,而与行在数组的位置无关
TitleList也是一个索引结构体,它里面的list是一个int数组,数组的每一个元素是标题在Chart表中的下标,在调用display时,此索引也同样可以影响display显示的标题和顺序
警告:在使用时一定要与相应的表匹配,否则结果不正确.
*/
typedef struct
{
	int *list;			//数组,里面的值存储的是指定表中的实际行(或列)的数组下标
	int listCount;		//记录数组的个数
	int AllocatedList;	//已分配的内存
	int IsOnStack;		//该值为1时表示list是动态分配的
	char *ListName;		//这个List的名称
} List, IndexList, TitleList;

/*
映射方案存储结构
用于存放从文件中读取的映射方案,用于代码到目标字符串的转换时
*/
typedef struct
{
	char **Val;				//映射方案的键存放的位置的首指针
	char **String;			//映射方案的值存放的位置的首指针
	int Count;				//映射方案中元素的个数
	char *MapName;			//此映射方案的名字,默认为读取的文件名称
} InfoMap;

/*
全局外部变量的声明
*/
//表集的声明
extern Chart ** ChartHead;			//全局:表的指针数组
extern int ChartCount;				//全局:已使用的表的个数
extern int AlloctedChartCount;		//全局:已分配的表的个数

//两种List集的声明
extern IndexList **IndexListHeadSet;//全局:IndexList的指针数组
extern int IndexListCount;			//全局:已使用的IndexList的个数
extern int AlloctedIndexListCount;	//全局:已分配的IndexList的个数

extern TitleList **TitleListHeadSet;//全局:TitleList的指针数组
extern int TitleListCount;			//全局:已使用的TitleList的个数
extern int AlloctedTitleListCount;	//全局:已分配的TitleList的个数


//输入输出函数
//ErrVal ReadFromFile(const char *FileName, Chart *OperateChart);
//ErrVal WriteToFile_Chart();
ErrVal ReadFromTwoFile(const char *ParamFileName,const char * DataFileName,Chart *OperateChart);
ErrVal ReadFromBinFile(const char *FileName, const char *PassWord, Chart *OperateChart);
ErrVal ExportToTxt(const char * FileName, Chart * OperateChart, IndexList * WriteLine, TitleList * WriteTitle);
ErrVal WriteToTwoFile_Chart(const char *ParamFileName,const char * DataFileName, Chart *OperateChart);
ErrVal WriteToTwoFileByList(const char * ParamFileName, const char * DataFileName, Chart * OperateChart, IndexList *WriteLine, TitleList *WriteTitle);
ErrVal WriteToBinFile_Chart(const char * FileName, const char * PassWord, Chart * OperateChart);
ErrVal WriteToBinFileByList(const char * FileName, const char * PassWord, Chart * OperateChart, IndexList *WriteLine, TitleList *WriteTitle);
ErrVal Display_Chart(Chart *OperateChart, IndexList *ShowLines, TitleList *ShowTitle, int Mode);
ErrVal Display_Page(Chart *OperateChart, IndexList *ShowLines, TitleList *ShowTitle, int Mode, int PageSize, int PageIndex);
ErrVal Display_Piece(Chart *OperateChart, int OperateLineIndex, TitleList *ShowTitle);


//表集操作函数
ErrVal NewChartSet(int CreateCount);
ErrVal FreeChartSet();

//表操作函数
ErrVal CreateNewUnit(Chart *OperateChart, int CreateCount, char(*NewTitleSet)[32], int *NewTitleLimits);
ErrVal CreateNewLine(Chart * OperateChart, int CreateCount, IndexList *NewList);
ErrVal InitNewChart(Chart *OperateChart,int LinesCount,int TitleCount,char* TitleList,int TitleLimits,...); 
ErrVal Translate(Chart *OperateChart,int TitleIndex,InfoMap *MapStruct);
ErrVal UnTranslate(Chart *OperateChart, int TitleIndex, InfoMap *MapStruct);
ErrVal FreeChart(Chart *OperateChart);

//对List操作的函数
ErrVal Sort(Chart *OperateChart, IndexList *OperateList, int BaseTitleIndex, int Mode);
ErrVal Search(Chart *OperateChart, IndexList *SearchList, IndexList *ResultList, int BaseTitleIndex, char * DestinString);
ErrVal InitList(List *OperateList, int Count, int ListData, ...);
ErrVal FillList(List *OperateList, int Count);
ErrVal CopyList(List *SourceList, List *DestList);
ErrVal GetListFromString(char* Input, List *list,int MaxIndex);
ErrVal FreeList(List *OperateList);
ErrVal WirteToIntArray(int* OperateArray, int n, int ListData, ...);

//List集操作函数
ErrVal NewListSet(int CreateCount,int ListType);
ErrVal FreeListSet(int ListType);

//映射关系操作函数
ErrVal ReadMapFile(char* MapFileName, InfoMap *MapStruct);
ErrVal FreeMapStruct(InfoMap *MapStruct);

//基础功能函数
int StrCmp(const char *A, const char *B);
int SearchHeadIndex(Chart *OperateChart, const char *UnitHeadName);
char* GetFileName(const char* Path);


/*
TODO:
需要对表中的空元素存储时使用#代替空字符串
检查NewUnit的内存泄漏问题 
输入函数存在内存泄漏的风险,以及容易出现无法读取文件的bug
*/
