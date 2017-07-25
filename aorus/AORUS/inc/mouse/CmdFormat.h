#pragma once

#include "../../lib/GvOrderLib.h"
#include "../../common/definition.h"

class CCmdFormat
{
public:
	static DWORD toHidCode(DWORD dwKeyCode);
	static DWORD toKeyCode(DWORD dwHidCode);
	static DWORD toKeyModifier(DWORD dwHidCode);
	static DWORD toHIDModifier(DWORD dwHidCode);

	static BYTE* toData(GVORDER_PROFILE status, BYTE* byData);
	static BYTE* toData(GVORDER_DPI dpi, BYTE* byData);
	static BYTE* toData(GVORDER_LED led, BYTE* byData);
	static BYTE* toData(GVORDER_MATRIX matrix, BYTE* byData);
	static BYTE* toData(GVORDER_MACROS_UNIT macros, BYTE* byData, int& nLen);
	static BYTE* toData(GVORDER_MACROS_ATTR macrosAttr, BYTE* byData);
	static BYTE* toData(GVORDER_KEYFUN keymapping, BYTE* byData);
	static BYTE* toData(GVORDER_TILT_TYPE tilt, BYTE* byData);
	static BYTE* toData(bool bLock, BYTE* byData);
	static BYTE* toData(GVORDER_LED_CFG cfg, BYTE* byData);
	static BYTE* toLedData(GVORDER_PROFILE status, BYTE* byData, bool bMultiColor);

	static GVORDER_PROFILE	toProfile(BYTE* byData);
	static GVORDER_DPI		toDPI(BYTE* nyData);
	static GVORDER_LED		toLed(BYTE* byData);
	static GVORDER_KEYFUN	toKeyFun(BYTE* byData);
	static GVORDER_LED_CFG	toLedCfg(BYTE* byData);
	static int				toReportRate(BYTE* byData);
	static int				toLockDPI(BYTE* byData);
	static int				toLockProfile(BYTE* byData);

	static GVORDER_MACROS_UNIT toMacrosunit(BYTE* byData, int& nLen);
	static GVORDER_MACROS_ATTR toMacrosattr(BYTE* byData);
};
