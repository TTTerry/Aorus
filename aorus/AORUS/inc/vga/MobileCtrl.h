#pragma once
#include "../socketapp/SocketApp.h"
class CMobileCtrl
{
public:
    CMobileCtrl();
    ~CMobileCtrl();
	void init();
	void syncLedState();
	void monitor();
protected:
	static UINT ListenThread(LPVOID lpParam);
	void GetCmd(const char* szData, CString sRecvIP);
private:
	CSocketApp m_listener;
	int m_nConenectIpCount;
	CString csIp[10];
};