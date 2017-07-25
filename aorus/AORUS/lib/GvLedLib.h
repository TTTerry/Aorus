#ifndef GV_GVLEDLIB_H
#define GV_GVLEDLIB_H

#ifdef GVLEDLIB_EXPORTS
#define GVLEDLIB_API __declspec(dllexport)
#else
#define GVLEDLIB_API __declspec(dllimport)
#endif


//////////////////////////////////////////////////////////////////////////
/// Led����ģʽ��For XH300/XC300/XC700/XTC300/XM300
#define TYPE_BRIGHT		1	// ����
#define TYPE_BREATH		2	// ����
#define TYPE_CYCLING	3	// ���ѭ��

//////////////////////////////////////////////////////////////////////////
/// Led�O�Å�����For XH300/XC300/XC700/XTC300
typedef struct _GVLED_XCFG
{
	int nType;				// Led ����
	int nBright;			// ���� 1~10
	int nSpeed;				// �ٶ� 1~10
	unsigned long clr;		// ��ɫ�б�

}GVLED_XCFG, *PGVLED_XCFG;
///
//////////////////////////////////////////////////////////////////////////
/// Led�O�Å�����For XK700
typedef struct _GVLED_KCFG
{
#define START_PRESS			0	// ������Ч��
#define START_AUTO			1	// �Ԅӆ���Ч��

#define TYPE_CONSISTENT		1	// �a��
#define TYPE_PULSING		2	// �������ɫ����1~2
#define TYPE_REACTIVE		3	// �|�l
#define TYPE_RIPPLE			4	// ���y
#define TYPE_CYCLINGS		5	// ���ѭ�h
#define TYPE_WAVE			6	// ����
#define TYPE_LOL			7	// LOL�����I
#define TYPE_CS				8	// CS�����I

	int		nType;			// LedЧ��
	int		nSpeed;			// �ٶ�
	int		nBright;		// ����
	int		nStartWay;		// ����Ч����ʽ
	int		nTimes;			// ����Ч���Δ�
	int		nWidth;			// ���ȣ����y/������Ч
	int		nAngle;			// �Ƕȣ�������Ч
	bool	bOn;			// �_�P��Ч
	int		nCount;			// �ɫ����
	unsigned long clrList[10];	// �ɫ�б�

}GVLED_KCFG, *PGVLED_KCFG;
///
//////////////////////////////////////////////////////////////////////////
/// XM300 LED�趨ֵ
typedef struct _GVLED_MCFG
{
	bool bBackLight;	// �Ƿ񱳹⣬true��ʾ������false��ʾoff
	int  nBright;		// ���� 0~10
	int  nSpeed;		// �ٶ� 0~5
	unsigned long clr;	// Profile�ɫ
	int nType;			// ����ģʽ

} GVLED_MCFG, *PGVLED_MCFG;
///
//////////////////////////////////////////////////////////////////////////
/// Keyboard ���I�������x
typedef enum _GVLED_VK
{
	GVK_LCTRL = 0,		//	Left CTRL
	GVK_LWIN,			//	Left WIN
	GVK_LALT,			//	Left ALT
	GVK_SPACE,			//	Space
	GVK_RALT,			//	Right ALT
	GVK_WINLOCK,		//	WinLock
	GVK_FN,				//	Fn
	GVK_RCTRL,			//	Right CTRL
	GVK_LEFT,			//	Left
	GVK_DOWN,			//	Down
	GVK_RIGHT,			//	Right
	GVK_NUM0,			//	Num 0
	GVK_NUM_PERIOD,		//	Num .
	GVK_NUM_ENTER,		//	Num Enter
	GVK_LSHIFT,			//	Left Shift
	GVK_Z,				//	Z
	GVK_X,				//	X
	GVK_C,				//	C
	GVK_V,				//	V
	GVK_B,				//	B
	GVK_N,				//	N
	GVK_M,				//	M
	GVK_COMMA,			//	,<
	GVK_PERIOD,			//	.>
	GVK_SLASH,			//	/?
	GVK_RSHIFT,			//	Right Shift
	GVK_UP,				//	Up
	GVK_NUM1,			//	Num 1
	GVK_NUM2,			//	Num 2
	GVK_NUM3,			//	Num 3
	GVK_CAPSLOCK,		//	CapsLock
	GVK_A,				//	A
	GVK_S,				//	S
	GVK_D,				//	D
	GVK_F,				//	F
	GVK_G,				//	G
	GVK_H,				//	H
	GVK_J,				//	J
	GVK_K,				//	K
	GVK_L,				//	Left 
	GVK_SEMICOLON,		//	;:
	GVK_APOSTROPHE,		//	'"
	GVK_ENTER,			//	Enter
	GVK_NUM4,			//	Num 4
	GVK_NUM5,			//	Num 5
	GVK_NUM6,			//	Num 6
	GVK_NUM_PLUS,		//	NUm +
	GVK_TAB,			//	Tab
	GVK_Q,				//	Q
	GVK_W,				//	W
	GVK_E,				//	E
	GVK_R,				//	Right 
	GVK_T,				//	T
	GVK_Y,				//	Y
	GVK_U,				//	U
	GVK_I,				//	I
	GVK_O,				//	O
	GVK_P,				//	P
	GVK_LBRACKETS,		//	[{
	GVK_RBRACKETS,		//	]}
	GVK_BACKSLASH,		//	\|
	GVK_DELETE,			//	Delete
	GVK_END,			//	End
	GVK_PAGEDOWN,		//	PageDown
	GVK_NUM7,			//	Num 7
	GVK_NUM8,			//	Num 8
	GVK_NUM9,			//	Num 9
	GVK_WAVY,			//	`~
	GVK_1,				//	1
	GVK_2,				//	2
	GVK_3,				//	3
	GVK_4,				//	4
	GVK_5,				//	5
	GVK_6,				//	6
	GVK_7,				//	7
	GVK_8,				//	8
	GVK_9,				//	9
	GVK_0,				//	0
	GVK_MINUS,			//	-_
	GVK_EQUAL,			//	=+
	GVK_BACKSPACE,		//	BackSpace
	GVK_INSERT,			//	Insert
	GVK_HOME,			//	Home
	GVK_PAGEUP,			//	Page Up
	GVK_NUM,			//	Num
	GVK_NUM_DIVIDE,		//	Num /
	GVK_NUM_MULTIPLY,	//	Num *
	GVK_NUM_SUBTRACT,	//	Num -
	GVK_ESC,			//	Esc
	GVK_F1,				//	F1
	GVK_F2,				//	F2
	GVK_F3,				//	F3
	GVK_F4,				//	F4
	GVK_F5,				//	F5
	GVK_F6,				//	F6
	GVK_F7,				//	F7
	GVK_F8,				//	F8
	GVK_F9,				//	F9
	GVK_F10,			//	F10
	GVK_F11,			//	F11
	GVK_F12,			//	F12
	GVK_PRINTSCREEN,	//	PrintScreen
	GVK_SCROLLLOCK,		//	Scroll Lock
	GVK_PAUSE,			//	Pause
	GVK_LOGO,			//	Logo

}GVLED_VK, *PVLED_VK;



