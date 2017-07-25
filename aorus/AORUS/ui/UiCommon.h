#ifndef  _UI_COMMON_H_
#define  _UI_COMMON_H_


/*****************************************************************************************************************
 *
 * Common.h: 该头文件包含了Ui模组中所需要用到的自定义消息，调用Ui模组的程式只需要对这些消息进行处理，则可以响应控件
 *           的消息处理。使用时只需要在添加ON_MESSAGE(WM_USERMSG, OnUserMsg)和afx_msg LRESULT OnUserMsg(WPARAM wParam, 
 *           LPARAM lParam)即可处理某个消息，其中每个消息的wParam和lParam的具体含义见下面说明。
 *
 *****************************************************************************************************************/

///////////////////////////////////////////////////////////////////
//sample.h file
//  afx_msg LRESULT OnUserMsg(WPARAM wParam, LPARAM lParam);
//
//sample.cpp file
//  ON_MESSAGE(WM_USERMSG, OnUserMsg)
//  LRESULT CSample::OnUserMsg(WPARAM wParam, LPARAM lParam) {}
///////////////////////////////////////////////////////////////////

//wParam=(UINT)CtrlID, lParam=(int)CurPos
#define WM_UI_SLIDER_MOVED		      WM_USER + 6000
//wParam=(UINT)CtrlID, lParam=(int)CurPos
#define WM_UI_SLIDER_MOVING		      WM_USER + 6001
//wParam=(UINT)CtrlID, lParam=(int)ItemId
#define WM_UI_PANEL_SELCHANGE         WM_USER + 6002
//wParam=(UINT),CtrlID lParam=(int)TabSel
#define WM_UI_TABCTRL_SELCHANGE       WM_USER + 6003
//wParam=(UINT)CtrlID, lParam=(int)ButtonType
#define WM_UI_BUTTON_CLICKED          WM_USER + 6004
//wParam=(HWND)WindowHandle, lParam=(SLIDE_DIRECTION)SlideDirection
#define WM_UI_ANIMATE_SLIDEFINISHED   WM_USER + 6005
//don't use it!
#define WM_UI_COMBOBOX_LIST           WM_USER + 6006
//wParam=(UINT)CtrlID, lParam=(int)CurSel
#define WM_UI_COMBOBOX_SELCHANGED     WM_USER + 6007
//wParam=(UINT)CtrlID
#define WM_UI_GRAPHCTRL_MOVING		  WM_USER + 6008
//wParam=(UINT)CtrlID
#define WM_UI_GRAPHCTRL_MOVED		  WM_USER + 6009
//wParam=(UINT)CtrlID
#define WM_UI_GRAPHCTRL_REMOVE		  WM_USER + 6010
//wParam=(UINT)CtrlID
#define WM_UI_EDIT_CHANGE			  WM_USER + 6011
//wParam=(UINT)CtrlID, lParam=(int)Angle
#define WM_UI_ANGLE_CHANGE			  WM_USER + 6012
//wParam=(UINT)CtrlID, lParam=(int)index
#define WM_UI_MULITSLIDER_MOVED	      WM_USER + 6013
//wParam=(UINT)CtrlID, lParam=(int)index
#define WM_UI_MULITSLIDER_MOVING	  WM_USER + 6014
//wParam=(UINT)CtrlID, lParam=(int)index
#define WM_UI_LIST_DBLCLK  		      WM_USER + 6015
#define WM_UI_LIST_CLK  		      WM_USER + 6016
#define WM_UI_LIST_EDITED             WM_USER + 6017
//wParam=(UINT)CtrlID, lParam=(int)ItemId
#define WM_UI_KEYBOARD_SELCHANGE      WM_USER + 6018

#endif