// CGameDlg.cpp: 实现文件
//

#include "pch.h"
#include "LianLianKan.h"
#include "afxdialogex.h"
#include "CGameDlg.h"
#include "CHelpDialog.h"



// CGameDlg 对话框

IMPLEMENT_DYNAMIC(CGameDlg, CDialogEx)

CGameDlg::CGameDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GAME_DIALOG, pParent)
{
	//初始化
	InitMember();
	m_mode = { 0,300,-1,-10 };
	//m_ptGameTop.SetPoint(GAME_MAP_LEFT, GAME_MAP_TOP);  //初始化游戏起点坐标
	//m_sizeElem.SetSize(PIC_WIDTH, PIC_HEIGHT);  //元素大小
	//int x2 = m_ptGameTop.x + m_sizeElem.cx * CCameControl::s_nCols;
	//int y2 = m_ptGameTop.y + m_sizeElem.cy * CCameControl::s_nRows;
	//m_rtGameRect.SetRect(m_ptGameTop.x, m_ptGameTop.y, x2, y2);   //游戏区域
	//m_bPlaying = false;
}


CGameDlg::CGameDlg(Mode mode, CWnd* pParent)
	: CDialogEx(IDD_GAME_DIALOG, pParent)
{
	InitMember();
	m_mode = mode;
}


CGameDlg::~CGameDlg()
{
}

void CGameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GAME_TIME, m_GameProgress);
}


