﻿#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "DataBase.h"

extern int CurrentChartIndex;				//最近在操作的表的编号
extern int CurrentIndexListIndex;			//最近在操作的IndexList的编号
extern int CurrentTitleListIndex;			//最近在操作的TitleList的编号
extern int CurrentTitleIndex;				//最近在操作的Chart表中的列的编号

#define CONFIGFILEPATH1 "Config\\Config1.config"	//配置文件的路径
#define CONFIGFILEPATH2 "Config\\Config2.config"	//配置文件的路径
#define CONFIGFILEPATH3 "Config\\Config3.config"	//配置文件的路径
#define CONFIGFILEPATH4 "Config\\Config4.config"	//配置文件的路径
#define CONFIGFILEPATH5 "Config\\Config5.config"	//配置文件的路径

#define RANDOMCOLOR 1//控制是否随机改变窗口颜色

#ifdef __APPLE__ 
#ifdef __MACH__
#define GETCH() getchar()
#define COMMAND_CLEAR() system("clear")
#else
#define GETCH()  system("pause>nul")
#define COMMAND_CLEAR() system("cls")
#endif
#else
#define GETCH()  system("pause>nul")
#define COMMAND_CLEAR() system("cls")
#endif

#define DELIMS_LINE " **********************************************************************************************************************\n"

void InitALL();
void FreeAll();
void Menu_DisplaySubMenu();
void Menu_DisplaySubMenu_Search();
void Menu_DisplaySubMenu_Display();
int Event_Input();
void ChangeColor();

void WriteConfig1(char *ConfigFile, char *ParamFileName, char * DataFileName, char *SexFileName, char *CollageFileName);
void WriteConfig2(char *ConfigFile, char * FileName);
void WriteConfig3(char *ConfigFile, char *ParamFileName, char * DataFileName);
void ReadConfig1(char *ConfigFile, char *ParamFileName, char * DataFileName, char *SexFileName, char *CollageFileName);
void ReadConfig2(char *ConfigFile, char * FileName);
void ReadConfig3(char *ConfigFile, char *ParamFileName, char * DataFileName);

//主菜单的入口
void MainMenu();

//黄智豪的函数
void SortList_M();
void CaluAverage();
void SortByName1();
void SortByEx1();
void SortByWhatYouWant();
