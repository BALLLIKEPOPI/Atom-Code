#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "game.h"

//��ʼ����ӭ���棬����dif��ֵ
void welcome(int *dif)
{
    char temp;

    printf("Welcome to minesweeper! Please elect your difficulty. \n\n");
    printf("Input the numbers below to choose your difficulty\n");
    printf("> 0--EASY\n> 1--MEDIUM\n> 2--DIFFICUL\n> 3--QUIT\n\n> ");
    scanf("%c",&temp);//�����Ѷ�
    getchar();//�����س�Ӱ��
    *dif=temp-48;
    printf("\n");
}

//ѡ���Ѷ�
void dif_elect(int *dif)
{
    char temp;

    while((*dif!=0)&&(*dif!=1)&&(*dif!=2))//�����벻�Ϸ�����������
    {
        printf("\a\nWRONG INOUT! Please try again. \n\n");
        putchar('>');
        scanf("%c",&temp);//��������
        getchar();//�����س�Ӱ��
        *dif=temp-48;
        printf("\n");
    }
    if(*dif==0)//����0�򷵻ؼ��Ѷ�
    {
        *dif=EASY;
    }
    if(*dif==1)//����1�򷵻��е��Ѷ�
    {
        *dif=MEDIUM;
    }
    if(*dif==2)//����2�򷵻������Ѷ�
    {
        *dif=DIFFICUL;
    }
}

//��Ϸ��ʼ��
void game_Init(int *dif,char set,char disp[60][60])
{
    int i,j;

    for(i=0;i<60;i++)
    {
        for(j=0;j<60;j++)
        {
            disp[i][j]=set;//��������
        }
    }
}

//�����Ϸ����
void DISP(int *dif,char disp[60][60])
{
    int i,j;

    system("cls");//����

    for(i=0;i<(3*(*dif)-8)/2+1;i++)//��ӡ��Ϸ��ʼ���
    {
        printf("=");
    }
    printf("GAME  ON");
    for(i=0;i<(3*(*dif)-8)/2+1;i++)
    {
        printf("=");
    }
    printf("\n\n  ");
    for(i=0;i<(*dif);i++)//��ӡ����
    {
        printf(" %2d",i+1);
    }
    printf("\n");

    for(i=1;i<=(*dif);i++)//��ӡ��ʼ���
    {
        printf("%2d",i);//��ӡ����
        for(j=1;j<=(*dif);j++)
        {
            printf("  %c",disp[i][j]);
        }
            printf("\n");
    }
    printf("\n");
    for(i=0;i<3*(*dif)+2;i++)//��ӡ�ָ���
    {
        printf("=");
    }
    printf("\n\n");
}

//���õ��׵�λ��
void MineSet(int *dif,char mine[60][60])
{
    int count=MINE_NUM,x,y;

    srand((unsigned)(time(NULL)));
    while(count)//��������ȡ�����
    {
        x=rand()%(*dif)+1;//��1~*dif���ȡ��
        y=rand()%(*dif)+1;
        if(mine[x][y]=='0')//�������겻Ϊ����������Ϊ����
        {
            mine[x][y]='1';
            count --;
        }
    }
}

//���벢����
int Input_Check(int *dif)
{
    int flag=1;//flagΪ�����־��1Ϊ����0Ϊ��ȷ��

    End=clock();//����ʱ���ֹ
    printf("Time: %.2f s\n",TIME);
    printf("Please input the coordinate(input [0 0] to quit): ");
    scanf("%d %d",&x_y_In.x,&x_y_In.y);//��������
    while(flag)//�����ж�
    {
        if(x_y_In.x==0&&x_y_In.y==0)//������0,0���˳�����
        {
            *dif=0;
            return 0;
        }
        if(x_y_In.x<1||x_y_In.y>*dif||x_y_In.y<1||x_y_In.y>*dif)//������Χ����������
        {
            printf("Wrong input! Please try again(input [0 0] to quit): ");
            scanf("%d %d",&x_y_In.x,&x_y_In.y);
            printf("\n");
        }
        else//������ȷ�ñ�־Ϊ0
        {
            flag=0;
        }
    }
    return 0;
}

//����Ƿ��ڵ���
int Find_Mine(int *dif,char mine[60][60],char disp[60][60])
{
    int i,j,count;//countΪ��������Χ������
    static int flag=0;//flagΪ��������

    while(disp[x_y_In.x][x_y_In.y]!=SET)//���������ѱ��ھ�Ҫ����������
    {
        printf("Seems that you've already unearthed this area. Try again.\n");
        Input_Check(&(*dif));//��������
        if(dif==0)
        {
            return 0;
        }
    }
    if(mine[x_y_In.x][x_y_In.y]=='1')//����������Ϊ������������
    {
        for(i=0;i<*dif;i++)//��ʾ���е���
        {
            for(j=0;j<*dif;j++)
            {
                if(mine[i][j]=='1')
                {
                    disp[i][j]=MINE;
                }
            }
        }
        DISP(&(*dif),disp);
        End=clock();//����ʱ���ֹ
        printf("Oops! You lose! \nTotal time: %.2f s\n",TIME);
        return 1;
    }
    else
    {
        count=mine[x_y_In.x-1][x_y_In.y]+mine[x_y_In.x-1][x_y_In.y-1]+mine[x_y_In.x][x_y_In.y-1]+\
        mine[x_y_In.x+1][x_y_In.y-1]+mine[x_y_In.x+1][x_y_In.y]+mine[x_y_In.x][x_y_In.y+1]\
        +mine[x_y_In.x+1][x_y_In.y+1]+mine[x_y_In.x-1][x_y_In.y+1]-8*'0';//�����������Χ������

        disp[x_y_In.x][x_y_In.y]=count+48;//���������������
        DISP(&(*dif),disp);
        flag ++;
    }
    if(flag==*dif* *dif-MINE_NUM)//�����׾�����
    {
        End=clock();//����ʱ���ֹ
        printf("Congratulation! You win!\nTotal time: %.2f s",TIME);
        return 1;
    }
    return 0;
}
