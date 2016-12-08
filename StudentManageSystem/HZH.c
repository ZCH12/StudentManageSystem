#include "HZH.h"
int ChartCount;
Chart ** ChartHead;

//����ƺ���
ErrVal NewChart(int CreateCount)
{
	int a;
	Chart** OldChartSet;			//ԭ���ı�
	int NewChartCount=ChartCount+CreateCount;
	if (CreateCount<=0)
		return ERR_ILLEGALPARAM;

	if (ChartCount==0)
	{
		//���ֱ�û��ʼ����,���г�ʼ��
		ChartHead=(Chart**)malloc(sizeof(Chart*)*CreateCount);
		//�жϴ���
		for (a=0;a<CreateCount;a++)
		{
			ChartHead[a]=(Chart*)calloc(sizeof(Chart),sizeof(Chart));
			//�жϴ���
		}
	} else {
		OldChartSet=ChartHead;
		ChartHead=(Chart**)malloc(sizeof(Chart*)*NewChartCount);
		for (a=0;a<ChartCount;a++)
			ChartHead[a]=OldChartSet[a];
		for (a=ChartCount;a<NewChartCount;a++)
		{
			ChartHead[a]=(Chart*)calloc(sizeof(Chart),sizeof(Chart));
			//�жϴ���
		}
	}
    return SUCCESS;
}


