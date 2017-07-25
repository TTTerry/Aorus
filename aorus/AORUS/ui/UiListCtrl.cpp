#include "stdafx.h"
#include "UiListCtrl.h"
#include "UiCommon.h"
	
//--------------------------------------------------------------------------------------------------------
CUiListCtrl::CUiListCtrl()
{
	//m_Slide = NULL;
	m_scrollId = 0;
	m_btnUpId = 0;
	m_btnDownId = 0;
	m_ImgList = NULL;
	m_bLButtonDown = false;
	m_nImgWidth = 0;
	m_nImgHeight = 0;
	m_nCursorId = NULL;
	m_nEditIndex=0;
	m_BkClr = RGB(0, 0, 0);
	m_ItemClr = RGB(0, 0, 0);
	m_TextClr = RGB(255, 255, 255);
	m_ItemSelClr = RGB(88, 35, 0);
	m_TextSelClr = RGB(255, 255, 255);

}

CUiListCtrl::~CUiListCtrl()
{
	if (NULL != m_ImgList)
	{
		m_ImgList->DeleteImageList();
		delete m_ImgList;
	}
}


BEGIN_MESSAGE_MAP(CUiListCtrl, CListCtrl)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_MEASUREITEM()
	ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, &CUiListCtrl::OnNMCustomdraw)
	ON_MESSAGE(WM_UI_SLIDER_MOVING, &CUiListCtrl::OnUiSliderMoving)
	ON_MESSAGE(WM_UI_BUTTON_CLICKED, &CUiListCtrl::OnUiButtonClick)
	ON_WM_NCCALCSIZE()
	ON_WM_VSCROLL()
	ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()

