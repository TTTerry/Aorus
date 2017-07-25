#include "stdafx.h"
#include "Font.h"
#include "../resource.h"
#include "../AorusDlg.h"


CFont* Font(int nFontSize, bool bBold)
{
	static CFont s_font05; 
	static CFont s_font06; 
	static CFont s_font08; 
	static CFont s_font09; 
	static CFont s_font10; 
	static CFont s_font11; 
	static CFont s_font12; 
	static CFont s_font13; 
	static CFont s_font14; 
	static CFont s_font18; 
	static CFont s_font22;
	static CFont s_font28;
	// bold
	static CFont s_font05_b; 
	static CFont s_font06_b; 
	static CFont s_font08_b; 
	static CFont s_font09_b; 
	static CFont s_font10_b; 
	static CFont s_font11_b; 
	static CFont s_font12_b; 
	static CFont s_font13_b; 
	static CFont s_font14_b; 
	static CFont s_font18_b; 
	static CFont s_font22_b;
	static CFont s_font28_b;
	static HANDLE s_hFont = NULL;
	static bool s_bCreate = false;

	if (!s_bCreate)
	{
		s_bCreate = true;

		HDC hdc = ::GetDC(NULL);
		int nDC = _ttoi(_T("98"));//::GetDeviceCaps(hdc, LOGPIXELSY);
		int nHPixel05 = (int)(( 5.5 * nDC) / 72);
		int nHPixel06 = ( 6 * nDC) / 72;
		int nHPixel08 = (int)((8.9999* nDC) / 72);
		int nHPixel09 = ( 9 * nDC) / 72;
		int nHPixel10 = (10 * nDC) / 72;
		int nHPixel11 = (int)((11.5 * nDC) / 72);
		int nHPixel12 = (12 * nDC) / 72;
		int nHPixel13 = (13 * nDC) / 72;
		int nHPixel14 = (14 * nDC) / 72;
		int nHPixel18 = (18 * nDC) / 72;
		int nHPixel22 = (22 * nDC) / 72;
		int nHPixel28 = (28 * nDC) / 72;

		::ReleaseDC(NULL, hdc);

		s_hFont = InstallFont(IDR_MAIN_FONT);
		s_font05.CreateFont(nHPixel05, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, 
			DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS,_T("Aldrich"));
		s_font06.CreateFont(nHPixel06, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, 
			DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS,_T("Aldrich"));
		s_font08.CreateFont(nHPixel08, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, 
			DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS,_T("Aldrich"));
		s_font09.CreateFont(nHPixel09, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, 
			DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("Aldrich"));
		s_font10.CreateFont(nHPixel09, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, 
			DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("Aldrich"));
		s_font11.CreateFont(nHPixel11, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, 
			DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS,_T("Aldrich"));
		s_font12.CreateFont(nHPixel12, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, 
			DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("Aldrich"));
		s_font13.CreateFont(nHPixel13, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, 
			DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("Aldrich"));
		s_font14.CreateFont(nHPixel14, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, 
			DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("Aldrich"));
		s_font18.CreateFont(nHPixel18, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, 
			DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS,_T("Aldrich"));
		s_font22.CreateFont(nHPixel22, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, 
			DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("Aldrich"));
		s_font28.CreateFont(nHPixel28, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, 
			DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("Aldrich"));
		// bold
		s_font05_b.CreateFont(nHPixel05, 0, 0, 0, FW_SEMIBOLD, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, 
			DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS,_T("Aldrich"));
		s_font06_b.CreateFont(nHPixel06, 0, 0, 0, FW_SEMIBOLD, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, 
			DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS,_T("Aldrich"));
		s_font08_b.CreateFont(nHPixel08, 0, 0, 0, FW_SEMIBOLD, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, 
			DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS,_T("Aldrich"));
		s_font09_b.CreateFont(nHPixel09, 0, 0, 0, FW_SEMIBOLD, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, 
			DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("Aldrich"));
		s_font10_b.CreateFont(nHPixel09, 0, 0, 0, FW_SEMIBOLD, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, 
			DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("Aldrich"));
		s_font11_b.CreateFont(nHPixel11, 0, 0, 0, FW_SEMIBOLD, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, 
			DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS,_T("Aldrich"));
		s_font12_b.CreateFont(nHPixel12, 0, 0, 0, FW_SEMIBOLD, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, 
			DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("Aldrich"));
		s_font13_b.CreateFont(nHPixel13, 0, 0, 0, FW_SEMIBOLD, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, 
			DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("Aldrich"));
		s_font14_b.CreateFont(nHPixel14, 0, 0, 0, FW_SEMIBOLD, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, 
			DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("Aldrich"));
		s_font18_b.CreateFont(nHPixel18, 0, 0, 0, FW_SEMIBOLD, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, 
			DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS,_T("Aldrich"));
		s_font22_b.CreateFont(nHPixel22, 0, 0, 0, FW_SEMIBOLD, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, 
			DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("Aldrich"));
		s_font28_b.CreateFont(nHPixel28, 0, 0, 0, FW_SEMIBOLD, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, 
			DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("Aldrich"));
	}

	CFont* pFont = NULL;
	switch(nFontSize)
	{
	case 5:  pFont = bBold ? &s_font05_b : &s_font05; break;
	case 6:  pFont = bBold ? &s_font06_b : &s_font06; break;
	case 8:  pFont = bBold ? &s_font08_b : &s_font08; break; 
	case 9:  pFont = bBold ? &s_font09_b : &s_font09; break; 
	case 10: pFont = bBold ? &s_font10_b : &s_font10; break; 
	case 11: pFont = bBold ? &s_font11_b : &s_font11; break; 
	case 12: pFont = bBold ? &s_font12_b : &s_font12; break; 
	case 13: pFont = bBold ? &s_font13_b : &s_font13; break; 
	case 14: pFont = bBold ? &s_font14_b : &s_font14; break; 
	case 18: pFont = bBold ? &s_font18_b : &s_font18; break; 
	case 22: pFont = bBold ? &s_font22_b : &s_font22; break;
	case 28: pFont = bBold ? &s_font28_b : &s_font28; break;
	}

	ASSERT(NULL != pFont);
	return pFont;
}