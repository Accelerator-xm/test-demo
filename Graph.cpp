#include<iostream>
#include"Graph.h"

using namespace std;

//���캯��, ��ʼ��
CGgraph::CGgraph()
{
	//Ȩֵ��Ϣ
	for (int i = 0; i < MAX_VERTEX_NUM; i++) {
		for (int j = 0; j < MAX_VERTEX_NUM; j++) {
			m_aAdjMatrix[i][j] = 0;
		}
	}
	//������
	m_nVexNum = 0;
}


//��Ӷ���
bool CGgraph::InsertVex(Vex sVex)
{
	//��������
	if (m_nVexNum == MAX_VERTEX_NUM) {
		return false;
	}
	
	m_aVexs[m_nVexNum++] = sVex;  //���붥����Ϣ
	return true;
}


//��ӱ�
bool CGgraph::InsertEdge(Edge sEdge)
{
	//�±�Խ��
	if (sEdge.vex1 < 0 || sEdge.vex1 >= m_nVexNum || sEdge.vex2 < 0 || sEdge.vex2 >= m_nVexNum) {
		return false;
	}

	//�������Ϣ
	m_aAdjMatrix[sEdge.vex1][sEdge.vex2] = sEdge.weight;
	m_aAdjMatrix[sEdge.vex2][sEdge.vex1] = sEdge.weight;

	return true;
}


//������о����ź����� ��ʽ�������-���֡�
void CGgraph::ShowVex()
{
	for (int i = 0; i < m_nVexNum; i++) {
		//����
		cout << m_aVexs[i].num << "-" << m_aVexs[i].name << endl;
	}
}



//��ȡ������
int CGgraph::GetVexNum()
{
	return m_nVexNum;
}


//��ȡ��Ӧ����
Vex CGgraph::GetVex(int v)
{	
	return m_aVexs[v];
}


//��ѯ���ھ���
int CGgraph::FindEdge(int v, Edge aEdge[])
{
	int k = 0;
	for (int i = 0; i < m_nVexNum; i++) {
		//����
		if (m_aAdjMatrix[v][i]) {
			aEdge[k].vex1 = v;
			aEdge[k].vex2 = i;
			aEdge[k].weight = m_aAdjMatrix[v][i];
			k++;
		}
	}

	return k;
}


//��ñ������(����·��)
void CGgraph::DFSTravese(int nVex, PathList& List)
{
	//�������
	bool *visit = new bool[m_nVexNum];
	for (int i = 0; i < m_nVexNum; i++) {
		visit[i] = false;  //��ʼ��
	}
	//·������
	int* path = new int[m_nVexNum];

	//�ݹ��ȡ����·������
	DFS(nVex,0, visit, path, List);
}


//�������������·��
int CGgraph::FindShortPath(int VexStart, int VexEnd, Edge aPath[])
{
	int *dist = new int[m_nVexNum]; //VexStart��ÿһ��ľ���
	bool* visit = new bool[m_nVexNum];  //�������
	int* last = new int[m_nVexNum]; //ÿ���ڵ��ֱ��ǰ��
	int vex = VexStart;  //�����ʵ�

	//��ʼ��
	for (int i = 0; i < m_nVexNum; i++) {
		dist[i] = INT32_MAX;  //��������Զ
		visit[i] = false;
		last[i] = -1;  //û��ǰ��
	}

	dist[vex] = 0;  
	visit[vex] = true;

	//Dijkstra�㷨
	for (int i = 0; i < m_nVexNum - 1; i++) {

		//���������ڽӱ�
		for (int j = 0; j < m_nVexNum; j++) {
			//VexStart->vex->i�ľ��� С�� VexStart->i ���½ڵ�
 			if (m_aAdjMatrix[vex][j] && m_aAdjMatrix[vex][j] + dist[vex] < dist[j]) {
				dist[j] = m_aAdjMatrix[vex][j] + dist[vex];
				last[j] = vex;
			}
		}

		//�ҵ���С��δ���ʵĽ�㣬��Ϊ��һ�������ʵ�
		int min = INT32_MAX;
		for (int j = 0; j < m_nVexNum; j++) {
			if (!visit[j] && dist[j] < min) {
				min = dist[j];
				vex = j;
			}
		}
		visit[vex] = true;
	}

	//����Ŀ��·��(������)
	vex = VexEnd;
	int num = 0;
	do{
		num++;
		vex = last[vex];
	}while (vex != -1);

	//����·��
	vex = VexEnd;
	for (int i = num - 2; i >= 0; i--) {
		aPath[i].vex2 = vex;
		aPath[i].vex1 = last[vex];
		aPath[i].weight = m_aAdjMatrix[vex][last[vex]];
		vex = last[vex];
	}

	return dist[VexEnd];
}



//��С������(Prime�㷨)
int CGgraph::FindMinTree(Edge aPath[])
{
	//��ʼ��
	int* dist = new int[m_nVexNum]; //����ÿһ��Ĵ���
	bool* visit = new bool[m_nVexNum];  //�������
	int* last = new int[m_nVexNum]; //ֱ��ǰ��
	int sum = 0; //�ܳ���
	for (int i = 0; i < m_nVexNum; i++) {
		dist[i] = INT32_MAX;  //���������
		visit[i] = false;
		last[i] = -1;
	}
	//�ӱ��0��ʼ
	int vex = 0;
	visit[vex] = true;
	dist[vex] = 0;

	//ѭ��n-1�Σ�����n-1����
	for (int i = 0; i < m_nVexNum - 1; i++) {
		//������vexΪ���ı�
		for (int j = 0; j < m_nVexNum; j++) {
			//������۸�С������
			if (m_aAdjMatrix[vex][j] && m_aAdjMatrix[vex][j] < dist[j]) {
				dist[j] = m_aAdjMatrix[vex][j];
				last[j] = vex;
			}
		}
		
		//�ҵ���δ�������С��
		int min = INT32_MAX;
		for (int j = 0; j < m_nVexNum; j++) {
			if (!visit[j] && dist[j] < min) {
				min = dist[j];
				vex = j;
			}
		}
		visit[vex] = true;   //�����

		//�����
		aPath[i].vex1 = last[vex];
		aPath[i].vex2 = vex;
		aPath[i].weight = dist[vex];

		sum += dist[vex];
	}

	return sum;
}


//�����������   (���ʵ㣬�ѷ�������������飬��ʱ��·�����飬·������)
void CGgraph::DFS(int nVex, int index, bool visit[], int path[], PathList& List)
{
	//����nVex
	visit[nVex] = true;
	path[index++] = nVex;

	//�Ѿ�������·��
	if (index == m_nVexNum) {
		//�����µĽ�㣬��ͷ�ӷ�
		PathNode *p = new PathNode;
		p->next = List->next;
		List->next = p;

		//����·������,��·�߱��
		p->path = new int[m_nVexNum];
		for (int i = 0; i < m_nVexNum; i++) {
			p->path[i] = path[i];
		}	
		return;
	}

	//�������㣬�ҵ�δ��ǵ��ڽӵ�
	for (int i=0; i<m_nVexNum; i++) {
		if (!visit[i] && m_aAdjMatrix[nVex][i]) {
			DFS(i, index, visit, path, List);
			visit[i] = false; //����·�ߣ�i����Ϊδ����
		}
	}
}


//���·�� ��ʽ����� -> ��1 -> ��2 ...��
void CGgraph::ShowTravel(int path[],int len)
{
	cout << m_aVexs[path[0]].name;
	for (int i = 1; i < len; i++) {
		cout << " -> " << m_aVexs[path[i]].name;
	}
	cout << endl;
}

