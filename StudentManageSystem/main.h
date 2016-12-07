//
//  main.h
//  StudentManageSystem
//
//  Created by wongziihou on 7/12/16.
//  Copyright © 2016 Wongziihou. All rights reserved.
//


#ifndef main_h
#define main_h
int temp,temp2;
char *temp3;

int n;
int i;
Chart **charthead;





void Display_Chart_M();
void SortList_M();
void SearchStudentByUnit_M();
void AddNewInformationUnit_M();
void DeleteInformationUnit_M();
void AddNewStudent_M();
void ChangeStudentInformation_M();
void DeleteAStudentFromList_M();
void ReadFromFile_M();
void WriteToFile_M();
void CreatNewChart_M();


void CreatNewChart();


void Display_Chart_M() {
    
    Display_Chart_M(&form, NULL, NULL, 0);
}
void SortList_M() {
    
    int order;
    int sortbase;
A:                                                                      //标记A
    while(printf(   "0.升序排序\n"
                 "1.降序排序\n"
                 "-1.退出\n\n"),
          scanf("%d", &order), order!=-1) {                      //当输入为-1时,直接跳出
        OUTSCANFAGAIN(order, -1, 1);                            //判断order是否越界,若越界则重新输入
        while (1) {                                             //order必为0或1
            for (i = 0; i < form1.TitleCount; i++) {                   //显示选项
                printf("%d.%s\n", i, form1.ChartTitle[i]);
            }
            scanf("%d", &sortbase);
            switch (order) {
                    
                case 1:                                         //order -> 0 对应 case 1.升序排序
                    OUTSCANFAGAIN(sortbase, 0, form1.TitleCount);      //判断sortbase是否越界,若越界则重新输入
                    Sort(list, n, sortbase, 0);
                    goto A;
                    
                case 2:                                         //order -> 1 对应 case 2.降序排序
                    OUTSCANFAGAIN(sortbase, 0, form1.TitleCount);
                    Sort(list, n, sortbase, 1);
                    goto A;
            }
        }
    }
    return;
}
void SearchStudentByUnit_M() {
    
    int order;
    int unitindex;
    char destin;
    
    
    while(printf("0.搜索\n"
                 "1."
                 "-1.退出\n\n"),
          scanf("%d", &order), order!=-1) {
        OUTSCANFAGAIN(order, -1, 0);
        
        while (1) {
            for (i = 0; i < form1.TitleCount; i++) {                    //打印列表
                printf("%d.%s\n", i, form1.ChartTitle[i]);
            }
            
            scanf("%d", &unitindex);
            printf("输入所需寻找的信息(如:张三,64)\n");
            scanf("%s", &destin);
            temp=Search(list, n, list2, unitindex, &destin);
            display(list2, n, 0);
        }
    }
    //缺循环，第二条件，第三条件，无限条件，退出
    return;
}
void AddNewInformationUnit_M() {
    
    char title[16], defaul;
    int unitlimits;
    
    
    printf("请输入:所添加的单元 单元字节范围 初始值\n");
    scanf("%s %d %c", title, &unitlimits, &defaul);
    CreateNewUnit(<#Chart *OperateChart#>, , <#char (*NewTitleSet)[32]#>, <#int *NewTitleLimits#>)
    NewUnit(title, unitlimits, defaul);
    display(list, n, 0);
    
    return;
}
void DeleteInformationUnit_M() {
    char title[16];
    for (i = 0; i<; <#increment#>) {
        <#statements#>
    }
    printf("%");
    scanf("%s", title);
    
    DeleteUnit(SearchHeadIndex(title));
    display(list, n, 0);
    
    return;
}
void AddNewStudent_M() {
    //     printf("\n新增一个学生\n");
    //     NewStudent(list, &n);
    //     display(list, n);
    
    NewStudent(list, &n);
    printf("\n已新增一个学生\n");
    display(list, n, 0);
    
    return;
    
}
void ChangeStudentInformation_M() {
    
    char getunit[16];
    int list_id;
    char information[16];
    
    display(list, n, 1);
    
    printf("请输入所需更改的单元\n");
    scanf("%s", getunit);
    printf("请输入所需更改的序号\n");
    scanf("%d", &list_id);
    printf("请输入更改的内容\n");
    scanf("%s", information);
    
    temp3 = GetString(list, list_id, SearchHeadIndex(getunit));
    strcpy(temp3, information);
    display(list, n, 1);
    
    return;
    
}
void DeleteAStudentFromList_M() {
    
    int studentnumber, mode;
    
    printf("请输入所需删除学生所有信息的序号\n");
    scanf("%d", &studentnumber);
    printf("请选择:\n"
           "0.未排序\n"
           "1.已排序\n"
           );
    switch (mode) {
        case 0:
            DeleteStudentInList(list, &n, studentnumber, 0);
            
            display(list, n, 1);
            break;
            
        case 1:
            DeleteStudentInList(list, &n, studentnumber, 0);
            display(list, n, 1);
            break;
    }
    
    return;
}
void ReadFromFile_M() {
    
    char filename;
    printf("请输入所需读取的文件名字,如(data.ini)");
    scanf("%s", &filename);
    
    ReadFromFile(&filename, OperateChart);       //读取data.ini
    GetList(list, &n);    		//取得一个名单
    
    return;
}
void WriteToFile_M() {
    
    char filename;
    
    printf("请输入所需读取的文件名字,如(data.ini)");
    scanf("%s", &filename);
    
    WriteIni(&filename, list, n);
    
    return;
    
}




Chart **charthead;

ErrVal CreatNewChart() {
    
    Chart *creat;
    static int had_creat_chart_num = 0;             //静态变量 已创建的表格数量
    int creatchartnum;                              //所需创建的表格数量
    printf("请输入所需创建表的数量\n");
    scanf("%d", &creatchartnum);
    
    
    charthead = (Chart **)malloc(sizeof(Chart *));
    if (charthead == NULL) {
        return ERR_MEMORYNOTENOUGH;
    }
    for (had_creat_chart_num = 0; had_creat_chart_num < creatchartnum; had_creat_chart_num++) {
        creat = (Chart *)malloc(sizeof(Chart));
        if (creat == NULL) {
            return ERR_MEMORYNOTENOUGH;
        }
        charthead[had_creat_chart_num] = creat;
    }
    
    printf("表已创建完成\n");
    return SUCCESS;
}





#endif /* main_h */
