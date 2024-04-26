#pragma once

#define MAX_VERTEX_NUM 160  //��󶥵���
#define MAX_ROW 10   //����
#define MAX_COL 16  //����
#define MAX_PIC_NUM 10  //��ɫ��
#define GAME_MAP_TOP 50   //��Ϸ��ͼ���Ͻ�������
#define GAME_MAP_LEFT 20  //��Ϸ��ͼ���ϽǺ����� 
#define PIC_WIDTH 40  //Ԫ�ؿ�
#define PIC_HEIGHT 40  //Ԫ�ظ�

#define BLANK -1     //Ԫ��Ϊ��

#define PLAY_TIMER_ID 1  //��ʱ�����

#define GAME_LOSE -1    //ʧ��
#define GAME_SUCCESS 0  //�ɹ�
#define GAME_PLAY 1    //��Ϸ���ڽ���



//����洢�ṹ
typedef struct{
	int row;   //��
	int col;   //��
	int info;  //ֵ��Ϣ
}Vertex;

//��Ϸģʽ�ṹ��
typedef struct {
	int min;         //��Сֵ
	int max;         //���ֵ
	int step;        //����
	int cost;        //�������ܵĴ���
}Mode;