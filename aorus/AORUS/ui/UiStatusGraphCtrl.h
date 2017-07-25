#ifndef _UI_CSTATUSGRAPH_H
#define _UI_CSTATUSGRAPH_H

#include "UiBase.h"

struct DATA 
{ 
	LONG Value; 
	int  realValue; 
	DATA* Next; 
	DATA();
};

class CGraphData  
{
public:
	 CGraphData();
	 CGraphData(int size);
	~CGraphData();

	LONG   GetMinValue();
	LONG   GetMaxValue();
	int    GetSize();
	int    GetNumOfValid();
	void   Init();
	void   Alloc(int size);
	void   Release();
	void   InsertValue(long value, int realValue);
	DATA*  GetLeft();
	DATA*  GetRight();
	
private:
	DATA*  m_pLeft;   //data will be deleted from left and inserted into right
	DATA*  m_pRight;
	LONG   m_nMax;
	LONG   m_nMin;
	int    m_nSize;
	int    m_nNumOfValid;
};

struct UISGC_GRAPH
{
	int         nIndex;
	int         nLineWidth;
	COLORREF    clrLine;
	CGraphData* pGraphData;

	 UISGC_GRAPH();
	 UISGC_GRAPH(int index, int width, COLORREF clrLine, CGraphData* pData);
	~UISGC_GRAPH();
};


class CUiStatusGraphCtrl : public CUiBase
{
public:
	CUiStatusGraphCtrl();
	virtual ~CUiStatusGraphCtrl();

public:       
	void     CreateGraph(int nIndex, int nLineWidth=1, COLORREF clrLine=CLR_NONE/*Default color*/);
	void     DeleteGraph(int nIndex);
	bool	 IsGraphExisted(int nIndex);
	void     SetValue(int nIndex, int nValue);
	void     GetRange(int &nMin, int &nMax);
	void     SetRange(int  nMin, int  nMax);
	int      GetSampleInterval();
	void     SetSampleInterval(int nInterval);
	void     SetMargin(int l, int t, int r, int b);
	void     GetMaxMinValue(int &nmin, int &nmax);
	void	 SetFont(CFont* pFont, COLORREF clrFont=CLR_NONE);
	void     ShowValue(CRect rc);

	bool     IsEnable();
	void     Enable(bool bEnable=true);

protected:
	void     DrawGraphs(CDC* pDC, CRect rcCli);
	virtual  void  Draw(CDC* pDC, CRect rcCli);

	int      Val2Pixel(int nValue);
	int      Pixel2Val(int pixel);
	void     ReAllocGraphData();

protected:
	bool         m_bEnable;
	int          m_nMax;
	int          m_nMin;
	int          m_nSampleInterval;
	CRect        m_rcMargin;
	CPtrArray    m_pArray;
	int          m_nNumOfGraph;
	CRect		 m_rcValuePos;
	CFont*       m_pFont;
	COLORREF	 m_clrText;

protected:
	//{{AFX_MSG(CUiStatusGraphCtrl)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif 
