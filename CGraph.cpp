#include "pch.h"
#include "CGraph.h"

//构造函数
CGraph::CGraph()
{
	InitGraph();
}

//析构函数
CGraph::~CGraph()
{
}


//添加顶点，返回数目
int CGraph::AddVertex(int nInfo)
{
	m_Verteices[m_nVerNum++] = nInfo;
	return m_nVerNum;
}


//交换顶点位置
void CGraph::ChangeVertex(int index1, int index2)
{
	int temp = m_Verteices[index1];
	m_Verteices[index1] = m_Verteices[index2];
	m_Verteices[index2] = temp;
}


//获得顶点信息
int CGraph::GetVertex(int index)
{
	return m_Verteices[index];
}


//更新点(nRow,nCol)的边信息
void CGraph::UpdateArc(int nRow, int nCol)
{
	int nRows = MAX_ROW;  //行数
	int nCols = MAX_COL;  //列数

	int index = nRow * nCols + nCol;  //编号
	//上面是有效坐标
	if (nRow > 0) {
		int index1 = (nRow - 1) * nCols + nCol;  //上面的编号
		UpdateVerToVer(index, index1);
		//UpdateVerToVer(index1, index);
	}
	//下面是有效坐标
	if (nRow < nRows-1) {
		int index2 = (nRow + 1) * nCols + nCol;  //下面的编号
		UpdateVerToVer(index, index2);
		//UpdateVerToVer(index2, index);
	}
	//左边是有效坐标
	if (nCol > 0) {
		int index3 = index - 1;  //左边的编号
		UpdateVerToVer(index, index3);
		//UpdateVerToVer(index3, index);
	}
	//右边是有效坐标
	if (nCol < nCols - 1) {
		int index4 = index + 1;  //右边的编号
		UpdateVerToVer(index, index4);
		//UpdateVerToVer(index4, index);
	}

	
}

bool CGraph::GetArc(int index1, int index2)
{
	return m_AdjMatrix[index1][index2];
}


//初始化
void CGraph::InitGraph()
{
	//初始化顶点为-1（有效顶点为0-9）
	m_nVerNum = 0;
	for (int i = 0; i < MAX_VERTEX_NUM; i++) {
		m_Verteices[i] = BLANK;
	}

	//初始化边为false-----没有边
	for (int i = 0; i < MAX_VERTEX_NUM; i++) {
		for (int j = 0; j < MAX_VERTEX_NUM; j++) {
			m_AdjMatrix[i][j] = false;
		}
	}
}


//更新两点之间的关系
void CGraph::UpdateVerToVer(int index1, int index2)
{
	//相邻两个格子 顶点编号相同、至少一个为空  -> 有边
	if (m_Verteices[index1] == -1 || m_Verteices[index2] == -1 
		|| m_Verteices[index1] == m_Verteices[index2]) {		
		m_AdjMatrix[index1][index2] = m_AdjMatrix[index2][index1] = true;

	}
	//没有边
	else {		
		m_AdjMatrix[index1][index2] = m_AdjMatrix[index2][index1] = false;
	}
}


//添加边
void CGraph::AddArc(int index1, int index2)
{
	m_AdjMatrix[index1][index2] = m_AdjMatrix[index2][index1] = true;
}



//更新顶点信息
void CGraph::UpdateVertex(int index, int Info)
{
	m_Verteices[index] = Info;
}


//获取顶点数
int CGraph::GetVexnum()
{
	return m_nVerNum;
}



//清空图
void CGraph::ClearGraph()
{
	InitGraph();
}
