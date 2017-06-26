
// MFCApplication6Dlg.h : 头文件
//

#pragma once
#include "afxbutton.h"
#include "afxwin.h"


// CMFCApplication6Dlg 对话框
class CMFCApplication6Dlg : public CDialogEx
{
// 构造
public:
	CMFCApplication6Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION6_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CMFCButton m1;
	afx_msg void OnBnClickedMfcbutton1();
	CButton m_1;
	afx_msg void OnBnClickedButton1();
	CButton m2;
	afx_msg void OnBnClickedButton2();
	CButton m3;
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	CButton m4;
	CButton m5;
	CButton m6;
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton5();
	CButton m7;
	CButton m8;
	afx_msg void OnBnClickedButton7();
};
