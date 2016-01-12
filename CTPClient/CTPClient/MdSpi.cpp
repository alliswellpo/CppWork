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
}

///登录请求响应
void CMdSpi::OnRspUserLogin(CThostFtdcRspUserLoginField	*pRspUserLogin,
	CThostFtdcRspInfoField		*pRspInfo,
	int							nRequestID,
	bool							bIsLast)
{

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
	bool									bIsLast)
{

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

}

///询价通知
void CMdSpi::OnRtnForQuoteRsp(CThostFtdcForQuoteRspField *pForQuoteRsp)
{

}