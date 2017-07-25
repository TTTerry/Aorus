#include "stdafx.h"
#include "UiEdit.h"


#define UIEDT_TYPE_NORMAL	0x0000
#define UIEDT_TYPE_FLOAT	0x0001
#define UIEDT_TYPE_INTEGER	0x0002
#define UIEDT_TYPE_HEX		0x0003

CUiEdit::CUiEdit()
{
	m_pFont   = NULL;
	m_clrText = CLR_NONE;
	m_nNumType = UIEDT_TYPE_NORMAL;
	m_nLength = 20;
	m_nDec    = 2;
	m_bAdjustCaret = true;
}

CUiEdit::~CUiEdit()
{
	m_Brush.DeleteObject();
}


BEGIN_MESSAGE_MAP(CUiEdit, CEdit)
	//ON_WM_NCPAINT()
	ON_WM_CHAR()
	ON_WM_CTLCOLOR_REFLECT()
	ON_CONTROL_REFLECT(EN_CHANGE, OnChange)
	ON_CONTROL_REFLECT(EN_SETFOCUS, OnSetFocus)
	ON_CONTROL_REFLECT(EN_KILLFOCUS , OnChanged)
END_MESSAGE_MAP()

BOOL CUiEdit::Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID)
{
	BOOL bSuccess = CEdit::Create(dwStyle, rect, pParentWnd, nID);
	if (bSuccess)
	{
		m_Height = CRect(rect).Height();
	}
	return bSuccess;
}

CToolTipCtrl* CUiEdit::GetToolTipCtrl()
{
	return &m_toolTip;
}

void CUiEdit::SetToolTip(CString sTip, int nMaxTipWidth)
{
	if(NULL != GetSafeHwnd() && sTip != _T("")) 
	{
		if(NULL == m_toolTip.GetSafeHwnd()) 
		{
			m_toolTip.Create(this, TTS_ALWAYSTIP);
			m_toolTip.Activate(TRUE);
			m_toolTip.AddTool(this, sTip);
			if(nMaxTipWidth > 0)
			{
				m_toolTip.SetMaxTipWidth(nMaxTipWidth);
			}
		}
		else
		{
			m_toolTip.UpdateTipText(sTip, this);	
			if(nMaxTipWidth > 0)
			{
				m_toolTip.SetMaxTipWidth(nMaxTipWidth);
			}
		}
	}
}

void CUiEdit::SetAsIntNumberEdit(int nLen)
{
	m_nNumType = UIEDT_TYPE_INTEGER;

	if(nLen > 0)
	{
		m_nLength = nLen;
	}
}

void CUiEdit::SetAsHexNumberEdit(int nLen)
{
	m_nNumType = UIEDT_TYPE_HEX;

	if(nLen > 0)
	{
		m_nLength = nLen;
	}
}

void CUiEdit::SetAsFloatNumberEdit(int nLen, int nPrecision)
{
	m_nNumType = UIEDT_TYPE_FLOAT;

	if(nLen > 0)
	{
		m_nLength = nLen;
	}

	if(nPrecision > 0)
	{
		m_nDec = nPrecision;
	}
}

void CUiEdit::SetWindowsValue(double fValue)
{
	ASSERT(UIEDT_TYPE_NORMAL != m_nNumType);
	CString sValue = _T("");
	switch (m_nNumType)
	{
	case UIEDT_TYPE_FLOAT: sValue.Format(_T("%g"), fValue); break;
	case UIEDT_TYPE_INTEGER: sValue.Format(_T("%d"), (int)fValue); break;
	case UIEDT_TYPE_HEX: sValue.Format(_T("%x"), (int)fValue); break;
	}
	if(UIEDT_TYPE_NORMAL != m_nNumType) SetWindowText(sValue);
}

double CUiEdit::GetWindowsValue()
{
	ASSERT(UIEDT_TYPE_NORMAL != m_nNumType);
	CString sValue = _T("");
	double fValue = -1;
	GetWindowText(sValue);
	switch (m_nNumType)
	{
	case UIEDT_TYPE_FLOAT: fValue = _tstof(sValue); break;
	case UIEDT_TYPE_INTEGER: fValue = _ttoi(sValue); break;
	case UIEDT_TYPE_HEX: fValue = _tcstol(sValue, NULL, 16); break;
	}
	return fValue;
}