//--------------------------------------------------------------------------------------------------------
void CUiListCtrl::CreateList(UINT uId, CRect rc, CWnd* pParentWnd, int nImgWidth, int nImgHeight, bool bEdit/*, UINT nCursorId*/)
{
	Create(WS_CHILD | WS_VISIBLE | LVS_REPORT | LVS_NOCOLUMNHEADER | LVS_SINGLESEL, rc, pParentWnd, uId);

	DWORD dwStyle = GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT; //选中某行使整行高亮
	//dwStyle |= LVS_EX_GRIDLINES;
	dwStyle |= LVS_EX_DOUBLEBUFFER;
	SetExtendedStyle(dwStyle);

	SetBkColor(m_BkClr);
	SetTextBkColor(m_ItemClr);
	SetTextColor(m_TextClr);
	SetIconSpacing(CSize(50,50));

	//m_ImgList = new CImageList();
	//m_ImgList->Create(nImgWidth, nImgHeight, ILC_COLOR32, 255, 255); 
	m_nImgWidth = nImgWidth;
	m_nImgHeight = nImgHeight;
	//m_nCursorId = nCursorId;

	m_bEdit = bEdit;
	m_edit.Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP | ES_AUTOHSCROLL | ES_CENTER, CRect(0, 0, 0, 0), this, 1);
	m_edit.ShowWindow(SW_HIDE);
}
//-------------------------------------------------------------------------------
int CUiListCtrl::InsertImgItem(int nIndex, UINT uBitmap)
{
	//CBitmap bitmap;
	//bitmap.LoadBitmap(uBitmap);
	//int n = 0;
	//if(NULL != m_ImgList) m_ImgList->Add(&bitmap, RGB(0, 0, 0));
	//bitmap.DeleteObject();
	//if(NULL != m_ImgList) SetImageList(m_ImgList, LVSIL_SMALL);

	LVITEM lvItem={0};                               // 列表视图控 LVITEM用于定义"项"的结构  
	//第一行数据  
	lvItem.mask = LVIF_IMAGE|LVIF_TEXT|LVIF_STATE;   // 文字、图片、状态  
	lvItem.iItem = nIndex;                           // 行号(第一行)  
	//lvItem.iImage = n;                          // 图片索引号  
	lvItem.iSubItem = 0;                             // 子列号  
	return InsertItem(&lvItem);  
}
//-------------------------------------------------------------------------------
int CUiListCtrl::InsertItem(const LVITEM* pItem)
{
	int nRet = CListCtrl::InsertItem(pItem->iItem, _T(""));
	if(NULL != m_Slide.GetSafeHwnd())
	{
		int nMin = 0, nMax = 0;
		GetScrollRange(SB_VERT, &nMin, &nMax);
		m_Slide.SetRange(nMin, nMax);
		ShowScrollself(nMax > 2);
	}
	return nRet;
}
//-------------------------------------------------------------------------------
void CUiListCtrl::SetScrollSliCtrl(UI_SLIDERCTRL sliderCtrl, UI_BTN btnUp, UI_BTN btnDown)
{
	sliderCtrl.pParent = this;
	btnUp.pParent = this;
	btnDown.pParent = this;

	// 設置滾動條
	m_Slide.CreateSliderCtrl(sliderCtrl);
	m_Slide.ModifyCtrlStyle(0, UISCS_VERTICAL);
	m_scrollId = sliderCtrl.uId;
	int nMin = 0, nMax = 0;
	GetScrollRange(SB_VERT, &nMin, &nMax);
	m_Slide.SetRange(nMin, nMax);
	ShowScrollBar(SB_VERT, SW_HIDE);

	// 設置向上按鈕
	m_BtnUp.CreateButton(btnUp);
	m_BtnUp.EnableConsecutiveHits(true);
	m_btnUpId = btnUp.uId;

	// 設置向下按鈕
	m_BtnDown.CreateButton(btnDown);
	m_BtnDown.EnableConsecutiveHits(true);
	m_btnDownId = btnDown.uId;

}
//-------------------------------------------------------------------------------
void CUiListCtrl::RemoveImgItem(int nIndex)
{
	SetItemState(nIndex, 0, LVIS_SELECTED | LVIS_FOCUSED);
	DeleteItem(nIndex);
	if(nIndex < GetItemCount()) SetItemState(nIndex, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
	int nMin = 0, nMax = 0;
	GetScrollRange(SB_VERT, &nMin, &nMax);
	m_Slide.SetRange(nMin, nMax);
	ShowScrollself(nMax > 2);
	//m_ImgList->Remove(nIndex);
}
//-------------------------------------------------------------------------------
void CUiListCtrl::RemoveAllItem()
{
	DeleteAllItems();
	if(NULL != m_ImgList) m_ImgList->DeleteImageList();
	if(NULL != m_ImgList) delete m_ImgList;
	m_ImgList = NULL;
	//m_ImgList = new CImageList();
	//m_ImgList->Create(m_nImgWidth, m_nImgHeight, ILC_COLOR32, 255, 255); 
	int nMin = 0, nMax = 0;
	GetScrollRange(SB_VERT, &nMin, &nMax);
	m_Slide.SetRange(nMin, nMax);
	ShowScrollself(nMax > 2);
}
//-------------------------------------------------------------------------------
void CUiListCtrl::OnLButtonDown(UINT nFlags, CPoint point)
{
	SetFocus();
	SetCapture();
	m_bLButtonDown = true;
	CListCtrl::OnLButtonDown(nFlags, point);

	CWnd* pParent = GetParent();
	while(NULL != pParent)
	{
		if(pParent->SendMessage(WM_UI_LIST_CLK, GetDlgCtrlID(), GetCurSel())) break;
		pParent = pParent->GetParent();
	}
	//OnMouseMove(nFlags, point);
}
//-------------------------------------------------------------------------------
void CUiListCtrl::OnMouseMove(UINT nFlags, CPoint point)
{
	if (m_bLButtonDown)
	{
		//SetCursor(m_nCursorId);
		//Active WM_MOUSELEAVE message
	}
	CListCtrl::OnMouseMove(nFlags, point);
}
//-------------------------------------------------------------------------------
void CUiListCtrl::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (!m_bLButtonDown) return;
	m_bLButtonDown = false;

	ReleaseCapture();
	//SetCursor(NULL);
	CListCtrl::OnLButtonUp(nFlags, point);
}
//-------------------------------------------------------------------------------
void CUiListCtrl::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	CWnd* pParent = GetParent();
	m_nEditIndex=GetCurSel();
	while(NULL != pParent)
	{
		if(pParent->SendMessage(WM_UI_LIST_DBLCLK, GetDlgCtrlID(), GetCurSel())) break;
		pParent = pParent->GetParent();
	}
	if (m_bEdit)
	{
		LVHITTESTINFO info;
		info.pt = point;
		info.flags = LVHT_ONITEMLABEL;
		if(SubItemHitTest(&info) >= 0)     //SubItemHitTest进行点击测试，目的是确定双击的单元格是第几行第几列。
		{
			int nRow = info.iItem;                        //行索引
			int nCol = info.iSubItem;                     //列索引
			if(nRow == GetItemCount()) return;
			ToEdit(nRow, nCol);
		}
	}
}
//-------------------------------------------------------------------------------
void CUiListCtrl::SetCursor(UINT nCursorId)
{
	if(m_hCursor != NULL) 
	{ 
		::DestroyCursor(m_hCursor);
		m_hCursor = NULL;
	}

	if(nCursorId != -1)
	{
		m_hCursor = (HCURSOR)::LoadImage(AfxFindResourceHandle(MAKEINTRESOURCE(nCursorId), RT_GROUP_CURSOR), 
			MAKEINTRESOURCE(nCursorId), IMAGE_CURSOR, 0, 0, 0);
	}
}

