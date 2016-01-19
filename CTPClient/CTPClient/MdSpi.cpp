#pragma once

#include "stdafx.h"
#include "MdSpi.h"
#include "Log.h"

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

void CMdSpi::ReqUserLogin()
{
	//TThostFtdcBrokerIDType	BROKER_ID = "1026";				// �������
	//TThostFtdcInvestorIDType INVESTOR_ID = "00007085";		// Ͷ���ߴ���
	//TThostFtdcPasswordType  PASSWORD = "025918";			// �û�����

	TThostFtdcBrokerIDType	BROKER_ID = "8060";				// ���͹�˾����
	TThostFtdcInvestorIDType INVESTOR_ID = "99016869";		// Ͷ���ߴ���
	TThostFtdcPasswordType  PASSWORD = "722486";				// �û�����

	CThostFtdcReqUserLoginField req;
	memset(&req, 0, sizeof(req));
	strcpy(req.BrokerID, BROKER_ID);
	strcpy(req.UserID, INVESTOR_ID);
	strcpy(req.Password, PASSWORD);
	int iRequestID = time(NULL);
	int iResult = m_pMdUserApi->ReqUserLogin(&req, ++iRequestID);
	if (0 == iResult)
	{
		LOG("User Log in Successfully!");
	}
}

void CMdSpi::OnFrontConnected()
{
	LOG("MD Front Connect Successfully!");
	ReqUserLogin();

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
	LOG("HeartBeat Warning", nTimeLapse);
}

///��¼������Ӧ
void CMdSpi::OnRspUserLogin(CThostFtdcRspUserLoginField	*pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	if (bIsLast && !IsErrorRspInfo(pRspInfo))
	{
		///��ȡ��ǰ������
		LOG2("Current Trading Day", m_pMdUserApi->GetTradingDay());
		// ����������
		SubscribeMarketData();
		// ������ѯ��,ֻ�ܶ���֣������ѯ�ۣ�����������ͨ��traderapi��Ӧ�ӿڷ���
		SubscribeForQuoteRsp();
	}
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
	bool								bIsLast)
{
	LOG2("Successfully Subscribed instrument ", pSpecificInstrument->InstrumentID);
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
	char MarketData[256] = { 0 };
	double Ask = pDepthMarketData->AskPrice1;
	double Bid = pDepthMarketData->BidPrice1;
	if (Ask > 0.01 && Bid > 0.01 )
		sprintf_s(MarketData, "Quete %s: Ask = %.1lf, Bid = %.1lf", pDepthMarketData->InstrumentID, Bid, Ask);
	LOG(MarketData);
}

///ѯ��֪ͨ
void CMdSpi::OnRtnForQuoteRsp(CThostFtdcForQuoteRspField *pForQuoteRsp)
{
	LOG2("Subscribed Quote Response for InstrmentID: ", pForQuoteRsp->InstrumentID);
}

bool CMdSpi::IsErrorRspInfo(CThostFtdcRspInfoField *pRspInfo)
{
	bool bResult = ((pRspInfo) && (pRspInfo->ErrorID != 0));
	if (bResult)
	{
		char err[100] = { 0 };
		sprintf(err, "ErrorID=%d, ErrorMsg=%s", pRspInfo->ErrorID, pRspInfo->ErrorMsg);
		LOG(err);
	}
	return bResult;
}

void CMdSpi::SubscribeMarketData()
{
	char *ppInstrumentID[] = { "IF1602", "IF1603", "m1605"};			// ���鶩���б�
	int iInstrumentID = 3;
	int iResult = m_pMdUserApi->SubscribeMarketData(ppInstrumentID, iInstrumentID);
	if (0 == iResult)
	{
		LOG("Subscirbe market data Successfully!");
	}
	//cerr << "--->>> �������鶩������: " << ((iResult == 0) ? "�ɹ�" : "ʧ��") << endl;
}

void CMdSpi::SubscribeForQuoteRsp()
{
	char *ppInstrumentID[] = { "IF1602", "IF1603", "m1605"};			// ���鶩���б�
	int iInstrumentID = 3;
	int iResult = m_pMdUserApi->SubscribeForQuoteRsp(ppInstrumentID, iInstrumentID);
	if (0 == iResult)
	{
		LOG("Subscirbe Quote Info Successfully!");
	}
}