//初始化背景
void CGameDlg::InitBackground()
{
	//创建DC
	CClientDC dc(this);

	//加载bmp图片资源
	HANDLE bmp = ::LoadImage(NULL, _T("theme\\picture\\fruit_bg.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	//创建与视频内存兼容的内存DC
	m_dcBG.CreateCompatibleDC(&dc);
	//将位图选进DC
	m_dcBG.SelectObject(bmp);

	//初始化内存DC
	//创建与视频内存兼容的内存DC
	m_dcMem.CreateCompatibleDC(&dc);
	CBitmap bmpMem;
	bmpMem.CreateCompatibleBitmap(&dc, 800, 600);
	//将位图选进DC
	m_dcMem.SelectObject(&bmpMem);

	m_dcMem.BitBlt(0, 0, 800, 600, &m_dcBG, 0, 0, SRCCOPY); 
}


//初始化变量
void CGameDlg::InitMember()
{
	m_ptGameTop.SetPoint(GAME_MAP_LEFT, GAME_MAP_TOP);  //初始化游戏起点坐标
	m_sizeElem.SetSize(PIC_WIDTH, PIC_HEIGHT);  //元素大小
	int x2 = m_ptGameTop.x + m_sizeElem.cx * CCameControl::s_nCols;
	int y2 = m_ptGameTop.y + m_sizeElem.cy * CCameControl::s_nRows;
	m_rtGameRect.SetRect(m_ptGameTop.x, m_ptGameTop.y, x2, y2);   //游戏区域
	m_bPlaying = false;
}




//调整游戏窗口大小
void CGameDlg::UpdateWindow()
{
	//调整窗口大小
	CRect rtWin;
	CRect rtClient;
	this->GetWindowRect(rtWin);   //获得窗口大小
	this->GetClientRect(rtClient);  //获取客户区大小
	//标题栏和外边框大小
	int nSpanWidth = rtWin.Width() - rtClient.Width();
	int nSpanHeight = rtWin.Height() - rtClient.Height();

	//设置窗口大小
	MoveWindow(0, 0, 800 + nSpanWidth, 600 + nSpanHeight);

	//居中
	CenterWindow();
}


//加载游戏元素图片
void CGameDlg::InitElement()
{
	HANDLE hBmp = ::LoadImage(NULL, _T("theme\\picture\\fruit_element.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	//创建DC
	CClientDC dc(this);
	//创建与视频内存兼容的内存DC
	m_dcElement.CreateCompatibleDC(&dc);
	//将位图选进DC
	m_dcElement.SelectObject(hBmp);

	//加载掩码BMP图片资源
	HANDLE hMask = ::LoadImage(NULL, _T("theme\\picture\\fruit_mask.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	//创建与视频内存兼容的内存dc
	m_dcMask.CreateCompatibleDC(&dc);
	//将位图选入DC
	m_dcMask.SelectObject(hMask);

	//加载暂停图片
	HANDLE hPause = ::LoadImage(NULL, _T("theme\\picture\\stop.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	//创建与视频内存兼容的内存DC
	m_dcPause.CreateCompatibleDC(&dc);
	//将位图选进DC
	m_dcPause.SelectObject(hPause);

	//保存游戏界面
	//CBitmap bmpMem;
	//bmpMem.CreateCompatibleBitmap(&dc, 640, 400);
	////将位图选进DC
	//m_Cache.SelectObject(&bmpMem);
}


//更新游戏地图
void CGameDlg::UpdateMap()
{
	//计算图片的顶点坐标与图片大小
	//(nLeft,nTop)为游戏区域顶点坐标
	int nLeft = m_ptGameTop.x;
	int nTop = m_ptGameTop.y;
	int nElemW = m_sizeElem.cx;
	int nElemH = m_sizeElem.cy;


	m_dcMem.BitBlt(m_rtGameRect.left, m_rtGameRect.top, m_rtGameRect.Width(), 
		m_rtGameRect.Height(),&m_dcBG, m_rtGameRect.left, m_rtGameRect.top, SRCCOPY);
	
	//获取行数的列数
	int nRows = CCameControl::s_nRows;
	int nCols = CCameControl::s_nCols;

	for (int i = 0; i < nRows; i++) {
		for (int j = 0; j < nCols; j++) {
			//得到图片编号的值
			int nElemVal = m_GameC.GetElement(i, j);
			//将背景与掩码相或，边保留，图像区域为1
			m_dcMem.BitBlt(nLeft + j * nElemW, nTop + i * nElemH, nElemW, nElemH, &m_dcMask, 0, nElemVal * nElemH, SRCPAINT);

			//将背景与掩码相与，边保留，图像区域为1
			m_dcMem.BitBlt(nLeft + j * nElemW, nTop + i * nElemH, nElemW, nElemH, &m_dcElement, 0, nElemVal * nElemH, SRCAND);

		}
	}

	//InvalidateRect(m_rtGameRect,false);
}


BEGIN_MESSAGE_MAP(CGameDlg, CDialogEx)
	ON_WM_PAINT()
//	ON_BN_CLICKED(IDC_BTN_START, &CGameDlg::OnBnClickedBtnStart)
ON_BN_CLICKED(IDC_BTN_START, &CGameDlg::OnClickedBtnStart)
ON_WM_LBUTTONUP()
//ON_BN_CLICKED(IDC_BTN_SETTING, &CGameDlg::OnClickedBtnReSet)
ON_BN_CLICKED(IDC_BNT_REARRANGE, &CGameDlg::OnClickedBntReSet)
ON_BN_CLICKED(IDC_BTN_HELP, &CGameDlg::OnClickedBtnHelp)
ON_BN_CLICKED(IDC_BTN_POINT, &CGameDlg::OnClickedBtnPoint)
ON_WM_TIMER()
ON_BN_CLICKED(IDC_BTN_STOP, &CGameDlg::OnClickedBtnStop)
END_MESSAGE_MAP()


// CGameDlg 消息处理程序


BOOL CGameDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	InitBackground();
	UpdateWindow();
	InitElement();


	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CGameDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	
	dc.BitBlt(0, 0, 800, 600, &m_dcMem, 0, 0, SRCCOPY);
	// 不为绘图消息调用 CDialogEx::OnPaint()
}


//点击开始游戏
void CGameDlg::OnClickedBtnStart()
{
	// TODO: 在此添加控件通知处理程序代码
	//初始化地图
	m_GameC.StarGame();
	//绘制地图
	UpdateMap();
	InvalidateRect(m_rtGameRect, false);
	//初始化点击标志
	m_bFirstPoint = true;
	//初始化是否在游戏中的标志
	m_bPlaying = true;
	//初始化暂停
	m_bPause = false;
	//禁用按钮-----游戏开始后不准使用按钮
	((CButton*)GetDlgItem(IDC_BTN_START))->EnableWindow(false);

	//初始进度条
	m_GameProgress.SetRange(m_mode.min, m_mode.max);  //范围
	m_GameProgress.SetStep(m_mode.step);       //步长
	m_GameProgress.SetPos(m_mode.max);       //起点
	//启动计时器
	this->SetTimer(PLAY_TIMER_ID, 1000, NULL);
	//绘制当前秒数
	DrawGameTime();
}


//点击图片
void CGameDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	// 判断是否在游戏中-----游戏未进行或游戏暂停时点击无效
	if (!m_bPlaying || m_bPause) {
		return CDialogEx::OnLButtonUp(nFlags, point);
	}

	//判断鼠标点击区域-----超出游戏地图范围点击无效点击无效
	if (point.y < m_rtGameRect.top || point.y > m_rtGameRect.bottom 
		|| point.x < m_rtGameRect.left || point.x > m_rtGameRect.right) {
		return CDialogEx::OnLButtonUp(nFlags, point);
	}

	int nRow = (point.y - m_rtGameRect.top) / m_sizeElem.cy;
	int nCol = (point.x - m_rtGameRect.left) / m_sizeElem.cx;

	//判断是否点到有效元素-----空元素区域点击无效
	if (m_GameC.GetElement(nRow, nCol) == BLANK) {
		return CDialogEx::OnLButtonUp(nFlags, point);
	}

	if (m_bFirstPoint) {   //第一个点
		DrawTipFrame(nRow, nCol);
		m_GameC.SetFirstPoint(nRow, nCol);
	}
	else {    //第二个点
		DrawTipFrame(nRow, nCol);
		m_GameC.SetSecondPoint(nRow, nCol);

		//连子判断
		Vertex avPath[4];  //存放端点、拐点
		int nVexnum = 0;   //端点、拐点总数
		bool bSuc = m_GameC.Link(avPath, nVexnum);
		if (bSuc) {
			//画提示线
			DrawTipLine(avPath, nVexnum);	

			//更新地图
			UpdateMap();

			//判断胜负
			JudgeWin();
		}	
		//延时0.1s
		Sleep(100);
		InvalidateRect(m_rtGameRect, false);


	}
	m_bFirstPoint = !m_bFirstPoint;

	CDialogEx::OnLButtonUp(nFlags, point);
}


//绘制矩形框
void CGameDlg::DrawTipFrame(int nRow, int nCol)
{
	CClientDC dc(this);
	CBrush brush(RGB(233, 43, 43));
	CRect rtTipFrame;
	rtTipFrame.left = m_ptGameTop.x + nCol * m_sizeElem.cx;
	rtTipFrame.top = m_ptGameTop.y + nRow * m_sizeElem.cy;
	rtTipFrame.right = rtTipFrame.left + m_sizeElem.cx;
	rtTipFrame.bottom = rtTipFrame.top + m_sizeElem.cy;
	dc.FrameRect(rtTipFrame, &brush);
}


//画提示线
void CGameDlg::DrawTipLine(Vertex avPath[], int nVernum)
{
	CClientDC dc(this);
	//设置画笔
	CPen penLine(PS_SOLID, 2, RGB(0, 255, 0));
	//将画笔选入dc
	CPen* pOldPen = dc.SelectObject(&penLine);

	dc.MoveTo(m_ptGameTop.x + avPath[0].col * m_sizeElem.cx + m_sizeElem.cx / 2,
		m_ptGameTop.y + avPath[0].row * m_sizeElem.cy + m_sizeElem.cy / 2);

	for (int i = 1; i < nVernum; i++) {
		dc.LineTo(m_ptGameTop.x + avPath[i].col * m_sizeElem.cx + m_sizeElem.cx / 2,
			m_ptGameTop.y + avPath[i].row * m_sizeElem.cy + m_sizeElem.cy / 2);
	}

	dc.SelectObject(pOldPen);
}


//绘制胜利图片
void CGameDlg::DrawWin()
{

	//(nLeft,nTop)为游戏区域顶点坐标
	int nLeft = m_ptGameTop.x;
	int nTop = m_ptGameTop.y;

	HANDLE hBmp = ::LoadImage(NULL, _T("theme\\picture\\win.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	HANDLE hMask = ::LoadImage(NULL, _T("theme\\picture\\WinMask.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	//创建DC
	CClientDC dc(this);
	//创建与视频内存兼容的内存DC

	CDC dcWin;
	dcWin.CreateCompatibleDC(&dc);
	//将位图选进DC
	dcWin.SelectObject(hBmp);

	CDC dcWinMask;
	dcWinMask.CreateCompatibleDC(&dc);
	//将位图选进DC
	dcWinMask.SelectObject(hMask);

	//计算画图位置 197 73
	int nWinW = 197;
	int nWinH = 73;
	int x = (m_rtGameRect.Width() - nWinW) / 2 + m_ptGameTop.x;
	int y = (m_rtGameRect.Height() - nWinH) / 2 + m_ptGameTop.y;


	m_dcMem.BitBlt(x, y, nWinW, nWinH, &dcWinMask, 0, 0, SRCPAINT);
	m_dcMem.BitBlt(x, y, nWinW, nWinH, &dcWin, 0, 0, SRCAND);

}



//显示倒计时
void CGameDlg::DrawGameTime()
{
	CClientDC dc(this);
	//创建字体
	CFont font;
	//(高度的十分之一，字体，默认0)
	font.CreatePointFont(200, _T("Courier New"));

	//将字体选进DC
	CFont* oldFont = dc.SelectObject(&font);

	//RGB(红，绿，蓝)
	//设置字体颜色  蓝色
	dc.SetTextColor(RGB(0, 0, 255));
	//设置背景颜色白色
	dc.SetBkColor(RGB(255, 255, 255));

	//获取进度条坐标
	CRect rect;
	GetDlgItem(IDC_GAME_TIME)->GetWindowRect(&rect);//获取控件的屏幕坐标
	ScreenToClient(&rect);//转换为对话框上的客户坐标

	//获取内容
	CString strText;
	strText.Format(_T("%d"), m_GameProgress.GetPos());

	//欢迎语起点坐标(x,y)  (左上角)
	int x = rect.right + 10;
	int y = rect.top;
	//输出欢迎语
	dc.TextOutW(x, y, strText);

	
}



//判断胜负
void CGameDlg::JudgeWin()
{
	int bGamestatus = m_GameC.IsWin(m_GameProgress.GetPos());
	//判断是否继续游戏
	if (bGamestatus == GAME_PLAY) {
		return;
	}
	else {
		//游戏结束
		m_bPlaying = false;
		//关闭计时器
		KillTimer(1);
		if (bGamestatus == GAME_SUCCESS) {
			DrawWin();
		}
		else if (bGamestatus == GAME_LOSE) {
			//提示游戏失败
			CString strTitle;
			this->GetWindowTextW(strTitle);
			MessageBox(_T("很遗憾，时间到了"), strTitle);
		}

		// “开始游戏”按钮解除禁用
		((CButton*)GetDlgItem(IDC_BTN_START))->EnableWindow(true);
	}
}



//重排按钮
void CGameDlg::OnClickedBntReSet()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!m_bPlaying || m_bPause) {
		return;
	}

	m_GameC.Reset();

	m_GameProgress.OffsetPos(m_mode.cost);
	DrawGameTime();

	UpdateMap();
	InvalidateRect(m_rtGameRect, false);
}


//帮助按钮
void CGameDlg::OnClickedBtnHelp()
{
	// TODO: 在此添加控件通知处理程序代码
	// 
	//如果游戏进行中且未暂停--》暂停游戏
	if (m_bPlaying && !m_bPause) {
		OnClickedBtnStop();
	}

	//打开帮助信息
	CHelpDialog dlg;
	dlg.DoModal();
}


//提示按钮
void CGameDlg::OnClickedBtnPoint()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!m_bPlaying || m_bPause) {
		return;
	}

	Vertex avPath[4];
	int nVexnum = 0;
	if (m_GameC.Help(avPath, nVexnum)) {
		DrawTipFrame(avPath[0].row, avPath[0].col);   //第一个元素画框
		DrawTipFrame(avPath[nVexnum - 1].row, avPath[nVexnum - 1].col);  //第二个元素画框
		DrawTipLine(avPath, nVexnum);   //画线

		m_GameProgress.OffsetPos(m_mode.cost);
		DrawGameTime();
	}
}


void CGameDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (nIDEvent == PLAY_TIMER_ID && m_bPlaying && !m_bPause) {
		//游戏时间减一秒
		m_GameProgress.StepIt();
		//绘制当前秒数
		DrawGameTime();
		//判断是否结束
		JudgeWin();
	}

	CDialogEx::OnTimer(nIDEvent);
}


//暂停
void CGameDlg::OnClickedBtnStop()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!m_bPlaying) {
		return;
	}

	if (m_bPause) {
		//原状态游戏暂停-----继续游戏操作
		((CButton*)GetDlgItem(IDC_BTN_STOP))->SetWindowTextW(L"暂停游戏");
		UpdateMap();
	}
	else {
		//原状态游戏正在进行-----暂停操作
		m_dcMem.BitBlt(m_rtGameRect.left, m_rtGameRect.top, m_rtGameRect.Width(),
			m_rtGameRect.Height(), &m_dcPause, 0, 0, SRCCOPY);

		((CButton*)GetDlgItem(IDC_BTN_STOP))->SetWindowTextW(L"继续游戏");
	}
	InvalidateRect(m_rtGameRect, false);

	m_bPause = !m_bPause;
}
