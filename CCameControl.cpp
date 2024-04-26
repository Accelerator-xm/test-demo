#include "pch.h"
#include "CCameControl.h"
#include"global.h"

int CCameControl::s_nRows = MAX_ROW;
int CCameControl::s_nCols = MAX_COL;
int CCameControl::s_nPicNum = MAX_PIC_NUM;

//��ʼ��Ϸ
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


//�õ�ĳ��Ԫ��
int CCameControl::GetElement(int nRow, int nCol)
{
	int index = nRow * s_nCols + nCol;
	return m_graph.GetVertex(index);
}


//���õ�һ����
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
	//�ж��Ƿ���ͬһ��
	if (m_SelectVer1.row == m_SelectVer2.row && m_SelectVer1.col == m_SelectVer2.col) {
		return false;
	}

	//�ж�ͼƬ�Ƿ���ͬ
	int index1 = m_SelectVer1.row * s_nCols + m_SelectVer1.col;
	int index2 = m_SelectVer2.row * s_nCols + m_SelectVer2.col;
	if (m_graph.GetVertex(index1) != m_graph.GetVertex(index2)) {
		return false;
	}


	if (m_GameLogic.IsLink(m_graph, m_SelectVer1, m_SelectVer2)) {
		//����
		m_GameLogic.Clear(m_graph, m_SelectVer1, m_SelectVer2);

		//����·������
		nVernum = m_GameLogic.GetVexPath(avPath);

		return true;
	}

	return false;
}


//�ж���Ϸ�Ƿ�ʤ��
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


//����
void CCameControl::Reset()
{
	m_GameLogic.ResetGraph(m_graph);
}


//��ʾ
bool CCameControl::Help(Vertex avPath[], int& nVernum)
{
	if (m_GameLogic.SearchValidPath(m_graph)) {
		//����·������
		nVernum = m_GameLogic.GetVexPath(avPath);

		return true;
	}

	return false;;
}
