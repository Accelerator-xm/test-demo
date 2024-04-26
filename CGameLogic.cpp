#include "pch.h"
#include "CGameLogic.h"
#include"CCameControl.h"

Vertex CGameLogic::move[4] = { {0,-1,BLANK} ,{-1,0,BLANK} ,{0,1,BLANK} ,{1,0,BLANK} };


CGameLogic::CGameLogic()
{
    m_nVexNum = 0;   //������  
}

//��ʼ����ͼ
int** CGameLogic::InitMap(CGraph& graph)
{
    //��ȡ��ͼ��С�ͻ�ɫ
    int nRows = CCameControl::s_nRows;
    int nCols = CCameControl::s_nCols;
    int nPicNum = CCameControl::s_nPicNum;

    //Ϊ��Ϸ�����ڴ�ռ�
    int** pGameMap = new int* [nRows]; //����
    
    if (NULL == pGameMap) {
        //throw new CGameException(_T("�ڴ�����쳣\n"));
    }
    else {
        for (int i = 0; i < nRows; i++) {
            pGameMap[i] = new int[nCols];  //����

            if (NULL == pGameMap) {
                //throw new CGameException(_T("�ڴ�����쳣\n"));

            }
            //�������ʼ��(��ʼ��ַ����ʼ����ֵ����ֵ�Ĵ�С(�ֽ���))
            memset(pGameMap[i], NULL, sizeof(int) * nCols); 
        }
    }

    //���㻨ɫ����
    if ((nRows * nCols) % (nPicNum * 2) != 0) {
        //�涨ÿ����ɫ���ָ�����ͬ����ÿ����ɫ����ɶԳ��ֲ�����ȥ�����Զԣ�nPicNum * 2��ȡ��
        ReleaseMap(pGameMap);
        //throw new CGameException(_T("��Ϸ��ɫ����Ϸ��ͼ��С��ƥ��\n"));
    }
    int nRepearNum = nRows * nCols / nPicNum;  //ÿ����ɫ���ִ���
    int nCount = 0;   //����Ļ�ɫ����
    for (int i = 0; i < nPicNum; i++) {
        //iΪ����Ļ�ɫ��ţ������Ҵ��ϵ��µ�˳��ÿ����ɫ��nRepearNum��
        for (int j = 0; j < nRepearNum; j++) {
            graph.AddVertex(i);
            pGameMap[nCount / nCols][nCount % nCols] = i;
            nCount++;
        }
    }

    //ResetGraph(pGameMap);
    ResetGraph(graph);

   return pGameMap;
}


//�ͷŵ�ͼ
void CGameLogic::ReleaseMap(int**& pGameMap)
{
    for (int i = 0; i < CCameControl::s_nRows; i++) {
        delete[] pGameMap[i];
    }
    delete[] pGameMap;
}


//�����ж�
bool CGameLogic::IsLink(CGraph& graph, Vertex v1, Vertex v2)
{
    ClearStack();

    int nCols = CCameControl::s_nCols;
    //��ö���������
    int index1 = v1.row * nCols + v1.col;
    int index2 = v2.row * nCols + v2.col;
    PushVertex(index1);  //ѹ���һ����
    m_avPath[0] = v1;

    //��Ѱ����֮�����ͨ·��
    if (SearchPath2(graph, index1, index2) == true)
    {
        m_avPath[m_nCorner+1] = v2;
        return true;
    }


    return false;
}


//��ȥ
void CGameLogic::Clear(CGraph& graph, Vertex v1, Vertex v2)
{  
    int nCols = CCameControl::s_nCols;
    int index1 = v1.row * nCols + v1.col;
    int index2 = v2.row * nCols + v2.col;
    //���µ�
    graph.UpdateVertex(index1, BLANK);
    graph.UpdateVertex(index2, BLANK);
    //���±�
    graph.UpdateArc(v1.row, v1.col);
    graph.UpdateArc(v2.row, v2.col);

}

//���·��
int CGameLogic::GetVexPath(Vertex avPath[])
{
    for (int i = 0; i < m_nCorner+2; i++) {
        avPath[i] = m_avPath[i];
    }
    return m_nCorner + 2;
}


//�Ƿ�����
bool CGameLogic::IsBlank(CGraph& graph)
{  
    int nVexnum = graph.GetVexnum();

    for (int i = 0; i < nVexnum; i++)
    {
        if (graph.GetVertex(i) != BLANK)
        {
            return false;
        }
    }
    return true;
}


