#pragma once
#include"global.h"

//图数据结构
class CGraph
{
protected:
	int m_Verteices[MAX_VERTEX_NUM];   //图的所有顶点
	int m_nVerNum;   //顶点数
	bool m_AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM]; //边信息(true=有边)
	//int m_nArcNum;   //边数量

public:
	CGraph();
	~CGraph();
	int AddVertex(int nInfo);   //添加顶点，返回数目
	void ChangeVertex(int index1, int index2);  //交换顶点位置
	int GetVertex(int index);   //获得顶点信息

	void UpdateArc(int nRow, int nCol);  //更新点(nRow,nCol)四周的边信息
	bool GetArc(int index1, int index2);  //获得边信息
	int GetVexnum();     //获取顶点数组中的顶点数
	void ClearGraph();   //将图中顶点和边还原为初始状态
	void AddArc(int index1, int index2);  //添加边
	void UpdateVertex(int index, int Info);   //将图顶点数组中索引号为nIndex的顶点的值更新为info 

protected:  
	void InitGraph();   //初始化
	void UpdateVerToVer(int index1, int index2);  //更新两点之间的边信息

};

