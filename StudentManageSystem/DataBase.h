#pragma once
/*
Create By ZCR
2016-12-10
*/

//�������
#define SUCCESS					0		//�����ɹ�
#define ERR_OPENFILE			1		//���ļ�ʧ��
#define ERR_NOTSTANDARDFILE		2		//����һ��������ɶ����ļ�
#define ERR_MEMORYNOTENOUGH		3		//�ڴ治��,�޷������ڴ�
#define ERR_ILLEGALCHART		4		//�Ƿ��ı�
#define ERR_UNINITIALIZEDCHART	5		//δ��ʼ���ı�
#define ERR_ILLEGALPARAM		6		//�Ƿ��Ĳ���
#define ERR_EMTYLIST			7		//��List
#define ERR_UNINITIALIZEDLIST	8		//δ��ʼ���ı�
#define ERR_WRONGPASSWORD		9		//���������
#define ERR_ILLEGALBINFILE		10		//����Ķ������ļ�

//���ǳ���
#define SORT_ASCENDING	0		//�������������
#define SORT_DESCENDING	1		//�������������
#define DISPLAY_HIDENUMBER	0	//���ر��
#define DISPLAY_SHOWNUMBER	1	//��ʾ���
#define LISTTYPE_INDEXLIST	0	//ָ��ΪIndexList���͵Ľṹ��
#define LISTTYPE_TITLELIST	1	//ָ��ΪTitleList���͵Ľṹ��

//��������
#define WTIA WirteToIntArray
#define SHI SearchHeadIndex

//���뿪��
#define SORT_ARITHMETIC 0		//�����㷨�������

//�����ڳ���
#define SORT_CHUNK_SIZE 8		//�����㷨���ò���������ٽ����

//���ͱ���
typedef int ErrVal;
typedef char*** Chart_t;
typedef char** ChartPiece_t;

//����һ����ṹ
typedef struct
{
	//��
	Chart_t Chart;				//�����������׵�ַ
	char *ChartName;			//����������

	//����
	int TitleCount;				//�洢����ĸ���
	ChartPiece_t ChartTitle;	//�洢ÿ��������ַ���(ÿ�����ⲻ�ó���31����ĸ)
	int *ChartLimits;			//�洢ÿһ�������µĵ�Ԫ������ַ�������󳤶�

	//��
	//int AllocatedLines;			//���ѷ���Ĵ�С(��ֵ���ڵ���UsedLines)(�ѷ��䵫δʹ�õ���δ�����ڴ�)
	int UsedLines;				//�ڱ���ʵ�ʱ�ʹ�õ���
	int HadInit;				//��¼������Ƿ��Ѿ�����ʼ��
} Chart;


/*
IndexList��һ�������ṹ��,�������list��һ��int����,�����ÿһ��Ԫ���ǵ�Ԫ����Chart���е�ʵ��˳����±�(��0��ʼ����),�ڵ���displayʱ,Ӱ�����������˳�����list���±��˳��,�������������λ���޹�
TitleListҲ��һ�������ṹ��,�������list��һ��int����,�����ÿһ��Ԫ���Ǳ�����Chart���е��±�,�ڵ���displayʱ,������Ҳͬ������Ӱ��display��ʾ�ı����˳��
����:��ʹ��ʱһ��Ҫ����Ӧ�ı�ƥ��,����������ȷ.
*/
typedef struct
{
	int *list;			//����,�����ֵ�洢����ָ�����е�ʵ����(����)�������±�
	int listCount;		//��¼����ĸ���
	int AllocatedList;	//�ѷ�����ڴ�
	int IsOnStack;		//��ֵΪ1ʱ��ʾlist�Ƕ�̬�����
	char *ListName;		//���List������
} List, IndexList, TitleList;

/*
ӳ�䷽���洢�ṹ
���ڴ�Ŵ��ļ��ж�ȡ��ӳ�䷽��,���ڴ��뵽Ŀ���ַ�����ת��ʱ
*/
typedef struct
{
	char **Val;				//ӳ�䷽���ļ���ŵ�λ�õ���ָ��
	char **String;			//ӳ�䷽����ֵ��ŵ�λ�õ���ָ��
	int Count;				//ӳ�䷽����Ԫ�صĸ���
	char *MapName;			//��ӳ�䷽��������,Ĭ��Ϊ��ȡ���ļ�����
} InfoMap;

