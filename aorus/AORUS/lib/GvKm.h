#ifndef _GVKM_abc123_H
#define _GVKM_abc123_H

#ifdef  GVKM_EXPORTS
#define GVKMEXPORT  __declspec(dllexport)
#else
#define GVKMEXPORT  __declspec(dllimport)
#endif


#define GVKM_MOUSE     0x001         
#define GVKM_KEYBOARD  0x002

#define WM_GVKM_KEYBOARD_USERMSG  _T("UWM_GVKM_KEYBOARD_USERMSG")
static  UINT WM_GVKM_HKYSTROKE = ::RegisterWindowMessage(WM_GVKM_KEYBOARD_USERMSG);

//WM_GVKM_HKYSTROKE消息的wParam参数含义
#define GVKM_HKY_VK              0x000000ff
#define GVKM_HKY_EXT_ALT         0x00000100
#define GVKM_HKY_EXT_SHIFT       0x00000200
#define GVKM_HKY_EXT_CONTROL     0x00000400
#define GVKM_HKY_STATE_MASKHKY   0x00001000
#define GVKM_HKY_STATE_PRESSED   0x00008000
#define GVKM_HKY_STATE_MASK      0x0000f000

#define GVKM_HKY_BASEON_MESSAGE  0x00010000
#define GVKM_HKY_BASEON_DINPUT8  0x00020000
#define GVKM_HKY_FROM_PROC3DDLL  0x00040000


