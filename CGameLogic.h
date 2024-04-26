#pragma once
#include"CGraph.h"

class CGameLogic
{
protected:
	Vertex m_avPath[MAX_VERTEX_NUM];   //连接路径经过的顶点
	int m_anPath[MAX_VERTEX_NUM];   //保存连通路径的顶点索引
	int m_nVexNum;   //顶点数  
	int m_nCorner;   //连接路径数组m_anPath中的拐点数
	
public:
	CGameLogic();
	int** InitMap(CGraph &graph);   //初始化游戏地图
	void ReleaseMap(int**& pGameMap);  //释放地图
	bool IsLink(CGraph& graph, Vertex v1,Vertex v2); //判断连通
	void Clear(CGraph& graph, Vertex v1, Vertex v2); //消去
	int GetVexPath(Vertex avPath[]);   //获取路径
	bool IsBlank(CGraph& graph);      //判断元素是否为空
	bool SearchValidPath(CGraph& graph);  //寻找可以进行消除的图片
	void ResetGraph(CGraph& graph);    //重排

	static Vertex move[4];
	void ResetGraph(int** pGameMap);   //重排

protected:
	bool SearchPath(CGraph& graph, int nV0, int nV1);   //采用深度优先搜索，判断V1在图g中是否连通
	bool IsExsit(int nVi);   //判断是否访问过
	bool IsCorner();   //判断是否有拐点
	void PushVertex(int nV);   //入栈
	void PopVertex();    //出栈
	void ClearStack();   //清除栈

	bool SearchPath2(CGraph& graph, int nV0, int nV1);   
	int PriorIndex(int nV1, int nV2);    //优先移动
	bool IsMove(int nV, Vertex move);    //是否能移动





	bool LinkInRow(int** pGameMap, Vertex v1, Vertex v2); //横向连通
	bool LinkInCol(int** pGameMap, Vertex v1, Vertex v2); //纵向连通
	bool OneCornerLink(int** pGameMap, Vertex v1, Vertex v2); //一个拐点连通
	bool TwoCornerLink(int** pGameMap, Vertex v1, Vertex v2); //两个拐点连通

	bool LineY(int** pGameMap, int nRow1, int nRow2, int nCol); //直线连通y轴
	bool LineX(int** pGameMap, int nRow, int nCol1, int nCol2); //直线连通x轴

	void PushVertex(Vertex v); //添加一个路径顶点
	//void PopVertex();   //取出一个路径顶点



};

