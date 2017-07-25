#ifndef _GV_COM_DLL_FTP_H_
#define _GV_COM_DLL_FTP_H_

#include "Base.h"
#include "afxinet.h"

namespace Gv {

//
// ����漰��ftp·������ftp����·��, ��'/folder/filen.txt', �����ļ���������·��;
//
class GVDLL Ftp : public Base
{
public:
	 Ftp(CString sFtpServer, CString sLogin, CString sPassword);
	~Ftp();

	//
	// �ς������ļ���ftp
	//
	bool UploadFile(CString sRemoteFile, CString sLocalFile);
	//
	// ���ȴ��ϵă����ς�ftp, ��ָ���ļ���ʽ���
	//
	bool UploadFromMemory(CString sRemoteFile, BYTE* pBuffer/*[in]*/, UINT nBufSize/*[in]*/);
	//
	// ���dftp�ļ�������
	//
	bool DownloadFile(CString sRemoteFile, CString sLocalFile);
	//
	// ���dftp�ļ����ȴ�, ���ⲿ����ȴ�, ֮�ṩ���������, 
	// �K���،��H��С; �ļ������ȴ��С�r, ���Ճȴ���g��С�M�����.
	//
	bool DownloadToMemory(CString sRemoteFile,  BYTE*& pBuffer/*[in/out]*/, UINT& nBufSize/*[in/out]*/);
	//
	// �h��ftp�ļ�
	//
	bool DeleteFile(CString sRemoteFile);
	//
	// ����ftp�ļ��A, �������ļ��A����·��, ��: '/folder/subfolder'
	// �����r, ������·���е������ļ��A��������, ������ͬ�r����
	//
	bool CreateDirectory(CString sRemoteDir);
	//
	// �h��ftp�ļ��A, �������ļ��A����·��, ��: '/folder/subfolder'
	//
	bool DeleteDirectory(CString sRemoteDir);

private:
	CInternetSession m_Session;
	CFtpConnection *m_pFtpConnection;
};

}

#endif
