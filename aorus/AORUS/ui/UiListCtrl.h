#ifndef _UI_LISTCTRL_H
#define _UI_LISTCTRL_H

#include "UiBase.h"
typedef struct _UI_LST_EDIT
{
	int nRow;
	int nCol;
	TCHAR szValue[1024];

}UI_LST_EDIT, *PUI_LST_EDIT;
class CUiListCtrl : public CListCtrl
{
public:
	CUiListCtrl();
	virtual ~CUiListCtrl();

public:   
	void  CreateList(UINT uId, CRect rc,  CWnd* pParentWnd, int nImgWidth, int nImgHeight, bool bEdit/*, UINT nCursorId*/);
	void  SetCursor(UINT nCursorId); 
	int   InsertImgItem(int nIndex, UINT uBitmap);
	void  RemoveImgItem(int nIndex);
	void  SetScrollSliCtrl(UI_SLIDERCTRL sliderCtrl, UI_BTN btnUp, UI_BTN btnDown);
	void  RemoveAllItem();
	int	  GetCurSel();
	void  SetCurSel(int nSel);	// Peter Lee 2017/7/9
	void  ToEdit(int nRow, int nCol);
	CEdit* GetEdit() { return &m_edit; }

protected:
	void  DisposeEdit();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	int InsertItem(const LVITEM* pItem);
	void ShowScrollself(bool bShow);

	CImageList*  m_ImgList;;
    int          m_nEditIndex;
	bool		 m_bEdit;
	CUiEdit		 m_edit;
	int			 m_nEditRow;
	int			 m_nEditCol;

	bool		 m_bLButtonDown;
	int			 m_nImgWidth;
	int			 m_nImgHeight;
	UINT		 m_nCursorId;
	HCURSOR		 m_hCursor;
	int			 m_nItemHeight;
	CUiSliderCtrl m_Slide;
	CUiButton	 m_BtnUp;
	CUiButton	 m_BtnDown;
	UINT		 m_scrollId;
	UINT		 m_btnUpId;
	UINT		 m_btnDownId;

	COLORREF	 m_BkClr;
	COLORREF	 m_ItemClr;
	COLORREF	 m_TextClr;
	COLORREF	 m_ItemSelClr;
	COLORREF	 m_TextSelClr;

protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);

	//{{AFX_MSG(CUiCurveGraphCtrl)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void MeasureItem (LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	afx_msg void OnNMCustomdraw(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg LRESULT OnUiSliderMoving(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUiButtonClick(WPARAM wParam, LPARAM lParam);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
};

#endif 
