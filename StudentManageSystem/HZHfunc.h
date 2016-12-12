#include "DataBase.h"

#define DELIMS_LINE " *********************************************************************************************************\n"

#ifdef __APPLE__
#ifdef __MACH__
#define COMMAND_CLEAR() system("clear")
#else
#define COMMAND_CLEAR() system("cls")
#endif
#else
#define COMMAND_CLEAR() system("cls")
#endif


void ReadFromTwoFile_M();
//void ReadFromFile_M();
void SortList_M();
void text();
void Average();