//����
void CGameLogic::ResetGraph(int** pGameMap)
{
    //��ȡ��ͼ��С
    int nRows = CCameControl::s_nRows;
    int nCols = CCameControl::s_nCols;

    //����ҵ�����λ�õ�ͼƬ����
    //��������
    srand((int)time(NULL));

    //������⽻����������
    int nVertexNum = nRows * nCols;  //��������
    for (int i = 0; i < nVertexNum; i++) {
        //����õ�����������ʾ�ѵ�nIndex1��Ԫ�غ͵�nIndex2��Ԫ�ؽ���
        int nIndex1 = rand() % nVertexNum;
        int nIndex2 = rand() % nVertexNum;
        //graph.ChangeVertex(nIndex1, nIndex2);

        //������ֵ
        int nTmp = pGameMap[nIndex1 / nCols][nIndex1 % nCols];
        pGameMap[nIndex1 / nCols][nIndex1 % nCols] = pGameMap[nIndex2 / nCols][nIndex2 % nCols];
        pGameMap[nIndex2 / nCols][nIndex2 % nCols] = nTmp;
    }

}


void CGameLogic::ResetGraph(CGraph& graph)
{
    //��ȡ��ͼ��С
    int nRows = CCameControl::s_nRows;
    int nCols = CCameControl::s_nCols;

    //����ҵ�����λ�õ�ͼƬ����
    //��������
    srand((int)time(NULL));

    //������⽻����������
    int nVertexNum = graph.GetVexnum();  //��������
    for (int i = 0; i < nVertexNum; i++) {
        //����õ�����������ʾ�ѵ�nIndex1��Ԫ�غ͵�nIndex2��Ԫ�ؽ���
        int nIndex1 = rand() % nVertexNum;
        int nIndex2 = rand() % nVertexNum;
        //����
        graph.ChangeVertex(nIndex1, nIndex2);
    }

    //��ʼ������Ϣ
    for (int i = 0; i < nRows; i++) {
        for (int j = 0; j < nCols; j++) {
            graph.UpdateArc(i, j);
        }
    }
}


//Ѱ�ҿ��Խ���������ͼƬ
bool CGameLogic::SearchValidPath(CGraph& graph)
{
    //�õ�������
    int nVexnum = graph.GetVexnum();
    //��ȡ��ͼ��С
    int nRows = CCameControl::s_nRows;
    int nCols = CCameControl::s_nCols;

    int info;
    for (int nV1 = 0; nV1 < nVexnum; nV1++) {
        //�ҵ���һ��ͼƬ
        info = graph.GetVertex(nV1);
        if (info == BLANK) continue;

        for (int nV2 = nV1+1; nV2 < nVexnum; nV2++) {
            //�ҵ���v1��ͬ��ͼƬv2
            if (graph.GetVertex(nV2) != info) continue;
            else {
                //�ж��Ƿ���ͨ
                Vertex v1 = { nV1 / nCols,nV1 % nCols,info };
                Vertex v2 = { nV2 / nCols,nV2 % nCols,info };
                if (IsLink(graph, v1, v2)) {
                    return true;
                }
            }
        }
    }


    return false;
}



//ʹ�����������������Ѱһ����Ч��ͨ·��
bool CGameLogic::SearchPath(CGraph& graph, int nV0, int nV1)
{
    //�õ�������
    int nVexnum = graph.GetVexnum();

    //����ͼ��nV0�У���0�е�nVexnum�У�ֵΪtrue�ĵ�
    for (int nVi = 0; nVi < nVexnum; nVi++)
    {
        if (graph.GetArc(nV0, nVi) && !IsExsit(nVi))
        {
            //ѹ�뵱ǰ���㣬����Ϊ·����һ����Ч����
            PushVertex(nVi);
            //���յ�������2 ʱ��ֱ�ӷ����ö���
            if (m_nCorner > 2)
            {
                PopVertex();    //ȡ��ѹ��Ķ��㣬��PushWertex(nVi)��Ӧ
                continue;
            }

            //�����յ�
            if (nVi == nV1) return true;

            //���м䶥�㲻Ϊ��ʱ����ʾ����·����ͨ
            if (graph.GetVertex(nVi) != BLANK)
            {
                PopVertex();      //ȡ��ѹ��Ķ��㣬��PushWertex(nVi)��Ӧ
                continue;
            }

            //�жϣ�nVi��nV1���Ƿ���ͨ
            if (SearchPath(graph, nVi, nV1)) return true;

            PopVertex();     //ȡ��ѹ��Ķ��㣬��PushWertex(nVi)��Ӧ
        }
    }
    return false;

}


