#ifndef _UI_CDIALOG_H
#define _UI_CDIALOG_H


/*****************************************************************************************************************
 *
 * CUiDlg: 由CDialog继承而来，用于实现对话框窗口的不规则绘制、透明绘制等功能。注意：绘图时，不存在父子关系的窗口与
 *         窗口之间重叠会导致先绘制的窗口在重叠区域中无法显示,而后绘制的窗口摆放在重叠区域的控件无法正常工作!!!
 *
 *****************************************************************************************************************/

class CUiDlg : public CDialog
{
	DECLARE_DYNAMIC(CUiDlg)

public:
	CUiDlg();
	CUiDlg(UINT nIDTemplate, CWnd* pParentWnd=NULL);
	CUiDlg(LPCTSTR lpszTemplateName, CWnd* pParentWnd=NULL);
	virtual ~CUiDlg();

public:
	// 资源的id，透明度，
	void    SetBkBitmap(UINT uId, UINT uAlpha=0xff, COLORREF clrMask=CLR_NONE);    // Set attributes of this dialog. 
	void    SetWinRgn(HRGN hWinGgn/*if null, set window region to null. this parameter will be ignored for have-no-parent window*/); 
	CDC*    GetBkDC();                                                             // Get memory dc of background.

private:
	void    Init();

private:
	UINT       m_uBk;
	UINT       m_uAlpha;
	COLORREF   m_clrMask;
	CDC        m_BkDC;
	bool       m_bStoredBkDc;
	bool       m_bPopupWin;
	bool	   m_bPopup;
	HRGN       m_hWinRgn;

protected:
	afx_msg void    OnPaint();
	afx_msg BOOL    OnEraseBkgnd(CDC* pDC);
	afx_msg LRESULT OnNcHitTest(CPoint point);
	DECLARE_MESSAGE_MAP()

	virtual BOOL    OnCommand(WPARAM wParam, LPARAM lParam);
	//virtual BOOL    OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
};

#endif 
