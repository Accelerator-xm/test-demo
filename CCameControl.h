#pragma once
#include"CGameLogic.h"
#include"CGraph.h"

class CCameControl
{
public:
	static int s_nRows;   //游戏行数
	static int s_nCols;   //游戏列数
	static int s_nPicNum;  //图片数

	CGraph m_graph;   //游戏地图
	int** m_pGameMap;    //游戏地图数组指针

	CGameLogic m_GameLogic;  //游戏逻辑操作对象
	Vertex m_SelectVer1;   //选中的第一个点
	Vertex m_SelectVer2;   //选中的第二个点


	void StarGame();  //开始游戏
	int GetElement(int nRow, int nCol);  //获得某个元素
	void SetFirstPoint(int nRow, int nCol); //设置第一个点
	void SetSecondPoint(int nRow, int nCol); //设置第二个点
	bool Link(Vertex avPath[], int& nVernum);  //判断连通
	int IsWin(int nTime);   //判断是否胜利
	void Reset();   //重排
	bool Help(Vertex avPath[], int& nVernum);    //提示功能

};

