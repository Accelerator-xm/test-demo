#pragma once
#include"CGameLogic.h"
#include"CGraph.h"

class CCameControl
{
public:
	static int s_nRows;   //��Ϸ����
	static int s_nCols;   //��Ϸ����
	static int s_nPicNum;  //ͼƬ��

	CGraph m_graph;   //��Ϸ��ͼ
	int** m_pGameMap;    //��Ϸ��ͼ����ָ��

	CGameLogic m_GameLogic;  //��Ϸ�߼���������
	Vertex m_SelectVer1;   //ѡ�еĵ�һ����
	Vertex m_SelectVer2;   //ѡ�еĵڶ�����


	void StarGame();  //��ʼ��Ϸ
	int GetElement(int nRow, int nCol);  //���ĳ��Ԫ��
	void SetFirstPoint(int nRow, int nCol); //���õ�һ����
	void SetSecondPoint(int nRow, int nCol); //���õڶ�����
	bool Link(Vertex avPath[], int& nVernum);  //�ж���ͨ
	int IsWin(int nTime);   //�ж��Ƿ�ʤ��
	void Reset();   //����
	bool Help(Vertex avPath[], int& nVernum);    //��ʾ����

};

