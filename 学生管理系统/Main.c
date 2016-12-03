#include "DataBase.h"

int list[1500];				//名单,里面保存的是学生的下标
int list2[1500];
int list3[1500];
int n;
int temp,temp2;
char *temp3;

void SortList();
void SearchStudentByUnit();
void AddNewInformationUnit();
void DeleteInformationUnit();
void AddNewStudent();
void ChangeStudentInformation();
void DeleteAStudentFromList();
void ReadFromFile();
void WriteToFile();






//     printf("\n新增一个项成绩3\n");
//     NewUnit("成绩3", 3, '0');
//     display(list, n);
//     printf("\n新增一个学生\n");
//     NewStudent(list, &n);
//     display(list, n);
//
//     printf("从名单中删除第一个同学的信息\n");
//     DeleteStudentInList(list, &n, list[0], 1);
//     display(list, n);
//     printf("\n将第n个人的姓名改为黄智豪\n");
//     temp3 = GetString(list, n - 1, SearchHeadIndex("姓名"));
//     strcpy(temp3, "黄智豪");
//     display(list, n);
//
//     printf("\n取得第n个人的姓名\n");
//     printf("%s\n", GetString(list, n-1, SearchHeadIndex("姓名")));
//     printf("将数据保存到new.ini\n");
//     WriteIni("new.ini", list, n);
//     */
//    printf("\n删除成绩1列\n");
//    DeleteUnit(SearchHeadIndex("成绩1"));
//    display(list, n);
//
//    //释放内存之后,不能再对表进行操作
//    DestroyStudentList();
//    system("pause");

int main() {
    
    ReadIni("data.ini");		//读取data.ini
    GetList(list, &n);			//取得一个名单
    
    printf(
           "0.显示所有学生信息\n"
           "1.排序\n"
           "2.查找学生\n"
           "3.新增数据列\n"
           "4.删除数据列\n"
           "5.新增学生\n"
           "6.修改学生信息\n"
           "7.删除指定学生\n"
           "8.读取学生信息\n"
           "9.保存学生信息\n"
           );
    int mode = -1;
    scanf("%d",&mode);
    switch (mode) {
        case 0://"0.显示所有学生信息"
            display(list, n);//完成
            break;
            
        case 1://"1.排序"
            SortList();//完成，缺循环及退出
            break;
            
        case 2://"2.查找学生"
            SearchStudentByUnit();//完成，缺循环，第二条件，第三条件。无限条件，退出。
            break;
            
        case 3://"3.新增数据列\n"
            AddNewInformationUnit();
            break;
            
        case 4://"4.删除数据列\n"
            DeleteInformationUnit();
            break;
            
        case 5://"5.新增学生\n"
            AddNewStudent();
            break;
            
        case 6://"6.修改学生信息\n"
            ChangeStudentInformation();
            break;
            
        case 7://"7.删除指定学生\n"
            DeleteAStudentFromList();
            break;
            
        case 8://"8.读取学生信息\n"
            ReadFromFile();
            break;
            
        case 9://"9.保存学生信息\n"
            WriteToFile();
            break;
            
    }
    return 0;
}

void SortList(){
    
    int order;
    char sortbase[16];
    
    printf("请输入所需排序的单元(如:名字,成绩1)\n");
    scanf("%s", sortbase);
    printf("请选择排序方式\n0.升序\n1.降序\n");
    scanf("%d", &order);
    switch (order) {
        case 0:
            Sort(list, n, SearchHeadIndex(sortbase), 0);
            display(list, n);
            break;
        case 1:
            Sort(list, n, SearchHeadIndex(sortbase), 1);
            display(list, n);
            break;
    }
    return;
}

void SearchStudentByUnit() {
    
    char searchunit[16];
    char destin;
    
    printf("请输入所需寻找的单元(如:姓名,成绩1)\n");
    scanf("%s",searchunit);
    printf("输入所需寻找的信息(如:张三,64)\n");
    scanf("%s",&destin);
    temp=Search(list, n, list2, SearchHeadIndex(searchunit), &destin);
    display(list2, n);
    
    
}
void AddNewInformationUnit() {
    printf("请输入:添加的单元名字 单元字节范围 初始值\n");
    NewUnit("成绩3", 3, '0');
    NewUnit(<#char *title#>, <#int UnitLimits#>, <#char Default#>)
    
}
void DeleteInformationUnit() {
    
}
void AddNewStudent() {
    
}
void ChangeStudentInformation() {
    
}
void DeleteAStudentFromList() {
    
}
void ReadFromFile() {
    
}
void WriteToFile() {
    
}



//    //测试代码,自行去掉注释进行测试
//
//    printf("按照姓名升序排序\n");
//    Sort(list, n, SearchHeadIndex("姓名"), 0);
//    display(list, n);
//
//    /*
//     printf("\n按照姓名降序排序\n");
//     Sort(list, n, SearchHeadIndex("姓名"), 1);
//     display(list, n);
//     printf("\n按照学号升序排序\n");
//     Sort(list, n, SearchHeadIndex("学号"), 0);
//     display(list, n);
//     printf("\n按照学号降序排序\n");
//     Sort(list, n, SearchHeadIndex("学号"), 1);
//     display(list, n);
//     printf("\n按照成绩1升序排序\n");
//     Sort(list, n, SearchHeadIndex("成绩1"), 0);
//     display(list, n);
//     printf("\n按照成绩1降序排序\n");
//     Sort(list, n, SearchHeadIndex("成绩1"), 1);
//     display(list, n);

//     printf("\n找到成绩1为65分的\n");
//     temp=Search(list, n, list2, SearchHeadIndex("成绩1"), "65");
//     display(list2, temp);
//     printf("\n找到成绩1为65分,并且成绩2为56分的\n");
//     temp2 = Search(list2, temp, list3, SearchHeadIndex("成绩2"), "56");
//     display(list3, temp2);
//


//
//
//  main.h
//  C
//
//  Created by wongziihou on 2/12/16.
//  Copyright © 2016 wongziihou. All rights reserved.
//


