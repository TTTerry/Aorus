#include "StdAfx.h"
#include "XK700Ctrl.h"
#include "XK700Cmd.h"
#include "math.h"

static int s_KEYClrList[KEY_ROW][KEY_COL] = {0};
static int s_KEYClr[KEY_ROW][KEY_COL] = {0};
static int s_KEYLight[KEY_ROW][KEY_COL] = {0};
static int s_KEYSpeed[KEY_ROW][KEY_COL] = {0};
static bool s_KEYSel[KEY_ROW][KEY_COL] = {0};
static bool s_KEYLastSel[KEY_ROW][KEY_COL] = {0};
static DWORD s_KEYID[KEY_ROW][KEY_COL] = {0};

CXK700Ctrl::CXK700Ctrl(void)
{
	for (int i = 0; i < KEY_ROW; i++)
	{
		for (int j = 0; j < KEY_COL; j++)
			s_KEYSel[i][j] = true;
	}
}

CXK700Ctrl::~CXK700Ctrl(void)
{
}

void CXK700Ctrl::ToPulsing(COLORREF clr1, COLORREF clr2, int nBright, int nSpeed, bool bRandom)
{
	int nClrList = m_nClrList;
	int nTimer = 100;
	int nClrCount = (bRandom ? 7 : 2);
	if(bRandom) m_nClrCount = 126;
	else m_nClrCount = 63;
	float Operity = (float)(1.0 / m_nClrCount * 2.0 * nClrCount);
	COLORREF lstclr[7] = { 
		RGB(255,   0,   0),
		RGB(255,  90,   0),
		RGB(255, 200,   0),
		RGB(  0, 255,   0),
		RGB(  0, 255, 255),
		RGB(  0,   0, 255),
		RGB(255,   0, 255),
	};
	if (!bRandom)
	{
		lstclr[0] = clr1;
		lstclr[1] = clr2;
	}

	for (int j = 0; j < nClrCount; j++)
	{
		for (int i = 0; i <= m_nClrCount / nClrCount / 2; i++)
		{
			s_lstClr[nClrList].lstClr[i + j * m_nClrCount / nClrCount] = RGB(
				GetRValue(lstclr[j]) * (i) * Operity, 
				GetGValue(lstclr[j]) * (i) * Operity, 
				GetBValue(lstclr[j]) * (i) * Operity
				);
			s_lstClr[nClrList].lstClr[m_nClrCount / nClrCount - i + j * m_nClrCount / nClrCount] = RGB(
				GetRValue(lstclr[j]) * (i) * Operity, 
				GetGValue(lstclr[j]) * (i) * Operity, 
				GetBValue(lstclr[j]) * (i) * Operity
				);
		}
	}
	s_lstClr[nClrList].nCount = m_nClrCount;

	for (int m = 0; m < KEY_ROW; m++)
	{
		for (int n = 0; n <  KEY_COL; n++)
		{
			if(s_KEYSel[m][n]) s_KEYClr[m][n] = 0;
			if(s_KEYSel[m][n]) s_KEYClrList[m][n] = m_nClrList;
			if(s_KEYSel[m][n]) s_KEYLight[m][n] = nBright;
			if(s_KEYSel[m][n]) s_KEYSpeed[m][n] = nTimer - 4 * nSpeed;
		}
	}
	ToByte(s_lstClr[nClrList].nCount, nTimer, nClrList);
}

void CXK700Ctrl::ToConsistent(COLORREF clr, int nBright, int nSpeed)
{
	int nClrList = m_nClrList;
	int nTimer = 1000;
	for (int m = 0; m < KEY_ROW; m++)
	{
		for (int n = 0; n <  KEY_COL; n++)
		{
			if(!s_KEYSel[m][n]) continue;
			s_KEYClr[m][n] = 0;
			s_KEYClrList[m][n] = nClrList;
			s_KEYLight[m][n] = nBright;
			s_KEYSpeed[m][n] = nTimer - 4 * nSpeed;
		}
	}

	nBright = 10;
	s_lstClr[nClrList].nCount = 1;
	for (int i = 0; i < 1; i++)
	{
		s_lstClr[nClrList].lstClr[i] = RGB(nBright / 10.0 * GetRValue(clr), nBright / 10.0 * GetGValue(clr), nBright / 10.0 * GetBValue(clr));
	}
	ToByte(s_lstClr[nClrList].nCount, nTimer, nClrList);
}

