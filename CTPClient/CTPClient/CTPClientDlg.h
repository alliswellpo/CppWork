
// CTPClientDlg.h : header file
#pragma once

#include "MdSpi.h"
#include "TraderSpi.h"

// CCTPClientDlg dialog
class CCTPClientDlg : public CDialogEx
{
// Construction
public:
	CCTPClientDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_CTPCLIENT_DIALOG };
	LRESULT CCTPClientDlg::OnRecvMdData(WPARAM wParam, LPARAM lParam);
	LRESULT CCTPClientDlg::OnRecvTraderData(WPARAM wParam, LPARAM lParam);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	static DWORD WINAPI CCTPClientDlg::CTPMdProc(LPVOID lpParameter);
	static DWORD WINAPI CCTPClientDlg::CTPTraderProc(LPVOID lpParameter);

// Implementation
protected:
	HICON m_hIcon;
	BOOL bConnected = false;
	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedInitConnect();
};
