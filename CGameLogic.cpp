#include "pch.h"
#include "CGameLogic.h"
#include"CCameControl.h"

Vertex CGameLogic::move[4] = { {0,-1,BLANK} ,{-1,0,BLANK} ,{0,1,BLANK} ,{1,0,BLANK} };


CGameLogic::CGameLogic()
{
    m_nVexNum = 0;   //顶点数  
}

//初始化地图
int** CGameLogic::InitMap(CGraph& graph)
{
    //获取地图大小和花色
    int nRows = CCameControl::s_nRows;
    int nCols = CCameControl::s_nCols;
    int nPicNum = CCameControl::s_nPicNum;

    //为游戏开辟内存空间
    int** pGameMap = new int* [nRows]; //行数
    
    if (NULL == pGameMap) {
        //throw new CGameException(_T("内存操作异常\n"));
    }
    else {
        for (int i = 0; i < nRows; i++) {
            pGameMap[i] = new int[nCols];  //列数

            if (NULL == pGameMap) {
                //throw new CGameException(_T("内存操作异常\n"));

            }
            //给数组初始化(起始地址，初始化的值，赋值的大小(字节数))
            memset(pGameMap[i], NULL, sizeof(int) * nCols); 
        }
    }

    //计算花色个数
    if ((nRows * nCols) % (nPicNum * 2) != 0) {
        //规定每个花色出现个数相同，且每个花色必须成对出现才能消去，所以对（nPicNum * 2）取余
        ReleaseMap(pGameMap);
        //throw new CGameException(_T("游戏花色与游戏地图大小不匹配\n"));
    }
    int nRepearNum = nRows * nCols / nPicNum;  //每个花色出现次数
    int nCount = 0;   //放入的花色个数
    for (int i = 0; i < nPicNum; i++) {
        //i为放入的花色编号，从左到右从上到下的顺序，每个花色放nRepearNum个
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


//释放地图
void CGameLogic::ReleaseMap(int**& pGameMap)
{
    for (int i = 0; i < CCameControl::s_nRows; i++) {
        delete[] pGameMap[i];
    }
    delete[] pGameMap;
}


//连接判断
bool CGameLogic::IsLink(CGraph& graph, Vertex v1, Vertex v2)
{
    ClearStack();

    int nCols = CCameControl::s_nCols;
    //获得顶点索引号
    int index1 = v1.row * nCols + v1.col;
    int index2 = v2.row * nCols + v2.col;
    PushVertex(index1);  //压入第一个点
    m_avPath[0] = v1;

    //搜寻两点之间的连通路径
    if (SearchPath2(graph, index1, index2) == true)
    {
        m_avPath[m_nCorner+1] = v2;
        return true;
    }


    return false;
}


//消去
void CGameLogic::Clear(CGraph& graph, Vertex v1, Vertex v2)
{  
    int nCols = CCameControl::s_nCols;
    int index1 = v1.row * nCols + v1.col;
    int index2 = v2.row * nCols + v2.col;
    //更新点
    graph.UpdateVertex(index1, BLANK);
    graph.UpdateVertex(index2, BLANK);
    //更新边
    graph.UpdateArc(v1.row, v1.col);
    graph.UpdateArc(v2.row, v2.col);

}

//获得路径
int CGameLogic::GetVexPath(Vertex avPath[])
{
    for (int i = 0; i < m_nCorner+2; i++) {
        avPath[i] = m_avPath[i];
    }
    return m_nCorner + 2;
}


//是否消完
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


//重排
void CGameLogic::ResetGraph(int** pGameMap)
{
    //获取地图大小
    int nRows = CCameControl::s_nRows;
    int nCols = CCameControl::s_nCols;

    //随机找到两个位置的图片交换
    //设置种子
    srand((int)time(NULL));

    //随机任意交换两个数字
    int nVertexNum = nRows * nCols;  //顶点总数
    for (int i = 0; i < nVertexNum; i++) {
        //随机得到两个数，表示把第nIndex1个元素和第nIndex2各元素交换
        int nIndex1 = rand() % nVertexNum;
        int nIndex2 = rand() % nVertexNum;
        //graph.ChangeVertex(nIndex1, nIndex2);

        //交换数值
        int nTmp = pGameMap[nIndex1 / nCols][nIndex1 % nCols];
        pGameMap[nIndex1 / nCols][nIndex1 % nCols] = pGameMap[nIndex2 / nCols][nIndex2 % nCols];
        pGameMap[nIndex2 / nCols][nIndex2 % nCols] = nTmp;
    }

}


void CGameLogic::ResetGraph(CGraph& graph)
{
    //获取地图大小
    int nRows = CCameControl::s_nRows;
    int nCols = CCameControl::s_nCols;

    //随机找到两个位置的图片交换
    //设置种子
    srand((int)time(NULL));

    //随机任意交换两个数字
    int nVertexNum = graph.GetVexnum();  //顶点总数
    for (int i = 0; i < nVertexNum; i++) {
        //随机得到两个数，表示把第nIndex1个元素和第nIndex2各元素交换
        int nIndex1 = rand() % nVertexNum;
        int nIndex2 = rand() % nVertexNum;
        //交换
        graph.ChangeVertex(nIndex1, nIndex2);
    }

    //初始化边信息
    for (int i = 0; i < nRows; i++) {
        for (int j = 0; j < nCols; j++) {
            graph.UpdateArc(i, j);
        }
    }
}


//寻找可以进行消除的图片
bool CGameLogic::SearchValidPath(CGraph& graph)
{
    //得到顶点数
    int nVexnum = graph.GetVexnum();
    //获取地图大小
    int nRows = CCameControl::s_nRows;
    int nCols = CCameControl::s_nCols;

    int info;
    for (int nV1 = 0; nV1 < nVexnum; nV1++) {
        //找到第一个图片
        info = graph.GetVertex(nV1);
        if (info == BLANK) continue;

        for (int nV2 = nV1+1; nV2 < nVexnum; nV2++) {
            //找到与v1相同的图片v2
            if (graph.GetVertex(nV2) != info) continue;
            else {
                //判断是否连通
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



//使用深度优先搜索法搜寻一条有效连通路径
bool CGameLogic::SearchPath(CGraph& graph, int nV0, int nV1)
{
    //得到顶点数
    int nVexnum = graph.GetVexnum();

    //遍历图中nV0行，从0列到nVexnum列，值为true的点
    for (int nVi = 0; nVi < nVexnum; nVi++)
    {
        if (graph.GetArc(nV0, nVi) && !IsExsit(nVi))
        {
            //压入当前顶点，假设为路径的一个有效顶点
            PushVertex(nVi);
            //当拐点数大于2 时，直接放弃该顶点
            if (m_nCorner > 2)
            {
                PopVertex();    //取出压入的顶点，与PushWertex(nVi)对应
                continue;
            }

            //到达终点
            if (nVi == nV1) return true;

            //当中间顶点不为空时，表示该条路径不通
            if (graph.GetVertex(nVi) != BLANK)
            {
                PopVertex();      //取出压入的顶点，与PushWertex(nVi)对应
                continue;
            }

            //判断（nVi，nV1）是否连通
            if (SearchPath(graph, nVi, nV1)) return true;

            PopVertex();     //取出压入的顶点，与PushWertex(nVi)对应
        }
    }
    return false;

}


//使用深度优先搜索法搜寻一条有效连通路径
bool CGameLogic::SearchPath2(CGraph& graph, int nV0, int nV1)
{ 
    int nCols = CCameControl::s_nCols;   //列数
    
    int nDir = PriorIndex(nV0, nV1);    //起始移动方向下标
    int nVi;

    //遍历四个方向移动
    for (int i = 0; i < 4; i++)
    {
        int index = (nDir + i) % 4;    //当前移动方向下标
        if (!IsMove(nV0,  move[index])) continue;

        nVi = nV0 + move[index].col + move[index].row * nCols;

        if (graph.GetArc(nV0, nVi) && !IsExsit(nVi))
        {           
            PushVertex(nVi);   //压入当前顶点，假设为路径的一个有效顶点         
            if (m_nCorner > 2)  //当拐点数大于2 时，直接放弃该顶点
            {
                PopVertex();    //取出压入的顶点，与PushWertex(nVi)对应
                continue;
            }
            
            if (nVi == nV1) return true;   //到达终点
            
            if (graph.GetVertex(nVi) != BLANK)    //当中间顶点不为空时，表示该条路径不通
            {
                PopVertex();      //取出压入的顶点，与PushWertex(nVi)对应
                continue;
            }

            //判断（nVi，nV1）是否连通
            if (SearchPath2(graph, nVi, nV1)) return true;

            PopVertex();     //取出压入的顶点，与PushWertex(nVi)对应
        }
    }
    return false;
}


//优先运动方向
int CGameLogic::PriorIndex(int nV1, int nV2)
{
    int nCols = CCameControl::s_nCols;

    int row1 = nV1 / nCols;
    int col1 = nV1 % nCols;
    int row2 = nV2 / nCols;
    int col2 = nV2 % nCols;

    if (row2 <= row1 && col2 < col1) return 0;          //优先左
    else if (row2 < row1 && col2 >= col1) return 1;     //优先上
    else if (row2 >= row1 && col2 > col1) return 2;     //优先右
    else if (row2 > row1 && col2 <= col1) return 3;     //优先下
}



//能否移动
bool CGameLogic::IsMove(int nV, Vertex move)
{
    int nCols = CCameControl::s_nCols;
    int nRows = CCameControl::s_nRows;

    //行号越界
    if (nV / nCols + move.row < 0 || nV / nCols + move.row > nRows - 1) {
        return false;
    }
    //列号越界
    if (nV % nCols + move.col < 0 || nV % nCols + move.col > nCols - 1) {
        return false;
    }

    return true;
}




//判断顶点是否已在路径中存在
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



//判断是否有拐点
bool CGameLogic::IsCorner()
{
    int nCols = CCameControl::s_nCols;

    //可能存在拐点
    if (m_nVexNum >= 3)
    {
        //与x轴平行 无拐点
        if ( (m_anPath[m_nVexNum - 1] / nCols == m_anPath[m_nVexNum - 2] / nCols) 
            && (m_anPath[m_nVexNum - 1] / nCols == m_anPath[m_nVexNum - 3] / nCols) )
        {
            return false;
        }

        //与y轴平行 无拐点
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
    //将顶点压栈
    m_anPath[m_nVexNum++] = nV;

    //判断是否形成新的拐点
    if (IsCorner())
    {
        m_avPath[++m_nCorner].row = m_anPath[m_nVexNum - 2] / CCameControl::s_nCols;
        m_avPath[m_nCorner].col = m_anPath[m_nVexNum - 2] % CCameControl::s_nCols;
        m_avPath[m_nCorner].info = BLANK;
    }
}



//取出一个路径顶点
void CGameLogic::PopVertex()
{
    //判断是否形成拐点，如果存在拐点，在取出之前减少拐点数
    if (IsCorner())
    {
        m_nCorner--;
    }
    m_nVexNum--;
}



//清除栈
void CGameLogic::ClearStack()
{
    m_nVexNum = 0;
    m_nCorner = 0;
}







//横向连通
bool CGameLogic::LinkInRow(int** pGameMap, Vertex v1, Vertex v2)
{
    int nCol1 = v1.col;
    int nCol2 = v2.col;
    int nRow = v1.row;

    return LineX(pGameMap,nRow,nCol1,nCol2);

}


//纵向连通
bool CGameLogic::LinkInCol(int** pGameMap, Vertex v1, Vertex v2)
{
    int nRow1 = v1.row;
    int nRow2 = v2.row;
    int nCol = v1.col;

    return LineY(pGameMap, nRow1, nRow2, nCol);

}


//一个拐点连通
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


//两个拐点连通
bool CGameLogic::TwoCornerLink(int** pGameMap, Vertex v1, Vertex v2)
{
    //找到一条与Y轴平行的联通线段
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

    //找到一条与X轴平行的连通线段
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


//直线连通y轴
bool CGameLogic::LineY(int** pGameMap, int nRow1, int nRow2, int nCol)
{
    //保证nCol1的值小于nCol2
    if (nRow1 > nRow2) {
        //交换数据
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


//直线连通x轴
bool CGameLogic::LineX(int** pGameMap, int nRow, int nCol1, int nCol2)
{
    //保证nCol1的值小于nCol2
    if (nCol1 > nCol2) {
        //交换数据
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



//添加一个路径顶点
void CGameLogic::PushVertex(Vertex v)
{
    m_avPath[m_nVexNum++] = v;
}







