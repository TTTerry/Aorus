#include "StdAfx.h"
#include "CmdFormat.h"

//////////////////////////////////////////////////////////////////////////
DWORD CCmdFormat::toHidCode(DWORD dwKeyCode)
{
	switch(dwKeyCode)
	{
	case VK_A:			return 0x04;		// A
	case VK_B:			return 0x05;		// B
	case VK_C:			return 0x06;		// C
	case VK_D:			return 0x07;		// D
	case VK_E:			return 0x08;		// E
	case VK_F:			return 0x09;		// F
	case VK_G:			return 0x0A;		// G
	case VK_H:			return 0x0B;		// H
	case VK_I:			return 0x0C;		// I
	case VK_J:			return 0x0D;		// J
	case VK_K:			return 0x0E;		// K
	case VK_L:			return 0x0F;		// L
	case VK_M:			return 0x10;		// M
	case VK_N:			return 0x11;		// N
	case VK_O:			return 0x12;		// O
	case VK_P:			return 0x13;		// P
	case VK_Q:			return 0x14;		// Q
	case VK_R:			return 0x15;		// R
	case VK_S:			return 0x16;		// S
	case VK_T:			return 0x17;		// T
	case VK_U:			return 0x18;		// U
	case VK_V:			return 0x19;		// V
	case VK_W:			return 0x1A;		// W
	case VK_X:			return 0x1B;		// X
	case VK_Y:			return 0x1C;		// Y
	case VK_Z:			return 0x1D;		// Z
	case VK_1:			return 0x1E;		// 1
	case VK_2:			return 0x1F;		// 2
	case VK_3:			return 0x20;		// 3
	case VK_4:			return 0x21;		// 4
	case VK_5:			return 0x22;		// 5
	case VK_6:			return 0x23;		// 6
	case VK_7:			return 0x24;		// 7
	case VK_8:			return 0x25;		// 8
	case VK_9:			return 0x26;		// 9
	case VK_0:			return 0x27;		// 0
	case VK_RETURN:		return 0x28;		// Return
	case VK_ESCAPE:		return 0x29;		// Esc
	case VK_BACK:		return 0x2A;		// Back
	case VK_TAB:		return 0x2B;		// Tab
	case VK_SPACE:		return 0x2C;		// Space
	case VK_OEM_MINUS:	return 0x2D;		// -_
	case VK_OEM_PLUS:	return 0x2E;		// +=
	case VK_OEM_4:		return 0x2F;		// [{
	case VK_OEM_6:		return 0x30;		// ]}
	case VK_OEM_5:		return 0x31;		// \|
	case VK_OEM_1:		return 0x33;		// ;:
	case VK_OEM_7:		return 0x34;		// '"
	case VK_OEM_3:		return 0x35;		// `~
	case VK_OEM_COMMA:  return 0x36;		// ,<
	case VK_OEM_PERIOD: return 0x37;		// .>
	case VK_OEM_2:		return 0x38;		// /?
	case VK_CAPITAL:	return 0x39;		// Caps Lock
	case VK_F1:			return 0x3A;		// F1
	case VK_F2:			return 0x3B;		// F2
	case VK_F3:			return 0x3C;		// F3
	case VK_F4:			return 0x3D;		// F4
	case VK_F5:			return 0x3E;		// F5
	case VK_F6:			return 0x3F;		// F6
	case VK_F7:			return 0x40;		// F7
	case VK_F8:			return 0x41;		// F8
	case VK_F9:			return 0x42;		// F9
	case VK_F10:		return 0x43;		// F10
	case VK_F11:		return 0x44;		// F11
	case VK_F12:		return 0x45;		// F12
	case VK_SNAPSHOT:	return 0x46;		// Print Screen
	case VK_SCROLL:		return 0x47;		// Scroll Lock
	case VK_PAUSE:		return 0x48;		// Pause
	case VK_INSERT:		return 0x49;		// Insert
	case VK_HOME:		return 0x4A;		// Home
	case VK_PRIOR:		return 0x4B;		// Page Up
	case VK_DELETE:		return 0x4C;		// Delete
	case VK_END:		return 0x4D;		// End
	case VK_NEXT:		return 0x4E;		// Next
	case VK_RIGHT:		return 0x4F;		// Right
	case VK_LEFT:		return 0x50;		// Left
	case VK_DOWN:		return 0x51;		// Down
	case VK_UP:			return 0x52;		// Up
	case VK_NUMLOCK:	return 0x53;		// Num Lock
	case VK_DIVIDE:		return 0x54;		// keypad /
	case VK_MULTIPLY:	return 0x55;		// Keypad *
	case VK_SUBTRACT:	return 0x56;		// Keypad -
	case VK_ADD:		return 0x57;		// Keypad +	
	case VK_NUMPAD1:	return 0x59;		// Num 1
	case VK_NUMPAD2:	return 0x5A;		// Num 2
	case VK_NUMPAD3:	return 0x5B;		// Num 3
	case VK_NUMPAD4:	return 0x5C;		// Num 4
	case VK_NUMPAD5:	return 0x5D;		// Num 5
	case VK_NUMPAD6:	return 0x5E;		// Num 6
	case VK_NUMPAD7:	return 0x5F;		// Num 7
	case VK_NUMPAD8:	return 0x60;		// Num 8
	case VK_NUMPAD9:	return 0x61;		// Num 9
	case VK_NUMPAD0:	return 0x62;		// Num 0
	case VK_DECIMAL:	return 0x63;		// Num .
	case VK_OEM_NEC_EQUAL:	return 0x67;	// Keypad =
	case VK_LCONTROL:	return 0xE0;		// Left Ctrl
	case VK_LSHIFT:		return 0xE1;		// Left Shift
	case VK_LMENU:		return 0xE2;		// Left Alt
	case VK_LWIN:		return 0xE3;		// Left Win
	case VK_RCONTROL:	return 0xE4;		// Right Ctrl
	case VK_RSHIFT:		return 0xE5;		// Right Shift
	case VK_RMENU :		return 0xE6;		// Right Alt
	case VK_RWIN:		return 0xE7;		// Right Win
	default: return 0;
	}
}
//////////////////////////////////////////////////////////////////////////
DWORD CCmdFormat::toKeyModifier(DWORD dwHidCode)
{
	DWORD dwKeyCode = 0;
	if (dwHidCode == SCAN_LEFT_CTRL)		dwKeyCode |= VK_LCONTROL;		// Left Ctrl	
	else if (dwHidCode == SCAN_LEFT_SHIFT)	dwKeyCode |= VK_LSHIFT;			// Left Shift	
	else if (dwHidCode == SCAN_LEFT_ALT)	dwKeyCode |= VK_LMENU ;			// Left Alt	
	else if (dwHidCode == SCAN_LEFT_GUI)	dwKeyCode |= VK_LWIN;			// Left Win	
	else if (dwHidCode == SCAN_RIGHT_CTRL)	dwKeyCode |= VK_RCONTROL;		// Right Ctrl	
	else if (dwHidCode == SCAN_RIGHT_SHIFT)	dwKeyCode |= VK_RSHIFT;			// Right Shift	
	else if (dwHidCode == SCAN_RIGHT_ALT)	dwKeyCode |= VK_RMENU ;			// Right Alt	
	else if (dwHidCode == SCAN_RIGHT_GUI)	dwKeyCode |= VK_RWIN;			// Right Win	
	else 
	{
		if (dwHidCode & SCAN_LEFT_CTRL)		dwKeyCode |= MOD_CONTROL;		// Left Ctrl	
		if (dwHidCode & SCAN_LEFT_ALT)		dwKeyCode |= MOD_SHIFT;			// Left Shift	
		if (dwHidCode & SCAN_LEFT_SHIFT)	dwKeyCode |= MOD_ALT ;			// Left Alt	
	}
	return dwKeyCode;
}
//////////////////////////////////////////////////////////////////////////
DWORD CCmdFormat::toHIDModifier(DWORD dwKeyCode)
{
	DWORD dwHIDCode = 0;
	if (dwKeyCode == VK_LCONTROL)		dwHIDCode |= SCAN_LEFT_CTRL;		// Left Ctrl	
	else if (dwKeyCode == VK_LSHIFT)	dwHIDCode |= SCAN_LEFT_SHIFT;		// Left Shift	
	else if (dwKeyCode == VK_LMENU)		dwHIDCode |= SCAN_LEFT_ALT ;		// Left Alt	
	else if (dwKeyCode == VK_LWIN)		dwHIDCode |= SCAN_LEFT_GUI;			// Left Win	
	else if (dwKeyCode == VK_RCONTROL)	dwHIDCode |= SCAN_RIGHT_CTRL;		// Right Ctrl	
	else if (dwKeyCode == VK_RSHIFT)	dwHIDCode |= SCAN_RIGHT_SHIFT;		// Right Shift	
	else if (dwKeyCode == VK_RMENU)		dwHIDCode |= SCAN_RIGHT_ALT;		// Right Alt	
	else if (dwKeyCode == VK_RWIN)		dwHIDCode |= SCAN_RIGHT_GUI;		// Right Win	
	else 
	{
		if (dwKeyCode & MOD_CONTROL)	dwHIDCode |= SCAN_LEFT_CTRL;		// Ctrl	
		if (dwKeyCode & MOD_ALT)		dwHIDCode |= SCAN_LEFT_SHIFT;		// Shift	
		if (dwKeyCode & MOD_SHIFT)		dwHIDCode |= SCAN_LEFT_ALT ;		// Alt	
	}

	return dwHIDCode;
}
//////////////////////////////////////////////////////////////////////////
DWORD CCmdFormat::toKeyCode(DWORD dwHidCode)
{
	switch(dwHidCode)
	{
	case 0x04:	return VK_A;				// A
	case 0x05:	return VK_B;				// B
	case 0x06:	return VK_C;				// C
	case 0x07:	return VK_D;				// D
	case 0x08:	return VK_E;				// E
	case 0x09:	return VK_F;				// F
	case 0x0A:	return VK_G;				// G
	case 0x0B:	return VK_H;				// H
	case 0x0C:	return VK_I;				// I
	case 0x0D:	return VK_J;				// J
	case 0x0E:	return VK_K;				// K
	case 0x0F:	return VK_L;				// L
	case 0x10:	return VK_M;				// M
	case 0x11:	return VK_N;				// N
	case 0x12:	return VK_O;				// O
	case 0x13:	return VK_P;				// P
	case 0x14:	return VK_Q;				// Q
	case 0x15:	return VK_R;				// R
	case 0x16:	return VK_S;				// S
	case 0x17:	return VK_T;				// T
	case 0x18:	return VK_U;				// U
	case 0x19:	return VK_V;				// V
	case 0x1A:	return VK_W;				// W
	case 0x1B:	return VK_X;				// X
	case 0x1C:	return VK_Y;				// Y
	case 0x1D:	return VK_Z;				// Z
	case 0x1E:	return VK_1;				// 1
	case 0x1F:	return VK_2;				// 2
	case 0x20:	return VK_3;				// 3
	case 0x21:	return VK_4;				// 4
	case 0x22:	return VK_5;				// 5
	case 0x23:	return VK_6;				// 6
	case 0x24:	return VK_7;				// 7
	case 0x25:	return VK_8;				// 8
	case 0x26:	return VK_9;				// 9
	case 0x27:	return VK_0;				// 0
	case 0x28:	return VK_RETURN;			// ENTER
	case 0x29:	return VK_ESCAPE;			// Esc
	case 0x2A:	return VK_BACK;				// Back
	case 0x2B:	return VK_TAB;				// Tab
	case 0x2C:	return VK_SPACE;			// Space
	case 0x2D:	return VK_OEM_MINUS;		// -_
	case 0x2E:	return VK_OEM_PLUS;			// +=
	case 0x2F:	return VK_OEM_4;			// [{
	case 0x30:	return VK_OEM_6;			// ]}
	case 0x31:	return VK_OEM_5;			// \ 
	case 0x33:	return VK_OEM_1;			// :;
	case 0x34:	return VK_OEM_7;			// '"
	case 0x35:	return VK_OEM_3;			// `~
	case 0x36:	return VK_OEM_COMMA;  		// ,<
	case 0x37:	return VK_OEM_PERIOD; 		// .>
	case 0x38:	return VK_OEM_2;			// /?
	case 0x39:	return VK_CAPITAL;			// Caps Lock
	case 0x3A:	return VK_F1;				// F1
	case 0x3B:	return VK_F2;				// F2
	case 0x3C:	return VK_F3;				// F3
	case 0x3D:	return VK_F4;				// F4
	case 0x3E:	return VK_F5;				// F5
	case 0x3F:	return VK_F6;				// F6
	case 0x40:	return VK_F7;				// F7
	case 0x41:	return VK_F8;				// F8
	case 0x42:	return VK_F9;				// F9
	case 0x43:	return VK_F10;				// F10
	case 0x44:	return VK_F11;				// F11
	case 0x45:	return VK_F12;				// F12
	case 0x46:	return VK_SNAPSHOT;			// Print Screen
	case 0x47:	return VK_SCROLL;			// Scroll Lock
	case 0x48:	return VK_PAUSE;			// Pause
	case 0x49:	return VK_INSERT;			// Insert
	case 0x4A:	return VK_HOME;				// Home
	case 0x4B:	return VK_PRIOR;			// Page Up
	case 0x4C:	return VK_DELETE;			// Delete
	case 0x4D:	return VK_END;				// End
	case 0x4E:	return VK_NEXT;				// Page Down
	case 0x4F:	return VK_RIGHT;			// Right
	case 0x50:	return VK_LEFT;				// Left
	case 0x51:	return VK_DOWN;				// Down
	case 0x52:	return VK_UP;				// Up
	case 0x53:	return VK_NUMLOCK;			// Num Lock
	case 0x54:	return VK_DIVIDE;			// keypad /
	case 0x55:	return VK_MULTIPLY;			// Keypad *
	case 0x56:	return VK_SUBTRACT;			// Keypad -
	case 0x57:	return VK_ADD;				// Keypad +
	case 0x59:	return VK_NUMPAD1;			// Num 1
	case 0x5A:	return VK_NUMPAD2;			// Num 2
	case 0x5B:	return VK_NUMPAD3;			// Num 3
	case 0x5C:	return VK_NUMPAD4;			// Num 4
	case 0x5D:	return VK_NUMPAD5;			// Num 5
	case 0x5E:	return VK_NUMPAD6;			// Num 6
	case 0x5F:	return VK_NUMPAD7;			// Num 7
	case 0x60:	return VK_NUMPAD8;			// Num 8
	case 0x61:	return VK_NUMPAD9;			// Num 9
	case 0x62:	return VK_NUMPAD0;			// Num 0
	case 0x63:	return VK_DECIMAL;			// Num .
	case 0x67:	return VK_OEM_NEC_EQUAL;	// Keypad =	
	case 0xE0:	return VK_LCONTROL;			// Left Ctrl
	case 0xE1:	return VK_LSHIFT;			// Left Shift
	case 0xE2:	return VK_LMENU;			// Left Alt
	case 0xE3:	return VK_LWIN;				// Left Win
	case 0xE4:	return VK_RCONTROL;			// Right Ctrl
	case 0xE5:	return VK_RSHIFT;			// Right Shift
	case 0xE6:	return VK_RMENU;			// Right Alt
	case 0xE7:	return VK_RWIN;				// Right Win
	default: return 0;
	}
}
//////////////////////////////////////////////////////////////////////////
BYTE* CCmdFormat::toData(GVORDER_PROFILE status, BYTE* byData)
{
	byData[DATA_STATUS_PROFILE]		= status.nProfile;
	byData[DATA_STATUS_BACKLIGHT]	= status.bBackLight ? 0xff : 0x00;
	byData[DATA_STATUS_ENABLE]		= status.bEnable ? 1 : 0;
	byData[DATA_STATUS_BREATH]		= status.nBeathType;
	return byData;
}
//////////////////////////////////////////////////////////////////////////
BYTE* CCmdFormat::toData(GVORDER_DPI dpi, BYTE* byData)
{
	byData[DATA_DPI_INDEX]	= dpi.nIndex;
	byData[DATA_DPI_X]		= dpi.nX;
	byData[DATA_DPI_Y]		= dpi.nY;
	return byData;
}
//////////////////////////////////////////////////////////////////////////
BYTE* CCmdFormat::toData(GVORDER_LED led, BYTE* byData)
{
	byData[DATA_LED_PROFILE]	= led.nProfile;
	byData[DATA_LED_R]			= GetRValue(led.clrRGB);
	byData[DATA_LED_G]			= GetGValue(led.clrRGB);
	byData[DATA_LED_B]			= GetBValue(led.clrRGB);
	byData[DATA_LED_BREATH]		= led.nBrightLight;
	return byData;
}
//////////////////////////////////////////////////////////////////////////
BYTE* CCmdFormat::toData(GVORDER_MATRIX matrix, BYTE* byData)
{
	int i = 0;
	BYTE* pData = byData;
	if (matrix.Matrix >= 0 && matrix.Matrix != GVORDER_MATRIX_DEFINE)
	{
		BYTE* pMatrix = s_KeyMatrix[matrix.Matrix];
		while (0 != pMatrix[i])
		{
			pData[pMatrix[i++] - 1] = matrix.nBrightLight;
		}
	}
	else if (GVORDER_MATRIX_DEFINE == matrix.Matrix)
	{
		pData[matrix.nLightNumber - 1] = matrix.nBrightLight;
	}
	else
	{
		for (int i = 0; i < MATRIX_LENGTH; i++)
		{
			pData[i] = matrix.nBrightLight;
		}
	}
	pData[MATRIX_LENGTH - 1] = matrix.Matrix;

	return byData;
}
//////////////////////////////////////////////////////////////////////////
BYTE* CCmdFormat::toData(GVORDER_MACROS_UNIT macros, BYTE* byData, int& nLen)
{
	nLen = 3;
	switch (macros.nType)
	{
	case GVORDER_MACROS_KEYBOARDUP:	{
											byData[DATA_MACROS_TYPEDOWN]  = MACROS_KB_UP;
											byData[DATA_MACROS_DWVAL1]	  = (BYTE)toHidCode(macros.dwValue);
											byData[DATA_MACROS_DWVAL2]	  = MACROS_DEFAULT;
											break;
									}
	case GVORDER_MACROS_KEYBOARDOWN:	{
											byData[DATA_MACROS_TYPEUP]	  = MACROS_KB_DOWN;
											byData[DATA_MACROS_UPVAL1]	  = (BYTE)toHidCode(macros.dwValue);
											byData[DATA_MACROS_DWVAL2]	  = MACROS_DEFAULT;
											break;
									}
	case GVORDER_MACROS_MEDIADOWN:	{
											byData[DATA_MACROS_TYPEDOWN]  = MACROS_MD_DOWN;
											byData[DATA_MACROS_DWVAL1]	  = ADDRL(macros.dwValue);
											byData[DATA_MACROS_DWVAL2]	  = ADDRM(macros.dwValue);
											break;
									}
	case GVORDER_MACROS_MEDIAUP:	{
											byData[DATA_MACROS_TYPEUP]	  = MACROS_MD_UP;
											byData[DATA_MACROS_UPVAL1]	  = ADDRL(macros.dwValue);
											byData[DATA_MACROS_UPVAL2]	  = ADDRM(macros.dwValue);
											break;
									}
	case GVORDER_MACROS_MOUSEDOWN:	{
											byData[DATA_MACROS_TYPEDOWN]  = MACROS_MS_DOWN;
											byData[DATA_MACROS_DWVAL1]	  = ADDRL(macros.dwValue);
											byData[DATA_MACROS_DWVAL2]	  = MACROS_DEFAULT;
											break;
									}
	case GVORDER_MACROS_MOUSEUP:	{
											byData[DATA_MACROS_TYPEUP]	  = MACROS_MS_UP;
											byData[DATA_MACROS_UPVAL1]	  = ADDRL(macros.dwValue);
											byData[DATA_MACROS_UPVAL2]	  = MACROS_DEFAULT;
											break;
									}
	case GVORDER_MACROS_MOUSEX:		{	
											byData[DATA_MACROS_TYPEDOWN]  = MACROS_MS_X;
											byData[DATA_MACROS_DWVAL1]	  = ADDRL(macros.dwValue);
											byData[DATA_MACROS_DWVAL2]	  = ADDRM(macros.dwValue);
											break;
									}
	case GVORDER_MACROS_MOUSEY:		{	
											byData[DATA_MACROS_TYPEDOWN]  = MACROS_MS_Y;
											byData[DATA_MACROS_DWVAL1]	  = ADDRL(macros.dwValue);
											byData[DATA_MACROS_DWVAL2]	  = ADDRM(macros.dwValue);
											break;
									}
	case GVORDER_MACROS_SCROLLUP:	{
											byData[DATA_MACROS_TYPEDOWN]  = MACROS_SLR_UP;
											byData[DATA_MACROS_DWVAL1]	  = MACROS_DEFAULT;
											byData[DATA_MACROS_DWVAL2]	  = MACROS_DEFAULT;
											break;
									}
	case GVORDER_MACROS_SCROLLDOWN: {
											byData[DATA_MACROS_TYPEDOWN]  = MACROS_SLR_DOWN;
											byData[DATA_MACROS_DWVAL1]	  = MACROS_DEFAULT;
											byData[DATA_MACROS_DWVAL2]	  = MACROS_DEFAULT;
											break;
									}
	case GVORDER_MACROS_DELAY:		{
											byData[DATA_MACROS_DELAY] = MACROS_DELAY;
											byData[DATA_MACROS_TIMEL] = ADDRL(macros.dwValue);
											byData[DATA_MACROS_TIMEH] = ADDRM(macros.dwValue);
											break;
									}
	}

	return byData;
}
//////////////////////////////////////////////////////////////////////////
BYTE* CCmdFormat::toData(GVORDER_MACROS_ATTR macrosAttr, BYTE* byData)
{
	USES_CONVERSION;
	byData[0] = macrosAttr.nIcon;
	memcpy(&byData[1], W2A(macrosAttr.szName), 15);
	BYTE bMode = 0;

	if(GVORDER_MACROS_EXEC == macrosAttr.RunType) //once
	{
		if(GVORDER_MACROS_AUTO == macrosAttr.TimeMode)
			bMode = 0x80;
		else if(GVORDER_MACROS_FIXEDTIME == macrosAttr.TimeMode)
			bMode = 0x81;
		else if(GVORDER_MACROS_NONE == macrosAttr.TimeMode)
			bMode = 0x82;
	}
	else if(GVORDER_MACROS_LOOP == macrosAttr.RunType)  // loop
	{
		if(GVORDER_MACROS_AUTO == macrosAttr.TimeMode)
			bMode = 0x88;
		else if(GVORDER_MACROS_FIXEDTIME == macrosAttr.TimeMode)
			bMode = 0x89;
		else if(GVORDER_MACROS_NONE == macrosAttr.TimeMode)
			bMode = 0x8a;
	}
	else if(GVORDER_MACROS_FIRE == macrosAttr.RunType) //fire key
	{
		if(GVORDER_MACROS_AUTO == macrosAttr.TimeMode)
			bMode = 0x8c;
		else if(GVORDER_MACROS_FIXEDTIME == macrosAttr.TimeMode)
			bMode = 0x8d;
		else if(GVORDER_MACROS_NONE == macrosAttr.TimeMode)
			bMode = 0x8e;
	}
	byData[MACROS_NAME_SIZE - 1] = bMode;

	return byData;
}
//////////////////////////////////////////////////////////////////////////
BYTE* CCmdFormat::toData(GVORDER_TILT_TYPE tilt, BYTE* byData)
{
	byData[DATA_TILT_TYPE] = tilt;
	return byData;
}
//////////////////////////////////////////////////////////////////////////
BYTE* CCmdFormat::toData(GVORDER_KEYFUN fnKey, BYTE* byData)
{
	byData[DATA_BTN_INDEX] = fnKey.nIndex;
	byData[DATA_BTN_TYPE] = fnKey.fnType;
	switch(fnKey.fnType)
	{
	case GVORDER_FUN_MOUSE:			
		byData[DATA_BTN_OPT1] = fnKey.value.mouse.msbutton;
		byData[DATA_BTN_OPT2] = fnKey.value.mouse.wheelcount;
		byData[DATA_BTN_OPT3] = fnKey.value.mouse.tiltcount;
		break;
	case GVORDER_FUN_KEYBOARD:		
		byData[DATA_BTN_OPT1] = (BYTE)toHIDModifier(fnKey.value.keyboard.keyModifier);
		byData[DATA_BTN_OPT2] = (BYTE)toHidCode(fnKey.value.keyboard.keyCode);
		byData[DATA_BTN_OPT3] = MACROS_DEFAULT;
		break;
	case GVORDER_FUN_MOUSELOOP:		
		byData[DATA_BTN_OPT1] = fnKey.value.mouseloop.msbutton;
		byData[DATA_BTN_OPT2] = fnKey.value.mouseloop.times;
		byData[DATA_BTN_OPT3] = fnKey.value.mouseloop.delay;
		break;
	case GVORDER_FUN_KEYLOOP:		
		byData[DATA_BTN_OPT1] = (BYTE)toHidCode(fnKey.value.keyloop.keyCode);
		byData[DATA_BTN_OPT2] = fnKey.value.keyloop.times;
		byData[DATA_BTN_OPT3] = fnKey.value.keyloop.delay;
		break;
	case GVORDER_FUN_MACROSONCE:	
	case GVORDER_FUN_MACROSLOOP:	
	case GVORDER_FUN_MACROCSFIRE:	
		{
			DWORD dwAddr = fnKey.value.macros.macrosIndex * MACROS_KEYS_SIZE + MACROS_KEYS_ADDR;
			byData[DATA_BTN_TYPE] = fnKey.value.macros.type;
			byData[DATA_BTN_OPT1] = ADDRL(dwAddr);
			byData[DATA_BTN_OPT2] = ADDRM(dwAddr);
			byData[DATA_BTN_OPT3] = ADDRH(dwAddr);
			break;
		}
	case GVORDER_FUN_FIREDPI:		
		byData[DATA_BTN_OPT1] = fnKey.value.dpi.x;
		byData[DATA_BTN_OPT2] = fnKey.value.dpi.y;
		byData[DATA_BTN_OPT3] = fnKey.value.dpi.ms;
		break;
	case GVORDER_FUN_SWITCHDPI:		
		byData[DATA_BTN_OPT1] = fnKey.value.dpi.x;
		byData[DATA_BTN_OPT2] = fnKey.value.dpi.y;
		byData[DATA_BTN_OPT3] = MACROS_DEFAULT;
		break;
	case GVORDER_FUN_MEDIA:			
		byData[DATA_BTN_OPT1] = MACROS_DEFAULT;
		byData[DATA_BTN_OPT2] = s_byMediaKey[fnKey.value.media.key][0];
		byData[DATA_BTN_OPT3] = s_byMediaKey[fnKey.value.media.key][1];
		break;
	case GVORDER_FUN_LOCKXY:
		byData[DATA_BTN_OPT1] = fnKey.value.lock.x;
		byData[DATA_BTN_OPT2] = fnKey.value.lock.y;
		byData[DATA_BTN_OPT3] = MACROS_DEFAULT;
		break;
	case GVORDER_FUN_APP:
		byData[DATA_BTN_OPT1] = fnKey.nIndex;
		byData[DATA_BTN_OPT2] = MACROS_DEFAULT;
		byData[DATA_BTN_OPT3] = MACROS_DEFAULT;
		break;
	case GVORDER_FUN_SWITCHPRO:		
		byData[DATA_BTN_OPT1] = fnKey.value.profile.nProfile;
		byData[DATA_BTN_OPT2] = MACROS_DEFAULT;
		byData[DATA_BTN_OPT3] = MACROS_DEFAULT;
		break;
	case GVORDER_FUN_GHOST:
	case GVORDER_FUN_PLUSDPI:		
	case GVORDER_FUN_SUBDPI:		
	case GVORDER_FUN_LOOPDPI:		
	case GVORDER_FUN_DEFAULT:	
	case GVORDER_FUN_NONE:			
	default:
		byData[DATA_BTN_OPT1] = MACROS_DEFAULT;
		byData[DATA_BTN_OPT2] = MACROS_DEFAULT;
		byData[DATA_BTN_OPT3] = MACROS_DEFAULT;
		break;
	}
	return byData;
}
//////////////////////////////////////////////////////////////////////////
BYTE* CCmdFormat::toData(bool bLock, BYTE* byData)
{
	byData[DATA_LOCK_STU] = bLock ? 0 : 1;
	return byData;
}
//////////////////////////////////////////////////////////////////////////
BYTE* CCmdFormat::toData(GVORDER_LED_CFG cfg, BYTE* byData)
{
	byData[DATA_LEDCFG_TYPE]	= cfg.type;
	byData[DATA_LEDCFG_BRIGHT]	= cfg.nBright;
	byData[DATA_LEDCFG_SPEED]	= cfg.nSpeed;
	byData[DATA_LEDCFG_CLRCUT]	= cfg.nClrCount;
	byData[DATA_LEDCFG_CYCLE]	= GVORDER_LED_CYCLING != cfg.type ? 8 : 0;
	return byData;
}
//////////////////////////////////////////////////////////////////////////
BYTE* CCmdFormat::toLedData(GVORDER_PROFILE status, BYTE* byData, bool bMultiColor)
{
	//+2原因0xcc在，數組的[1]的位置
	byData[DATA_SHW_STYLE+2]	= status.nBeathType;
	// check Multi Color
	if (bMultiColor)
	{
		if (status.nBeathType == 2)		// breath
			byData[DATA_SHW_STYLE+2] = 6;	// change color breath
		else if (status.nBeathType == 4)	// single flash
			byData[DATA_SHW_STYLE+2] = 7;	// single flash change color
		else if (status.nBeathType == 5)	// dual flash
			byData[DATA_SHW_STYLE+2] = 8;	// dual flash change color
	}
	byData[DATA_SHW_BRIGHT+2]	= (BYTE)(status.nBrightness * 25.5);
	byData[DATA_SHW_BRIGHT+2]     = status.nBrightness;    // Peter Lee 2017/7/4 for M3
	byData[DATA_SHW_R+2]		= GetRValue(status.clr);
	byData[DATA_SHW_G+2]		= GetGValue(status.clr);
	byData[DATA_SHW_B+2]		= GetBValue(status.clr);
	//byData[DATA_SHW_SPEED+2]    = 5 - status.nSpeed + 5;
	// Peter Lee 2017/7/4 for M3
	if (status.nBeathType == GVORDER_LED_SINGLETWINKLE || status.nBeathType == GVORDER_LED_TWICETWINKLE || status.nBeathType == 7 || status.nBeathType == 8)
		byData[DATA_SHW_SPEED+2] = (BYTE)(11 - status.nSpeed) * 20; 
	else
		byData[DATA_SHW_SPEED+2] = (BYTE)(11 - status.nSpeed) * 2;  
	if (!status.bBackLight) byData[DATA_SHW_BRIGHT+2] = 0;
	return byData;

}
//////////////////////////////////////////////////////////////////////////
GVORDER_PROFILE CCmdFormat::toProfile(BYTE* byData)
{
	GVORDER_PROFILE status;
	status.nProfile		= byData[DATA_STATUS_PROFILE];
	status.bBackLight	= byData[DATA_STATUS_BACKLIGHT] == 0xff;
	status.bEnable		= byData[DATA_STATUS_ENABLE] == 1;
	status.nBeathType	= (GVORDER_LED_MODE)byData[DATA_STATUS_BREATH];
	return status;
}
//////////////////////////////////////////////////////////////////////////
GVORDER_DPI CCmdFormat::toDPI(BYTE* byData)
{
	GVORDER_DPI dpi;
	dpi.nIndex	= byData[DATA_DPI_INDEX];
	dpi.nX		= byData[DATA_DPI_X];
	dpi.nY		= byData[DATA_DPI_Y];
	return dpi;
}
//////////////////////////////////////////////////////////////////////////
GVORDER_LED CCmdFormat::toLed(BYTE* byData)
{
	GVORDER_LED led;
	led.nProfile	= byData[DATA_LED_PROFILE];
	led.clrRGB		= RGB(byData[DATA_LED_R], byData[DATA_LED_G], byData[DATA_LED_B]);
	led.nBrightLight= byData[DATA_LED_BREATH];
	return led;
}
//////////////////////////////////////////////////////////////////////////
GVORDER_LED_CFG	CCmdFormat::toLedCfg(BYTE* byData)
{
	GVORDER_LED_CFG cfg;
	cfg.type = (GVORDER_LED_MODE)byData[DATA_LEDCFG_TYPE];
	cfg.nBright = byData[DATA_LEDCFG_BRIGHT];
	cfg.nSpeed = byData[DATA_LEDCFG_SPEED];
	cfg.nClrCount = byData[DATA_LEDCFG_CLRCUT];

	return cfg;
}
//////////////////////////////////////////////////////////////////////////
GVORDER_KEYFUN CCmdFormat::toKeyFun(BYTE* byData)
{
	GVORDER_KEYFUN fnKey;
	fnKey.nIndex = byData[DATA_BTN_INDEX];
	fnKey.fnType = (GVORDER_FUNCTION_TYPE) byData[DATA_BTN_TYPE];
	switch(fnKey.fnType)
	{
	case GVORDER_FUN_MOUSE:			
		fnKey.value.mouse.msbutton   = byData[DATA_BTN_OPT1];
		fnKey.value.mouse.wheelcount = byData[DATA_BTN_OPT2];
		fnKey.value.mouse.tiltcount  = byData[DATA_BTN_OPT3];
		break;
	case GVORDER_FUN_KEYBOARD:		
		fnKey.value.keyboard.keyModifier = (BYTE)toKeyModifier(byData[DATA_BTN_OPT1]);
		fnKey.value.keyboard.keyCode	 = (BYTE)toKeyCode(byData[DATA_BTN_OPT2]);
		break;
	case GVORDER_FUN_MOUSELOOP:		
		fnKey.value.mouseloop.msbutton = byData[DATA_BTN_OPT1];
		fnKey.value.mouseloop.times	   = byData[DATA_BTN_OPT2];
		fnKey.value.mouseloop.delay    = byData[DATA_BTN_OPT3];
		break;
	case GVORDER_FUN_KEYLOOP:		
		fnKey.value.keyloop.keyCode = (BYTE)toKeyCode(byData[DATA_BTN_OPT1]);
		fnKey.value.keyloop.times   = byData[DATA_BTN_OPT2];
		fnKey.value.keyloop.delay   = byData[DATA_BTN_OPT3];
		break;
	case GVORDER_FUN_MACROSONCE:
	case GVORDER_FUN_MACROSLOOP:	
	case GVORDER_FUN_MACROCSFIRE:	
		fnKey.value.macros.type = (byData[DATA_BTN_TYPE] - GVORDER_FUN_MACROSONCE);
		fnKey.value.macros.macrosIndex = ((byData[DATA_BTN_OPT1] | (byData[DATA_BTN_OPT2] << 8) | (byData[DATA_BTN_OPT3] << 16)) - MACROS_KEYS_ADDR) / MACROS_KEYS_SIZE;
		break;
	case GVORDER_FUN_FIREDPI:		
		fnKey.value.dpi.ms = byData[DATA_BTN_OPT3];
	case GVORDER_FUN_SWITCHDPI:
		fnKey.value.dpi.x = byData[DATA_BTN_OPT1];
		fnKey.value.dpi.y = byData[DATA_BTN_OPT2];
		break;
	case GVORDER_FUN_MEDIA:
		for (int i = 0; i < GVORDER_MEDIA_QTY; i++)
		{
			if(s_byMediaKey[i][0] == byData[DATA_BTN_OPT2] && s_byMediaKey[i][1] == byData[DATA_BTN_OPT3])
			{
				fnKey.value.media.key = (GVORDER_MEDIA_KEY)i;
				break;
			}
		}
		break;
	case GVORDER_FUN_LOCKXY:			
		fnKey.value.lock.x = byData[DATA_BTN_OPT1];
		fnKey.value.lock.y = byData[DATA_BTN_OPT2];
		break;
	case GVORDER_FUN_SWITCHPRO:   
		fnKey.value.profile.nProfile = byData[DATA_BTN_OPT1];
		break;
	}
	return fnKey;
}
//////////////////////////////////////////////////////////////////////////
GVORDER_MACROS_UNIT CCmdFormat::toMacrosunit(BYTE* byData, int& nLen)
{
	GVORDER_MACROS_UNIT macros = {GVORDER_MACROS_DELAY};
	nLen = 3;

	switch (byData[0])
	{
	case MACROS_DELAY:		{
									macros.nType = GVORDER_MACROS_DELAY;
									macros.dwValue = ((byData[DATA_MACROS_TIMEL]) | (byData[DATA_MACROS_TIMEH] << 8));
									break;
							}
	case MACROS_KB_DOWN:	{
									macros.nType = GVORDER_MACROS_KEYBOARDOWN;
									macros.dwValue = toKeyCode(byData[DATA_MACROS_DWVAL1]);
									break;
							}
	case MACROS_KB_UP:		{
									macros.nType = GVORDER_MACROS_KEYBOARDUP;
									macros.dwValue = toKeyCode(byData[DATA_MACROS_UPVAL1]);
									break;
							}
	case MACROS_MD_DOWN:	{
									macros.nType = GVORDER_MACROS_MOUSEDOWN;
									macros.dwValue = (byData[DATA_MACROS_DWVAL1] | (byData[DATA_MACROS_DWVAL2] << 8));
									break;
							}
	case MACROS_MD_UP:		{
									macros.nType = GVORDER_MACROS_MOUSEUP;
									macros.dwValue = (byData[DATA_MACROS_UPVAL1] | (byData[DATA_MACROS_UPVAL2] << 8));
									break;
							}
	case MACROS_MS_DOWN:	{
									macros.nType = GVORDER_MACROS_MOUSEDOWN;
									macros.dwValue = byData[DATA_MACROS_DWVAL1];
									break;
							}
	case MACROS_MS_UP:		{
									macros.nType = GVORDER_MACROS_MOUSEUP;
									macros.dwValue = byData[DATA_MACROS_UPVAL1];
									break;
							}
	case MACROS_MS_X:		{	
									macros.nType = GVORDER_MACROS_MOUSEX;
									macros.dwValue = (byData[DATA_MACROS_DWVAL1] | (byData[DATA_MACROS_DWVAL2] << 8));
									break;
							}
	case MACROS_MS_Y:		{	
									macros.nType = GVORDER_MACROS_MOUSEY;
									macros.dwValue = (byData[DATA_MACROS_DWVAL1] | (byData[DATA_MACROS_DWVAL2] << 8));
									break;
							}
	case MACROS_SLR_UP:		{
									macros.nType = GVORDER_MACROS_SCROLLUP;
									break;
							}
	case MACROS_SLR_DOWN:	{
									macros.nType = GVORDER_MACROS_SCROLLDOWN;
									break;
							}
	default:						nLen = 0;
									break;
	}

	return macros;
}
//////////////////////////////////////////////////////////////////////////
GVORDER_MACROS_ATTR CCmdFormat::toMacrosattr(BYTE* byData)
{
	GVORDER_MACROS_ATTR macrosAttr;
	USES_CONVERSION;
	char szName[15] = "";
	memcpy(szName, &byData[1], 14);
	_tcscpy_s(macrosAttr.szName, 15, A2W(szName));
	macrosAttr.szName[14] = 0;
	macrosAttr.nIcon = byData[0];
	BYTE bMode = 0;

	switch(byData[MACROS_NAME_SIZE - 1])
	{
	case 0x80: 
	case 0x81: 
	case 0x82: 
		macrosAttr.RunType = GVORDER_MACROS_EXEC; break;
	case 0x88: 
	case 0x89: 
	case 0x8A: 
		macrosAttr.RunType = GVORDER_MACROS_LOOP; break;
	case 0x8C: 
	case 0x8D: 
	case 0x8E: 
		macrosAttr.RunType = GVORDER_MACROS_FIRE; break;
	}

	switch(byData[MACROS_NAME_SIZE - 1])
	{
	case 0x80: 
	case 0x88: 
	case 0x8C: 
		macrosAttr.TimeMode = GVORDER_MACROS_AUTO; break;
	case 0x81: 
	case 0x89: 
	case 0x8D: 
		macrosAttr.TimeMode = GVORDER_MACROS_FIXEDTIME; break;
	case 0x82: 
	case 0x8A: 
	case 0x8E: 
		macrosAttr.TimeMode = GVORDER_MACROS_NONE; break;
	}

	return macrosAttr;
}
//////////////////////////////////////////////////////////////////////////
int CCmdFormat::toReportRate(BYTE* byData)
{
	return byData[DATA_REPORT_RATE];
}
//////////////////////////////////////////////////////////////////////////
int CCmdFormat::toLockDPI(BYTE* byData)
{
	return byData[DATA_LOCK_DPI];
}
//////////////////////////////////////////////////////////////////////////
int CCmdFormat::toLockProfile(BYTE* byData)
{
	return byData[DATA_LOCK_PRO];
}
