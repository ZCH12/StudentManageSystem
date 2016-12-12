#pragma once
#include "DataBase.h"


extern int CurrentChartIndex;
extern int CurrentIndexListIndex;
extern int CurrentTitleListIndex;
extern int CurrentTitleIndex;

#ifdef __APPLE__ 
#ifdef __MACH__ 
#define COMMAND_CLEAR() system("clear")
#else
#define COMMAND_CLEAR() system("cls")
#endif
#else
#define COMMAND_CLEAR() system("cls")
#endif


#define DELIMS_LINE " *********************************************************************************************************\n"

void InitALL();
void FreeAll();
void Menu_DisplaySubMenu();
void Menu_DisplaySubMenu_Search();
int Event_Input();