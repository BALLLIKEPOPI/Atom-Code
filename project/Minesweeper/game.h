#ifndef __GAME_H
#define __GAME_H

#include <time.h>

#define EASY 10//�����Ѷ�
#define MEDIUM 30//�е��Ѷ�
#define DIFFICUL 50//�����Ѷ�
#define SET '+'//δ������ͼ��
#define MINE '*'//����ͼ��
#define MINE_NUM 3*(*dif)//ĳ���Ѷ�������
#define TIME (double)(End-Start)/CLOCKS_PER_SEC//��Ϸʱ��

struct x_y_In{
    int x;
    int y;
}x_y_In;//��������ṹ��
clock_t Start,End;

void welcome(int *dif);
void dif_elect(int *dif);
void game_Init(int *dif,char set,char disp[60][60]);
void DISP(int *dif,char disp[60][60]);
void MineSet(int *dif,char mine[60][60]);
int Input_Check(int *dif);
int Find_Mine(int *dif,char mine[60][60],char disp[60][60]);


#endif // __GAME_H
