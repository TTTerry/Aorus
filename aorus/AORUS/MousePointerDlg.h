#pragma once


// CMousePointerDlg dialog

class CMousePointerDlg : public CUiDlg
{
	typedef enum 
	{
// 		BTN_MPOINT_ADDPROFILE,
// 		BTN_MPOINT_EDITPROFILE,
// 		BTN_MPOINT_DELPROFILE,

 		BTN_MPOINT_DPI1,
 		BTN_MPOINT_DPI2,
 		BTN_MPOINT_DPI3,
 		BTN_MPOINT_DPI4,
 
 		BTN_MPOINT_DPI1_LINK,
 		BTN_MPOINT_DPI2_LINK,
 		BTN_MPOINT_DPI3_LINK,
 		BTN_MPOINT_DPI4_LINK,
 
 		BTN_MPOINT_DPI1_XDEC, // DPI1 X -
 		BTN_MPOINT_DPI1_XINC, // DPI1 X +
 		BTN_MPOINT_DPI1_YDEC, // DPI1 Y -
 		BTN_MPOINT_DPI1_YINC,  // DPI1 Y +
 
  		BTN_MPOINT_DPI2_XDEC,
  		BTN_MPOINT_DPI2_XINC,
  		BTN_MPOINT_DPI2_YDEC,
  		BTN_MPOINT_DPI2_YINC,
  
  		BTN_MPOINT_DPI3_XDEC,
  		BTN_MPOINT_DPI3_XINC,
  		BTN_MPOINT_DPI3_YDEC,
  		BTN_MPOINT_DPI3_YINC,
  
  		BTN_MPOINT_DPI4_XDEC,
  		BTN_MPOINT_DPI4_XINC,
  		BTN_MPOINT_DPI4_YDEC,
  		BTN_MPOINT_DPI4_YINC,
  
  		BTN_MPOINT_REPORT_RATE_DEC,
  		BTN_MPOINT_REPORT_RATE_INC,

		BTN_MPOINT_APPLY,
		BTN_MPOINT_RESET,
		BTN_MPOINT_DEFAULT,
		BTN_MPOINT_NUM
	};

	typedef enum
	{
		COMBOX_MPOINT_PROFILE,
		COMBOX_MPOINT_NUM,
	};

	typedef enum
	{
		SLD_MPOINT_DPI1,
		SLD_MPOINT_DPI2,
		SLD_MPOINT_DPI3,
		SLD_MPOINT_DPI4,
		SLD_MPOINT_REPORT_RATE,

		SLD_MPOINT_DPI1_X,
		SLD_MPOINT_DPI1_Y,
		SLD_MPOINT_DPI2_X,
		SLD_MPOINT_DPI2_Y,
		SLD_MPOINT_DPI3_X,
		SLD_MPOINT_DPI3_Y,
		SLD_MPOINT_DPI4_X,
		SLD_MPOINT_DPI4_Y,
		SLD_MPOINT_NUM, 
	};

	typedef enum
	{
		STC_MPOINT_STATUS1,
		STC_MPOINT_STATUS2,
		STC_MPOINT_STATUS3,
		STC_MPOINT_STATUS4,

  		STC_MPOINT_DPI1_X,
   		STC_MPOINT_DPI1_Y,
   		STC_MPOINT_DPI2_X,
   		STC_MPOINT_DPI2_Y,
   		STC_MPOINT_DPI3_X,
   		STC_MPOINT_DPI3_Y,
   		STC_MPOINT_DPI4_X,
   		STC_MPOINT_DPI4_Y,
   		STC_MPOINT_REPORT_RATE,
   		STC_MPOINT_REPORT_RATE_VAL,
		STC_MPOINT_NUM, // 鼠標POINTER
	};


	DECLARE_DYNAMIC(CMousePointerDlg)

public:
	CMousePointerDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CMousePointerDlg();
	void InitState();
	void UpdateUI();
	void OnHIDInput(BYTE* byData);
// Dialog Data
	enum { IDD = IDD_VGA_LED_DIALOG };

protected:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	afx_msg void OnPaint();
	afx_msg LRESULT OnUiButtonClicked(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUiSliderMoving(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()

	void Ui();
	void UiMain();
	void EnableDPIOne(int index);
	void EnableAll(bool b);
	CString GetDPIString(int num);
	void ShowXY(int index, int x, int y);
	int GetReportRate(int pos);

private:
	CUiStatic m_stc[STC_MPOINT_NUM];
	CUiSliderCtrl	m_slider[SLD_MPOINT_NUM];
	CUiButton		m_btn[BTN_MPOINT_NUM];		// 所有btn的数组
	CUiComboBox m_combobox[COMBOX_MPOINT_NUM];

	int m_nReportRate;
	GVORDER_DPI m_dpi[4];
	int m_ndpiIndex; // DPIindex，根據界面上DPISetting上3個單選控件產生值

	
};
