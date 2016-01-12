// ForexHedgingMT4vsMT4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <winsock2.h>
#include <errno.h>
#include <time.h>
#include <sys/timeb.h>
#include <vector>
#include <list>
#include <fstream>

#pragma comment(lib, "ws2_32.lib") 
using namespace std;

struct Prices
{
	string symbol = "";
	float bid = 0.0;
	float ask = 0.0;
	long long tmstamp = 0;
};

struct LogInfo
{
	float bidMT4_1 = 0.0;
	float askMT4_1 = 0.0;
	long long tmstampMT4_1 = 0;

	float bidMT4_2 = 0.0;
	float askMT4_2 = 0.0;
	long long tmstampMT4_2 = 0;
};

int _tmain(int argc, _TCHAR* argv[])
{
	struct timeb tm_cur;
	long long tmstamp;

	ftime(&tm_cur);
	tmstamp = tm_cur.time * 1000 + tm_cur.millitm;
	char fname[22] = "\0";
	sprintf(fname, "%lld.txt", tmstamp);
	ofstream flog(fname, ios::out);
	if (flog.is_open())
		flog << "MT4 VS MT4\n";
	flog.flush();
	

	WSADATA wsaData;
	WORD sockVersion = MAKEWORD(2, 2);
	if (WSAStartup(sockVersion, &wsaData) != 0)
	{
		return 0;
	}

	SOCKET srvSocketMT4_1 = socket(AF_INET, SOCK_DGRAM, 0);
	SOCKET srvSocketMT4_2 = socket(AF_INET, SOCK_DGRAM, 0);
	if (srvSocketMT4_1 == INVALID_SOCKET || srvSocketMT4_2 == INVALID_SOCKET)
	{
		printf("socket error !");
		return 0;
	}

	sockaddr_in srvAddrMT4_1, srvAddrMT4_2;
	srvAddrMT4_1.sin_family = AF_INET;
	srvAddrMT4_1.sin_port = htons(6001);
	srvAddrMT4_1.sin_addr.S_un.S_addr = INADDR_ANY;

	srvAddrMT4_2.sin_family = AF_INET;
	srvAddrMT4_2.sin_port = htons(6002);
	srvAddrMT4_2.sin_addr.S_un.S_addr = INADDR_ANY;

	if (bind(srvSocketMT4_1, (sockaddr *)&srvAddrMT4_1, sizeof(srvAddrMT4_1)) == SOCKET_ERROR ||
		bind(srvSocketMT4_2, (sockaddr *)&srvAddrMT4_2, sizeof(srvAddrMT4_2)) == SOCKET_ERROR)
	{
		printf("bind error !");
		closesocket(srvSocketMT4_1);
		closesocket(srvSocketMT4_2);
		return 0;
	}

	sockaddr_in clientAddr;
	clientAddr.sin_family = AF_INET;
	clientAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");;
	int nAddrLen = sizeof(clientAddr);

	int iMode = 1; //0£º×èÈû
	ioctlsocket(srvSocketMT4_1, FIONBIO, (u_long FAR*) &iMode);//·Ç×èÈûÉèÖÃ
	ioctlsocket(srvSocketMT4_2, FIONBIO, (u_long FAR*) &iMode);//·Ç×èÈûÉèÖÃ
	
	Prices price_MT4_1, price_MT4_2;
	Prices oldprice_MT4_1, oldprice_MT4_2;
	vector<char*> vecPrices_1, vecPrices_2;
	list<LogInfo> lsLogInfo;
	const char *split = ",  ";
	
	while (true)
	{
		char recvDataMT4_1[255];
		char recvDataMT4_2[255];
		char converteddata_MT4_1[255] = { '\0' };
		char converteddata_MT4_2[255] = { '\0' };
		memset(recvDataMT4_1, 0, 255);
		int ret1 = recvfrom(srvSocketMT4_1, recvDataMT4_1, 255, 0, (sockaddr *)&clientAddr, &nAddrLen);
		int ret2 = recvfrom(srvSocketMT4_2, recvDataMT4_2, 255, 0, (sockaddr *)&clientAddr, &nAddrLen);
		if (ret1 > 0)
		{
			ftime(&tm_cur);
			tmstamp = tm_cur.time * 1000 + tm_cur.millitm;
			
			for (int i = 0, j = 0; j < 200; i++, j = j + 2)
			{
				converteddata_MT4_1[i] = recvDataMT4_1[j];
			}
			//printf("%s: \r\n", inet_ntoa(clientAddr.sin_addr));
			printf("%s: \r\n", converteddata_MT4_1);
			const char *split = ",  ";
			char *p;
			p = strtok(converteddata_MT4_1, split);
			while (p != NULL) 
			{
				vecPrices_1.push_back(p);
				p = strtok(NULL, split);
			}
			memcpy(&oldprice_MT4_1, &price_MT4_1, sizeof(Prices));
			price_MT4_1.symbol.assign(vecPrices_1[0], 0, 6);
			price_MT4_1.bid = atof(vecPrices_1[1]);
			price_MT4_1.ask = atof(vecPrices_1[2]);
			price_MT4_1.tmstamp = tmstamp;
			vecPrices_1.clear();
		}
		if (ret2 > 0)
		{
			ftime(&tm_cur);
			tmstamp = tm_cur.time * 1000 + tm_cur.millitm;

			for (int i = 0, j = 0; j < 200; i++, j = j + 2)
			{
				converteddata_MT4_2[i] = recvDataMT4_2[j];
			}
			//printf("%s: \r\n", inet_ntoa(clientAddr.sin_addr));
			printf("%s: \r\n", converteddata_MT4_2);
			
			char *p;
			p = strtok(converteddata_MT4_2, split);
			while (p != NULL)
			{
				vecPrices_2.push_back(p);
				p = strtok(NULL, split);
			}
			memcpy(&oldprice_MT4_2, &price_MT4_2, sizeof(Prices));
			price_MT4_2.symbol.assign(vecPrices_2[0], 0, 6);
			price_MT4_2.bid = atof(vecPrices_2[1]);
			price_MT4_2.ask = atof(vecPrices_2[2]);
			price_MT4_2.tmstamp = tmstamp;
			vecPrices_2.clear();
		}
		if (ret1 > 0 || ret2 > 0)
		{
			if(price_MT4_1.bid == oldprice_MT4_1.bid && price_MT4_1.ask == oldprice_MT4_1.ask)
				continue;
			if(price_MT4_2.bid == oldprice_MT4_2.bid && price_MT4_2.ask == oldprice_MT4_2.ask)
				continue;
			if (price_MT4_1.tmstamp == 0 || price_MT4_2.tmstamp == 0)
				continue;
			if (price_MT4_1.tmstamp - price_MT4_2.tmstamp >= 100 ||
				price_MT4_2.tmstamp - price_MT4_1.tmstamp >= 100)
				continue;
			
			//if (price_MT4_1.bid > price_MT4_2.ask || price_MT4_1.ask < price_MT4_2.bid)
			//{
				LogInfo logInfo;
				logInfo.askMT4_1 = price_MT4_1.ask;
				logInfo.bidMT4_1 = price_MT4_1.bid;
				logInfo.askMT4_2 = price_MT4_2.ask;
				logInfo.bidMT4_2 = price_MT4_2.bid;
				logInfo.tmstampMT4_1 = price_MT4_1.tmstamp;
				logInfo.tmstampMT4_2 = price_MT4_2.tmstamp;
				lsLogInfo.push_back(logInfo);
			//}
			if (lsLogInfo.size() == 5)
			{
				char s[255] = "\0";
				for (auto it = lsLogInfo.begin(); it != lsLogInfo.end(); it++)
				{
					long long ts = ((*it).tmstampMT4_1 >= (*it).tmstampMT4_2) ? (*it).tmstampMT4_2 : (*it).tmstampMT4_1;
					float bidMT4_1 = (*it).bidMT4_1;
					float bidMT4_2 = (*it).bidMT4_2;
					float askMT4_1 = (*it).askMT4_1;
					float askMT4_2 = (*it).askMT4_2;
					sprintf(s, "%lld >> bidMT4_1=%.5f <==> askMT4_1=%.5f   ||   ", ts, bidMT4_1, askMT4_1);
					flog << s;
					sprintf(s, "askMT4_2=%.5f <==> bidMT4_2=%.5f\n", askMT4_2, bidMT4_2);
					flog << s;
					if (askMT4_1 < bidMT4_2)
					{
						sprintf(s, "%lld >> bidMT4_2=%.5f - askMT4_1=%.5f = %.1f\n", ts, bidMT4_2, askMT4_1,
							(bidMT4_2 - askMT4_1) * 10000);
						flog << s;
					}
					if (askMT4_2 < bidMT4_1)
					{
						sprintf(s, "%lld >> bidMT4_1=%.5f - askMT4_2=%.5f = %.1f\n", ts, bidMT4_1, askMT4_2,
							(bidMT4_1 - askMT4_2) * 10000);
						flog << s;
					}
					flog.flush();
				}

				lsLogInfo.clear();
			}
		}
		Sleep(1);

	}
	flog.close();
	closesocket(srvSocketMT4_1);
	closesocket(srvSocketMT4_2);
	WSACleanup();
	return 0;
}

