#pragma once

//景点信息路径
#define VexPath "D:\\code\\c++\\DataStructureLab\\GraphCPro\\Vex.txt"
//边信息路径 
#define EdgePath "D:\\code\\c++\\DataStructureLab\\GraphCPro\\Edge.txt"

//创建景区景点图
void CreateGraph();
//查询指定景点信息
void GetSpotInfo();
//查询景点导航路线
void TravelPath();
//搜索两个景点的最短路径
void FindShortPath();
//查询铺设电路规划图
void DesignPath();