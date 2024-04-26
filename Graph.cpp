#include<iostream>
#include"Graph.h"

using namespace std;

//构造函数, 初始化
CGgraph::CGgraph()
{
	//权值信息
	for (int i = 0; i < MAX_VERTEX_NUM; i++) {
		for (int j = 0; j < MAX_VERTEX_NUM; j++) {
			m_aAdjMatrix[i][j] = 0;
		}
	}
	//顶点数
	m_nVexNum = 0;
}


//添加顶点
bool CGgraph::InsertVex(Vex sVex)
{
	//顶点已满
	if (m_nVexNum == MAX_VERTEX_NUM) {
		return false;
	}
	
	m_aVexs[m_nVexNum++] = sVex;  //插入顶点信息
	return true;
}


//添加边
bool CGgraph::InsertEdge(Edge sEdge)
{
	//下标越界
	if (sEdge.vex1 < 0 || sEdge.vex1 >= m_nVexNum || sEdge.vex2 < 0 || sEdge.vex2 >= m_nVexNum) {
		return false;
	}

	//插入边信息
	m_aAdjMatrix[sEdge.vex1][sEdge.vex2] = sEdge.weight;
	m_aAdjMatrix[sEdge.vex2][sEdge.vex1] = sEdge.weight;

	return true;
}


//输出所有景点编号和名字 格式：“编号-名字”
void CGgraph::ShowVex()
{
	for (int i = 0; i < m_nVexNum; i++) {
		//测试
		cout << m_aVexs[i].num << "-" << m_aVexs[i].name << endl;
	}
}



//获取景点数
int CGgraph::GetVexNum()
{
	return m_nVexNum;
}


//获取相应顶点
Vex CGgraph::GetVex(int v)
{	
	return m_aVexs[v];
}


//查询相邻景点
int CGgraph::FindEdge(int v, Edge aEdge[])
{
	int k = 0;
	for (int i = 0; i < m_nVexNum; i++) {
		//相邻
		if (m_aAdjMatrix[v][i]) {
			aEdge[k].vex1 = v;
			aEdge[k].vex2 = i;
			aEdge[k].weight = m_aAdjMatrix[v][i];
			k++;
		}
	}

	return k;
}


//获得遍历结果(所有路径)
void CGgraph::DFSTravese(int nVex, PathList& List)
{
	//标记数组
	bool *visit = new bool[m_nVexNum];
	for (int i = 0; i < m_nVexNum; i++) {
		visit[i] = false;  //初始化
	}
	//路线数组
	int* path = new int[m_nVexNum];

	//递归获取所有路线序列
	DFS(nVex,0, visit, path, List);
}


//搜索两点间的最短路径
int CGgraph::FindShortPath(int VexStart, int VexEnd, Edge aPath[])
{
	int *dist = new int[m_nVexNum]; //VexStart到每一点的距离
	bool* visit = new bool[m_nVexNum];  //标记数组
	int* last = new int[m_nVexNum]; //每个节点的直接前驱
	int vex = VexStart;  //待访问点

	//初始化
	for (int i = 0; i < m_nVexNum; i++) {
		dist[i] = INT32_MAX;  //距离无穷远
		visit[i] = false;
		last[i] = -1;  //没有前驱
	}

	dist[vex] = 0;  
	visit[vex] = true;

	//Dijkstra算法
	for (int i = 0; i < m_nVexNum - 1; i++) {

		//遍历所有邻接边
		for (int j = 0; j < m_nVexNum; j++) {
			//VexStart->vex->i的距离 小于 VexStart->i 更新节点
 			if (m_aAdjMatrix[vex][j] && m_aAdjMatrix[vex][j] + dist[vex] < dist[j]) {
				dist[j] = m_aAdjMatrix[vex][j] + dist[vex];
				last[j] = vex;
			}
		}

		//找到最小的未访问的结点，作为下一个带访问点
		int min = INT32_MAX;
		for (int j = 0; j < m_nVexNum; j++) {
			if (!visit[j] && dist[j] < min) {
				min = dist[j];
				vex = j;
			}
		}
		visit[vex] = true;
	}

	//搜索目标路线(景点数)
	vex = VexEnd;
	int num = 0;
	do{
		num++;
		vex = last[vex];
	}while (vex != -1);

	//复制路线
	vex = VexEnd;
	for (int i = num - 2; i >= 0; i--) {
		aPath[i].vex2 = vex;
		aPath[i].vex1 = last[vex];
		aPath[i].weight = m_aAdjMatrix[vex][last[vex]];
		vex = last[vex];
	}

	return dist[VexEnd];
}



//最小生成树(Prime算法)
int CGgraph::FindMinTree(Edge aPath[])
{
	//初始化
	int* dist = new int[m_nVexNum]; //纳入每一点的代价
	bool* visit = new bool[m_nVexNum];  //标记数组
	int* last = new int[m_nVexNum]; //直接前驱
	int sum = 0; //总长度
	for (int i = 0; i < m_nVexNum; i++) {
		dist[i] = INT32_MAX;  //代价无穷大
		visit[i] = false;
		last[i] = -1;
	}
	//从编号0开始
	int vex = 0;
	visit[vex] = true;
	dist[vex] = 0;

	//循环n-1次，纳入n-1条边
	for (int i = 0; i < m_nVexNum - 1; i++) {
		//遍历以vex为起点的边
		for (int j = 0; j < m_nVexNum; j++) {
			//如果代价更小，更新
			if (m_aAdjMatrix[vex][j] && m_aAdjMatrix[vex][j] < dist[j]) {
				dist[j] = m_aAdjMatrix[vex][j];
				last[j] = vex;
			}
		}
		
		//找到还未纳入的最小点
		int min = INT32_MAX;
		for (int j = 0; j < m_nVexNum; j++) {
			if (!visit[j] && dist[j] < min) {
				min = dist[j];
				vex = j;
			}
		}
		visit[vex] = true;   //纳入点

		//纳入边
		aPath[i].vex1 = last[vex];
		aPath[i].vex2 = vex;
		aPath[i].weight = dist[vex];

		sum += dist[vex];
	}

	return sum;
}


//深度优先搜索   (访问点，已访问数，标记数组，临时存路线数组，路线链表)
void CGgraph::DFS(int nVex, int index, bool visit[], int path[], PathList& List)
{
	//访问nVex
	visit[nVex] = true;
	path[index++] = nVex;

	//已经是完整路线
	if (index == m_nVexNum) {
		//创建新的结点，用头接法
		PathNode *p = new PathNode;
		p->next = List->next;
		List->next = p;

		//创建路线数组,存路线编号
		p->path = new int[m_nVexNum];
		for (int i = 0; i < m_nVexNum; i++) {
			p->path[i] = path[i];
		}	
		return;
	}

	//遍历顶点，找到未标记的邻接点
	for (int i=0; i<m_nVexNum; i++) {
		if (!visit[i] && m_aAdjMatrix[nVex][i]) {
			DFS(i, index, visit, path, List);
			visit[i] = false; //找新路线，i重置为未访问
		}
	}
}


//输出路线 格式“起点 -> 点1 -> 点2 ...”
void CGgraph::ShowTravel(int path[],int len)
{
	cout << m_aVexs[path[0]].name;
	for (int i = 1; i < len; i++) {
		cout << " -> " << m_aVexs[path[i]].name;
	}
	cout << endl;
}

