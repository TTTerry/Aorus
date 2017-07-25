#pragma once

class CShareMemory
{
public:
	CShareMemory(void);
	~CShareMemory(void);

	bool Init(LPCWSTR sMutex, LPCWSTR sShmName, int nMemSize, bool bOpen = false);
	void Free();
	void Write(void* pMem);
	void Read(void* pMem);

private:
	HANDLE	m_hDataLock;
	HANDLE  m_hFileMapping;
	char*   m_pSharedBlock;
	int		m_nMemSize;

};

class CShareRestrictedSD  
{
public:
	CShareRestrictedSD();
	virtual ~CShareRestrictedSD();

	SECURITY_ATTRIBUTES* GetSA();

protected:
	PVOID  ptr;
	SECURITY_ATTRIBUTES sa;
	SECURITY_DESCRIPTOR sd;
};