//ʹ�����������������Ѱһ����Ч��ͨ·��
bool CGameLogic::SearchPath2(CGraph& graph, int nV0, int nV1)
{ 
    int nCols = CCameControl::s_nCols;   //����
    
    int nDir = PriorIndex(nV0, nV1);    //��ʼ�ƶ������±�
    int nVi;

    //�����ĸ������ƶ�
    for (int i = 0; i < 4; i++)
    {
        int index = (nDir + i) % 4;    //��ǰ�ƶ������±�
        if (!IsMove(nV0,  move[index])) continue;

        nVi = nV0 + move[index].col + move[index].row * nCols;

        if (graph.GetArc(nV0, nVi) && !IsExsit(nVi))
        {           
            PushVertex(nVi);   //ѹ�뵱ǰ���㣬����Ϊ·����һ����Ч����         
            if (m_nCorner > 2)  //���յ�������2 ʱ��ֱ�ӷ����ö���
            {
                PopVertex();    //ȡ��ѹ��Ķ��㣬��PushWertex(nVi)��Ӧ
                continue;
            }
            
            if (nVi == nV1) return true;   //�����յ�
            
            if (graph.GetVertex(nVi) != BLANK)    //���м䶥�㲻Ϊ��ʱ����ʾ����·����ͨ
            {
                PopVertex();      //ȡ��ѹ��Ķ��㣬��PushWertex(nVi)��Ӧ
                continue;
            }

            //�жϣ�nVi��nV1���Ƿ���ͨ
            if (SearchPath2(graph, nVi, nV1)) return true;

            PopVertex();     //ȡ��ѹ��Ķ��㣬��PushWertex(nVi)��Ӧ
        }
    }
    return false;
}


//�����˶�����
int CGameLogic::PriorIndex(int nV1, int nV2)
{
    int nCols = CCameControl::s_nCols;

    int row1 = nV1 / nCols;
    int col1 = nV1 % nCols;
    int row2 = nV2 / nCols;
    int col2 = nV2 % nCols;

    if (row2 <= row1 && col2 < col1) return 0;          //������
    else if (row2 < row1 && col2 >= col1) return 1;     //������
    else if (row2 >= row1 && col2 > col1) return 2;     //������
    else if (row2 > row1 && col2 <= col1) return 3;     //������
}



//�ܷ��ƶ�
bool CGameLogic::IsMove(int nV, Vertex move)
{
    int nCols = CCameControl::s_nCols;
    int nRows = CCameControl::s_nRows;

    //�к�Խ��
    if (nV / nCols + move.row < 0 || nV / nCols + move.row > nRows - 1) {
        return false;
    }
    //�к�Խ��
    if (nV % nCols + move.col < 0 || nV % nCols + move.col > nCols - 1) {
        return false;
    }

    return true;
}




//�ж϶����Ƿ�����·���д���
bool CGameLogic::IsExsit(int nVi)
{
    for (int i = 0; i < m_nVexNum; i++)
    {
        if (m_anPath[i] == nVi)
        {
            return true;
        }
    }
    return false;
}



//�ж��Ƿ��йյ�
bool CGameLogic::IsCorner()
{
    int nCols = CCameControl::s_nCols;

    //���ܴ��ڹյ�
    if (m_nVexNum >= 3)
    {
        //��x��ƽ�� �޹յ�
        if ( (m_anPath[m_nVexNum - 1] / nCols == m_anPath[m_nVexNum - 2] / nCols) 
            && (m_anPath[m_nVexNum - 1] / nCols == m_anPath[m_nVexNum - 3] / nCols) )
        {
            return false;
        }

        //��y��ƽ�� �޹յ�
        if ((m_anPath[m_nVexNum - 1] % nCols == m_anPath[m_nVexNum - 2] % nCols)
            && (m_anPath[m_nVexNum - 1] % nCols == m_anPath[m_nVexNum - 3] % nCols))
        {
            return false;
        }

        return true;
    }

    return false;
}


void CGameLogic::PushVertex(int nV)
{
    //������ѹջ
    m_anPath[m_nVexNum++] = nV;

    //�ж��Ƿ��γ��µĹյ�
    if (IsCorner())
    {
        m_avPath[++m_nCorner].row = m_anPath[m_nVexNum - 2] / CCameControl::s_nCols;
        m_avPath[m_nCorner].col = m_anPath[m_nVexNum - 2] % CCameControl::s_nCols;
        m_avPath[m_nCorner].info = BLANK;
    }
}



