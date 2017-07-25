#ifndef _GV_COM_DLL_FTP_H_
#define _GV_COM_DLL_FTP_H_

#include "Base.h"
#include "afxinet.h"

namespace Gv {

//
// 本類涉及的ftp路徑均為ftp相對路徑, 如'/folder/filen.txt', 本地文件均為完整路徑;
//
class GVDLL Ftp : public Base
{
public:
	 Ftp(CString sFtpServer, CString sLogin, CString sPassword);
	~Ftp();

	//
	// 上傳本地文件至ftp
	//
	bool UploadFile(CString sRemoteFile, CString sLocalFile);
	//
	// 將內存上的內容上傳ftp, 以指定文件格式存放
	//
	bool UploadFromMemory(CString sRemoteFile, BYTE* pBuffer/*[in]*/, UINT nBufSize/*[in]*/);
	//
	// 下載ftp文件至本地
	//
	bool DownloadFile(CString sRemoteFile, CString sLocalFile);
	//
	// 下載ftp文件至內存, 由外部分配內存, 之後供本函數填充, 
	// 並返回實際大小; 文件超出內存大小時, 按照內存空間大小進行填充.
	//
	bool DownloadToMemory(CString sRemoteFile,  BYTE*& pBuffer/*[in/out]*/, UINT& nBufSize/*[in/out]*/);
	//
	// 刪除ftp文件
	//
	bool DeleteFile(CString sRemoteFile);
	//
	// 創建ftp文件夾, 參數為文件夾相對路徑, 如: '/folder/subfolder'
	// 創建時, 在相對路徑中的所有文件夾若不存在, 均會被同時創建
	//
	bool CreateDirectory(CString sRemoteDir);
	//
	// 刪除ftp文件夾, 參數為文件夾相對路徑, 如: '/folder/subfolder'
	//
	bool DeleteDirectory(CString sRemoteDir);

private:
	CInternetSession m_Session;
	CFtpConnection *m_pFtpConnection;
};

}

#endif
