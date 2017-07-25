// AORUS.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CAORUSApp:
// See AORUS.cpp for the implementation of this class
//

class CAORUSApp : public CWinApp
{
public:
	CAORUSApp();

// Overrides
	public:
	virtual BOOL InitInstance();
    virtual void WinHelpInternal(DWORD_PTR dwData, UINT nCmd);
// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CAORUSApp theApp;