int CUiListCtrl::GetCurSel()
{
	int nSel = -1;
	for(int i=0; i<GetItemCount(); i++)
	{
		if(LVIS_SELECTED == GetItemState(i, LVIS_SELECTED))
		{
			nSel = i; break;
		}
	}

	return nSel;
}

void CUiListCtrl::SetCurSel(int nSel)	// Peter Lee 2017/7/9
{
	SetItemState(nSel, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
    EnsureVisible(nSel, FALSE);
    Invalidate();
}

void CUiListCtrl::MeasureItem ( LPMEASUREITEMSTRUCT lpMeasureItemStruct )
{
	if( m_nItemHeight > 0 )
		lpMeasureItemStruct->itemHeight = m_nItemHeight;
}

void CUiListCtrl::OnNMCustomdraw(NMHDR *pNMHDR, LRESULT *pResult)
{
	static BOOL s_bThisItemSelect = FALSE;

	NMLVCUSTOMDRAW* pLVCD = reinterpret_cast<LPNMLVCUSTOMDRAW>(pNMHDR);
	*pResult = CDRF_DODEFAULT;
	switch (pLVCD->nmcd.dwDrawStage)
	{
	case CDDS_PREPAINT:
		*pResult = CDRF_NOTIFYITEMDRAW;   
		break;

	case CDDS_ITEMPREPAINT:
		{
			UINT ordin = pLVCD->nmcd.lItemlParam;   

			s_bThisItemSelect = FALSE;
			if (GetCurSel() == ordin) {
				s_bThisItemSelect = TRUE;
				SetItemState(pLVCD->nmcd.dwItemSpec, 0, LVIS_SELECTED);       

				pLVCD->clrText = m_TextSelClr;    // your custom color
				pLVCD->clrTextBk = m_ItemSelClr;
			}
			*pResult = CDRF_NOTIFYPOSTPAINT;   
		}
		break;

	case CDDS_ITEMPOSTPAINT:
		if (s_bThisItemSelect)
			SetItemState(pLVCD->nmcd.dwItemSpec, 0xFF, LVIS_SELECTED);   
		break;
	}
}

LRESULT CUiListCtrl::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	if(message == WM_VSCROLL || message == WM_HSCROLL)
	{
		WORD sbCode = LOWORD(wParam);
		if (sbCode == SB_THUMBTRACK || sbCode == SB_THUMBPOSITION)
		{
			SCROLLINFO siv = {0};
			siv.cbSize = sizeof(SCROLLINFO);
			siv.fMask = SIF_ALL;

			SCROLLINFO sih = siv;
			int nPos = HIWORD(wParam);

			CRect rcClient;
			GetClientRect(&rcClient);
			GetScrollInfo(SB_VERT, &siv);
			GetScrollInfo(SB_HORZ, &sih);

			SIZE sizeAll;
			if (sih.nPage == 0) 
				sizeAll.cx = rcClient.right;
			else
				sizeAll.cx = rcClient.right * (sih.nMax + 1) / sih.nPage ;

			if (siv.nPage == 0)
				sizeAll.cy = rcClient.bottom;
			else
				sizeAll.cy = rcClient.bottom * (siv.nMax + 1) / siv.nPage ;

			SIZE size = {0, 0};
			if (WM_VSCROLL == message)
			{
				size.cy = sizeAll.cy * (nPos - siv.nPos) / (siv.nMax + 1);
			}
			else
			{
				size.cx = sizeAll.cx * (nPos-sih.nPos) / (sih.nMax + 1);
			}
			Scroll(size);
			
			m_BtnDown.Invalidate(FALSE);
			m_BtnUp.Invalidate(FALSE);
			m_Slide.Invalidate(FALSE);
			return 1;
		}
	}
	return CListCtrl::WindowProc(message, wParam, lParam);
}

void CUiListCtrl::OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp)
{
	if(NULL != m_Slide.GetSafeHwnd())
	{
		ShowScrollBar(SB_VERT, SW_HIDE);
		ShowScrollBar(SB_HORZ, SW_HIDE);
		int nMin = 0, nMax = 0;
		GetScrollRange(SB_VERT, &nMin, &nMax);
		m_Slide.SetRange(nMin, nMax);
		ShowScrollself(nMax > 2);
	}

	CListCtrl::OnNcCalcSize(bCalcValidRects, lpncsp);
}

void CUiListCtrl::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{

	CListCtrl::OnVScroll(nSBCode, nPos, pScrollBar);
}

