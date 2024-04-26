#pragma once
#include "CCameControl.h"

// CGameDlg 对话框

class CGameDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGameDlg)

public:
	CGameDlg(CWnd* pParent = nullptr);   // 标准构造函数
	CGameDlg(Mode mode, CWnd* pParent = nullptr);   // 构造函数
	virtual ~CGameDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GAME_DIALOG };
#endif

protected:
	CDC m_dcMem;   //内存
	CDC m_dcBG;    //背景
	CDC m_dcElement;  //元素内存
	CDC m_dcMask;   //掩码内存
	//CDC m_Cache;    //缓存dc
	CDC m_dcPause;  //暂停图片
	CPoint m_ptGameTop; //游戏区起点坐标
	CSize m_sizeElem;  //元素图标大小
	CRect m_rtGameRect;  //游戏区域大小
	CCameControl m_GameC;  //游戏控制
	bool m_bPlaying;      //游戏状态标识
	bool m_bFirstPoint;  //判断是否是第一次点击
	bool m_bPause;       //暂停标识
	CProgressCtrl m_GameProgress;   //进度条
	Mode m_mode;            //游戏模式

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()


public:
	virtual BOOL OnInitDialog(); //窗口初始化函数

	afx_msg void OnPaint();   //消息函数
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);   //鼠标单击
	afx_msg void OnClickedBtnStart();     //开始游戏
	afx_msg void OnClickedBntReSet();     //重排
	afx_msg void OnClickedBtnHelp();      //帮助
	afx_msg void OnClickedBtnPoint();     //提示
	afx_msg void OnTimer(UINT_PTR nIDEvent); //进度条
	afx_msg void OnClickedBtnStop();         //暂停

protected:
	void InitElement();     //初始化元素图片与dc
	void InitBackground();  //初始话窗口背景
	void InitMember();      //初始化变量
	void UpdateWindow();    //更新界面

	void UpdateMap();       //更新游戏地图

	void DrawTipFrame(int nRow, int nCol);   //绘制提示框
	void DrawTipLine(Vertex avPath[], int nVernum); //画提示线

	void DrawWin();        //绘制胜利图片；
	void DrawGameTime();   //显示时间倒计时
	void JudgeWin();       //判断胜负

};
