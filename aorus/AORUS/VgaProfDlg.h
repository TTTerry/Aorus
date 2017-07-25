#pragma once


// CVgaProfDlg dialog
#include "CustomizedDlg.h"
class CVgaProfDlg : public CUiDlg
{
	DECLARE_DYNAMIC(CVgaProfDlg)
	typedef enum _VGAPROF_BTN_ID
	{
		BTN_VGAPROF_GPUCLK_DEC,
		BTN_VGAPROF_GPUCLK_INC,
		BTN_VGAPROF_MEMCLK_DEC,
		BTN_VGAPROF_MEMCLK_INC,
		BTN_VGAPROF_GPUVOL_DEC,
		BTN_VGAPROF_GPUVOL_INC,
		BTN_VGAPROF_FANSPD_DEC,
		BTN_VGAPROF_FANSPD_INC,
		BTN_VGAPROF_PWRTAR_DEC,
		BTN_VGAPROF_PWRTAR_INC,
		BTN_VGAPROF_TARTEM_DEC,
		BTN_VGAPROF_TARTEM_INC,
		BTN_VGAPROF_ADDFILE,
		BTN_VGAPROF_DELFILE,
		BTN_VGAPROF_SAVEFILE,
		BTN_VGAPROF_GPULOCK,
		BTN_VGAPROF_LINK,
		BTN_VGAPROF_APPLY,
		BTN_VGAPROF_RESET,
		BTN_VGAPROF_DEFAULT,
		BTN_VGAPROF_GPUCUST,
		BTN_VGAPROF_FANAUTO,
		BTN_VGAPROF_FANMANUAL,
		BTN_VGAPROF_FANCUST,
		BTN_VGAPROF_NUM
	};
	typedef enum _VGAPROF_SLIDER_ID
	{
		SLIDER_VGAPROF_GPUCLK,
		SLIDER_VGAPROF_MEMCLK,
		SLIDER_VGAPROF_GPUVOL,
		SLIDER_VGAPROF_FANSPD,
		SLIDER_VGAPROF_PWRTAR,
		SLIDER_VGAPROF_TARTEM,
		SLIDER_VGAPROF_NUM,
	};
	typedef enum _VGAPROF_STATIC_ID
	{
		STC_VGAPROF_GPUCLK_NAME,
		STC_VGAPROF_MEMCLK_NAME,
		STC_VGAPROF_GPUVOL_NAME,
		STC_VGAPROF_FANSPD_NAME,
		STC_VGAPROF_PWRTAR_NAME,
		STC_VGAPROF_TARTEM_NAME,

		STC_VGAPROF_GPUCLK_OFFSET,
		STC_VGAPROF_MEMCLK_OFFSET,
		STC_VGAPROF_GPUVOL_OFFSET,
		STC_VGAPROF_FANSPD_OFFSET,
		STC_VGAPROF_PWRTAR_OFFSET,
		STC_VGAPROF_TARTEM_OFFSET,

		STC_VGAPROF_GPUCLK_VALUE,
		STC_VGAPROF_MEMCLK_VALUE,		
		STC_VGAPROF_GPUVOL_VALUE,
		STC_VGAPROF_FANSPD_VALUE,
		STC_VGAPROF_PWRTAR_VALUE,
		STC_VGAPROF_TARTEM_VALUE,
		STC_VGAPROF_NUM
	};
	typedef enum  _VGAPROF_LIST_ID
	{
		LST_VGAPROF_PROFILE = 0,
		LST_VGAPROF_NUM

	} LIST_ID;
public:
	CVgaProfDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CVgaProfDlg();
	void InitState();
	void UpdateProfile(DWORD dwPerfs, const VGA_PERFORMANCE& perf);
	int  SetLinkedPowerTemp(DWORD dwPerfs, int value);
	void OnApply();
	void OnReset();
	void UIShowCustomized(bool flag,int CurveIndex=0);
	void OnUpdateUI(BOOL bDefault=FALSE);
	void AddFile();
	void DeleteFile();
	void SaveFile(bool bApply=false);
	void SwitchProfile(int nProfile);
	int m_CurSelProfile;
	CCustomizedDlg m_CustomizedDlg;
// Dialog Data
	enum { IDD = IDD_VGA_PROF_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    virtual BOOL OnInitDialog();
	afx_msg LRESULT OnUiButtonClicked(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUiSliderMoved(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUiSliderMoving(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUiListClick(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUiListEdited(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnFanStopStateChange(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()

	void Ui();
	void UiMain();
private:

	BOOL PreTranslateMessage(MSG* pMsg);

	CUiButton m_btn[BTN_VGAPROF_NUM];
	CUiSliderCtrl	m_slider[SLIDER_VGAPROF_NUM];
	CUiStatic m_stc[STC_VGAPROF_NUM];
	CUiListCtrl m_list[LST_VGAPROF_NUM];

	VGA_SPECIALPERFS m_specialPerf;
	VGA_PERFORMANCE m_perfDefault;
};