BOOL CUiListCtrl::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	if(NULL != m_Slide.GetSafeHwnd())
	{
		int nMax = 0, nMin = 0;    
		m_Slide.GetRange(nMin, nMax);  
		int nPos = m_Slide.GetPos();
		const int nMaxPos = nMax; 

		if (zDelta<0)
		{
			if (nPos < nMaxPos)
			{
				zDelta = min(max(nMaxPos/20,5),nMaxPos-nPos);

				nPos += zDelta;
				m_Slide.SetPos(nPos);
			}
		}
		else if(zDelta != 0)
		{
			if (nPos > 0)
			{
				zDelta = -min(max(nMaxPos/20,5),nPos);

				nPos += zDelta;
				m_Slide.SetPos(nPos);
			}
		}

		PostMessage(WM_VSCROLL,MAKELONG(SB_THUMBPOSITION, nPos),0);
	}

	return CListCtrl::OnMouseWheel(nFlags, zDelta, pt);
}

LRESULT CUiListCtrl::OnUiSliderMoving(WPARAM wParam, LPARAM lParam)
{
	if(wParam == m_scrollId)
	{
		SendMessage(WM_VSCROLL,MAKELONG(SB_THUMBTRACK, lParam), 0);
	}
	return 1;
}

LRESULT CUiListCtrl::OnUiButtonClick(WPARAM wParam, LPARAM lParam)
{
	if(wParam == m_btnUpId)
	{
		m_Slide.OffsetPos(-1);
		OnUiSliderMoving(m_scrollId, m_Slide.GetPos());
	}
	else if (wParam == m_btnDownId)
	{
		m_Slide.OffsetPos(1);
		OnUiSliderMoving(m_scrollId, m_Slide.GetPos());
	}
	return 1;
}

void CUiListCtrl::ShowScrollself(bool bShow)
{
	m_Slide.ShowWindow(bShow ? SW_SHOW : SW_HIDE);
	m_BtnDown.ShowWindow(bShow ? SW_SHOW : SW_HIDE);
	m_BtnUp.ShowWindow(bShow ? SW_SHOW : SW_HIDE);
}
void CUiListCtrl::OnKillFocus(CWnd* pNewWnd)
{
	CListCtrl::OnKillFocus(pNewWnd);

	//if (m_bEdit)
	//{
	//	DisposeEdit();
	//}
}
void CUiListCtrl::ToEdit(int nRow, int nCol)
{
	if(!m_bEdit) return;
	if(nRow >= GetItemCount() || nCol >= GetHeaderCtrl()->GetItemCount()) return;

	CString sValue;
	CRect rc;
	GetSubItemRect(nRow, nCol, LVIR_LABEL, rc); //得到该单元格矩形的位置大小信息。
	sValue = GetItemText(nRow,nCol);                               //获取该单元格已存在的文本内容。
	m_edit.MoveWindow(rc);                              //把编辑框移动到该单元格矩形上。
	m_edit.SetWindowText(sValue);                             //把单元格原本的内容显示到编辑框上。
	m_edit.ShowWindow(SW_SHOW);                  //显示编辑框。
	m_edit.SetSel(0, -1);                                         //全选编辑框的内容。
	m_edit.SetFocus();                                           //设置输入焦点在编辑框上。
	m_nEditRow = nRow;
	m_nEditCol = nCol;
	UpdateWindow();

}
void CUiListCtrl::DisposeEdit()
{ 
	if(m_nEditRow < 0 || m_nEditCol < 0) return;
	CString sLabel;
	m_edit.GetWindowText(sLabel);
	SetItemText(m_nEditRow, m_nEditCol, sLabel);
	m_edit.ShowWindow(SW_HIDE);

	UI_LST_EDIT editlst;
	editlst.nRow = m_nEditRow;
	editlst.nCol = m_nEditCol;
	_tcscpy(editlst.szValue, sLabel.GetBuffer(1024));
	sLabel.ReleaseBuffer();

	CWnd* pParent = GetParent();
	while(NULL != pParent)
	{
		//if(pParent->SendMessage(WM_UI_LIST_EDIT, GetDlgCtrlID(), (LPARAM)&editlst)) break;
		pParent = pParent->GetParent();
	}

	m_nEditRow = m_nEditCol = -1;
	return ;
}
BOOL CUiListCtrl::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)    
	{    
		if (m_bEdit)
		{
			DisposeEdit();
			CWnd* pParent = GetParent();
			while(NULL != pParent)
			{
				if(pParent->SendMessage(WM_UI_LIST_EDITED, GetDlgCtrlID(), m_nEditIndex)) break;
				pParent = pParent->GetParent();
			}
		}
		return TRUE;
	}

	return CListCtrl::PreTranslateMessage(pMsg);
}