#pragma once

#include "stdafx.h"
#include "MdSpi.h"

void CMdSpi::OnFrontConnected()
{
	char msg[] = "Connect Successfully!!";
	Prices* price = new Prices();
	price->ask = 0.0;
	price->bid = 0.0;
	
	// Synchronous 
	::SendMessage(m_hwnd, WM_RECVDATA, 0, (LPARAM)price);
	::SendMessage(m_hwnd, WM_RECVDATA, 1, (LPARAM)msg);

	// Asynchronous
	//::PostMessage(m_hwnd, WM_RECVDATA, 0, (LPARAM)price);
	//::PostMessage(m_hwnd, WM_RECVDATA, 1, (LPARAM)msg);
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