#ifdef __cplusplus
extern "C" {
#endif

	/****************************************************************************************
	 * ����������
	 * ��ʼ���O�䣬
	 * VID���̶�Ϊ 0x1044
	 * PID��XH300(0x7A24), XC300(0x7A21), XC700(0x7A22), XCT7(0x7A23), XK700(0x7A19/0x7A1A), XM300(0x7A13)
	 *
	 * ���������
	 * [in]  wVID      �O��VID
	 * [in]  wPID      �O��PID
	 * [out] nIndex    �O������
	 * 
	 * ����ֵ��
	 * true ��ʾ��ʼ���ɹ���
	 ****************************************************************************************/
	GVLEDLIB_API bool GvLedInit(unsigned short wVID, unsigned short wPID, int& nIndex);

	/****************************************************************************************
	 * ����������
	 * �@ȡ�O���Ƿ��B��
	 *
	 * ���������
	 * [in] nIndex    �O������
	 * 
	 * ����ֵ��
	 * true ��ʾ��Ȼ�B�ӣ�
	 ****************************************************************************************/
	GVLEDLIB_API bool GvLedIsConnect(int nIndex);
	
	/****************************************************************************************
	 * ����������
	 * ����Timer
	 *
	 * ���������
	 * [in] nIndex    �O������
	 * 
	 * ����ֵ��
	 * true ��ʾ��Ȼ�B�ӣ�
	 ****************************************************************************************/
	GVLEDLIB_API bool GvLedResetTimer(int nIndex);
	
	/****************************************************************************************
	 * ����������
	 * �O���ɫ
	 *
	 * ���������
	 * [in] nIndex    �O������
	 * 
	 * ����ֵ��
	 * true ��ʾ��Ȼ�B�ӣ�
	 ****************************************************************************************/
	GVLEDLIB_API bool GvLedSetClr(unsigned long clr, int nIndex);
	
	/****************************************************************************************
	 * ����������
	 * ��ʱ�趨Led����
	 *
	 * ���������
	 * [in] nIndex    �O������
	 * [in] config    Led���Ʋ���
	 * 
	 * ����ֵ��
	 * true ��ʾ���ͳɹ���
	 ****************************************************************************************/
	GVLEDLIB_API bool GvLedXSet(int nIndex, GVLED_XCFG config);
	
	/****************************************************************************************
	 * ����������
	 * ��ȡLed����
	 *
	 * ���������
	 * [in]  nIndex    �O������
	 * [out] config    Led���Ʋ���
	 * 
	 * ����ֵ��
	 * true ��ʾ���ͳɹ���
	 ****************************************************************************************/
	GVLEDLIB_API bool GvLedXGet(int nIndex, GVLED_XCFG& config);
	
	/****************************************************************************************
	 * ����������
	 * ��������趨������ִ������ָ���κ��ָ�ԭ��״̬
	 *
	 * ���������
	 * [in]  nIndex    �O������
	 * 
	 * ����ֵ��
	 * true ��ʾ���ͳɹ���
	 ****************************************************************************************/
	GVLEDLIB_API bool GvLedXSave(int nIndex);

	/****************************************************************************************
	 * ����������
	 * �趨XK700 Led����
	 *
	 * ���������
	 * [in] nIndex    �O������
	 * [in] config    Led���Ʋ���
	 * 
	 * ����ֵ��
	 * true ��ʾ���ͳɹ���
	 ****************************************************************************************/
	GVLEDLIB_API bool GvLedKSet(int nIndex, GVLED_KCFG config);

	/****************************************************************************************
	 * ����������
	 * �趨XK700 �Ϊ����I Led����
	 *
	 * ���������
	 * [in] nIndex    �O������
	 * [in] config    Led���Ʋ���
	 * 
	 * ����ֵ��
	 * true ��ʾ���ͳɹ���
	 ****************************************************************************************/
	GVLEDLIB_API bool GvLedKSetSingle(int nIndex, bool bKbStatus[107], GVLED_KCFG config);

	/****************************************************************************************
	 * ����������
	 * �@ȡXK700Ĭ�JLed����
	 *
	 * ���������
	 * [in]  nType     LedЧ�����
	 * [out] config    Led���Ʋ���
	 * 
	 * ����ֵ��
	 * void
	 ****************************************************************************************/
	GVLEDLIB_API void GvLedKGetDef(int nType, GVLED_KCFG& config);

	/****************************************************************************************
	 * ����������
	 * ��ʱ�趨Led����, For XM300
	 *
	 * ���������
	 * [in] nIndex    �O������
	 * [in] config    Led���Ʋ���
	 * 
	 * ����ֵ��
	 * true ��ʾ���ͳɹ���
	 ****************************************************************************************/
	GVLEDLIB_API bool GvLedMSet(int nIndex, GVLED_MCFG config);
	
	/****************************************************************************************
	 * ����������
	 * ��ȡLed����, For XM300
	 *
	 * ���������
	 * [in]  nIndex    �O������
	 * [out] config    Led���Ʋ���
	 * 
	 * ����ֵ��
	 * true ��ʾ���ͳɹ���
	 ****************************************************************************************/
	GVLEDLIB_API bool GvLedMGet(int nIndex, GVLED_MCFG& config);
	
	/****************************************************************************************
	 * ����������
	 * ��������趨������ִ������ָ���κ��ָ�ԭ��״̬, For XM300
	 *
	 * ���������
	 * [in]  nIndex    �O������
	 * [out] config    Led���Ʋ���
	 * 
	 * ����ֵ��
	 * true ��ʾ���ͳɹ���
	 ****************************************************************************************/
	GVLEDLIB_API bool GvLedMSave(int nIndex, GVLED_MCFG config);


#ifdef __cplusplus
}
#endif

#endif