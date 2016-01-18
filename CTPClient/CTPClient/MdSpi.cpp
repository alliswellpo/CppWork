#pragma once

#include "stdafx.h"
#include "MdSpi.h"

CMdSpi::CMdSpi(HWND hwnd, CThostFtdcMdApi *pMdUserApi)
{
	m_hwnd = hwnd;
	m_pMdUserApi = pMdUserApi;
}
CMdSpi::~CMdSpi()
{
	if (m_pMdUserApi)
	{
		m_pMdUserApi->RegisterSpi(NULL);
		m_pMdUserApi->Release();
		m_pMdUserApi = NULL;
	}
}

void CMdSpi::OnFrontConnected()
{
	::AfxMessageBox("MD Front Connect Successfully!");
}

///���ͻ����뽻�׺�̨ͨ�����ӶϿ�ʱ���÷��������á���������������API���Զ��������ӣ��ͻ��˿ɲ�������
///@param nReason ����ԭ��
///        0x1001 �����ʧ��
///        0x1002 ����дʧ��
///        0x2001 ����������ʱ
///        0x2002 ��������ʧ��
///        0x2003 �յ�������
void CMdSpi::OnFrontDisconnected(int nReason)
{

}

///������ʱ���档����ʱ��δ�յ�����ʱ���÷��������á�
///@param nTimeLapse �����ϴν��ձ��ĵ�ʱ��
void CMdSpi::OnHeartBeatWarning(int nTimeLapse)
{
}

///��¼������Ӧ
void CMdSpi::OnRspUserLogin(CThostFtdcRspUserLoginField	*pRspUserLogin,
	CThostFtdcRspInfoField		*pRspInfo,
	int							nRequestID,
	bool							bIsLast)
{

}

///�ǳ�������Ӧ
void CMdSpi::OnRspUserLogout(CThostFtdcUserLogoutField	*pUserLogout,
	CThostFtdcRspInfoField		*pRspInfo,
	int							nRequestID,
	bool						bIsLast)
{

}

///����Ӧ��
void CMdSpi::OnRspError(CThostFtdcRspInfoField	*pRspInfo,
	int						nRequestID,
	bool						bIsLast)
{

}

///��������Ӧ��
void CMdSpi::OnRspSubMarketData(CThostFtdcSpecificInstrumentField	*pSpecificInstrument,
	CThostFtdcRspInfoField				*pRspInfo,
	int									nRequestID,
	bool									bIsLast)
{

}

///ȡ����������Ӧ��
void CMdSpi::OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField	*pSpecificInstrument,
	CThostFtdcRspInfoField				*pRspInfo,
	int								nRequestID,
	bool								bIsLast)
{

}

///����ѯ��Ӧ��
void CMdSpi::OnRspSubForQuoteRsp(CThostFtdcSpecificInstrumentField *pSpecificInstrument,
	CThostFtdcRspInfoField *pRspInfo,
	int nRequestID, bool bIsLast)
{

}

///ȡ������ѯ��Ӧ��
void CMdSpi::OnRspUnSubForQuoteRsp(CThostFtdcSpecificInstrumentField *pSpecificInstrument,
	CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{

}

///�������֪ͨ
void CMdSpi::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData)
{

}

///ѯ��֪ͨ
void CMdSpi::OnRtnForQuoteRsp(CThostFtdcForQuoteRspField *pForQuoteRsp)
{

}