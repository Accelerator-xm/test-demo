#include<iostream>
#include"Graph.h"
#include"Tourism.h"

using namespace std;

CGgraph m_Graph;


//1.创建景区景点图
void CreateGraph() {
	cout << endl;
	cout << "===== 创建景区景点图 ====== " << endl;

	//设置图顶点=========
	int Vnum;   //景点数

	//打开文件
	FILE* in = fopen(VexPath, "rb");
	if (in == NULL) {
		cout << "文件打开失败" << endl;
		return;
	}
	fscanf(in, "%d", &Vnum);

	cout << "顶点数目:" << Vnum << endl;
	cout << "----- 顶点 ------" << endl;

	Vex vex;
	for (int i = 0; i < Vnum; i++) {
		fscanf(in, "%d %s %s", &vex.num, vex.name, vex.desc);
		m_Graph.InsertVex(vex);   //添加点信息
	}
	//关闭文件
	fclose(in);

	//展示所有点
	m_Graph.ShowVex();

	
	//设置图的边==========
	cout << "----- 边 ------" << endl;
	
	//打开文件
	in = fopen(EdgePath, "rb");
	if (in == NULL) {
		cout << "文件打开失败" << endl;
		return;
	}

	Edge edge;
	while (!feof(in)) {
		fscanf(in, "%d %d %d ", &edge.vex1, &edge.vex2, &edge.weight);
		m_Graph.InsertEdge(edge);   //边插入邻接矩阵

		//输出边信息
		cout << "<v" << edge.vex1 << ",v" << edge.vex2 << "> " << edge.weight << "m" << endl;
	}

	cout << endl << endl << endl;
}


//2.查询景点信息
void GetSpotInfo() {
	cout << endl ;
	if (m_Graph.GetVexNum() == 0) {
		cout << "请先创建地图" << endl << endl << endl;
		return;
	}
	cout << "===== 查询景点信息 =====" << endl;
	m_Graph.ShowVex();
	cout << "请输入想要查询的景点编号:";
	

	//获取相应景点信息
	int vexIndex;    //需要查询的景点编号
	cin >> vexIndex;
	Vex vex = m_Graph.GetVex(vexIndex);  //获取需要查询的点
	cout << vex.name << endl;
	cout << vex.desc << endl;

	cout << "----- 周边景区 -----" << endl;
	Edge *edge = new Edge[m_Graph.GetVexNum()];   //邻接边数组(最多和其他顶点都相连)
	Vex tempV;
	int edgeNum = m_Graph.FindEdge(vexIndex,edge);  //获取邻接边

	//展示边 格式：“查询点->邻接点 距离”
	for (int i = 0; i < edgeNum; i++) {
		tempV = m_Graph.GetVex(edge[i].vex2);
		cout << vex.name << "->" << tempV.name << " " << edge[i].weight << "m" << endl;
	}

	cout << endl << endl << endl;
}


//3.查询景点导航路线
void TravelPath()
{
	cout << endl;

	if (m_Graph.GetVexNum() == 0) {
		cout << "请先创建地图" << endl << endl << endl;
		return;
	}
	cout << "===== 旅游景点导航 =====" << endl;
	m_Graph.ShowVex();
	cout << "请输入起始点编号:";
	int vexStart;  //起点编号
	cin >> vexStart;

	//初始化路线链表头结点
	PathList List = new PathNode;
	List->next = NULL;
    //获取路线链表
	m_Graph.DFSTravese(vexStart, List);

	//输出路线 格式：“路线i：起点 -> 点1 -> 点2 ...”
	int index = 1;
	for (PathNode* p = List->next; p != NULL; p = p->next, index++) {
		cout << "路线" << index << ": ";

		//将路线编号序列转成路线格式
		m_Graph.ShowTravel(p->path, m_Graph.GetVexNum());
	}

	cout << endl << endl << endl;
}


//4.搜索两个景点的最短路径
void FindShortPath()
{
	cout << endl;

	if (m_Graph.GetVexNum() == 0) {
		cout << "请先创建地图" << endl << endl << endl;
		return;
	}
	cout << "===== 搜索最短路径 =====" << endl;
	m_Graph.ShowVex();

	int vStart, vEnd;
	cout << "请输入起点的编号: ";
	cin >> vStart;
	cout << "请输入终点的编号: ";
	cin >> vEnd;
	
	//获取全部景点
	Vex* vexs = new Vex[m_Graph.GetVexNum()];
	for (int i = 0; i < m_Graph.GetVexNum(); i++) {
		vexs[i] = m_Graph.GetVex(i);
	}

	//获取路线边信息
	//创建路线边数组(最长n-1条边)，按路线顺序存边
	Edge* aPath = new Edge[m_Graph.GetVexNum() - 1];  
	//获取路线，返回距离
	int len = m_Graph.FindShortPath(vStart, vEnd, aPath); 
	
	//输出最短路线 格式：“点1 -> 点2 ...   距离”
	cout << "最短路线为: " << vexs[vStart].name;
	for (int i = 0;; i++) {
		cout << " -> " << vexs[aPath[i].vex2].name;
		if (aPath[i].vex2 == vEnd) break;
	}

	cout << "\n最短距离为: " << len << "m" << endl;

	cout << endl << endl << endl;
}


//查询铺设电路规划图
void DesignPath()
{
	cout << endl;

	if (m_Graph.GetVexNum() == 0) {
		cout << "请先创建地图" << endl << endl << endl;
		return;
	}
	cout << "===== 铺设电路规划 =====" << endl;
	cout << "在以下两个景点之间铺设电路" << endl;

	//获取全部景点
	Vex *vexs = new Vex[m_Graph.GetVexNum()];
	for (int i = 0; i < m_Graph.GetVexNum(); i++) {
		vexs[i] = m_Graph.GetVex(i);
	}

	//获取最小生成树边信息
	Edge* aPath = new Edge[m_Graph.GetVexNum() - 1];
	//返回长度
	int sum = m_Graph.FindMinTree(aPath);

	//遍历所有边信息
	
	for (int i = 0; i < m_Graph.GetVexNum() - 1; i++) {
		cout << vexs[aPath[i].vex1].name << " - " << vexs[aPath[i].vex2].name << " " << aPath[i].weight << "m\n";
		//sum += aPath[i].weight;
	}
	cout << "铺设电路的总长度为: " << sum << "m\n";
	
	//孙汉 软件2202

	cout << endl << endl << endl;
}



