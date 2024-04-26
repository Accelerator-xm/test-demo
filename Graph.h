#pragma once

//��󶥵���
#define MAX_VERTEX_NUM 20

//����ṹ��
struct Vex {
	int num;      //������
	char name[20];  //��������
	char desc[1024]; //�������
};

//�߽ṹ��
struct Edge {
	int vex1;   //����1
	int vex2;   //����2
	int weight;  //Ȩֵ
};

//·������(ÿ���ڵ����һ��·��)
typedef struct PathNode {
	int *path;   //·�߾���������
	struct PathNode* next;
}PathNode, *PathList;

//ͼ
class CGgraph {
private:
	int m_aAdjMatrix[20][20]; //�ڽӾ���
	Vex m_aVexs[20];   //������Ϣ����
	int m_nVexNum;    //��ǰͼ�Ķ������
public:
	//���캯��
	CGgraph();
	//���붥����Ϣ
	bool InsertVex(Vex sVex);
	//�������Ϣ
	bool InsertEdge(Edge sEdge);
	//��ȡ�������
	int GetVexNum();
	//������о����ź�����
	void ShowVex();
	//��ȡ��Ӧ����
	Vex GetVex(int v);
	//��ѯ���ھ���,���رߵ�����
	int FindEdge(int v, Edge aEdge[]);
	//��ñ������(����·��)
	void DFSTravese(int nVex,PathList &List);
	//�������������·��
	int FindShortPath(int VexStart, int VexEnd, Edge aPath[]);
	//������С������
	int FindMinTree(Edge aPath[]);
	//���·��(����������У���ʽ�������Ӧ��·����Ϣ)
	void ShowTravel(int path[],int len);
private:
	//�����������
	void DFS(int nVex,int index,bool visit[],int path[], PathList& List);

};
