#pragma once

#include "stdafx.h"
#include "MdSpi.h"
#include "Log.h"

int iInstrumentID = 459;
char *ppInstrumentID[] = {
	//Shanghai
	"ag1602", "ag1603", "ag1604", "ag1605", "ag1606", "ag1607", "ag1608", "ag1609", "ag1610", "ag1611", "ag1612", "ag1701",
	"al1602", "al1603", "al1604", "al1605", "al1606", "al1607", "al1608", "al1609", "al1610", "al1611", "al1612", "al1701",
	"au1602", "au1603", "au1604", "au1606", "au1608", "au1610", "au1612", "au1702",
	"bu1602", "bu1603", "bu1604", "bu1605", "bu1606", "bu1607", "bu1609", "bu1612", "bu1703", "bu1706", "bu1709", "bu1712",
	"cu1602", "cu1603", "cu1604", "cu1605", "cu1606", "cu1607", "cu1608", "cu1609", "cu1610", "cu1611", "cu1612", "cu1701",
	"fu1603", "fu1604", "fu1605", "fu1606", "fu1607", "fu1608", "fu1609", "fu1610", "fu1611", "fu1612",
	"hc1602", "hc1603", "hc1604", "hc1605", "hc1606", "hc1607", "hc1608", "hc1609", "hc1610", "hc1611", "hc1612", "hc1701",
	"im1601", "im1602", "im1603", "im1606", "im1609",
	"ni1602", "ni1603", "ni1604", "ni1605", "ni1606", "ni1607", "ni1608", "ni1609", "ni1610", "ni1611", "ni1612", "ni1701",
	"pb1602", "pb1603", "pb1604", "pb1605", "pb1606", "pb1607", "pb1608", "pb1609", "pb1610", "pb1611", "pb1612", "pb1701",
	"rb1602", "rb1603", "rb1604", "rb1605", "rb1606", "rb1607", "rb1608", "rb1609", "rb1610", "rb1611", "rb1612", "rb1701",
	"ru1603", "ru1604", "ru1605", "ru1606", "ru1607", "ru1608", "ru1609", "ru1610", "ru1611", "ru1701",
	"sn1602", "sn1603", "sn1604", "sn1605", "sn1606", "sn1607", "sn1608", "sn1609", "sn1610", "sn1611", "sn1612", "sn1701",
	"wr1602", "wr1603", "wr1604", "wr1605", "wr1606", "wr1607", "wr1608", "wr1609", "wr1610", "wr1611", "wr1612", "wr1701",
	"zn1602", "zn1603", "zn1604", "zn1605", "zn1606", "zn1607", "zn1608", "zn1609", "zn1610", "zn1611", "zn1612", "zn1701",
	//Dalian
	"a1603", "a1605", "a1607", "a1609", "a1611", "a1701", "a1703", "a1705", "a1707",
	"b1603", "b1605", "b1607", "b1609", "b1611", "b1701",
	"bb1602", "bb1603", "bb1604", "bb1605", "bb1606", "bb1607", "bb1608", "bb1609", "bb1610", "bb1611", "bb1612", "bb1701",
	"c1603", "c1605", "c1607", "c1609", "c1611", "c1701",
	"cs1603", "cs1605", "cs1607", "cs1609", "cs1611", "cs1701",
	"fb1602", "fb1603", "fb1604", "fb1605", "fb1606", "fb1607", "fb1608", "fb1609", "fb1610", "fb1611", "fb1612", "fb1701",
	"i1602", "i1603", "i1604", "i1605", "i1606", "i1607", "i1608", "i1609", "i1610", "i1611", "i1612", "i1701",
	"j1602", "j1603", "j1604", "j1605", "j1606", "j1607", "j1608", "j1609", "j1610", "j1611", "j1612", "j1701",
	"jd1602", "jd1603", "jd1604", "jd1605", "jd1606", "jd1609", "jd1610", "jd1611", "jd1612", "jd1701",
	"jm1602", "jm1603", "jm1604", "jm1605", "jm1606", "jm1607", "jm1608", "jm1609", "jm1610", "jm1611", "jm1612", "jm1701",
	"l1602", "l1603", "l1604", "l1605", "l1606", "l1607", "l1608", "l1609", "l1610", "l1611", "l1612", "l1701",
	"m1603", "m1605", "m1607", "m1608", "m1609", "m1611", "m1612", "m1701",
	"p1602", "p1603", "p1604", "p1605", "p1606", "p1607", "p1608", "p1609", "p1610", "p1611", "p1612", "p1701",
	"pp1602", "pp1603", "pp1604", "pp1605", "pp1606", "pp1607", "pp1608", "pp1609", "pp1610", "pp1611", "pp1612", "pp1701",
	"v1602", "v1603", "v1604", "v1605", "v1606", "v1607", "v1608", "v1609", "v1610", "v1611", "v1612", "v1701",
	"y1603", "y1605", "y1607", "y1608", "y1609", "y1611", "y1612", "y1701",
	//Zhenzhou
	"CF603", "CF605", "CF607", "CF609", "CF611", "CF701",
	"FG602", "FG603", "FG604", "FG605", "FG606", "FG607", "FG608", "FG609", "FG610", "FG611", "FG612", "FG701",
	"JR603", "JR605", "JR607", "JR609", "JR611", "JR701",
	"LR603", "LR605", "LR607", "LR609", "LR611", "LR701",
	"MA602", "MA603", "MA604", "MA605", "MA606", "MA607", "MA608", "MA609", "MA610", "MA611", "MA612", "MA701",
	"OI603", "OI605", "OI607", "OI609", "OI611", "OI701",
	"PM603", "PM605", "PM607", "PM609", "PM611", "PM701",
	"RI603", "RI605", "RI607", "RI609", "RI611", "RI701",
	"RM603", "RM605", "RM607", "RM608", "RM609", "RM611", "RM701",
	"RS607", "RS608", "RS609", "RS611",
	"SF602", "SF603", "SF604", "SF605", "SF606", "SF607", "SF608", "SF609", "SF610", "SF611", "SF612", "SF701",
	"SM602", "SM603", "SM604", "SM605", "SM606", "SM607", "SM608", "SM609", "SM610", "SM611", "SM612", "SM701",
	"SR603", "SR605", "SR607", "SR609", "SR611", "SR701", "SR703", "SR705", "SR707",
	"TA602", "TA603", "TA604", "TA605", "TA606", "TA607", "TA608", "TA609", "TA610", "TA611", "TA612", "TA701",
	"TC602", "TC603", "TC604",
	"WH603", "WH605", "WH607", "WH609", "WH611", "WH701",
	"ZC605", "ZC606", "ZC607", "ZC608", "ZC609", "ZC610", "ZC611", "ZC612", "ZC701"
};

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
	char MarketData[80] = { 0 };
	double Ask = pDepthMarketData->AskPrice1;
	double Bid = pDepthMarketData->BidPrice1;
	double Price = pDepthMarketData->LastPrice;
	double Close = pDepthMarketData->ClosePrice;
	if ((Ask > 0.01 && Ask < 9999999) && (Bid > 0.01 && Bid < 9999999) /*&& Price>0 && Price<9999999*/)
	//if (Close<999999 && Close >0)
	{
		/*Price = %.1lf,*/
		sprintf_s(MarketData, "Quote of %s: Ask = %.1lf, Bid = %.1lf", pDepthMarketData->InstrumentID, Ask, Bid);
		//sprintf_s(MarketData, "Close Price of %s: Clsoe = %.1lf", pDepthMarketData->InstrumentID, Close);
		LOG(MarketData);
	}
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
	int iResult = m_pMdUserApi->SubscribeMarketData(ppInstrumentID, iInstrumentID);
	if (0 == iResult)
	{
		LOG("Subscirbe market data Successfully!");
	}
	//cerr << "--->>> 发送行情订阅请求: " << ((iResult == 0) ? "成功" : "失败") << endl;
}

void CMdSpi::SubscribeForQuoteRsp()
{
	int iResult = m_pMdUserApi->SubscribeForQuoteRsp(ppInstrumentID, iInstrumentID);
	if (0 == iResult)
	{
		LOG("Subscirbe Quote Info Successfully!");
	}
}