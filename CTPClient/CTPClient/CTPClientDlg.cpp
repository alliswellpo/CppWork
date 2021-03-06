
// CTPClientDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CTPClient.h"
#include "CTPClientDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCTPClientDlg dialog

CCTPClientDlg::CCTPClientDlg(CWnd* pParent /*=NULL*/)
: CDialogEx(CCTPClientDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCTPClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCTPClientDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_INIT_CONNECT, &CCTPClientDlg::OnBnClickedInitConnect)
	ON_MESSAGE(WM_RECTRADERVDATA, &OnRecvTraderData)
END_MESSAGE_MAP()


// CCTPClientDlg message handlers

BOOL CCTPClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCTPClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCTPClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CCTPClientDlg::OnBnClickedInitConnect()
{

	// TODO: Add your control notification handler code here
	if (!bConnected)
	{
		HANDLE hThreadMd = CreateThread(NULL, 0, CTPMdProc, (LPVOID)m_hWnd, 0, NULL);
		HANDLE hThreadTrader = CreateThread(NULL, 0, CTPTraderProc, (LPVOID)m_hWnd, 0, NULL);
		bConnected = true;
	}
	else
	{
		CString str = _T("Already connected!!");
		MessageBox(str);
	}
}

DWORD WINAPI CCTPClientDlg::CTPMdProc(LPVOID lpParameter)
{
	CThostFtdcMdApi *pUserMdApi = CThostFtdcMdApi::CreateFtdcMdApi("", true, false);
	CThostFtdcMdSpi *pUserMdSpi = new CMdSpi((HWND)lpParameter, pUserMdApi);
	//char FRONT_ADDR[] = "tcp://asp-sim2-md1.financial-trading-platform.com:26213"; //上期模拟
	char FRONT_ADDR[] = "tcp://180.166.65.114:41213"; //招商证券
	//char FRONT_ADDR[] = "tcp://222.66.235.70:61213";//申银万国
	pUserMdApi->RegisterSpi(pUserMdSpi);
	pUserMdApi->RegisterFront(FRONT_ADDR);
	pUserMdApi->Init();
	pUserMdApi->Join();
	return 0;
}

DWORD WINAPI CCTPClientDlg::CTPTraderProc(LPVOID lpParameter)
{
	CThostFtdcTraderApi *pUserTraderApi = CThostFtdcTraderApi::CreateFtdcTraderApi();
	CThostFtdcTraderSpi *pUserTraderSpi = new CTraderSpi((HWND)lpParameter, pUserTraderApi);
	//char FRONT_ADDR[] = "tcp://asp-sim2-front1.financial-trading-platform.com:26205"; //上期模拟
	char FRONT_ADDR[] = "tcp://180.166.65.114:41205";  //招商证券
	//char FRONT_ADDR[] = "tcp://222.66.235.70:61205"; //申银万国
	pUserTraderApi->RegisterSpi((CThostFtdcTraderSpi*)pUserTraderSpi);	// 注册事件类
	pUserTraderApi->SubscribePublicTopic(THOST_TERT_QUICK);				// 注册公有流
	pUserTraderApi->SubscribePrivateTopic(THOST_TERT_QUICK);			// 注册私有流
	pUserTraderApi->RegisterFront(FRONT_ADDR);							// connect
	pUserTraderApi->Init();
	pUserTraderApi->Join();
	return 0;
}

LRESULT CCTPClientDlg::OnRecvMdData(WPARAM wParam, LPARAM lParam)
{
	if (wParam == 0)
	{
		Prices* price = (Prices*)(lParam);
	}
	else if (wParam == 1)
	{
		CString str = (char*)lParam;
		MessageBox(str);
	}
	return TRUE;
}

LRESULT CCTPClientDlg::OnRecvTraderData(WPARAM wParam, LPARAM lParam)
{
	if (wParam == 0)
	{
		Prices* price = (Prices*)(lParam);
	}
	else if (wParam == 1)
	{
		CString str = (char*)lParam;
		MessageBox(str);
	}
	return TRUE;
}
