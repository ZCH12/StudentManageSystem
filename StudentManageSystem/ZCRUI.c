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
			"                     ���˵�\n"\
			DELIMS_LINE\
		);
		Menu_DisplaySubMenu();

		printf(
			DELIMS_LINE\
			" [1].��ȡ�ļ�\n"\
			" [2].��ѧ����������\n"\
			" [3].����ָ��ѧ��\n"\
			" [4].�޸�ѧ����Ϣ\n"\
			" [5].��ʾѧ����Ϣ\n"\
			" [6].������txt\n"\
			" [7].�߼�����\n"\
			" [0].�˳�ϵͳ\n"\
			DELIMS_LINE
		);
		switch (Event_Input())
		{
		case 1:
			//��ȡ�ļ�
			break;
		case 2:
			//����
			break;
		case 3:
			//����
			break;
		case 4:
			//�޸�
			break;
		case 5:
			//��ʾѧ����Ϣ
			break;
		case 6:
			//������txt
			break;
		case 7:
			//�߼�����
			break;
		case 0:
			exit(0);
		}
	}
	return 0;
}