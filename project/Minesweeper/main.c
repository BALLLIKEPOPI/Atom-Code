#include <stdio.h>
#include <stdlib.h>
#include "game.h"

int main()
{
    int dif,flag;//��ʼ�����Ѷ�
    char mine[60][60];
    char disp[60][60];

    welcome(&dif);//�������dif����main����
    if(dif==3)//������Ϊ3���˳���Ϸ
    {
        return 0;
    }
    else
    {
        dif_elect(&dif);//����dif�Ƿ����Ҫ��
    }
    game_Init(&dif,SET,disp);//��ʼ����Ϸ����
    DISP(&dif,disp);//�����Ϸ����
    Start=clock();//����ʱ�俪ʼ
    game_Init(&dif,'0',mine);//��ʼ����������
    MineSet(&dif,mine);//���õ���
    Input_Check(&dif);//���벢����
    if(dif==0)//��dif����0���˳���Ϸ
    {
        return 0;
    }
    while(1)//�ظ��������겢���
    {
        flag=Find_Mine(&dif,mine,disp);//����Ƿ��ڵ��ײ�����ֵ������1����ֹ��
        if(flag==1)
        {
            return 0;
        }
        Input_Check(&dif);
        if(dif==0)
        {
            return 0;
        }
    }
    return 0;
}
