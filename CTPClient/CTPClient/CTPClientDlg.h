
// CTPClientDlg.h : header file
#pragma once

#include "MdSpi.h"

// CCTPClientDlg dialog
class CCTPClientDlg : public CDialogEx
{
// Construction
public:
	CCTPClientDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_CTPCLIENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support



// Implementation
protected:
	HICON m_hIcon;
	CThostFtdcMdApi *pUserApi;
	CThostFtdcMdSpi *pUserSpi;
	BOOL bConnected = false;
	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedInitConnect();
};
