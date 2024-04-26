﻿
// LianLianKanDlg.h: 头文件
//

#pragma once


// CLianLianKanDlg 对话框
class CLianLianKanDlg : public CDialogEx
{
// 构造
public:
	CLianLianKanDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LIANLIANKAN_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	CDC m_dcMem;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	void InitBackground();  //初始化背景
public:
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton1();

	afx_msg void OnClickedBtnBasic();     //基础模式
	afx_msg void OnBnClickedBtnRelax();   //休闲模式
	afx_msg void OnBnClickedBntHelp();    //帮助
};
