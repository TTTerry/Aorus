 // GvFireware.h : main header file for the GvFireware DLL
#ifndef _GVFIREWARE_H
#define _GVFIREWARE_H

#ifdef  GVFIREWARE_EXPORTS
#define GVFIREWARE_API __declspec(dllexport) 
#else
#define GVFIREWARE_API __declspec(dllimport) 
#endif


////////////////////////////////////////////////////////////////////////////////////
// Defined for error code
// 
#define GVAPI_OK					0x00000000
#define GVAPI_FWERR_FAILED			0x20000001	// Unknown Error
#define GVAPI_FWERR_ERR_PARAM		0x20000002	// invalid parameter
#define GVAPI_FWERR_ERR_NOBOARD		0x20000003	// no boards found
#define GVAPI_FWERR_NOHID			0x20000004	// no HID found
#define GVAPI_FWERR_DEVNOFOUND		0x20000005	// device not found
#define GVAPI_FWERR_DEVNOOPEN		0x20000006	// device not open
#define GVAPI_FWERR_CONNECT			0x20000007	// connect device failed
#define GVAPI_FWERR_DISCONNECT		0x20000008	// disconnect device failed
#define GVAPI_FWERR_SENDDATA		0x20000009	// send data failed
#define GVAPI_FWERR_RECVDATA		0x2000000A	// receive data failed
#define GVAPI_FWERR_NOINIT			0x2000000B	// Firmware haven't Init
#define GVAPI_FWERR_USBUNPLUG		0x2000000C	// USB Device was unplugged
#define GVAPI_FWERR_PASSWORDERR		0x2000000D	// Send BSL Password Failed
#define GVAPI_FWERR_READRMABSL		0x2000000E	// Failed to read data from RAM BSL
#define GVAPI_FWERR_MEMVERIFY		0x2000000F	// Memory verification error
#define GVAPI_FWERR_UNSUPPORT		0x20000010	// UnSupport

//
////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////
// Defined for Board info
//
#define GVFW_MAX_BOARD	10

typedef struct _GVFW_BOARDINFO
{
	int  nDevIndex;
	char szSerialNubmer[40];

} GVFW_BOARDINFO, *PGVFW_BOARDINFO;
//
////////////////////////////////////////////////////////////////////////////////////

