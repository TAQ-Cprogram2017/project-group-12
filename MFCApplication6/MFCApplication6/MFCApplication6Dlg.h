
// MFCApplication6Dlg.h : ͷ�ļ�
//

#pragma once
#include "afxbutton.h"
#include "afxwin.h"


// CMFCApplication6Dlg �Ի���
class CMFCApplication6Dlg : public CDialogEx
{
// ����
public:
	CMFCApplication6Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION6_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
