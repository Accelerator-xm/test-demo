#include "pch.h"
#include "CGraph.h"

//���캯��
CGraph::CGraph()
{
	InitGraph();
}

//��������
CGraph::~CGraph()
{
}


//��Ӷ��㣬������Ŀ
int CGraph::AddVertex(int nInfo)
{
	m_Verteices[m_nVerNum++] = nInfo;
	return m_nVerNum;
}


//��������λ��
void CGraph::ChangeVertex(int index1, int index2)
{
	int temp = m_Verteices[index1];
	m_Verteices[index1] = m_Verteices[index2];
	m_Verteices[index2] = temp;
}


//��ö�����Ϣ
int CGraph::GetVertex(int index)
{
	return m_Verteices[index];
}


//���µ�(nRow,nCol)�ı���Ϣ
void CGraph::UpdateArc(int nRow, int nCol)
{
	int nRows = MAX_ROW;  //����
	int nCols = MAX_COL;  //����

	int index = nRow * nCols + nCol;  //���
	//��������Ч����
	if (nRow > 0) {
		int index1 = (nRow - 1) * nCols + nCol;  //����ı��
		UpdateVerToVer(index, index1);
		//UpdateVerToVer(index1, index);
	}
	//��������Ч����
	if (nRow < nRows-1) {
		int index2 = (nRow + 1) * nCols + nCol;  //����ı��
		UpdateVerToVer(index, index2);
		//UpdateVerToVer(index2, index);
	}
	//�������Ч����
	if (nCol > 0) {
		int index3 = index - 1;  //��ߵı��
		UpdateVerToVer(index, index3);
		//UpdateVerToVer(index3, index);
	}
	//�ұ�����Ч����
	if (nCol < nCols - 1) {
		int index4 = index + 1;  //�ұߵı��
		UpdateVerToVer(index, index4);
		//UpdateVerToVer(index4, index);
	}

	
}

bool CGraph::GetArc(int index1, int index2)
{
	return m_AdjMatrix[index1][index2];
}


//��ʼ��
void CGraph::InitGraph()
{
	//��ʼ������Ϊ-1����Ч����Ϊ0-9��
	m_nVerNum = 0;
	for (int i = 0; i < MAX_VERTEX_NUM; i++) {
		m_Verteices[i] = BLANK;
	}

	//��ʼ����Ϊfalse-----û�б�
	for (int i = 0; i < MAX_VERTEX_NUM; i++) {
		for (int j = 0; j < MAX_VERTEX_NUM; j++) {
			m_AdjMatrix[i][j] = false;
		}
	}
}


//��������֮��Ĺ�ϵ
void CGraph::UpdateVerToVer(int index1, int index2)
{
	//������������ ��������ͬ������һ��Ϊ��  -> �б�
	if (m_Verteices[index1] == -1 || m_Verteices[index2] == -1 
		|| m_Verteices[index1] == m_Verteices[index2]) {		
		m_AdjMatrix[index1][index2] = m_AdjMatrix[index2][index1] = true;

	}
	//û�б�
	else {		
		m_AdjMatrix[index1][index2] = m_AdjMatrix[index2][index1] = false;
	}
}


//��ӱ�
void CGraph::AddArc(int index1, int index2)
{
	m_AdjMatrix[index1][index2] = m_AdjMatrix[index2][index1] = true;
}



//���¶�����Ϣ
void CGraph::UpdateVertex(int index, int Info)
{
	m_Verteices[index] = Info;
}


//��ȡ������
int CGraph::GetVexnum()
{
	return m_nVerNum;
}



//���ͼ
void CGraph::ClearGraph()
{
	InitGraph();
}
