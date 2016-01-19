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
	//TThostFtdcBrokerIDType	BROKER_ID = "1026";				// 申银万国
	//TThostFtdcInvestorIDType INVESTOR_ID = "00007085";		// 投资者代码
	//TThostFtdcPasswordType  PASSWORD = "025918";			// 用户密码

	TThostFtdcBrokerIDType	BROKER_ID = "8060";				// 经纪公司代码
	TThostFtdcInvestorIDType INVESTOR_ID = "99016869";		// 投资者代码
	TThostFtdcPasswordType  PASSWORD = "722486";				// 用户密码

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

///当客户端与交易后台通信连接断开时，该方法被调用。当发生这个情况后，API会自动重新连接，客户端可不做处理。
///@param nReason 错误原因
///        0x1001 网络读失败
///        0x1002 网络写失败
///        0x2001 接收心跳超时
///        0x2002 发送心跳失败
///        0x2003 收到错误报文
void CMdSpi::OnFrontDisconnected(int nReason)
{

}

///心跳超时警告。当长时间未收到报文时，该方法被调用。
///@param nTimeLapse 距离上次接收报文的时间
void CMdSpi::OnHeartBeatWarning(int nTimeLapse)
{
	LOG("HeartBeat Warning", nTimeLapse);
}

///登录请求响应
void CMdSpi::OnRspUserLogin(CThostFtdcRspUserLoginField	*pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	if (bIsLast && !IsErrorRspInfo(pRspInfo))
	{
		///获取当前交易日
		LOG2("Current Trading Day", m_pMdUserApi->GetTradingDay());
		// 请求订阅行情
		SubscribeMarketData();
		// 请求订阅询价,只能订阅郑商所的询价，其他交易所通过traderapi相应接口返回
		SubscribeForQuoteRsp();
	}
}

///登出请求响应
void CMdSpi::OnRspUserLogout(CThostFtdcUserLogoutField	*pUserLogout,
							CThostFtdcRspInfoField		*pRspInfo,
							int							nRequestID,
							bool						bIsLast)
{

}

///错误应答
void CMdSpi::OnRspError(CThostFtdcRspInfoField	*pRspInfo,
	int						nRequestID,
	bool						bIsLast)
{

}

///订阅行情应答
void CMdSpi::OnRspSubMarketData(CThostFtdcSpecificInstrumentField	*pSpecificInstrument,
	CThostFtdcRspInfoField				*pRspInfo,
	int									nRequestID,
	bool								bIsLast)
{
	LOG2("Successfully Subscribed instrument ", pSpecificInstrument->InstrumentID);
}

///取消订阅行情应答
void CMdSpi::OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField	*pSpecificInstrument,
	CThostFtdcRspInfoField				*pRspInfo,
	int								nRequestID,
	bool								bIsLast)
{

}

///订阅询价应答
void CMdSpi::OnRspSubForQuoteRsp(CThostFtdcSpecificInstrumentField *pSpecificInstrument,
	CThostFtdcRspInfoField *pRspInfo,
	int nRequestID, bool bIsLast)
{

}

///取消订阅询价应答
void CMdSpi::OnRspUnSubForQuoteRsp(CThostFtdcSpecificInstrumentField *pSpecificInstrument,
	CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{

}

///深度行情通知
void CMdSpi::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData)
{
	char MarketData[256] = { 0 };
	double Ask = pDepthMarketData->AskPrice1;
	double Bid = pDepthMarketData->BidPrice1;
	if (Ask > 0.01 && Bid > 0.01 )
		sprintf_s(MarketData, "Quete %s: Ask = %.1lf, Bid = %.1lf", pDepthMarketData->InstrumentID, Bid, Ask);
	LOG(MarketData);
}

///询价通知
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
	char *ppInstrumentID[] = { "IF1602", "IF1603", "m1605"};			// 行情订阅列表
	int iInstrumentID = 3;
	int iResult = m_pMdUserApi->SubscribeMarketData(ppInstrumentID, iInstrumentID);
	if (0 == iResult)
	{
		LOG("Subscirbe market data Successfully!");
	}
	//cerr << "--->>> 发送行情订阅请求: " << ((iResult == 0) ? "成功" : "失败") << endl;
}

void CMdSpi::SubscribeForQuoteRsp()
{
	char *ppInstrumentID[] = { "IF1602", "IF1603", "m1605"};			// 行情订阅列表
	int iInstrumentID = 3;
	int iResult = m_pMdUserApi->SubscribeForQuoteRsp(ppInstrumentID, iInstrumentID);
	if (0 == iResult)
	{
		LOG("Subscirbe Quote Info Successfully!");
	}
}