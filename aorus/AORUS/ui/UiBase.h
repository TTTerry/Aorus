#ifndef _UI_CBASE_H
#define _UI_CBASE_H


// text-align 
#define ST_TOP          0x00000001
#define ST_LEFT         0x00000002
#define ST_CENTER       0x00000004
#define ST_RIGHT        0x00000008
#define ST_VCENTER      0x00000010
#define ST_BOTTOM       0x00000020
#define ST_SINGLELINE   0x00000040


/*****************************************************************************************************************
 *
 * CUiBase: 控件类父类。实现控件类的背景颜色、画刷、背景位图的设定以及控件窗口的绘制。控件子类无需自己处理WM_PAINT、
 *          WM_ERASEBKGND消息，而只需要继承父类的virtual void Draw(CDC* pDC, CRect rcCli)，并将子类窗口绘制在pDC上
 *          即可。
 *
 *****************************************************************************************************************/
class CUiBase : public CWnd
{
	DECLARE_DYNAMIC(CUiBase)

public:
	CUiBase();
	virtual ~CUiBase();
	
public:
	virtual  BOOL  Create(CWnd* pParent, UINT nId, RECT rect=CRect(0, 0, 0, 0), DWORD dwStyle=WS_CHILD|WS_VISIBLE); 

	virtual  DWORD GetCtrlStyle();                                //实现子控件自身特殊属性的设定和获取
	virtual  void  ModifyCtrlStyle(DWORD dwRemove, DWORD dwAdd);

	CDC*     GetBkDC();                    //获取背景DC，该DC为内存DC
	COLORREF GetBkColor();                 //获取背景颜色
	CBrush*  GetBkBrush();                 //获取背景画刷
	void     SetBkColor(COLORREF clrBk);   //设定背景颜色
	void     SetBkBrush(CBrush* pBrush);   //设定背景画刷
	void     SetBkBitmap(UINT uBkBmpId, COLORREF clrMask=CLR_NONE, int nWinPosX=0, int nWinPosY=0, bool bAutoMoveWin=false);  //设定背景位图，可设置位图透明色，以及是否按照位图大小调整窗口大小

	static   HRGN CreateRgn(UINT uBitmapId, COLORREF clrMask);     //根据指定的位图和透明色创建(不规则)区域
	static   HRGN CreateRgn(CDC* pDC, COLORREF clrMask);           //根据制定的DC(中的绘图)和透明色创建(不规则)区域

protected:
	virtual  void RecalLayout();                          //继承该函数实现子控件窗口位置的重新调整
	virtual  void Draw(CDC* pDC, CRect rcCli) = 0;        //继承该函数实现子控件窗口绘制
	
private:
	void     Refresh(CDC* pDC, CRect rcCli);
	static   HRGN CreateRgn(CBitmap* pBitmap, COLORREF clrMask);

private:
	CDC      m_BkDC;
	bool     m_bStoredBkDc;
	COLORREF m_clrBk;
	CBrush*  m_pBkBrush;
	UINT     m_uBkBmpId;
	COLORREF m_clrBkBmpMask;
	DWORD    m_dwStyle;

protected:
	//{{AFX_MSG(CUiBase)
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
};

#endif 
