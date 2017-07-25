#pragma once


// CRemoteSetting 对话框

class CRemoteSetting : public CUiDlg
{
	typedef enum _REMOTE_BTN_ID
	{
		BTN_REMOTE_CLOSE,
		BTN_REMOTE_APPLY,
		BTN_REMOTE_CANCEL,
		BTN_REMOTE_NUM
	};
	typedef enum _REMOTE_STC_ID
	{
		STC_REMOTE_NAME,
		STC_REMOTE_PASSWORD,
		STC_REMOTE_CAPTION,
		STC_REMOTE_NUM
	};
	typedef enum _REMOTE_EDIT_ID
	{
		EDIT_REMOTE_NAME,
		EDIT_REMOTE_PASSWORD,
		EDIT_REMOTE_NUM
	};
	DECLARE_DYNAMIC(CRemoteSetting)

public:
	CRemoteSetting(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CRemoteSetting();

// 对话框数据
	enum { IDD = IDD_REMOTECTR_SETTING };

protected:
	afx_msg LRESULT OnUiButtonClicked(WPARAM wParam, LPARAM lParam);
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	void Ui();
	void UiMain();
	void OnOK();
	//BOOL PreTranslateMessage(MSG* pMsg);
	DECLARE_MESSAGE_MAP()
private:
	CUiButton m_btn[BTN_REMOTE_NUM];
	CUiStatic m_stc[STC_REMOTE_NUM];
	CUiEdit m_edit[EDIT_REMOTE_NUM];
};
