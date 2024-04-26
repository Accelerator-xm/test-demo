#include "pch.h"
#include "CCameControl.h"
#include"global.h"

int CCameControl::s_nRows = MAX_ROW;
int CCameControl::s_nCols = MAX_COL;
int CCameControl::s_nPicNum = MAX_PIC_NUM;

//开始游戏
void CCameControl::StarGame()
{
	/*m_pGameMap = new int* [s_nRows];
	for (int i = 0; i < s_nRows; i++) m_pGameMap[i] = new int[s_nCols];
	for (int i = 0; i < s_nRows; i++) {
		for (int j = 0; j < s_nCols; j++) {
			m_pGameMap[i][j] = -1;
		}
	}
	m_pGameMap[0][0] = 1;
	m_pGameMap[0][1] = 1;*/
	m_pGameMap = m_GameLogic.InitMap(m_graph);
}


//得到某个元素
int CCameControl::GetElement(int nRow, int nCol)
{
	int index = nRow * s_nCols + nCol;
	return m_graph.GetVertex(index);
}


//设置第一个点
void CCameControl::SetFirstPoint(int nRow, int nCol)
{
	m_SelectVer1.row = nRow;
	m_SelectVer1.col = nCol;

	int index = nRow * s_nCols + nCol;
	m_SelectVer1.info = m_graph.GetVertex(index);
}

void CCameControl::SetSecondPoint(int nRow, int nCol)
{
	m_SelectVer2.row = nRow;
	m_SelectVer2.col = nCol;

	int index = nRow * s_nCols + nCol;
	m_SelectVer2.info = m_graph.GetVertex(index);
}

bool CCameControl::Link(Vertex avPath[], int& nVernum)
{
	//判断是否是同一张
	if (m_SelectVer1.row == m_SelectVer2.row && m_SelectVer1.col == m_SelectVer2.col) {
		return false;
	}

	//判断图片是否相同
	int index1 = m_SelectVer1.row * s_nCols + m_SelectVer1.col;
	int index2 = m_SelectVer2.row * s_nCols + m_SelectVer2.col;
	if (m_graph.GetVertex(index1) != m_graph.GetVertex(index2)) {
		return false;
	}


	if (m_GameLogic.IsLink(m_graph, m_SelectVer1, m_SelectVer2)) {
		//消子
		m_GameLogic.Clear(m_graph, m_SelectVer1, m_SelectVer2);

		//返回路径顶点
		nVernum = m_GameLogic.GetVexPath(avPath);

		return true;
	}

	return false;
}


//判断游戏是否胜利
int CCameControl::IsWin(int nTime)
{
	if (nTime <= 0) {
		return GAME_LOSE;
	}

	if (m_GameLogic.IsBlank(m_graph)) {
		return GAME_SUCCESS;
	}

	return GAME_PLAY;
}


//重排
void CCameControl::Reset()
{
	m_GameLogic.ResetGraph(m_graph);
}


//提示
bool CCameControl::Help(Vertex avPath[], int& nVernum)
{
	if (m_GameLogic.SearchValidPath(m_graph)) {
		//返回路径顶点
		nVernum = m_GameLogic.GetVexPath(avPath);

		return true;
	}

	return false;;
}