void CXK700Ctrl::ToCycling(int nBright, int nSpeed)
{
	int nClrList = m_nClrList;
	int nTimer = 100;
	for (int m = 0; m < KEY_ROW; m++)
	{
		for (int n = 0; n <  KEY_COL; n++)
		{
			if(s_KEYSel[m][n]) s_KEYClr[m][n] = 0;
			if(s_KEYSel[m][n]) s_KEYClrList[m][n] = nClrList;
			if(s_KEYSel[m][n]) s_KEYLight[m][n] = nBright;
			if(s_KEYSel[m][n]) s_KEYSpeed[m][n] = nTimer - 4 * nSpeed;
		}
	}

	nBright = 10;
	s_lstClr[nClrList].nCount = 128;
	for (int i = 0; i < s_lstClr[nClrList].nCount; i++)
	{
		COLORREF clr = HSBToRGB(i * ((float)360.0 / s_lstClr[nClrList].nCount));
		s_lstClr[nClrList].lstClr[i] = RGB(nBright / 10.0 * GetRValue(clr), nBright / 10.0 * GetGValue(clr), nBright / 10.0 * GetBValue(clr));
	}
	ToByte(s_lstClr[nClrList].nCount, 100, nClrList);
}

void CXK700Ctrl::ToWave(int nAngle, int nClr, int nBright, int nSpeed)
{
	int nClrList = m_nClrList;
	int nTimer = 50;
	for (int i = 0; i < CLR_COUNT; i++)
	{
		COLORREF clr = HSBToRGB(i * ((float)360.0 / CLR_COUNT));
		s_lstClr[nClrList].lstClr[i] = clr;//RGB(nBright / 10.0 * GetRValue(clr), nBright / 10.0 * GetGValue(clr), nBright / 10.0 * GetBValue(clr));
	}
	s_lstClr[nClrList].nCount = CLR_COUNT;

	CPoint ptCoor[KEY_ROW + KEY_COL + KEY_ROW + KEY_COL][KEY_COL + KEY_ROW + KEY_ROW + KEY_COL];
	CPoint ptSame[KEY_ROW][KEY_COL];
	for (int m = 0; m < KEY_ROW + KEY_COL + KEY_ROW + KEY_COL; m++)
	{
		for (int n = 0; n <  KEY_ROW + KEY_COL + KEY_ROW + KEY_COL; n++)
		{
			ptCoor[m][n] = CPoint(-1, -1);
		}
	}

	int nKEYClr[KEY_ROW][KEY_COL] = {0};
	for (int m = 0; m < KEY_ROW; m++)
	{
		for (int n = 0; n <  KEY_COL; n++)
		{
			ptSame[m][n] = CPoint(-1, -1);
			nKEYClr[m][n] = -1;
			if(s_KEYSel[m][n]) s_KEYClr[m][n] = -1;
			if(s_KEYSel[m][n]) s_KEYClrList[m][n] = nClrList;
			if(s_KEYSel[m][n]) s_KEYLight[m][n] = nBright;
			if(s_KEYSel[m][n]) s_KEYSpeed[m][n] = nTimer - 4 * nSpeed;
		}
	}

	for (int m = 0; m < KEY_ROW; m++)
	{
		for (int n = 0; n < KEY_COL; n++)
		{
			int i = (int)(m * cos(nAngle / 180.0 * 3.14159265358979323846) - n * sin(nAngle / 180.0 * 3.14159265358979323846) + KEY_COL);
			int j = (int)(n * cos(nAngle / 180.0 * 3.14159265358979323846) + m * sin(nAngle / 180.0 * 3.14159265358979323846) + KEY_COL);
			if(i < 0 || j < 0) AfxMessageBox(_T("Warning"));
			if(ptCoor[i][j] != CPoint(-1, -1)) 
				ptSame[m][n] = ptCoor[i][j];
			else ptCoor[i][j] = CPoint(m, n);
		}
	}

	for (int m = 0; m < KEY_ROW + KEY_COL + KEY_ROW + KEY_COL; m++)
	{
		for (int n = 0; n < KEY_ROW + KEY_COL + KEY_ROW + KEY_COL; n++)
		{
			if(ptCoor[m][n] == CPoint(-1, -1)) continue;
			SetClr(ptCoor[m][n].x, ptCoor[m][n].y, nClr, nKEYClr);
			SetClr(ptCoor[m][n].x, ptCoor[m][n].y, nClr);
		}
		nClr++;
	}

	for (int m = 0; m < KEY_ROW; m++)
	{
		for (int n = 0; n <  KEY_COL; n++)
		{
			if(ptSame[m][n] == CPoint(-1, -1)) continue;
			if(s_KEYSel[m][n]) s_KEYClr[m][n] = nKEYClr[ptSame[m][n].x][ptSame[m][n].y];
		}
	}
	ToByte(s_lstClr[nClrList].nCount, nTimer, nClrList);
}

