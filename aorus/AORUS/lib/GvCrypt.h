#ifndef _GVCRYPT_H
#define _GVCRYPT_H


#ifdef  GVCRYPT_EXPORTS
#define GVCRYPT_API __declspec(dllexport)
#else
#define GVCRYPT_API __declspec(dllimport)
#endif


#define GVAPI_OK 0x00000000

extern "C"
{
	GVCRYPT_API DWORD GvEncryptFileA(char    *szSrcPath, char    *szDestPath, PBYTE lpPassword);
	GVCRYPT_API DWORD GvEncryptFileW(wchar_t *szSrcPath, wchar_t *szDestPath, PBYTE lpPassword);
	#ifdef UNICODE
	#define GvEncryptFile  GvEncryptFileW
	#else
	#define GvEncryptFile  GvEncryptFileA
	#endif // !UNICODE

	GVCRYPT_API DWORD GvDecryptFileA(char    *szSrcPath, char    *szDestPath, PBYTE lpPassword);
	GVCRYPT_API DWORD GvDecryptFileW(wchar_t *szSrcPath, wchar_t *szDestPath, PBYTE lpPassword);
	#ifdef UNICODE
	#define GvDecryptFile  GvDecryptFileW
	#else
	#define GvDecryptFile  GvDecryptFileA
	#endif // !UNICODE
}

#endif