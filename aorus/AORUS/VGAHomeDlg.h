#pragma once

#include "resource.h"

// CVGAHomeDlg dialog

class CVGAHomeDlg : public CUiDlg
{
	DECLARE_DYNAMIC(CVGAHomeDlg)
	typedef enum _VGAH_BTN_ID // 按钮
	{
		BTN_VGAH_OCMODE = 0,
		BTN_VGAH_GAMINGMODE,
		BTN_VGAH_SILENTMODE,
		BTN_VGAH_USERMODE,
		BTN_VGAH_NUM
	}vgah_btn;
	typedef enum _VGAH_PROFILESEL_ID
	{
		COMB_VGAH_PROFILESEL,
		COMB_VGAH_NUM
	};
public:
	CVGAHomeDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CVGAHomeDlg();
	void InitState();
	void UpdateUI();
// Dialog Data
	enum { IDD = IDD_VGA_HOME_DIALOG };

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg LRESULT OnUiButtonClicked(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUiComboBoxSelChanged(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()

	void Ui();
	void UiMain();
private:
	CUiButton m_btn[BTN_VGAH_NUM];// 所有btn的数组
	CUiComboBox		m_combobox[COMB_VGAH_NUM];
	VGA_PERFORMANCE m_perfDefault;
	bool m_bVgaCard;
};
