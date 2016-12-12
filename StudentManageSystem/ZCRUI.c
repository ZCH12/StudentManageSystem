#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "ZCRUI.h"

void MainMenu()
{
	while (1)
	{
		COMMAND_CLEAR();
		printf(
			DELIMS_LINE\
			"                     主菜单\n"\
			DELIMS_LINE\
		);
		Menu_DisplaySubMenu();

		printf(
			DELIMS_LINE\
			" [1].读取文件\n"\
			" [2].对学生进行排序\n"\
			" [3].查找指定学生\n"\
			" [4].修改学生信息\n"\
			" [5].显示学生信息\n"\
			" [6].导出到txt\n"\
			" [7].高级设置\n"\
			" [0].退出系统\n"\
			DELIMS_LINE
		);
		switch (Event_Input())
		{
		case 1:
			//读取文件
			break;
		case 2:
			//排序
			break;
		case 3:
			//查找
			break;
		case 4:
			//修改
			break;
		case 5:
			//显示学生信息
			break;
		case 6:
			//导出到txt
			break;
		case 7:
			//高级设置
			break;
		case 0:
			exit(0);
		}
	}
	return 0;
}