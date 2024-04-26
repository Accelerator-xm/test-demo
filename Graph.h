#pragma once

//最大顶点数
#define MAX_VERTEX_NUM 20

//顶点结构体
struct Vex {
	int num;      //景点编号
	char name[20];  //景点名字
	char desc[1024]; //景点介绍
};

//边结构体
struct Edge {
	int vex1;   //顶点1
	int vex2;   //顶点2
	int weight;  //权值
};

//路线链表(每个节点代表一个路线)
typedef struct PathNode {
	int *path;   //路线景点编号序列
	struct PathNode* next;
}PathNode, *PathList;

//图
class CGgraph {
private:
	int m_aAdjMatrix[20][20]; //邻接矩阵
	Vex m_aVexs[20];   //顶点信息数组
	int m_nVexNum;    //当前图的顶点个数
public:
	//构造函数
	CGgraph();
	//插入顶点信息
	bool InsertVex(Vex sVex);
	//插入边信息
	bool InsertEdge(Edge sEdge);
	//获取顶点个数
	int GetVexNum();
	//输出所有景点编号和名字
	void ShowVex();
	//获取相应顶点
	Vex GetVex(int v);
	//查询相邻景点,返回边的条数
	int FindEdge(int v, Edge aEdge[]);
	//获得遍历结果(所有路径)
	void DFSTravese(int nVex,PathList &List);
	//搜索两点间的最短路径
	int FindShortPath(int VexStart, int VexEnd, Edge aPath[]);
	//构造最小生成树
	int FindMinTree(Edge aPath[]);
	//输出路线(给出编号序列，格式化输出相应的路线信息)
	void ShowTravel(int path[],int len);
private:
	//深度优先搜索
	void DFS(int nVex,int index,bool visit[],int path[], PathList& List);

};
