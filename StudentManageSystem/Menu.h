#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "DataBase.h"

extern int CurrentChartIndex;				//����ڲ����ı�ı��
extern int CurrentIndexListIndex;			//����ڲ�����IndexList�ı��
extern int CurrentTitleListIndex;			//����ڲ�����TitleList�ı��
extern int CurrentTitleIndex;				//����ڲ�����Chart���е��еı��
extern int CurrentPageIndex;				//��ǰ�ڲ�����ҳ

#define CONFIGFILEPATH1 "Config\\Config1.config"	//�����ļ���·��
#define CONFIGFILEPATH2 "Config\\Config2.config"	//�����ļ���·��
#define CONFIGFILEPATH3 "Config\\Config3.config"	//�����ļ���·��
#define CONFIGFILEPATH4 "Config\\Config4.config"	//�����ļ���·��
#define CONFIGFILEPATH5 "Config\\Config5.config"	//�����ļ���·��

#define RANDOMCOLOR 1//�����Ƿ�����ı䴰����ɫ
#define WARNING_TOMUCHITEM 2000				//���ƺ�ʱ�������������̫��
#define SIZE_PAGE 2000						//һҳ�Ĵ�С

//��ƽ̨�Զ����뿪��
#ifdef __APPLE__ 
#ifdef __MACH__
#define GETPASSWORD 0
#define GETCH() getchar()
#define COMMAND_CLEAR() system("clear")
#else
#include <conio.h> 
#define GETPASSWORD 1
#define GETCH()  system("pause>nul")
#define COMMAND_CLEAR() system("cls")
#endif
#else
#include <conio.h> 
#define GETPASSWORD 1
#define GETCH()  system("pause>nul")
#define COMMAND_CLEAR() system("cls")
#endif

#define DELIMS_LINE " **********************************************************************************************************************\n"

void InitALL();
void FreeAll();
void Menu_DisplaySubMenu();
char* Menu_DisplaySubMenu_Search();
void Menu_DisplaySubMenu_Display();
void Menu_DisplaySubMenu_Page();
int Event_Input();
int InputPassWord(char *PassWord, int MaxSize);
void ChangeColor();

//���ڴ�ȡ�����ļ�
void WriteConfig1(char *ConfigFile, char *ParamFileName, char * DataFileName, char *SexFileName, char *CollageFileName);
void WriteConfig2(char *ConfigFile, char * FileName);
void WriteConfig3(char *ConfigFile, char *ParamFileName, char * DataFileName);
void ReadConfig1(char *ConfigFile, char *ParamFileName, char * DataFileName, char *SexFileName, char *CollageFileName);
void ReadConfig2(char *ConfigFile, char * FileName);
void ReadConfig3(char *ConfigFile, char *ParamFileName, char * DataFileName);

//��Ҫ����ʹ�õ�UI
void SubMenu_Display();

//���˵������
void MainMenu();


