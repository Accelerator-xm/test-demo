#pragma once
#include"CGraph.h"

class CGameLogic
{
protected:
	Vertex m_avPath[MAX_VERTEX_NUM];   //����·�������Ķ���
	int m_anPath[MAX_VERTEX_NUM];   //������ͨ·���Ķ�������
	int m_nVexNum;   //������  
	int m_nCorner;   //����·������m_anPath�еĹյ���
	
public:
	CGameLogic();
	int** InitMap(CGraph &graph);   //��ʼ����Ϸ��ͼ
	void ReleaseMap(int**& pGameMap);  //�ͷŵ�ͼ
	bool IsLink(CGraph& graph, Vertex v1,Vertex v2); //�ж���ͨ
	void Clear(CGraph& graph, Vertex v1, Vertex v2); //��ȥ
	int GetVexPath(Vertex avPath[]);   //��ȡ·��
	bool IsBlank(CGraph& graph);      //�ж�Ԫ���Ƿ�Ϊ��
	bool SearchValidPath(CGraph& graph);  //Ѱ�ҿ��Խ���������ͼƬ
	void ResetGraph(CGraph& graph);    //����

	static Vertex move[4];
	void ResetGraph(int** pGameMap);   //����

protected:
	bool SearchPath(CGraph& graph, int nV0, int nV1);   //������������������ж�V1��ͼg���Ƿ���ͨ
	bool IsExsit(int nVi);   //�ж��Ƿ���ʹ�
	bool IsCorner();   //�ж��Ƿ��йյ�
	void PushVertex(int nV);   //��ջ
	void PopVertex();    //��ջ
	void ClearStack();   //���ջ

	bool SearchPath2(CGraph& graph, int nV0, int nV1);   
	int PriorIndex(int nV1, int nV2);    //�����ƶ�
	bool IsMove(int nV, Vertex move);    //�Ƿ����ƶ�





	bool LinkInRow(int** pGameMap, Vertex v1, Vertex v2); //������ͨ
	bool LinkInCol(int** pGameMap, Vertex v1, Vertex v2); //������ͨ
	bool OneCornerLink(int** pGameMap, Vertex v1, Vertex v2); //һ���յ���ͨ
	bool TwoCornerLink(int** pGameMap, Vertex v1, Vertex v2); //�����յ���ͨ

	bool LineY(int** pGameMap, int nRow1, int nRow2, int nCol); //ֱ����ͨy��
	bool LineX(int** pGameMap, int nRow, int nCol1, int nCol2); //ֱ����ͨx��

	void PushVertex(Vertex v); //���һ��·������
	//void PopVertex();   //ȡ��һ��·������



};

