#pragma once
#include "afxdialogex.h"


// CHelpDialog 对话框

class CHelpDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CHelpDialog)

public:
	CHelpDialog(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CHelpDialog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_HELP };
#endif

protected:
	HICON m_hIcon;    //系统图片
	CDC m_dcMem;      //内存dc
	CDC m_dcHelp;     //帮助图片dc
	CRect m_rtHelp;  //帮助图片显示工作区
	BITMAP bmpMes;   //图片信息

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CScrollBar m_ScrollBar;
	void InitHelpPicture();   //初始化帮助图片
	void InitScrollBar();     //初始化滚动条
	void UpdateHelp(int nPos);  //显示位置
};