extern "C"
{
	/****************************************************************************************
	 * 功能描述：
	 * 初始化GvKm.dll
	 *
	 * 输入参数：
	 * hWnd   调用GvKm.dll的程式主窗口句柄
	 * dwHook Hook类型, 指定调用GvKm.dll中关于键盘或鼠标的API. 该值可为GVKM_MOUSE/GVKM_KEYBOARD, 或两者(|操作)
	 *
	 * 返回值：
	 * 返回TRUE表示调用成功
	 ****************************************************************************************/
	GVKMEXPORT bool GvKmInstallHook(HWND hWnd, DWORD dwHook=GVKM_KEYBOARD);

	/****************************************************************************************
	 * 功能描述：
	 * 释放GvKm.dll
	 ****************************************************************************************/
	GVKMEXPORT void GvKmUninstallHook();

	/****************************************************************************************
	 * 功能描述：
	 * 设置关注的热键, 设置后, 该热键若被按下, 则会发出WM_GVKM_HKYSTROKE通知调用GvKm.dll的窗口,
	 * 或者调用GvKmIsHotKeyPressed()主动查询热键状态.两者方式互斥.当利用WM_GVKM_HKYSTROKE通知时,
	 * 用ON_REGISTERED_MESSAGE(WM_GVKM_HKYSTROKE, OnHotKeyPressed)对消息进行响应.
	 * 响应函数原型为:
	 * afx_msg LRESULT OnHotKeyPressed(WPARAM wParam, LPARAM lParam);
	 * 其中, wParam包含热键以及其他信息,具体见上面说明.lParam为HWND句柄,表示热键发生自哪个窗口. 
	 *
	 * 输入参数：
	 * vk       热键的虚拟码, 如VK_F1
	 * bAlt     当前热键中是否包含Alt健
	 * bShift   当前热键中是否包含Shift健
	 * bCtrl    当前热键中是否包含Ctrl健
	 * bMaskHKY 是否屏蔽该热键, 即:当对该热键进行屏蔽时,只有调用GvKm.dll的窗口能够得知热键被
	 *          按下,平台的其他进程窗口都无法获知热键被按下(对其屏蔽). 
	 * 
	 * 返回值：
	 * 调用成功时, 返回该热键的index值. 失败时返回-1.
	 *
	 * 注意：
	 * 若之前已调用了GvKmSetHotKey()设置某HotKey, 若需重新设置, 记住调用GvKmResetHotKey()释放资源.
	 ****************************************************************************************/
	GVKMEXPORT int GvKmSetHotKey(BYTE vk, bool bCtrl=false, bool bAlt=false, bool bShift=false, bool bMaskHKY=false); 

	/****************************************************************************************
	 * 功能描述：
	 * 清除调用GvKmSetHotKey设置的热键.
	 *
	 * 输入参数：
	 * nIndex   标志某个热键的Index值, 该值为由调用GvKmSetHotKey()返回的值
	 * 
	 * 返回值：
	 * 返回TRUE表示调用成功
	 ****************************************************************************************/
	GVKMEXPORT bool GvKmResetHotKey(int nIndex);

	/****************************************************************************************
	 * 功能描述：
	 * 询问设置的热键是否被按下. 
	 *
	 * 输入参数：
	 * nIndex 标志某个热键的Index值, 该值为由调用GvKmSetHotKey()返回的值
	 * 
	 * 返回值：
	 * 返回TRUE表示该热键被按下. 返回FALSE表示未被按下, 或者在调用GvKmIsHotKeyPressed()之前,已有
	 * 其他键盘KEY被按下(即之前热键被按下的状态已被覆盖掉)
	 ****************************************************************************************/
	GVKMEXPORT bool GvKmIsHotKeyPressed(int nIndex);

	/****************************************************************************************
	 * 功能描述：
	 * 模拟发送键盘热键被按下
	 *
	 * 输入参数：
	 * vk       热键的虚拟码, 如VK_F1
	 * bAlt     当前热键中是否包含Alt健
	 * bShift   当前热键中是否包含Shift健
	 * bCtrl    当前热键中是否包含Ctrl健
	 * 
	 * 返回值：
	 * 返回TRUE表示调用成功
	 ****************************************************************************************/
	GVKMEXPORT bool GvKmSimulateHotKey(BYTE vk, bool bAlt, bool bShift, bool bCtrl);

	/****************************************************************************************
	 * 功能描述：
	 * 移动鼠标到指定位置
	 *
	 * 输入参数：
	 * nXCoord   目的X坐标, 该坐标为绝对坐标(相对于屏幕坐标)
	 * nYCoord   目的Y坐标, 该坐标为绝对坐标(相对于屏幕坐标), 注意, nXCoord, nYCoord均以调用
	 *           GvKmInstallHook()时平台的屏幕分辨率为基准
	 ****************************************************************************************/
	GVKMEXPORT void GvKmMouseMove(int nXCoord, int nYCoord);

	/****************************************************************************************
	 * 功能描述：
	 * 模拟鼠标主键(默认为左键)点击, 若当前鼠标主键设置为右键, 则该函数模拟鼠标右键点击
	 *
	 * 输入参数：
	 * nXCoord    目的X坐标, 该坐标为绝对坐标(相对于屏幕坐标)
	 * nYCoord    目的Y坐标, 该坐标为绝对坐标(相对于屏幕坐标), 注意, nXCoord, nYCoord均以调用
	 *            GvKmInstallHook()时平台的屏幕分辨率为基准
	 * bMouseMove 是否在模拟鼠标点击过程中不移动鼠标, TRUE表不移动, FALSE表移动到点击的位置
	 ****************************************************************************************/
	GVKMEXPORT void GvKmMouseLButtonClick(int nXCoord, int nYCoord, bool bMouseMove=false);

	/****************************************************************************************
	 * 功能描述：
	 * 模拟鼠标副键(默认为右键)点击, 若当前鼠标副键设置为左键, 则该函数模拟鼠标左键点击
	 *
	 * 输入参数：
	 * nXCoord    目的X坐标, 该坐标为绝对坐标(相对于屏幕坐标)
	 * nYCoord    目的Y坐标, 该坐标为绝对坐标(相对于屏幕坐标), 注意, nXCoord, nYCoord均以调用
	 *            GvKmInstallHook()时平台的屏幕分辨率为基准
	 * bMouseMove 是否在模拟鼠标点击过程中不移动鼠标, TRUE表不移动, FALSE表移动到点击的位置
	 ****************************************************************************************/
	GVKMEXPORT void GvKmMouseRButtonClick(int nXCoord, int nYCoord, bool bMouseMove=false);
}

#endif  //_GVKM_abc123_H