//void CXK700Ctrl::ToCircle(int i, int j, int nClr, int nBright, int nSpeed)
//{
//	int nClrList = m_nClrList;
//	int nTimer = 70;
//	for (int i = 0; i < CLR_COUNT; i++)
//	{
//		COLORREF clr = HSBToRGB(i * (360.0 / CLR_COUNT));
//		s_lstClr[nClrList].lstClr[i] = clr;//RGB(nBright / 10.0 * GetRValue(clr), nBright / 10.0 * GetGValue(clr), nBright / 10.0 * GetBValue(clr));
//	}
//	s_lstClr[nClrList].nCount = CLR_COUNT;
//
//	int nKEYClr[KEY_ROW][KEY_COL] = {0};
//	for (int m = 0; m < KEY_ROW; m++)
//	{
//		int nClr = 0;
//		for (int n = 0; n < KEY_COL; n++)
//		{
//			if(s_KEYSel[m][n]) s_KEYClr[m][n] = -1;
//			if(s_KEYSel[m][n]) s_KEYClrList[m][n] = nClrList;
//			if(s_KEYSel[m][n]) s_KEYLight[m][n] = nBright;
//			if(s_KEYSel[m][n]) s_KEYSpeed[m][n] = nTimer - 4 * nSpeed;
//		}
//	}
//
//	int nOffset = nClr;
//	int nDire = 0;
//	int nBegin = j;
//	SetClr(i, j, nClr);
//	while ((j < KEY_COL && nBegin <= KEY_COL / 2)
//		|| (j >= 0 && nBegin > KEY_COL / 2))
//	{
//		for (int m = 0; m < 2; m++)
//		{
//			for(int t = 0; t < nOffset; t++)
//			{
//				switch(nDire)
//				{
//				case 0: SetClr(  i, --j, nOffset / 2 + 1); break;
//				case 1: SetClr(++i,   j, nOffset / 2 + 1); break;
//				case 2: SetClr(  i, ++j, nOffset / 2 + 1); break;
//				case 3:	SetClr(--i,   j, nOffset / 2 + 1); break;
//				}
//			}
//			nDire = (nDire + 1) % 4;
//		}
//		nOffset ++;
//	}
//	ToByte(m_nClrCount, nTimer, nClrList);
//}