BOOL CUiEdit::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_MOUSEMOVE)
	{
		if (m_toolTip.GetSafeHwnd()) { m_toolTip.RelayEvent(pMsg); }
	}
	return CEdit::PreTranslateMessage(pMsg);
}

//-------------------------------------------------------------------------------
void CUiEdit::SetFont(CFont* pFont, COLORREF clrFont)
{
	m_pFont   = pFont;
	m_clrText = clrFont;
}
//-------------------------------------------------------------------------------
void CUiEdit::SetBkColor(COLORREF clrBk)
{
	ASSERT(clrBk != CLR_NONE);

	m_Brush.DeleteObject();
	m_Brush.CreateSolidBrush(clrBk);
}
//-------------------------------------------------------------------------------
void CUiEdit::SetBkBitmap(UINT uBitmap, BOOL bAutoMove)
{
	ASSERT(uBitmap != 0);
	
	CBitmap bitmap;
	bitmap.LoadBitmap(uBitmap);
	m_Brush.DeleteObject();
	m_Brush.CreatePatternBrush(&bitmap); 
	if(bAutoMove)
	{
		BITMAP bmp;
		bitmap.GetBitmap(&bmp);
		SetWindowPos(NULL, 0, 0, bmp.bmWidth, bmp.bmHeight, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
	}
	bitmap.DeleteObject();
}
//-------------------------------------------------------------------------------
HBRUSH CUiEdit::CtlColor(CDC* pDC, UINT nCtlColor)
{
	pDC->SetBkMode(TRANSPARENT);

	if(m_pFont != NULL)
	{
		pDC->SelectObject(m_pFont);
	}

	if(m_clrText != CLR_NONE)
	{
		pDC->SetTextColor(m_clrText);
	}

	if(NULL != m_Brush.GetSafeHandle())
	{
		return (HBRUSH)m_Brush;
	}

	return NULL; //TODO: Return a NULL brush if the parent's handler should be called. 
}
//-------------------------------------------------------------------------------
void CUiEdit::OnChanged()
{
	CWnd* pParent = GetParent();
	while(NULL != pParent)
	{
		if(pParent->SendMessage(WM_UI_EDIT_CHANGE, GetDlgCtrlID(), NULL)) break;
		pParent = pParent->GetParent();
	}
}
//-------------------------------------------------------------------------------
void CUiEdit::OnSetFocus()
{
	if (m_bAdjustCaret)
	{
		CreateSolidCaret(1, m_Height);
	}
	ShowCaret();
}
//-------------------------------------------------------------------------------
void CUiEdit::OnChange()
{
	// TODO: If this is a RICHEDIT control, the control will not 
	// send this notification unless you override the CEdit::OnInitDialog() 
	// function and call CRichEditCtrl().SetEventMask() 
	// with the ENM_CHANGE flag ORed into the mask. 
	if(!(GetStyle() & ES_READONLY))
	{
		InvalidateRect(NULL, FALSE);
	}
}
//-------------------------------------------------------------------------------
void CUiEdit::OnNcPaint() 
{
	return CEdit::OnNcPaint();
}
//-------------------------------------------------------------------------------
void CUiEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if(UIEDT_TYPE_NORMAL == m_nNumType)
	{
		return CEdit::OnChar(nChar, nRepCnt, nFlags);
	}

	BOOL bConitue = FALSE;

	if(UIEDT_TYPE_INTEGER == m_nNumType)
	{
		//有效按键是数字和负号正号和回退键
		bConitue = (nChar >= 48 && nChar <= 57) // '0' ~ '9'
			|| nChar == 43	// '+'
			|| nChar == 45	// '-'
			|| nChar == 8;	// Back
	}
	if(UIEDT_TYPE_HEX == m_nNumType)
	{
		//有效按键是数字和负号正号和回退键
		bConitue = (nChar >= 48 && nChar <= 57) // '0' ~ '9'
			|| (nChar >= 'A' && nChar <= 'F')	// 'A' ~ 'F'
			|| (nChar >= 'a' && nChar <= 'f')	// 'a' ~ 'f'
			|| nChar == 8;	// Back
		if (nChar >= 'a' && nChar <= 'f') 
			nChar = nChar - 'a' + 'A';
	}
	else if(UIEDT_TYPE_FLOAT == m_nNumType)
	{
		//有效按键是数字和负号正号小数点和回退键
		bConitue = (nChar >= 48 && nChar <= 57) // '0' ~ '9'
					|| nChar == 43	// '+'
					|| nChar == 45	// '-'
					|| nChar == 46	// '.'
					|| nChar == 8;	// Back
	}

	if(!bConitue)
		return;

	CString sBefore,sAfter;
	GetWindowText(sBefore);

	//保存光标位置
	int nPosCurbgn, nPosCurend;
	GetSel(nPosCurbgn, nPosCurend);
	CEdit::OnChar(nChar,  nRepCnt,  nFlags);
	GetWindowText(sAfter);
	int nLength = sAfter.GetLength();
	int nDotPos = sAfter.Find(_T("."));

	if(1 == sAfter.GetLength())
		return;

	// 长度超过设置
	if(nLength > m_nLength)
	{
		SetWindowText(sBefore);
		SetSel(nPosCurbgn, nPosCurend, true);
		return;
	}

	// 精度超过设置
	if(nDotPos != CB_ERR && nLength - nDotPos -1 > m_nDec)
	{
		SetWindowText(sBefore);
		SetSel(nPosCurbgn, nPosCurend, true);
		return;
	}

	// 小数点在首位
	if(nLength > 0 && sAfter.Left(1) == _T("."))
	{
		SetWindowText(sBefore);
		SetSel(nPosCurbgn, nPosCurend, true);
		return;
	}

	// 超过一个小数点
	if(sBefore.Find(_T(".")) != CB_ERR && nChar == 46)
	{
		SetWindowText(sBefore);
		SetSel(nPosCurbgn, nPosCurend, true);
		return;
	}

	// 超过一个+号, 或者不在第一位
	if(sBefore.Find(_T("-")) != CB_ERR && nChar == 45)
	{
		SetWindowText(sBefore);
		SetSel(nPosCurbgn, nPosCurend, true);
		return;
	}

	// 超过一个-号, 或者不在第一位
	if(sBefore.Find(_T("+")) != CB_ERR && nChar == 43)
	{
		SetWindowText(sBefore);
		SetSel(nPosCurbgn, nPosCurend, true);
		return;
	}

	// 同时存在+和-符号
	if((sBefore.Find(_T("+")) != CB_ERR && nChar == 45) || (sBefore.Find(_T("-")) != CB_ERR && nChar == 43))
	{
		sBefore.SetAt(0, nChar);
		SetWindowText(sBefore);
		SetSel(nPosCurbgn, nPosCurend, true);
		return;
	}

	// 存在类似"00.0"或"0123"等最前面为'0', 但'0'后面不为'.'的情况. 
	if(
		(nChar != 46 && nChar != 8) && // '.' & back
		(
			(0 == sAfter.Find(_T("+")) && 1 == sAfter.Find(_T("0"))) ||
			(0 == sAfter.Find(_T("-")) && 1 == sAfter.Find(_T("0"))) ||
			(0 == sAfter.Find(_T("0")))
		)
	)
	{
		CString sTmp = sAfter;
		if(0 == sAfter.Find(_T("+")) || 0 == sAfter.Find(_T("-"))) 
			sAfter = sAfter.Mid(0, 1) + sTmp.Mid(2, sTmp.GetLength() - 2);
		if(0 == sAfter.Find(_T("0"))) 
			sAfter = sTmp.Mid(1, sTmp.GetLength() - 1);
		SetWindowText(sAfter);
		SetSel(nPosCurbgn, nPosCurend, true);
		return;
	}
}
