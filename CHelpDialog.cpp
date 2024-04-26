// CHelpDialog.cpp: 实现文件
//

#include "pch.h"
#include "LianLianKan.h"
#include "afxdialogex.h"
#include "CHelpDialog.h"


// CHelpDialog 对话框

IMPLEMENT_DYNAMIC(CHelpDialog, CDialogEx)

CHelpDialog::CHelpDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_HELP, pParent)
{

}

CHelpDialog::~CHelpDialog()
{
}

void CHelpDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_SCROLLBAR_HELP, m_ScrollBar);
}


BEGIN_MESSAGE_MAP(CHelpDialog, CDialogEx)
	ON_WM_PAINT()
	ON_WM_VSCROLL()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CHelpDialog 消息处理程序


BOOL CHelpDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//设置对话框图标
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	SetIcon(m_hIcon, TRUE);    //设置大图标
	SetIcon(m_hIcon, FALSE);   //设置小图标

	GetClientRect(&m_rtHelp);  //获取对话框大小
	InitHelpPicture();
	InitScrollBar();


	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CHelpDialog::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	//绘制图片 
	dc.BitBlt(0, 0, m_rtHelp.Width(), m_rtHelp.Height(), &m_dcMem, 0, 0, SRCCOPY);
	// 不为绘图消息调用 CDialogEx::OnPaint()
}


void CHelpDialog::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	int pos = m_ScrollBar.GetScrollPos();
	
	switch (nSBCode) {
		case SB_LINEUP:      //点击向上
			pos --;
			break;
		case SB_LINEDOWN:      //点击向下
			pos ++;
			break;
		case SB_PAGEUP:      //向上翻页
			pos -= 10;
			break;
		case SB_PAGEDOWN:      //向下翻页
			pos += 10;
			break;
		case SB_TOP:          //顶部
			pos = 0;
			break;
		case SB_BOTTOM:      //底部
			pos = bmpMes.bmHeight - m_rtHelp.bottom + m_rtHelp.top;;
			break;
		case SB_THUMBPOSITION:    //点击滑块
			pos = nPos;
			break;
		default:
			break;
	}

	//设置滚动条当前值
	m_ScrollBar.SetScrollPos(pos, TRUE);
	//更新帮助信息
	UpdateHelp(pos);


	CDialogEx::OnVScroll(nSBCode, nPos, pScrollBar);
}


//初始化帮助图片
void CHelpDialog::InitHelpPicture()
{
	//获取当前设备环境
	CClientDC dc(this);

	//加载help图片
	HANDLE bHelp = ::LoadImageW(NULL, _T("theme\\picture\\basic_help.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	m_dcHelp.CreateCompatibleDC(&dc);
	m_dcHelp.SelectObject(bHelp);
	//获取位图信息
	GetObject(bHelp, sizeof(BITMAP), &bmpMes);

	//创建内存dc大小
	m_dcMem.CreateCompatibleDC(&dc);

	//初始化缓冲内存
	CBitmap bmpMem;
	bmpMem.CreateCompatibleBitmap(&dc, m_rtHelp.Width(), m_rtHelp.Height());
	m_dcMem.SelectObject(&bmpMem);

	//绘制白色背景
	m_dcMem.BitBlt(0, 0, m_rtHelp.Width(), m_rtHelp.Height(), NULL, 0, 0, WHITENESS);
	//绘制帮助图片到缓冲区
	m_dcMem.BitBlt(0, 0, m_rtHelp.Width(), m_rtHelp.Height(), &m_dcHelp, 0, 0, SRCCOPY);
}


//初始化滚动条
void CHelpDialog::InitScrollBar()
{
	m_ScrollBar.SetScrollRange(0, bmpMes.bmHeight - m_rtHelp.bottom + m_rtHelp.top);
	m_ScrollBar.SetScrollPos(0);
}

void CHelpDialog::UpdateHelp(int nPos)
{
	//绘制白色
	m_dcMem.BitBlt(m_rtHelp.left, m_rtHelp.top, m_rtHelp.Width(), m_rtHelp.Height(), NULL, 0, 0, WHITENESS);
	//绘制帮助信息
	m_dcMem.BitBlt(m_rtHelp.left, m_rtHelp.top, m_rtHelp.Width(), m_rtHelp.Height(), &m_dcHelp, 0, nPos, SRCCOPY);
	//更新界面
	InvalidateRect(m_rtHelp, FALSE);
}


HBRUSH CHelpDialog::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	if (pWnd->GetDlgCtrlID() == IDC_STATIC_COPYRIGHT) {
		COLORREF clr = RGB(255, 255, 255);
		pDC->SetBkColor(clr);
		HBRUSH bkBrush = ::CreateSolidBrush(clr);
		return bkBrush;
	}


	return hbr;
}