extern "C"
{
	
	/****************************************************************************************
	 * 功能描述：
	 * 获取不同ID的Devices Index
	 *
	 * 输入参数：
	 * [in]  uVendor      所要連接裝置的VID
	 * [in]  uProduct     所要連接裝置的PID
	 * 
	 * 返回值：
	 * 返回GVAPI_OK表示调用成功；GVAPI_FWERR_ERR_NOBOARD表示沒有找到裝置；
	 ****************************************************************************************/
	GVFIREWARE_API int GetUsbDevicesIndex(WORD uVendor, WORD uProduct);

	/****************************************************************************************
	 * 功能描述：
	 * 初始化Fireware連接
	 *
	 * 输入参数：
	 * [out] nIndex       初始化设备的Index
	 * [in]  uVendor      所要連接裝置的VID
	 * [in]  uProduct     所要連接裝置的PID
	 * 
	 * 返回值：
	 * 返回GVAPI_OK表示调用成功；GVAPI_FWERR_ERR_NOBOARD表示沒有找到裝置；
	 ****************************************************************************************/
	GVFIREWARE_API DWORD GvInitFireware(int &nIndex, int nHID, WORD uVendor, WORD uProduct);
	
	/****************************************************************************************
	 * 功能描述：
	 * 釋放设备連接
	 *
	 * 输入参数：
	 * [in]  nIndex       设备Index
	 * 
	 * 返回值：
	 * 返回GVAPI_OK表示调用成功；GVAPI_FWERR_NOINIT表示尚未Init；
	 ****************************************************************************************/
	GVFIREWARE_API DWORD GvFreeFireware(int nIndex);
	
	/****************************************************************************************
	 * 功能描述：
	 * 重刷新Fireware連接
	 *
	 * 输入参数：
	 * [in]  nIndex       设备Index
	 * 
	 * 返回值：
	 * 返回GVAPI_OK表示调用成功；GVAPI_FWERR_NOINIT表示尚未Init；
	 ****************************************************************************************/
	GVFIREWARE_API DWORD GvRefreshFireware(int nIndex);

	/****************************************************************************************
	 * 功能描述：
	 * 獲取裝置是否連接
	 *
	 * 输入参数：
	 * [in]  nIndex       设备Index
	 * [in]  nBrd         裝置索引
	 * 
	 * 返回值：
	 * 返回TRUE表示已連接，反之；
	 ****************************************************************************************/
	GVFIREWARE_API BOOL  GvIsConnectBrd(int nIndex, int nBrd);
	
	/****************************************************************************************
	 * 功能描述：
	 * 連接指定裝置
	 *
	 * 输入参数：
	 * [in]  nIndex       设备Index
	 * [in]  nBrd         裝置索引
	 * [in]  nHID		  HID索引
	 * 
	 * 返回值：
	 * 返回GVAPI_OK表示連接成功，GVAPI_FWERR_CONNECT表示連接失敗；
	 ****************************************************************************************/
	GVFIREWARE_API DWORD GvConnectBrd(int nIndex, int nBrd, int nHID);
	
	/****************************************************************************************
	 * 功能描述：
	 * 斷開指定裝置
	 *
	 * 输入参数：
	 * [in]  nIndex       设备Index
	 * [in]  nBrd         裝置索引
	 * 
	 * 返回值：
	 * 返回GVAPI_OK表示斷開成功，GVAPI_FWERR_DISCONNECT表示斷開失敗；
	 ****************************************************************************************/
	GVFIREWARE_API DWORD GvDisConnectBrd(int nIndex, int nBrd);
	
	/****************************************************************************************
	 * 功能描述：
	 * 獲取當前連接的裝置
	 *
	 * 输入参数：
	 * [in]  nIndex       设备Index
	 * [in]  stBoards     存放裝置資訊的結構題數組
	 * [out] nCount       識別到的裝置數量，最多可以識別10個裝置
	 * 
	 * 返回值：
	 * 返回GVAPI_OK表示獲取成功，GVAPI_FWERR_NOINIT表示尚未Init；
	 ****************************************************************************************/
	GVFIREWARE_API DWORD GvGetBoards(int nIndex, GVFW_BOARDINFO stBoards[GVFW_MAX_BOARD], int& nCount);

	/****************************************************************************************
	 * 功能描述：
	 * 發送字符串的命令到指定裝置
	 *
	 * 输入参数：
	 * [in]  nIndex       设备Index
	 * [in]  nBrd         裝置索引
	 * [in]  nHID		  HID索引
	 * [in]  szCmd        發送的指令
	 * [out] szReceive    從裝置收到的返回值
	 * 
	 * 返回值：
	 * 返回GVAPI_OK表示發送成功，GVAPI_FWERR_ERR_PARAM表示參數錯誤，GVAPI_FWERR_SENDDATA表示發送失敗；
	 ****************************************************************************************/
	GVFIREWARE_API DWORD GvSendCommand(int nIndex, int nBrd, int nHID, char* szCmd, char* szReceive);
	
	/****************************************************************************************
	 * 功能描述：
	 * 發送字節命令到指定裝置
	 *
	 * 输入参数：
	 * [in]  nIndex       设备Index
	 * [in]  nBrd         裝置索引
	 * [in]  nHID		  HID索引
	 * [in]  szCmd        發送的指令
	 * [out] szReceive    從裝置收到的返回指令，若传递NULL则表示无需返回
	 * [in/out]  nCmdLen  傳入指令的長度，回傳返回指令長度
	 * 
	 * 返回值：
	 * 返回GVAPI_OK表示發送成功，GVAPI_FWERR_ERR_PARAM表示參數錯誤，GVAPI_FWERR_SENDDATA表示發送失敗；
	 ****************************************************************************************/
	GVFIREWARE_API DWORD GvSendCommandByte(int nIndex, int nBrd, int nHID, BYTE* szCmd, BYTE* szReceive, int& nCmdLen);

	/****************************************************************************************
	 * 功能描述：
	 * 開始準備刷寫
	 *
	 * 输入参数：
	 * [in]  nIndex       设备Index
	 * [in]  nBrd         裝置索引
	 * [in]  nHID		  HID索引
	 * [out] nDeviceId    刷写设备Index
	 * 
	 * 返回值：
	 * 返回GVAPI_OK表示可以開始刷寫，GVAPI_FWERR_UNSUPPORT表示不支援；
	 ****************************************************************************************/
	GVFIREWARE_API DWORD GvBeginToFlash(int nIndex, int nBrd, int nHID);

	/****************************************************************************************
	 * 功能描述：
	 * 發送字節命令到指定裝置
	 *
	 * 输入参数：
	 * [in]  nDeviceId    刷写设备Index
	 * [in]  szPath       FW文件路径
	 * [out] nProgress	  当前刷写进度，实时更新
	 * 
	 * 返回值：
	 * 返回GVAPI_OK表示斷開成功，其他Error見錯誤描述；
	 ****************************************************************************************/
	GVFIREWARE_API DWORD GvFlashFromFile(char* szPath, int* pProgress);
}

#endif

