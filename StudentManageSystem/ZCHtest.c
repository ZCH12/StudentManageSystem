#include <stdio.h>
#include <string.h>
#include "DataBase.h"

#define CRTDBG_MAP_ALLOC    
#include <stdlib.h>  
#include <crtdbg.h>    

//���Դ�����
void Demo()
{
	Chart c;
	int a;
	IndexList stulist;
	IndexList stulist2;
	IndexList stulist3;
	TitleList titlelist;

	//��ʼ��һ��3*5�ı�
	InitNewChart(&c, 5, 3, "����", 5, "�༶", 5, "����", 5);

	//д������
	strcpy(c.Chart[0][0], "����");
	strcpy(c.Chart[1][0], "����");
	strcpy(c.Chart[2][0], "����");
	strcpy(c.Chart[3][0], "���");
	strcpy(c.Chart[4][0], "����");
	strcpy(c.Chart[0][1], "303");
	strcpy(c.Chart[1][1], "302");
	strcpy(c.Chart[2][1], "303");
	strcpy(c.Chart[3][1], "301");
	strcpy(c.Chart[4][1], "301");
	strcpy(c.Chart[0][2], "1");
	strcpy(c.Chart[1][2], "2");
	strcpy(c.Chart[2][2], "3");
	strcpy(c.Chart[3][2], "4");
	strcpy(c.Chart[4][2], "5");

	//��ʼ��һ��ѧ���б�
	FillList(&stulist, 5);

	Display_Chart(&c,NULL,NULL,DISPLAY_HIDENUMBER);
	/*********************************************************/
	//�������
	//��������������
	printf("��������������\n");
	Sort(&c, &stulist, SHI(&c, "����"), SORT_ASCENDING);
	Display_Chart(&c, &stulist, NULL, DISPLAY_HIDENUMBER);			//��ʾ����
	printf("\n");

	//�����Ž�������
	printf("�����Ž�������\n");
	Sort(&c, &stulist, SHI(&c, "����"), SORT_DESCENDING);
	Display_Chart(&c, &stulist, NULL, DISPLAY_HIDENUMBER);			//��ʾ����
	/*********************************************************/
	//ɸѡ����
	FillList(&stulist2, 10);			//Listʹ��֮ǰҪ�Ƚ��г�ʼ��
	FillList(&stulist3, 10);			//Listʹ��֮ǰҪ�Ƚ��г�ʼ��

	Search(&c, &stulist, &stulist2, SHI(&c, "����"), "����");

	if (stulist2.listCount > 0) {
		printf("\n�ҵ�����Ϊ������ѧ������:\n");
		Display_Chart(&c, &stulist2, NULL, DISPLAY_HIDENUMBER);
	}
	else printf("\nû���ҵ��й�ѧ������Ϣ\n");

	Search(&c, &stulist2, &stulist3, SHI(&c, "�༶"), "303");		//��֮ǰ��������Ļ������������༶Ϊ303��ѧ��
	if (stulist3.listCount > 0)
	{
		printf("\n�ҵ�����Ϊ������ѧ������:\n");
		Display_Chart(&c, &stulist3, NULL, DISPLAY_HIDENUMBER);
	}
	else printf("\nû���ҵ��й�ѧ������Ϣ\n");
	/**********************************************************/
	//�����ʱ������������ŷ��ں��治����,û��ϵ,���Խ��е���

	printf("\n���µ�����֮������\n");
	InitList(&titlelist, 3, SHI(&c, "����"), SHI(&c, "�༶"), SHI(&c, "����"));
	Display_Chart(&c, &stulist, &titlelist, DISPLAY_HIDENUMBER);

	printf("\n�ٰ�������������һ��\n");
	Sort(&c, &stulist, SHI(&c, "����"), SORT_ASCENDING);
	Display_Chart(&c, &stulist, &titlelist, DISPLAY_HIDENUMBER);

	//������Ϻ��ͷ��ڴ�,��ָֹ�붪ʧ����ڴ�й¶
	FreeList(&stulist);
	FreeList(&stulist2);
	FreeList(&stulist3);
	FreeList(&titlelist);
	FreeChart(&c);
}

int main()
{
	//Demo();
	//int *a=(int*)malloc(sizeof(int)*10);
	//*a=0;
	int a[10]={1,2,3};
	printf("%d",*a);

	_CrtDumpMemoryLeaks();
	system("pause");

}



