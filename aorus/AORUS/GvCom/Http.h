#ifndef _GV_COM_DLL_HTTP_H_
#define _GV_COM_DLL_HTTP_H_

#include "Base.h"

namespace Gv {

//
// 本類涉及的Url路徑均為完整Http文件網絡路徑, 本地文件均為完整路徑;
//
class GVDLL Http : public Base
{
public:
	struct GVDLL STATUS	 // 下載進度狀態
	{
		CWnd* pProgDesc;			// 顯示進度的窗口控件
		CProgressCtrl* pProgress;	// 顯示進度的進度條控件
	};

public:
	 Http();
	~Http();

	//
	// 上傳本地文件至網絡
	//
	bool UploadFile(CString sUrl, CString sLocalFile);
	//
	// 將內存上的內容上傳網絡, 以指定文件格式存放
	//
	bool UploadFromMemory(CString sUrl, BYTE* pBuffer/*[in]*/, UINT nBufSize/*[in]*/);
	//
	// 判別網址指向文件是否有效
	//
	bool Http::IsUrlExisted(CString sUrl, bool& bExisted/*函數成功時, true: 存在; false: 不存在*/);
	//
	// 下載網絡文件至本地
	//
	bool DownloadFile(CString sUrl, CString sLocalFile, STATUS* pStatus=NULL/*下載進度狀態*/);
	//
	// 下載網絡文件至內存, 由外部分配內存, 之後供本函數填充, 
	// 並返回實際大小; 文件超出內存大小時, 按照內存空間大小進行填充.
	//
	bool DownloadToMemory(CString sUrl,  BYTE*& pBuffer/*[in/out]*/, UINT& nBufSize/*[in/out]*/);
};
}

#endif