void CXK700Ctrl::ToByte(int nClrCount, int nTimer, int nClrIndex)
{
	//return;
	const int BLOCK = 64 * 64;
	int nSpeed = 1;
	nSpeed = 10;//GetDlgItemInt(IDC_EDIT_SPEED);
	DWORD dwAddr = 0x16000;
	DWORD dwClrAddr = m_dwClrLastAddr + dwAddr;

	BYTE* byClrList = &m_LedMemory[dwAddr - 0x11000];

	byClrList[m_dwClrLastAddr] = nClrCount;
	int nIndex = m_dwClrLastAddr + 1;
	// 生成Clr List 1
	for(int i = 0; i < nClrCount; i++)
	{
		byClrList[nIndex++] = GetRValue(s_lstClr[nClrIndex].lstClr[i]);
		byClrList[nIndex++] = GetGValue(s_lstClr[nClrIndex].lstClr[i]);
		byClrList[nIndex++] = GetBValue(s_lstClr[nClrIndex].lstClr[i]);
	}
	// 寫入Clr List
	CXK700Cmd::Write4KByte(byClrList, 0x16000);
	m_dwClrLastAddr += nClrCount * 3 + 1;

	DWORD dwAddrs[] = {
		0x11000,
		0x11380,	
		0x11700,	
		0x11A80,	
		0x11E00,	
		0x13000,	
		0x13380,	
		0x13700,	
		0x13A80,	
		0x13E00,	
	};

	// 生成Profile 1
	int nProfile = 0;//((CComboBox*)GetDlgItem(IDC_COMBO_PRO))->GetCurSel();
	dwAddr = dwAddrs[nProfile];

	BYTE* byKey = &m_LedMemory[dwAddr - 0x11000];
	nIndex = 0x180;
	byKey[0] = m_nClrList;
	byKey[1 + nClrIndex * 3] = ADDRH(dwClrAddr);
	byKey[2 + nClrIndex * 3] = ADDRM(dwClrAddr);
	byKey[3 + nClrIndex * 3] = ADDRL(dwClrAddr);

	for (int i = KEY_ROW - 1; i >= 0; i--)
	{
		int nCount = 0;
		for (int j = 0; j < KEY_COL; j++)
		{
			byKey[nIndex++] = s_KEYClrList[i][j] + 1;
			byKey[nIndex++] = s_KEYClr[i][j];
			byKey[nIndex++] = s_KEYSpeed[i][j];
			byKey[nIndex++] = s_KEYLight[i][j];
			nCount++;
			if(nIndex >= BLOCK)
			{
				AfxMessageBox(_T("超出索引!"));
				break;
			}
		}
		for (int j = nCount; j < 21; j++)
		{
			byKey[nIndex++] = 0;
			byKey[nIndex++] = 0;
			byKey[nIndex++] = 0;
		}
	}
	// 寫入Profile1 ~ 5
	CXK700Cmd::Write4KByte(byKey, nProfile > 5 ? dwAddrs[5] : dwAddrs[0]);

	for (int m = 0; m < KEY_ROW; m++)
	{
		for (int n = 0; n <  KEY_COL; n++)
		{
			s_KEYSel[m][n] = false;
		}
	}
}

bool CXK700Ctrl::SetClr(int i, int j, int nClr)
{
	if(i < 0 || j < 0 || i >= KEY_ROW || j >= KEY_COL || s_KEYClr[i][j] > 0) return false;
	s_KEYClr[i][j] = (CLR_COUNT - nClr) % CLR_COUNT;
	return true;
}

bool CXK700Ctrl::SetClr(int i, int j, int nClr, int nKey[KEY_ROW][KEY_COL])
{
	if(i < 0 || j < 0 || i >= KEY_ROW || j >= KEY_COL || nKey[i][j] > 0) return false;
	nKey[i][j] = (CLR_COUNT - nClr) % CLR_COUNT;
	return true;
}

