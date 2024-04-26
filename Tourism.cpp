#include<iostream>
#include"Graph.h"
#include"Tourism.h"

using namespace std;

CGgraph m_Graph;


//1.������������ͼ
void CreateGraph() {
	cout << endl;
	cout << "===== ������������ͼ ====== " << endl;

	//����ͼ����=========
	int Vnum;   //������

	//���ļ�
	FILE* in = fopen(VexPath, "rb");
	if (in == NULL) {
		cout << "�ļ���ʧ��" << endl;
		return;
	}
	fscanf(in, "%d", &Vnum);

	cout << "������Ŀ:" << Vnum << endl;
	cout << "----- ���� ------" << endl;

	Vex vex;
	for (int i = 0; i < Vnum; i++) {
		fscanf(in, "%d %s %s", &vex.num, vex.name, vex.desc);
		m_Graph.InsertVex(vex);   //��ӵ���Ϣ
	}
	//�ر��ļ�
	fclose(in);

	//չʾ���е�
	m_Graph.ShowVex();

	
	//����ͼ�ı�==========
	cout << "----- �� ------" << endl;
	
	//���ļ�
	in = fopen(EdgePath, "rb");
	if (in == NULL) {
		cout << "�ļ���ʧ��" << endl;
		return;
	}

	Edge edge;
	while (!feof(in)) {
		fscanf(in, "%d %d %d ", &edge.vex1, &edge.vex2, &edge.weight);
		m_Graph.InsertEdge(edge);   //�߲����ڽӾ���

		//�������Ϣ
		cout << "<v" << edge.vex1 << ",v" << edge.vex2 << "> " << edge.weight << "m" << endl;
	}

	cout << endl << endl << endl;
}


//2.��ѯ������Ϣ
void GetSpotInfo() {
	cout << endl ;
	if (m_Graph.GetVexNum() == 0) {
		cout << "���ȴ�����ͼ" << endl << endl << endl;
		return;
	}
	cout << "===== ��ѯ������Ϣ =====" << endl;
	m_Graph.ShowVex();
	cout << "��������Ҫ��ѯ�ľ�����:";
	

	//��ȡ��Ӧ������Ϣ
	int vexIndex;    //��Ҫ��ѯ�ľ�����
	cin >> vexIndex;
	Vex vex = m_Graph.GetVex(vexIndex);  //��ȡ��Ҫ��ѯ�ĵ�
	cout << vex.name << endl;
	cout << vex.desc << endl;

	cout << "----- �ܱ߾��� -----" << endl;
	Edge *edge = new Edge[m_Graph.GetVexNum()];   //�ڽӱ�����(�����������㶼����)
	Vex tempV;
	int edgeNum = m_Graph.FindEdge(vexIndex,edge);  //��ȡ�ڽӱ�

	//չʾ�� ��ʽ������ѯ��->�ڽӵ� ���롱
	for (int i = 0; i < edgeNum; i++) {
		tempV = m_Graph.GetVex(edge[i].vex2);
		cout << vex.name << "->" << tempV.name << " " << edge[i].weight << "m" << endl;
	}

	cout << endl << endl << endl;
}


//3.��ѯ���㵼��·��
void TravelPath()
{
	cout << endl;

	if (m_Graph.GetVexNum() == 0) {
		cout << "���ȴ�����ͼ" << endl << endl << endl;
		return;
	}
	cout << "===== ���ξ��㵼�� =====" << endl;
	m_Graph.ShowVex();
	cout << "��������ʼ����:";
	int vexStart;  //�����
	cin >> vexStart;

	//��ʼ��·������ͷ���
	PathList List = new PathNode;
	List->next = NULL;
    //��ȡ·������
	m_Graph.DFSTravese(vexStart, List);

	//���·�� ��ʽ����·��i����� -> ��1 -> ��2 ...��
	int index = 1;
	for (PathNode* p = List->next; p != NULL; p = p->next, index++) {
		cout << "·��" << index << ": ";

		//��·�߱������ת��·�߸�ʽ
		m_Graph.ShowTravel(p->path, m_Graph.GetVexNum());
	}

	cout << endl << endl << endl;
}


//4.����������������·��
void FindShortPath()
{
	cout << endl;

	if (m_Graph.GetVexNum() == 0) {
		cout << "���ȴ�����ͼ" << endl << endl << endl;
		return;
	}
	cout << "===== �������·�� =====" << endl;
	m_Graph.ShowVex();

	int vStart, vEnd;
	cout << "���������ı��: ";
	cin >> vStart;
	cout << "�������յ�ı��: ";
	cin >> vEnd;
	
	//��ȡȫ������
	Vex* vexs = new Vex[m_Graph.GetVexNum()];
	for (int i = 0; i < m_Graph.GetVexNum(); i++) {
		vexs[i] = m_Graph.GetVex(i);
	}

	//��ȡ·�߱���Ϣ
	//����·�߱�����(�n-1����)����·��˳����
	Edge* aPath = new Edge[m_Graph.GetVexNum() - 1];  
	//��ȡ·�ߣ����ؾ���
	int len = m_Graph.FindShortPath(vStart, vEnd, aPath); 
	
	//������·�� ��ʽ������1 -> ��2 ...   ���롱
	cout << "���·��Ϊ: " << vexs[vStart].name;
	for (int i = 0;; i++) {
		cout << " -> " << vexs[aPath[i].vex2].name;
		if (aPath[i].vex2 == vEnd) break;
	}

	cout << "\n��̾���Ϊ: " << len << "m" << endl;

	cout << endl << endl << endl;
}


//��ѯ�����·�滮ͼ
void DesignPath()
{
	cout << endl;

	if (m_Graph.GetVexNum() == 0) {
		cout << "���ȴ�����ͼ" << endl << endl << endl;
		return;
	}
	cout << "===== �����·�滮 =====" << endl;
	cout << "��������������֮�������·" << endl;

	//��ȡȫ������
	Vex *vexs = new Vex[m_Graph.GetVexNum()];
	for (int i = 0; i < m_Graph.GetVexNum(); i++) {
		vexs[i] = m_Graph.GetVex(i);
	}

	//��ȡ��С����������Ϣ
	Edge* aPath = new Edge[m_Graph.GetVexNum() - 1];
	//���س���
	int sum = m_Graph.FindMinTree(aPath);

	//�������б���Ϣ
	
	for (int i = 0; i < m_Graph.GetVexNum() - 1; i++) {
		cout << vexs[aPath[i].vex1].name << " - " << vexs[aPath[i].vex2].name << " " << aPath[i].weight << "m\n";
		//sum += aPath[i].weight;
	}
	cout << "�����·���ܳ���Ϊ: " << sum << "m\n";
	
	//�ﺺ ���2202

	cout << endl << endl << endl;
}



