#pragma once
#include"global.h"

//ͼ���ݽṹ
class CGraph
{
protected:
	int m_Verteices[MAX_VERTEX_NUM];   //ͼ�����ж���
	int m_nVerNum;   //������
	bool m_AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM]; //����Ϣ(true=�б�)
	//int m_nArcNum;   //������

public:
	CGraph();
	~CGraph();
	int AddVertex(int nInfo);   //��Ӷ��㣬������Ŀ
	void ChangeVertex(int index1, int index2);  //��������λ��
	int GetVertex(int index);   //��ö�����Ϣ

	void UpdateArc(int nRow, int nCol);  //���µ�(nRow,nCol)���ܵı���Ϣ
	bool GetArc(int index1, int index2);  //��ñ���Ϣ
	int GetVexnum();     //��ȡ���������еĶ�����
	void ClearGraph();   //��ͼ�ж���ͱ߻�ԭΪ��ʼ״̬
	void AddArc(int index1, int index2);  //��ӱ�
	void UpdateVertex(int index, int Info);   //��ͼ����������������ΪnIndex�Ķ����ֵ����Ϊinfo 

protected:  
	void InitGraph();   //��ʼ��
	void UpdateVerToVer(int index1, int index2);  //��������֮��ı���Ϣ

};

