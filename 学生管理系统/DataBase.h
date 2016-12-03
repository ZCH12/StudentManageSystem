#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char ***StudentList;
extern int StudentCount;

void ReadIni(char *File);
void WriteIni(char* File, int *list, int n);
void NewUnit(char *title, int UnitLimits, char Default);
int NewStudent(int *list, int *n);
void DeleteUnit(int Unit);
void DeleteStudentInList(int *list, int *n, int StudentNumber, int mode);
int StrCmp(const char *A, const char *B);
int SearchHeadIndex(const char *ListHeadName);
void Sort(int *list, int n, int sortBase, int Order);
int Search(int *Sourcelist, int n, int *Resultlist, int SearchUnit, const char *destin);
void GetList(int *list, int *n);
void display(int *list, int n, int mode);
void DestroyStudentList();
char* GetString(int *list, int list_ID, int GetUnit);
char* GetUnitTittle(int Unit);