/*
ȫ���ⲿ����������
*/
//��������
extern Chart ** ChartHead;			//ȫ��:���ָ������
extern int ChartCount;				//ȫ��:��ʹ�õı�ĸ���
extern int AlloctedChartCount;		//ȫ��:�ѷ���ı�ĸ���

//����List��������
extern IndexList **IndexListHeadSet;//ȫ��:IndexList��ָ������
extern int IndexListCount;			//ȫ��:��ʹ�õ�IndexList�ĸ���
extern int AlloctedIndexListCount;	//ȫ��:�ѷ����IndexList�ĸ���

extern TitleList **TitleListHeadSet;//ȫ��:TitleList��ָ������
extern int TitleListCount;			//ȫ��:��ʹ�õ�TitleList�ĸ���
extern int AlloctedTitleListCount;	//ȫ��:�ѷ����TitleList�ĸ���


//�����������
//ErrVal ReadFromFile(const char *FileName, Chart *OperateChart);
//ErrVal WriteToFile_Chart();
ErrVal ReadFromTwoFile(const char *ParamFileName, const char * DataFileName, Chart *OperateChart);
ErrVal ReadFromBinFile(const char *FileName, const char *PassWord, Chart *OperateChart);
ErrVal ExportToTxt(const char * FileName, Chart * OperateChart, IndexList * WriteLine, TitleList * WriteTitle);
ErrVal WriteToTwoFile_Chart(const char *ParamFileName, const char * DataFileName, Chart *OperateChart);
ErrVal WriteToTwoFileByList(const char * ParamFileName, const char * DataFileName, Chart * OperateChart, IndexList *WriteLine, TitleList *WriteTitle);
ErrVal WriteToBinFile_Chart(const char * FileName, const char * PassWord, Chart * OperateChart);
ErrVal WriteToBinFileByList(const char * FileName, const char * PassWord, Chart * OperateChart, IndexList *WriteLine, TitleList *WriteTitle);
ErrVal Display_Chart(Chart *OperateChart, IndexList *ShowLines, TitleList *ShowTitle, int Mode);
ErrVal Display_Page(Chart *OperateChart, IndexList *ShowLines, TitleList *ShowTitle, int Mode, int PageSize, int PageIndex);
ErrVal Display_Piece(Chart *OperateChart, int OperateLineIndex, TitleList *ShowTitle);


//����������
ErrVal NewChartSet(int CreateCount);
ErrVal FreeChartSet();

//���������
ErrVal CreateNewUnit(Chart *OperateChart, int CreateCount, char(*NewTitleSet)[32], int *NewTitleLimits);
ErrVal CreateNewLine(Chart * OperateChart, int CreateCount, IndexList *NewList);
ErrVal InitNewChart(Chart *OperateChart, int LinesCount, int TitleCount, char* TitleList, int TitleLimits,...);
ErrVal Translate(Chart *OperateChart, int TitleIndex, InfoMap *MapStruct);
ErrVal UnTranslate(Chart *OperateChart, int TitleIndex, InfoMap *MapStruct);
ErrVal FreeChart(Chart *OperateChart);

//��List�����ĺ���
ErrVal Sort(Chart *OperateChart, IndexList *OperateList, int BaseTitleIndex, int Mode);
ErrVal Search(Chart *OperateChart, IndexList *SearchList, IndexList *ResultList, int BaseTitleIndex, char * DestinString);
ErrVal InitList(List *OperateList, int Count, int ListData, ...);
ErrVal FillList(List *OperateList, int Count);
ErrVal CopyList(List *SourceList, List *DestList);
ErrVal GetListFromString(char* Input,int n, List *list, int MaxIndex);
ErrVal GetListFromStringViaList(char* Input, int n, List *Resultlist, List *SourceList);
ErrVal FreeList(List *OperateList);
ErrVal WirteToIntArray(int* OperateArray, int n, int ListData, ...);

//List����������
ErrVal NewListSet(int CreateCount, int ListType);
ErrVal FreeListSet(int ListType);

//ӳ���ϵ��������
ErrVal ReadMapFile(char* MapFileName, InfoMap *MapStruct);
ErrVal FreeMapStruct(InfoMap *MapStruct);

//�������ܺ���
int StrCmp(const char *A, const char *B);
int SearchHeadIndex(Chart *OperateChart, const char *UnitHeadName);
char* GetFileName(const char* Path);


/*
TODO:
��Ҫ�Ա��еĿ�Ԫ�ش洢ʱʹ��#������ַ���
���NewUnit���ڴ�й©���� 
���뺯�������ڴ�й©�ķ���,�Լ����׳����޷���ȡ�ļ���bug
*/
