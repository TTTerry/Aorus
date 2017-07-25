#ifndef _UI_CLASSHEDER_H
#define _UI_CLASSHEDER_H


/*****************************************************************************************************************
 *
 * UiClass.h: include了所有Ui模组中用到的头文件。当某个程式使用Ui模组时，只需要把整个UiClass文件夹(该文件夹包含了整
 *            个Ui模组的.h文件和.cpp文件)拷贝到程式工程文件路径下，并在程式的stdafx.h头文件中添加#include "UiClass.h"
 *            语句，则可以在整个程式工程中调用整个Ui模组中的所有控件类。
 *
 *****************************************************************************************************************/

#include "UiCommon.h"
#include "UiButton.h"
#include "UiTabCtrl.h"
#include "UiSliderCtrl.h"
#include "UiMulitSliderCtrl.h"
#include "UiProgressCtrl.h"
#include "UiPanelCtrl.h"
#include "UiNumberCtrl.h"
#include "UiScrollStringCtrl.h"
#include "UiDlg.h"
#include "UiCurveGraphCtrl.h"
#include "UiAngleCtrl.h"
#include "UiStatusGraphCtrl.h"
#include "UiStatic.h"
#include "UiEdit.h"
#include "UiHotKeyCtrl.h"
#include "UiComboBox.h"
#include "UiTrayIcon.h"
#include "UiAnimate.h"
#include "UiSliderNumCtrl.h"
#include "UiListCtrl.h"
#include "UiSliderFixCtrl.h"
#include "UiKeyboardCtrl.h"

#endif 