WORD CXK700Ctrl::ToKey(int& i, int& j)
{
	/*switch(s_KEYID[i][j])
	{
	case IDC_STATIC_ESC: return  VK_ESCAPE;
	case IDC_STATIC_F1: return  VK_F1;
	case IDC_STATIC_F2: return  VK_F2;
	case IDC_STATIC_F3: return  VK_F3;
	case IDC_STATIC_F4: return  VK_F4;
	case IDC_STATIC_F5: return  VK_F5;
	case IDC_STATIC_F6: return  VK_F6;
	case IDC_STATIC_F7: return  VK_F7;
	case IDC_STATIC_F8: return  VK_F8;
	case IDC_STATIC_F9: return  VK_F9;
	case IDC_STATIC_F10: return  VK_F10;
	case IDC_STATIC_F11: return  VK_F11;
	case IDC_STATIC_F12: return  VK_F12;
	case IDC_STATIC_PRTSC: return  VK_SNAPSHOT;
	case IDC_STATIC_SCROLL: return  VK_SCROLL;
	case IDC_STATIC_BREAK: return  VK_PAUSE;

	case IDC_STATIC_OEM_3: return  VK_OEM_3;
	case IDC_STATIC_1: return  VK_1;
	case IDC_STATIC_2: return  VK_2;
	case IDC_STATIC_3: return  VK_3;
	case IDC_STATIC_4: return  VK_4;
	case IDC_STATIC_5: return  VK_5;
	case IDC_STATIC_6: return  VK_6;
	case IDC_STATIC_7: return  VK_7;
	case IDC_STATIC_8: return  VK_8;
	case IDC_STATIC_9: return  VK_9;
	case IDC_STATIC_0: return  VK_0;
	case IDC_STATIC_MINUS: return  VK_OEM_MINUS;
	case IDC_STATIC_PLUS: return  VK_OEM_PLUS;
	case IDC_STATIC_BACK: return  VK_BACK;
	case IDC_STATIC_INSERT: return  VK_INSERT;
	case IDC_STATIC_HOME: return  VK_HOME;
	case IDC_STATIC_PAGEUP: return  VK_PRIOR;
	case IDC_STATIC_NUMLOCK: return  VK_NUMLOCK;
	case IDC_STATIC_DIVIDE: return  VK_DIVIDE;
	case IDC_STATIC_MULTIPLY: return  VK_MULTIPLY;
	case IDC_STATIC_SUBTRACT: return  VK_SUBTRACT;

	case IDC_STATIC_TAB: return  VK_TAB;
	case IDC_STATIC_Q: return  VK_Q;
	case IDC_STATIC_W: return  VK_W;
	case IDC_STATIC_E: return  VK_E;
	case IDC_STATIC_R: return  VK_R;
	case IDC_STATIC_T: return  VK_T;
	case IDC_STATIC_Y: return  VK_Y;
	case IDC_STATIC_U: return  VK_U;
	case IDC_STATIC_I: return  VK_I;
	case IDC_STATIC_O: return  VK_O;
	case IDC_STATIC_P: return  VK_P;
	case IDC_STATIC_OEM_4: return  VK_OEM_4;
	case IDC_STATIC_OEM_6: return  VK_OEM_6;
	case IDC_STATIC_OEM_5: return  VK_OEM_5;
	case IDC_STATIC_DELETE: return  VK_DELETE;
	case IDC_STATIC_END: return  VK_END;
	case IDC_STATIC_NEXT: return  VK_NEXT;
	case IDC_STATIC_NUMPAD7: return  VK_NUMPAD7;
	case IDC_STATIC_NUMPAD8: return  VK_NUMPAD8;
	case IDC_STATIC_NUMPAD9: return  VK_NUMPAD9;
	case IDC_STATIC_ADD: return  VK_ADD;

	case IDC_STATIC_CAPITAL: return  VK_CAPITAL;
	case IDC_STATIC_A: return  VK_A;
	case IDC_STATIC_S: return  VK_S;
	case IDC_STATIC_D: return  VK_D;
	case IDC_STATIC_F: return  VK_F;
	case IDC_STATIC_G: return  VK_G;
	case IDC_STATIC_H: return  VK_H;
	case IDC_STATIC_J: return  VK_J;
	case IDC_STATIC_K: return  VK_K;
	case IDC_STATIC_L: return  VK_L;
	case IDC_STATIC_OEM_1: return  VK_OEM_1;
	case IDC_STATIC_OEM_7: return  VK_OEM_7;
	case IDC_STATIC_RETURN: return  VK_RETURN;
	case IDC_STATIC_NUMPAD4: return  VK_NUMPAD4;
	case IDC_STATIC_NUMPAD5: return  VK_NUMPAD5;
	case IDC_STATIC_NUMPAD6: return  VK_NUMPAD6;

	case IDC_STATIC_LSHIFT: return  VK_LSHIFT;
	case IDC_STATIC_Z: return  VK_Z;
	case IDC_STATIC_X: return  VK_X;
	case IDC_STATIC_C: return  VK_C;
	case IDC_STATIC_V: return  VK_V;
	case IDC_STATIC_B: return  VK_B;
	case IDC_STATIC_N: return  VK_N;
	case IDC_STATIC_M: return  VK_M;
	case IDC_STATIC_OEM_COMMA: return  VK_OEM_COMMA;
	case IDC_STATIC_OEM_PERIOD: return  VK_OEM_PERIOD;
	case IDC_STATIC_OEM_2: return  VK_OEM_2;
	case IDC_STATIC_RSHIFT: return  VK_RSHIFT;
	case IDC_STATIC_UP: return  VK_UP;
	case IDC_STATIC_NUMPAD1: return  VK_NUMPAD1;
	case IDC_STATIC_NUMPAD2: return  VK_NUMPAD2;
	case IDC_STATIC_NUMPAD3: return  VK_NUMPAD3;

	case IDC_STATIC_LCONTROL: return  VK_LCONTROL;
	case IDC_STATIC_LWIN: return  VK_LWIN;
	case IDC_STATIC_LMENU: return  VK_LMENU;
	case IDC_STATIC_SPACE: return  VK_SPACE;
	case IDC_STATIC_RMENU: return  VK_RMENU;
	case IDC_STATIC_RWIN: return  VK_RWIN;
	case IDC_STATIC_MENU: return  VK_APPS;
	case IDC_STATIC_RCTRL: return  VK_RCONTROL;
	case IDC_STATIC_LEFT: return  VK_LEFT;
	case IDC_STATIC_DOWN: return  VK_DOWN;
	case IDC_STATIC_RIGHT: return  VK_RIGHT;
	case IDC_STATIC_NUMPAD0: return  VK_NUMPAD0;
	case IDC_STATIC_DECIMAL: return  VK_DECIMAL;
	}**/
return 1;
}

