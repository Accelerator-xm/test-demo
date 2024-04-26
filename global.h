#pragma once

#define MAX_VERTEX_NUM 160  //最大顶点数
#define MAX_ROW 10   //行数
#define MAX_COL 16  //列数
#define MAX_PIC_NUM 10  //花色数
#define GAME_MAP_TOP 50   //游戏地图左上角纵坐标
#define GAME_MAP_LEFT 20  //游戏地图左上角横坐标 
#define PIC_WIDTH 40  //元素宽
#define PIC_HEIGHT 40  //元素高

#define BLANK -1     //元素为空

#define PLAY_TIMER_ID 1  //计时器编号

#define GAME_LOSE -1    //失败
#define GAME_SUCCESS 0  //成功
#define GAME_PLAY 1    //游戏正在进行



//顶点存储结构
typedef struct{
	int row;   //行
	int col;   //列
	int info;  //值信息
}Vertex;

//游戏模式结构体
typedef struct {
	int min;         //最小值
	int max;         //最大值
	int step;        //步长
	int cost;        //辅助功能的代价
}Mode;