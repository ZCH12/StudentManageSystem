#include "DataBase.h"


extern int ChartCount;
extern Chart ** ChartHead;
extern int AlloctedChartCount;




ErrVal NewChart(int CreateCount);

void ReadFromFile_M();
void ReadFromTwoFile_M();
void SortList_M();
