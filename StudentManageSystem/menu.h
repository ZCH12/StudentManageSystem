#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "DataBase.h"

extern int CurrentChartIndex;
extern int CurrentIndexListIndex;
extern int CurrentTitleListIndex;
extern int CurrentTitleIndex;

#ifdef __APPLE__ 
#ifdef __MACH__ 
#include <unistd.h>
#define GETCH() pause()
#define COMMAND_CLEAR() system("clear")
#else
#define GETCH()  system("pause>nul")
#define COMMAND_CLEAR() system("cls")
#endif
#else
#define GETCH()  system("pause>nul")
#define COMMAND_CLEAR() system("cls")
#endif


#define DELIMS_LINE " *********************************************************************************************************\n"

void InitALL();
void FreeAll();
void Menu_DisplaySubMenu();
void Menu_DisplaySubMenu_Search();
int Event_Input();

//主菜单的入口
void MainMenu();

//原HZHfun.h
void ReadFromTwoFile_M();
//void ReadFromFile_M();
void SortList_M();
void text();
void Average();