int CXK700Ctrl::TokeyByteIndex(int i, int j)
{
	/*switch(s_KEYID[i][j])
	{
	case IDC_STATIC_ESC: return 105;
	case IDC_STATIC_F1: return  107;
	case IDC_STATIC_F2: return  108;
	case IDC_STATIC_F3: return  109;
	case IDC_STATIC_F4: return  110;
	case IDC_STATIC_F5: return  111;
	case IDC_STATIC_F6: return  112;
	case IDC_STATIC_F7: return  113;
	case IDC_STATIC_F8: return  114;
	case IDC_STATIC_F9: return  115;
	case IDC_STATIC_F10: return  116;
	case IDC_STATIC_F11: return  117;
	case IDC_STATIC_F12: return  118;
	case IDC_STATIC_PRTSC: return  119;
	case IDC_STATIC_SCROLL: return  120;
	case IDC_STATIC_BREAK: return  121;

	case IDC_STATIC_OEM_3: return 84;
	case IDC_STATIC_1: return  85;
	case IDC_STATIC_2: return  86;
	case IDC_STATIC_3: return  87;
	case IDC_STATIC_4: return  88;
	case IDC_STATIC_5: return  89;
	case IDC_STATIC_6: return  90;
	case IDC_STATIC_7: return  91;
	case IDC_STATIC_8: return  92;
	case IDC_STATIC_9: return  93;
	case IDC_STATIC_0: return  94;
	case IDC_STATIC_MINUS: return  95;
	case IDC_STATIC_PLUS: return  96;
	case IDC_STATIC_BACK: return  97;
	case IDC_STATIC_INSERT: return  98;
	case IDC_STATIC_HOME: return  99;
	case IDC_STATIC_PAGEUP: return  100;
	case IDC_STATIC_NUMLOCK: return  101;
	case IDC_STATIC_DIVIDE: return  102;
	case IDC_STATIC_MULTIPLY: return  103;
	case IDC_STATIC_SUBTRACT: return  104;

	case IDC_STATIC_TAB: return  63;
	case IDC_STATIC_Q: return  64;
	case IDC_STATIC_W: return  65;
	case IDC_STATIC_E: return  66;
	case IDC_STATIC_R: return  67;
	case IDC_STATIC_T: return  68;
	case IDC_STATIC_Y: return  69;
	case IDC_STATIC_U: return  70;
	case IDC_STATIC_I: return  71;
	case IDC_STATIC_O: return  72;
	case IDC_STATIC_P: return  73;
	case IDC_STATIC_OEM_4: return  74;
	case IDC_STATIC_OEM_6: return  75;
	case IDC_STATIC_OEM_5: return  76;
	case IDC_STATIC_DELETE: return  77;
	case IDC_STATIC_END: return  78;
	case IDC_STATIC_NEXT: return  79;
	case IDC_STATIC_NUMPAD7: return  80;
	case IDC_STATIC_NUMPAD8: return  81;
	case IDC_STATIC_NUMPAD9: return  82;
	case IDC_STATIC_ADD: return  62;

	case IDC_STATIC_CAPITAL: return  42;
	case IDC_STATIC_A: return  43;
	case IDC_STATIC_S: return  44;
	case IDC_STATIC_D: return  45;
	case IDC_STATIC_F: return  46;
	case IDC_STATIC_G: return  47;
	case IDC_STATIC_H: return  48;
	case IDC_STATIC_J: return  49;
	case IDC_STATIC_K: return  50;
	case IDC_STATIC_L: return  51;
	case IDC_STATIC_OEM_1: return  52;
	case IDC_STATIC_OEM_7: return  53;
	case IDC_STATIC_RETURN: return  76;
	case IDC_STATIC_NUMPAD4: return  59;
	case IDC_STATIC_NUMPAD5: return  60;
	case IDC_STATIC_NUMPAD6: return  61;

	case IDC_STATIC_LSHIFT: return  21;
	case IDC_STATIC_Z: return  22;
	case IDC_STATIC_X: return  23;
	case IDC_STATIC_C: return  24;
	case IDC_STATIC_V: return  25;
	case IDC_STATIC_B: return  26;
	case IDC_STATIC_N: return  27;
	case IDC_STATIC_M: return  28;
	case IDC_STATIC_OEM_COMMA: return  29;
	case IDC_STATIC_OEM_PERIOD: return  30;
	case IDC_STATIC_OEM_2: return  31;
	case IDC_STATIC_RSHIFT: return  33;
	case IDC_STATIC_UP: return  36;
	case IDC_STATIC_NUMPAD1: return  38;
	case IDC_STATIC_NUMPAD2: return  39;
	case IDC_STATIC_NUMPAD3: return  40;

	case IDC_STATIC_LCONTROL: return  0;
	case IDC_STATIC_LWIN: return  1;
	case IDC_STATIC_LMENU: return  2;
	case IDC_STATIC_SPACE: return  5;
	case IDC_STATIC_RMENU: return  9;
	case IDC_STATIC_RWIN: return  11;
	case IDC_STATIC_MENU: return  12;
	case IDC_STATIC_RCTRL: return  13;
	case IDC_STATIC_LEFT: return  14;
	case IDC_STATIC_DOWN: return  15;
	case IDC_STATIC_RIGHT: return  16;
	case IDC_STATIC_NUMPAD0: return  17;
	case IDC_STATIC_DECIMAL: return  19;
	case IDC_STATIC_NUMRETURN: return  20;
	}*/
return 1;
}

