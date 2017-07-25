// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently,
// but are changed infrequently

#pragma once

#ifndef _SECURE_ATL
#define _SECURE_ATL 1
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // Exclude rarely-used stuff from Windows headers
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // some CString constructors will be explicit

// turns off MFC's hiding of some common and often safely ignored warning messages
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions


#include <afxdisp.h>        // MFC Automation classes



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC support for Internet Explorer 4 Common Controls
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>                     // MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT









#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif

#include <dbt.h>
#include "inc/language/LangX.h"
CLangX c;
#include "Ui/UiClass.h"
#include "GvCom/GvCom.h"
using namespace Gv;
#include "common/Common.h"

#include "lib/GvAutoUpdate.h"
#pragma comment(lib, "lib/GvAutoUpdate.lib")

#include "lib/GvBiosLib.h"
#pragma comment(lib, "lib/GvBiosLib.lib")

#include "lib/GvCrypt.h"
#pragma comment(lib, "lib/GvCrypt.lib")

#include "lib/GvDisplay.h"
#pragma comment(lib, "lib/GvDisplay.lib")

#include "lib/GvFireware.h"
#pragma comment(lib, "lib/GvFireware.lib")

#include "lib/GvKm.h"
#pragma comment(lib, "lib/GvKm.lib")

#include "lib/GvOrderLib.h"
#pragma comment(lib, "lib/GvOrderLib.lib")

#include "lib/GvLedLib.h"

#include "inc/audio/AudioVolume.h"

#include "inc/IniFile.h"
#include "common/definition.h"
#include "common/Font.h"
#include "inc/vga/VGACtrl.h"
#include "inc/mainboard/MBCtrl.h"
#include "inc/vga/Cfg.h"
#include "inc/led/NvApiTemp.h"
#include "inc/FurmarkReader/FurmarkReader.h"
#include "inc/xled/XLedCmd.h"
#include "inc/xled/Device.h"
#include "inc/led/SyncLed.h"

#include "inc/kb/XK700Cmd.h"
#include "inc/kb/KbLedCtrl.h"
#include "inc/kb/KbCfg.h"

class CAORUSDlg;
extern CAORUSDlg* Aorus(); // Get AorusDlg object
extern SYNCLED_CONFIG s_SyncLedConfig;