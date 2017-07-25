#pragma once


// CDisplayClkDlg dialog

class CDisplayClkDlg : public CUiDlg
{
	typedef enum _CLKVIEW_STC_ID
	{
		STC_CLKVIEW_GPUCLKTITLE,
		STC_CLKVIEW_MEMCLKTITLE,
		STC_CLKVIEW_GPUCLKUINIT,
		STC_CLKVIEW_MEMCLKUINIT,
		STC_CLKVIEW_GPUCLKVALUE,
		STC_CLKVIEW_MEMCLKVALUE,
		STC_CLKVIEW_NUM
	}clkview_stc;
	DECLARE_DYNAMIC(CDisplayClkDlg)

public:
	CDisplayClkDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDisplayClkDlg();
	void InitState();
	void UpdateUI();
// Dialog Data
	enum { IDD = IDD_VGA_DISPLAYCLK_DIALOG };

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	DECLARE_MESSAGE_MAP()
	void Ui();
	void UiMain();
private:

	CUiStatic		m_stc[STC_CLKVIEW_NUM];
};
