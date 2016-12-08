#include "DataBase.h"
#include "stdio.h"
#include "hzh.h"



//******学生成绩系统菜单*******
//1. 原始文件读取
//2. 按姓名排序，输出
//3. 按平均成绩排序，输出
//4. 输出给定学院学生
//5. 修改给定学生成绩信息(修改后的信息，需输出到文件)
//6. 按姓名查询学生，输出
//7. 修改系统密码*
//0. 返回上一级菜单
//*****************************

//int main() {
//    
//    
//    
//    int mode = 0;
//    
//    printf("1. 原始文件读取\n"
//           "2. 按姓名排序，输出\n"
//           "3. 按平均成绩排序，输出\n"
//           "4. 输出给定学院学生\n"
//           "5. 修改给定学生成绩信息(修改后的信息，需输出到文件)\n"
//           "6. 按姓名查询学生，输出\n"
//           "7. 修改系统密码\n"
//           "0. 返回上一级菜单\n");
//    scanf("%d", &mode);
//    switch (mode) {
//        case 1:
//            ReadFromFile_M();
//            break;
//            
//        case 2:
//            SortList_M();
//            break;
//            
//        
//    }
//    return SUCCESS;
//}

//
//int main() {
//    
//    Start_M();
//    
//    int mode = 0;
//    printf(" 0.显示所有学生信息\n"
//           " 1.排序\n"
//           " 2.查找学生\n"
//           " 3.新增数据列\n"
//           " 4.删除数据列\n"
//           " 5.新增学生\n"
//           " 6.修改学生信息\n"
//           " 7.删除指定学生\n"
//           " 8.读取学生信息\n"
//           " 9.保存学生信息\n"
//           "-1.退出"
//           );
//    while(scanf("%d",&mode),mode==-1){                                          //当输入mode
//        switch (mode) {
//            case 0://"0.显示所有学生信息"//缺循环，单独选择显示一个或多个学生信息表，退出
//                
//                Display_Chart_M();
//                break;
//                
//            case 1://"1.排序"
//                SortList_M();//允许排任何一列数据列，支持升降序使用                                   //完成
//                break;
//                
//            case 2://"2.查找学生"
//                SearchStudentByUnit_M();//缺循环，第二条件，第三条件，无限条件，退出
//                break;
//                
//            case 3://"3.新增数据列\n"//缺循环，同时新增多个数据列，退出
//                AddNewInformationUnit_M();
//                break;
//                
//            case 4://"4.删除数据列\n"//缺循环，同时删除多个数据列，退出
//                DeleteInformationUnit_M();
//                break;
//                
//            case 5://"5.新增学生\n"//缺循环，同时新增多个学生，退出
//                AddNewStudent_M();
//                break;
//                
//            case 6://"6.修改学生信息\n"//缺循环，同时修改多个学生的信息，同时修改学生的多个信息，退出
//                ChangeStudentInformation_M();
//                break;
//                
//            case 7://"7.删除指定学生\n"//缺循环，同时修删除多个指定学生的同一个信息，同时删除同一个学生的多个指定信息，退出
//                DeleteAStudentFromList_M();
//                break;
//                
//            case 8://"8.读取学生信息\n"//缺循环，同时读取多个文件，退出
//                ReadFromFile_M();
//                break;
//                
//            case 9://"9.保存学生信息\n"//缺循环,同时保持多个学生信息表，退出
//                WriteToFile_M();
//                break;
//                
//        }
//    }
//    return 0;
//}
//

