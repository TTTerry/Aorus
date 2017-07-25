#ifndef _GV_COM_DLL_HEADER_
#define _GV_COM_DLL_HEADER_

/////////////////// !!!!!NOTE ///////////////////
//
// Project which calls this DLL, must use [Use MFC in a Shared DLL] setting, not [Use MFC in a Static Library].
// See: project -> Properities -> Configuration Properities -> General -> Use of MFC -> Use MFC in a Shared DLL
// 
/////////////////// !!!!!NOTE ///////////////////

#include "Convert.h"		//  1) 數字與字符串, 日期等之間的轉換
#include "IniFile.h"		//  2) 讀寫*.Ini
#include "Excel.h"			//  3) 讀寫Excel文檔
#include "Encode.h"			//  4) 編解碼txt檔案
#include "Sql.h"			//  5) 數據庫讀寫訪問
#include "SqlCmd.h"			//  6) 讀寫Excel文檔
#include "DataTable.h"		//  7) 類C#的DataTable類
#include "HwTool.h"			//  8) HwTool相關資料庫讀寫
#include "DataLink.h"		//  9) HwTool資料庫鏈接讀寫
#include "Distance.h"		// 10) 點, 線, 矩形, 圓等之間距離計算
#include "User.h"			// 11) KM_SYS_User資料庫訪問
#include "Menus.h"			// 12) KM_SYS_Menus資料庫訪問
#include "Ftp.h"			// 13) FTP下載與上傳
#include "Http.h"			// 14) HTTP下載與上傳
#include "Registry.h"		// 15) 讀寫註冊表
#include "Verify.h"			// 16) AP程式權限管控
#include "OS.h"				// 17) 操作系統相關信息, 如程式版本, OS版本, 32/64bits判別, 獲取臨時路徑等
#include "Driver.h"			// 18) 通過安裝Driver, 實現讀取OS底層內存地址內容
#include "Device.h"			// 19) 各種設備信息讀取, 如顯卡, BIOS等.
#include "Shell.h"			// 20) 對ShellExecuteEx()進一步封裝與擴展功能(鼠標/鍵盤點擊)
#include "LiveUpdate.h"		// 21) 實現顯卡官網信息獲取, 在線Update等. 如官網BIOS, Model規格
#endif

