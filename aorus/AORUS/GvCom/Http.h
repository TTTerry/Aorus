#ifndef _GV_COM_DLL_HTTP_H_
#define _GV_COM_DLL_HTTP_H_

#include "Base.h"

namespace Gv {

//
// ����漰��Url·����������Http�ļ��W�j·��, �����ļ���������·��;
//
class GVDLL Http : public Base
{
public:
	struct GVDLL STATUS	 // ���d�M�Ƞ�B
	{
		CWnd* pProgDesc;			// �@ʾ�M�ȵĴ��ڿؼ�
		CProgressCtrl* pProgress;	// �@ʾ�M�ȵ��M�ȗl�ؼ�
	};

public:
	 Http();
	~Http();

	//
	// �ς������ļ����W�j
	//
	bool UploadFile(CString sUrl, CString sLocalFile);
	//
	// ���ȴ��ϵă����ς��W�j, ��ָ���ļ���ʽ���
	//
	bool UploadFromMemory(CString sUrl, BYTE* pBuffer/*[in]*/, UINT nBufSize/*[in]*/);
	//
	// �Єe�Wַָ���ļ��Ƿ���Ч
	//
	bool Http::IsUrlExisted(CString sUrl, bool& bExisted/*�����ɹ��r, true: ����; false: ������*/);
	//
	// ���d�W�j�ļ�������
	//
	bool DownloadFile(CString sUrl, CString sLocalFile, STATUS* pStatus=NULL/*���d�M�Ƞ�B*/);
	//
	// ���d�W�j�ļ����ȴ�, ���ⲿ����ȴ�, ֮�ṩ���������, 
	// �K���،��H��С; �ļ������ȴ��С�r, ���Ճȴ���g��С�M�����.
	//
	bool DownloadToMemory(CString sUrl,  BYTE*& pBuffer/*[in/out]*/, UINT& nBufSize/*[in/out]*/);
};
}

#endif
