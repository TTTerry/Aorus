#ifndef _UI_CHOOK_H
#define _UI_CHOOK_H


class CHook
{
public:
	static BOOL    HookFunction();            //Hook API function BeginPaint() and EndPaint() to paint the window to our DC.
	static void    SetPaintDC(HDC hdc);       //DC we want to paint.

	//do not call them!!!
public:
	static HDC     CALLBACK MY_BeginPaint(HWND hWnd, /*handle to window*/ LPPAINTSTRUCT lpPaint /*paint information*/);
	static BOOL    CALLBACK MY_EndPaint(HWND hWnd,   /*handle to window*/ CONST PAINTSTRUCT *lpPaint  /* paint data*/);

private:
	static HDC     m_hPaintDC;     
	static LPVOID  m_pOldBeginPaint;
	static LPVOID  m_pNewBeginPaint;
	static LPVOID  m_pOldEndPaint;
	static LPVOID  m_pNewEndPaint;
	static DWORD   m_dwOffBeginPaint;
	static DWORD   m_dwOffEndPaint;
};


//---------------------------------------------------------------------------------
DWORD  CHook::m_dwOffBeginPaint = 0;
DWORD  CHook::m_dwOffEndPaint   = 0;
HDC    CHook::m_hPaintDC        = NULL;     
LPVOID CHook::m_pOldBeginPaint  = NULL;
LPVOID CHook::m_pNewBeginPaint  = NULL;
LPVOID CHook::m_pOldEndPaint    = NULL;
LPVOID CHook::m_pNewEndPaint    = NULL;
//---------------------------------------------------------------------------------
void CHook::SetPaintDC(HDC hdc)
{
	m_hPaintDC = hdc;
}
//---------------------------------------------------------------------------------
BOOL CHook::HookFunction()
{
	if(m_dwOffBeginPaint != 0 && m_dwOffEndPaint != 0)
	{
		return TRUE;
	}

	HMODULE hModule = GetModuleHandle(_T("User32.dll"));
	if(hModule != NULL)
	{
		m_pOldEndPaint   = GetProcAddress(hModule,   "EndPaint");
		m_pOldBeginPaint = GetProcAddress(hModule, "BeginPaint");
	}

	if(m_pOldBeginPaint == NULL || m_pOldEndPaint == NULL)
	{
		return FALSE;
	}

	m_pNewEndPaint   = MY_EndPaint;
	m_pNewBeginPaint = MY_BeginPaint;

	DWORD dwOldProtection = 0;                     
	if(0 != ::VirtualProtect(m_pOldBeginPaint, 8, PAGE_EXECUTE_READWRITE, &dwOldProtection)) 
	{
		m_dwOffBeginPaint = *(DWORD*)((BYTE*)m_pOldBeginPaint + 1);

		BYTE btJump[5] = {0xe9, 0, 0, 0, 0};
                
		DWORD dwAddr = (DWORD)((UINT_PTR)m_pNewBeginPaint - (UINT_PTR)m_pOldBeginPaint) - sizeof(btJump); 
		memcpy(btJump + 1, &dwAddr, sizeof(dwAddr));       
		memcpy(m_pOldBeginPaint, btJump, sizeof(btJump));  
	}

	if(0 != ::VirtualProtect(m_pOldEndPaint, 8, PAGE_EXECUTE_READWRITE, &dwOldProtection)) 
	{
		m_dwOffEndPaint = *(DWORD*)((BYTE*)m_pOldEndPaint + 1);

		BYTE btJump[5] = {0xe9, 0, 0, 0, 0};
                                       
		DWORD dwAddr = (DWORD)((UINT_PTR)m_pNewEndPaint - (UINT_PTR)m_pOldEndPaint) - sizeof(btJump); 
		memcpy(btJump + 1, &dwAddr, sizeof(dwAddr));       
		memcpy(m_pOldEndPaint, btJump, sizeof(btJump));  
	}

	return (m_dwOffBeginPaint != 0 && m_dwOffEndPaint != 0);
}
//---------------------------------------------------------------------------------
HDC CALLBACK CHook::MY_BeginPaint(HWND hWnd, LPPAINTSTRUCT lpPaint)
{
	if(m_hPaintDC != NULL)
	{
		lpPaint->hdc = m_hPaintDC;
		GetClientRect(hWnd, &lpPaint->rcPaint);
		return m_hPaintDC;
	}

	DWORD pBegin = (DWORD)(UINT_PTR)m_pOldBeginPaint + 5;

	__asm
	{
		mov     eax, m_dwOffBeginPaint
		push    lpPaint
		push    hWnd
		call    [pBegin]
	}
}
//---------------------------------------------------------------------------------
BOOL CALLBACK CHook::MY_EndPaint(HWND hWnd, CONST PAINTSTRUCT *lpPaint)
{
	if(m_hPaintDC != NULL)
	{
		m_hPaintDC = NULL;
		return TRUE;
	}

	DWORD pEnd = (DWORD)(UINT_PTR)m_pOldEndPaint + 5;

	__asm
	{
		mov     eax, m_dwOffEndPaint
		push    lpPaint
		push    hWnd
		call    [pEnd]
	}
}
//---------------------------------------------------------------------------------


#endif 
