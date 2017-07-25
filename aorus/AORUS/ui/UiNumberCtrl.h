#ifndef _UI_CNUMBERCTRL_H
#define _UI_CNUMBERCTRL_H

#include "UiBase.h"


/*****************************************************************************************************************
 *
 * CUiNumberCtrl: 由CUiBase继承而来。通过继承父类的virtual void Draw(CDC* pDC, CRect rcCli)，实现控件绘制。该控件
 *                可以自动将数字(多位，同时可带符号)用位图形式的表示出来，前提必须设置0 ~ 9数字以及符号的位图表示方式。
 *
 *****************************************************************************************************************/

class UINC_NUMBER        //设定控件的数字位图和符号位图以及透明色
{
public:
	UINT     Sign[2]; 
	UINT     Num[10];
	COLORREF clrMask;

	UINC_NUMBER();
	UINC_NUMBER(UINT num[], int count=10, UINT sign[]=NULL, int signCount=2, COLORREF mask=CLR_NONE);
	UINC_NUMBER(UINT num0, UINT num1, UINT num2, UINT num3, UINT num4, UINT num5, UINT num6, UINT num7, UINT num8, UINT num9, 
		        UINT signPositive=0, UINT signNegative=0, COLORREF mask=CLR_NONE);
	UINC_NUMBER& operator = (const UINC_NUMBER* pNum);
};


class UI_NUMBERCTRL    //填充该结构，可用于创建控件
{
public:
	CWnd*       pParent;
	UINT        uId;
	CRect       rect;
	DWORD       dwStyle;
	UINC_NUMBER number;
	CRect*      pNumLoc;
	int         nCount;
	CRect       rcSign;

	UI_NUMBERCTRL();
	UI_NUMBERCTRL(CWnd* parent, UINT id, CRect rcWin, UINC_NUMBER num, CRect* pLoc, int count, CRect* pSign=NULL, DWORD style=WS_CHILD|WS_VISIBLE);
	UI_NUMBERCTRL& operator = (const UI_NUMBERCTRL* pNumCtrl);
};

class CUiNumberCtrl : public CUiBase
{
public:
	CUiNumberCtrl();
	virtual ~CUiNumberCtrl();

public:
	void     CreateNumberCtrl(UI_NUMBERCTRL numCtrl); //该函数相当于CUiBase::Create() + CUiNumberCtrl::SetNumberBitmap() + CUiNumberCtrl::SetNumberLocation()
	void     SetNumberBitmap(UINC_NUMBER num);        //设置控件的0 ~ 9数字以及符号的表示位图
	void     SetNumberLocation(CRect num[], int nNumCount, CRect* pSign=NULL);  //设置显示各个数字/符号的具体位置(相对控件左上角位置)

	LONG     GetValue();                             //获取当前控件显示的数值
	void     SetValue(LONG lValue);                  //设置当前控件显示的数值

protected:
	void     DrawNumber(CDC* pDC, CRect rcCli);
	virtual  void  Draw(CDC* pDC, CRect rcCli);

protected:
	LONG         m_nValue;
	int          m_nNumOfItems;
	UINC_NUMBER  m_number;
	CPtrArray    m_pArray;
	CRect*       m_pSign;
	
protected:
	afx_msg void OnDestroy();
	DECLARE_MESSAGE_MAP()
};

#endif 