void CXK700Ctrl::ToIndex(WORD dwKey, int& i, int& j)
{
	switch(dwKey)
	{
	case VK_ESCAPE:	i = 0; j = 1;	break;
	case VK_F1:		i = 0; j = 2;	break;
	case VK_F2:		i = 0; j = 3;	break;
	case VK_F3:		i = 0; j = 4;	break;
	case VK_F4:		i = 0; j = 5;	break;
	case VK_F5:		i = 0; j = 7;	break;
	case VK_F6:		i = 0; j = 8;	break;
	case VK_F7:		i = 0; j = 9;	break;
	case VK_F8:		i = 0; j = 10;	break;
	case VK_F9:		i = 0; j = 11;	break;
	case VK_F10:	i = 0; j = 12;	break;
	case VK_F11:	i = 0; j = 13;	break;
	case VK_F12:	i = 0; j = 14;	break;
	case VK_SNAPSHOT:	i = 0; j = 15;	break;
	case VK_SCROLL:	i = 0; j = 16;	break;
	case VK_PAUSE:	i = 0; j = 17;	break;

		//case VK_G1:		i = 1;  j = 0;	break;
	case VK_OEM_3:	i = 1;  j = 1;	break;
	case VK_1:		i = 1;  j = 2;	break;
	case VK_2:		i = 1;  j = 3;	break;
	case VK_3:		i = 1;  j = 4;	break;
	case VK_4:		i = 1;  j = 5;	break;
	case VK_5:		i = 1;  j = 6;	break;
	case VK_6:		i = 1;  j = 7;	break;
	case VK_7:		i = 1;  j = 8;	break;
	case VK_8:		i = 1;  j = 9;	break;
	case VK_9:		i = 1;  j = 10;	break;
	case VK_0:		i = 1;  j = 11;	break;
	case VK_OEM_MINUS:	i = 1;  j = 12;	break;
	case VK_OEM_PLUS:	i = 1;  j = 13;	break;
	case VK_BACK:	i = 1;  j = 14;	break;
	case VK_INSERT:	i = 1;  j = 15;	break;
	case VK_HOME:	i = 1;  j = 16;	break;
	case VK_PRIOR:	i = 1;  j = 17;	break;
	case VK_NUMLOCK:i = 1;  j = 18;	break;
	case VK_DIVIDE:	i = 1;  j = 19;	break;
	case VK_MULTIPLY:i = 1;  j = 20;break;
	case VK_SUBTRACT:i = 1;  j = 21;break;

		//case VK_G2:		i = 2;  j = 0;	break;
	case VK_TAB:	i = 2;  j = 1;	break;
	case VK_Q:		i = 2;  j = 2;	break;
	case VK_W:		i = 2;  j = 3;	break;
	case VK_E:		i = 2;  j = 4;	break;
	case VK_R:		i = 2;  j = 5;	break;
	case VK_T:		i = 2;  j = 6;	break;
	case VK_Y:		i = 2;  j = 7;	break;
	case VK_U:		i = 2;  j = 8;	break;
	case VK_I:		i = 2;  j = 9;	break;
	case VK_O:		i = 2;  j = 10;	break;
	case VK_P:		i = 2;  j = 11;	break;
	case VK_OEM_4:	i = 2;  j = 12;	break;
	case VK_OEM_6:	i = 2;  j = 13;	break;
	case VK_OEM_5:	i = 2;  j = 14;	break;
	case VK_DELETE:	i = 2;  j = 15;	break;
	case VK_END:	i = 2;  j = 16;	break;
	case VK_NEXT:	i = 2;  j = 17;	break;
	case VK_NUMPAD7:i = 2;  j = 18;	break;
	case VK_NUMPAD8:i = 2;  j = 19;	break;
	case VK_NUMPAD9:i = 2;  j = 20;	break;
	case VK_ADD:	i = 2;  j = 21;	break;

		//case VK_G3:		i = 3;  j = 0;	break;
	case VK_CAPITAL:i = 3;  j = 1;	break;
	case VK_A:		i = 3;  j = 2;	break;
	case VK_S:		i = 3;  j = 3;	break;
	case VK_D:		i = 3;  j = 4;	break;
	case VK_F:		i = 3;  j = 5;	break;
	case VK_G:		i = 3;  j = 6;	break;
	case VK_H:		i = 3;  j = 7;	break;
	case VK_J:		i = 3;  j = 8;	break;
	case VK_K:		i = 3;  j = 9;	break;
	case VK_L:		i = 3;  j = 10;	break;
	case VK_OEM_1:	i = 3;  j = 11;	break;
	case VK_OEM_7:	i = 3;  j = 12;	break;
	case VK_RETURN:	i = 3;  j = 14;	break;
	case VK_NUMPAD4:i = 3;  j = 18;	break;
	case VK_NUMPAD5:i = 3;  j = 19;	break;
	case VK_NUMPAD6:i = 3;  j = 20;	break;

		//case VK_G4:		i = 4;  j = 0;	break;
	case VK_LSHIFT:	i = 4;  j = 1;	break;
	case VK_Z:		i = 4;  j = 2;	break;
	case VK_X:		i = 4;  j = 3;	break;
	case VK_C:		i = 4;  j = 4;	break;
	case VK_V:		i = 4;  j = 5;	break;
	case VK_B:		i = 4;  j = 6;	break;
	case VK_N:		i = 4;  j = 7;	break;
	case VK_M:		i = 4;  j = 8;	break;
	case VK_OEM_COMMA:	i = 4;  j = 9;	break;
	case VK_OEM_PERIOD:	i = 4;  j = 10;	break;
	case VK_OEM_2:		i = 4;  j = 11;	break;
	case VK_RSHIFT:		i = 4;  j = 13;	break;
	case VK_UP:			i = 4;  j = 15;	break;
	case VK_NUMPAD1:	i = 4;  j = 17;	break;
	case VK_NUMPAD2:	i = 4;  j = 18;	break;
	case VK_NUMPAD3:	i = 4;  j = 19;	break;

		//case VK_G5:			i = 5;  j = 0;	break;
	case VK_LCONTROL:	i = 5;  j = 1;	break;
	case VK_LWIN:		i = 5;  j = 2;	break;
	case VK_LMENU:		i = 5;  j = 3;	break;
	case VK_SPACE:		i = 5;  j = 6;	break;
	case VK_RMENU:		i = 5;  j = 10;	break;
	case VK_RWIN:		i = 5;  j = 11;	break;
	case VK_APPS:		i = 5;  j = 12;	break;
	case VK_RCONTROL:	i = 5;  j = 13;	break;
	case VK_LEFT:		i = 5;  j = 14;	break;
	case VK_DOWN:		i = 5;  j = 15;	break;
	case VK_RIGHT:		i = 5;  j = 11;	break;
	case VK_NUMPAD0:	i = 5;  j = 12;	break;
	case VK_DECIMAL:	i = 5;  j = 14;	break;
		//case VK_NUMRETURN:	i = 5;  j = 15;	break;
	}
}