//ȡ��һ��·������
void CGameLogic::PopVertex()
{
    //�ж��Ƿ��γɹյ㣬������ڹյ㣬��ȡ��֮ǰ���ٹյ���
    if (IsCorner())
    {
        m_nCorner--;
    }
    m_nVexNum--;
}



//���ջ
void CGameLogic::ClearStack()
{
    m_nVexNum = 0;
    m_nCorner = 0;
}







//������ͨ
bool CGameLogic::LinkInRow(int** pGameMap, Vertex v1, Vertex v2)
{
    int nCol1 = v1.col;
    int nCol2 = v2.col;
    int nRow = v1.row;

    return LineX(pGameMap,nRow,nCol1,nCol2);

}


//������ͨ
bool CGameLogic::LinkInCol(int** pGameMap, Vertex v1, Vertex v2)
{
    int nRow1 = v1.row;
    int nRow2 = v2.row;
    int nCol = v1.col;

    return LineY(pGameMap, nRow1, nRow2, nCol);

}


//һ���յ���ͨ
bool CGameLogic::OneCornerLink(int** pGameMap, Vertex v1, Vertex v2)
{
    if (pGameMap[v1.row][v2.col] == BLANK) {
        if (LineY(pGameMap, v1.row, v2.row, v2.col) && LineX(pGameMap, v1.row, v1.col, v2.col)) {
            Vertex v = { v1.row,v2.col,BLANK };
            PushVertex(v);
            return true;
        }
    }

    if (pGameMap[v2.row][v1.col] == BLANK) {
        if (LineY(pGameMap, v1.row, v2.row, v1.col) && LineX(pGameMap, v2.row, v1.col, v2.col)) {
            Vertex v = { v2.row,v1.col,BLANK };
            PushVertex(v);
            return true;
        }
    }

    return false;
}


//�����յ���ͨ
bool CGameLogic::TwoCornerLink(int** pGameMap, Vertex v1, Vertex v2)
{
    //�ҵ�һ����Y��ƽ�е���ͨ�߶�
    for (int nCol = 0; nCol < CCameControl::s_nCols; nCol++) {
        if (pGameMap[v1.row][nCol] == BLANK && pGameMap[v2.row][nCol] == BLANK) {
            if (LineX(pGameMap,v1.row,v1.col,nCol) && LineX(pGameMap,v2.row,v2.col,nCol) && LineY(pGameMap, v1.row, v2.row, nCol)) {
                Vertex vx1 = { v1.row,nCol,BLANK };
                Vertex vx2 = { v2.row,nCol,BLANK };
                PushVertex(vx1);
                PushVertex(vx2);
                return true;
            }
        }
    }

    //�ҵ�һ����X��ƽ�е���ͨ�߶�
    for (int nRow = 0; nRow < CCameControl::s_nRows; nRow++) {
        if (pGameMap[nRow][v1.col] == BLANK && pGameMap[nRow][v2.col] == BLANK) {
            if (LineY(pGameMap, nRow, v1.row, v1.col) && LineY(pGameMap, nRow, v2.row, v2.col) && LineX(pGameMap, nRow, v1.col, v2.col)) {
                Vertex vx1 = { nRow,v1.col,BLANK };
                Vertex vx2 = { nRow,v2.col,BLANK };
                PushVertex(vx1);
                PushVertex(vx2);
                return true;
            }
        }
    }

    return false;
}


//ֱ����ͨy��
bool CGameLogic::LineY(int** pGameMap, int nRow1, int nRow2, int nCol)
{
    //��֤nCol1��ֵС��nCol2
    if (nRow1 > nRow2) {
        //��������
        int temp = nRow1;
        nRow1 = nRow2;
        nRow2 = temp;
    }

    for (int i = nRow1 + 1; i <= nRow2; i++) {
        if (i == nRow2) return true;
        if (pGameMap[i][nCol] != BLANK) break;
    }

    return false;
}


//ֱ����ͨx��
bool CGameLogic::LineX(int** pGameMap, int nRow, int nCol1, int nCol2)
{
    //��֤nCol1��ֵС��nCol2
    if (nCol1 > nCol2) {
        //��������
        int temp = nCol1;
        nCol1 = nCol2;
        nCol2 = temp;
    }

    for (int i = nCol1 + 1; i <= nCol2; i++) {
        if (i == nCol2) return true;
        if (pGameMap[nRow][i] != BLANK) break;
    }
    return false;
}



//���һ��·������
void CGameLogic::PushVertex(Vertex v)
{
    m_avPath[m_nVexNum++] = v;
}







