#ifndef GV_ORDERLIB_H
#define GV_ORDERLIB_H


#ifdef  GV_ORDERLIB_EXPORTS
#define GV_ORDERLIB_API __declspec(dllexport)
#else
#define GV_ORDERLIB_API __declspec(dllimport)
#endif

#define GVORDER_DEVICE_MAX	20

#define GVAPI_OK					0x00000000
#define GVAPI_CMDERR_FAILED			0x20000001	// Unknown Error
#define GVAPI_CMDERR_ERR_PARAM		0x20000002	// invalid parameter
#define GVAPI_CMDERR_ERR_NOBOARD	0x20000003	// no boards found
#define GVAPI_CMDERR_NOHID			0x20000004	// no HID found
#define GVAPI_CMDERR_DEVNOFOUND		0x20000005	// device not found
#define GVAPI_CMDERR_DEVNOOPEN		0x20000006	// device not open
#define GVAPI_CMDERR_CONNECT		0x20000007	// connect device failed
#define GVAPI_CMDERR_DISCONNECT		0x20000008	// disconnect device failed
#define GVAPI_CMDERR_SENDDATA		0x20000009	// send data failed
#define GVAPI_FWERR_IMPORT			0x20000010	// Import Marco Error
#define GVAPI_FWERR_EXPORT			0x20000011	// Export Marco Error
#define GVAPI_CMDERR_RECVDATA		0x2000000A	// receive data failed
#define GVAPI_CMDERR_NOINIT			0x2000000B	// Fireware havn't Init

//////////////////////////////////////////////////////////////////////////
/// �ƺž�����Ϸ����
typedef enum _GVORDER_MATRIX_GAME
{
	GVORDER_MATRIX_NONE = -1,
	GVORDER_MATRIX_FPS = 0,
	GVORDER_MATRIX_MMO,
	GVORDER_MATRIX_MOBA,
	GVORDER_MATRIX_RTS,
	GVORDER_MATRIX_CSGO,
	GVORDER_MATRIX_DOTAII,
	GVORDER_MATRIX_LOL,
	GVORDER_MATRIX_STARCRAFTII,
	GVORDER_MATRIX_DEFINE,

}GVORDER_MATRIX_GAME, *PGVORDER_MATRIX_GAME;
///
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
/// �豸ID�ṹ��
typedef struct _GVORDER_DEVICE
{
	DWORD dwVID;
	DWORD dwPID;
	DWORD dwHID;

} GVORDER_DEVICE, *PGVORDER_DEVICE;
///
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
/// �ƺž�����Ϸ����
typedef enum _GVORDER_LED_MODE
{
	GVORDER_LED_CONSISTENT = 1, // �a��
	GVORDER_LED_BREATHING,		// ����
	GVORDER_LED_CYCLING,		// �ɫѭ�h
	GVORDER_LED_SINGLETWINKLE,
	GVORDER_LED_TWICETWINKLE,
	GVORDER_LED_OFF,			// �ɫ�P�]

}GVORDER_LED_MODE, *PGVORDER_LED_MODE;

//////////////////////////////////////////////////////////////////////////
/// Profile�趨ֵ
typedef struct _GVORDER_STATUS
{
	int  nProfile;
	bool bBackLight;  // �Ƿ񱳹⣬true��ʾ������false��ʾoff
	bool bEnable;	  // �Ƿ���
	int  nBrightness; // ���� 0~10
	int  nSpeed;	  // �ٶ� 0~5
	COLORREF clr;	  // Profile�ɫ
	GVORDER_LED_MODE nBeathType; // ����ģʽ

} GVORDER_PROFILE, *PGVORDER_STATUS;
///
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
/// LED����
#define GVORDER_LED_TYPE	0x00001
#define GVORDER_LED_BRIGHT	0x00002
#define GVORDER_LED_SPEED	0x00004
#define GVORDER_LED_BASE	((GVORDER_LED_TYPE)|(GVORDER_LED_BRIGHT)|(GVORDER_LED_SPEED))
#define GVORDER_LED_COLOR	0x00008
#define GVORDER_LED_ALL		0xFFFFF

#define GVORDER_CLR_MAX 10
typedef struct _GVORDER_LED_CFG
{
	GVORDER_LED_MODE type;
	int nBright;
	int nSpeed;
	int nClrCount; // �ɫ���M���п������pɫ�������������ģʽ����ɫѭ�h���t��7���a����1���������ܞ�1���ܞ�2(�pɫ����)
	COLORREF clrArray[GVORDER_CLR_MAX];

}GVORDER_LED_CFG, *PGVORDER_LED_CFG;
///
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
/// DPI�趨ֵ
typedef struct _GVORDER_DPI
{
	int nIndex;		// Dpi Index
	int nX;
	int nY;

} GVORDER_DPI, *PGVORDER_DPI;
///
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
/// LED�趨ֵ For K7
typedef struct _GVORDER_LED
{
	int nProfile;
	COLORREF clrRGB;	// �ɫ
	int  nBrightLight;  // if > 128, it's breath
	GVORDER_MATRIX_GAME Matrix; // ���Ⱦ��
	int nLight;

} GVORDER_LED, *PGVORDER_LED;
///
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
/// ���ҝL݆ģʽ
typedef enum _GVORDER_TILT_TYPE
{
	GVORDER_TILT_TYPE_HW = 1,	// Ӳ��ģʽ
	GVORDER_TILT_TYPE_SW,		// ܛ��ģʽ��Ӳ��HID��Ϣ��0xBC

}GVORDER_TILT_TYPE, *PGVORDER_TILT_TYPE;

#define GVORDER_TILT_MSG	0xBC
///
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
/// ��ý�w�I
typedef enum _GVORDER_MEDIA_KEY
{
	GVORDER_MEDIA_BROWSER = 0,		// �g�[��
	GVORDER_MEDIA_VOLUP,			// ����׃��
	GVORDER_MEDIA_VOLDOWN,			// ����׃С
	GVORDER_MEDIA_CACULATOR,		// Ӌ����
	GVORDER_MEDIA_PLAY,				// ��������
	GVORDER_MEDIA_STOP,				// ����ֹͣ
	GVORDER_MEDIA_NEXT,				// ��һ��
	GVORDER_MEDIA_PREV,				// ��һ��
	GVORDER_MEDIA_EMAIL,			// �]��
	GVORDER_MEDIA_COMPUTER,			// �ҵ���X
	GVORDER_MEDIA_MEDIAPLAYER,		// MeidaPlay
	GVORDER_MEDIA_SLEEP,			// ˯��
	GVORDER_MEDIA_MUTE,				// �o��
	GVORDER_MEDIA_QTY,				// ��ý�w�I���x����

}GVORDER_MEDIA_KEY, *PGVORDER_MEDIA_KEY;

//////////////////////////////////////////////////////////////////////////
/// ����I���cMouse Key Code����
typedef enum _GVORDER_MOUSE_KEY
{
	GVORDER_MOUSE_LEFT = 1,		// ��
	GVORDER_MOUSE_RIGHT = 2,	// ��
	GVORDER_MOUSE_MIDDLE = 4,	// ��
	GVORDER_MOUSE_KEY4 = 8,		// 4�I����߅�I��
	GVORDER_MOUSE_KEY5 = 10,	// 5�I����߅�I��

}GVORDER_MOUSE_KEY, *PGVORDER_MOUSE_KEY;

//////////////////////////////////////////////////////////////////////////
/// ���I��Q�������x
typedef enum _GVORDER_FUNCTION_TYPE
{
	GVORDER_FUN_DEFAULT = 0,		// Ĭ�J
	GVORDER_FUN_NONE,				// �o����
	GVORDER_FUN_MOUSE,				// ���
	GVORDER_FUN_KEYBOARD,			// �I�P
	GVORDER_FUN_MOUSELOOP,			// ����B��
	GVORDER_FUN_KEYLOOP,			// �I�P�B��
	GVORDER_FUN_MACROSONCE,			// �޼�����һ��
	GVORDER_FUN_MACROSLOOP,			// �޼����·��_��ѭ�h���У��ٰ��·��_��ֹͣ
	GVORDER_FUN_MACROCSFIRE,		// �޼�������ѭ�h���У����_��ֹͣ
	GVORDER_FUN_FIREDPI,			// ָ��DPI(�������ГQDPI  ���_��؏�ԭDPI)
	GVORDER_FUN_SWITCHDPI,			// ָ��DPI(���·��_���ГQDPI  �ٰ��·��_�؏�ԭDPI)
	GVORDER_FUN_PLUSDPI,			// DPI+
	GVORDER_FUN_SUBDPI,				// DPI-
	GVORDER_FUN_LOOPDPI,			// DPIѭ�h�ГQ
	GVORDER_FUN_SWITCHPRO,			// Profileѭ�h�ГQ
	GVORDER_FUN_MEDIA,				// ��ý�w�I
	GVORDER_FUN_LOCKXY,				// �i��XY��1���i����0�����_
	GVORDER_FUN_GHOST,				// Ghost�I��Ӳ��HID��Ϣ��0xBF
	GVORDER_FUN_APP,
}GVORDER_FUNCTION_TYPE, *PGVORDER_FUNCTION_TYPE;

#define GVORDER_GHOST_MSG	0xBF

//////////////////////////////////////////////////////////////////////////
/// ���I����
typedef struct _GVORDER_KEYFUN
{
	int nIndex;		// ���IIndex
	int nProfile;	// ����Profile
	GVORDER_FUNCTION_TYPE fnType;	// ���I�������
	union{
		struct
		{
			BYTE msbutton;	// ���I ���� GVORDER_MOUSE_KEY
			BYTE wheelcount;// ���ʣ�L݆ 0x01 ���ϣ�0xff ����
			BYTE tiltcount; // ������ҝL݆ 0x01 ����0xff ����
		}mouse;		// ��� GVORDER_FUN_MOUSE

		struct
		{
			// Ctrl - VK_LCTRL/VK_RCTRL; Alt - VK_LMENU/VK_RMENU; Shift - VK_LSHIFT/VK_RSHIFT; Win - VK_LWIN/VK_RWIN
			BYTE keyModifier;
			BYTE keyCode; // VKeyCode

		}keyboard; // �I�P GVORDER_FUN_KEYBOARD

		struct
		{
			BYTE msbutton;  // ���I ���� GVORDER_MOUSE_KEY
			BYTE times;		// �Δ�
			BYTE delay;		// delay�r�g
		}mouseloop; // ����B�� GVORDER_FUN_MOUSELOOP

		struct
		{
			BYTE keyCode;   // key Code
			BYTE times;		// �Δ�
			BYTE delay;		// delay�r�g
		}keyloop; // �I�P�B�� GVORDER_FUN_KEYLOOP

		struct
		{
			WORD macrosIndex;  // Marco Index
			BYTE type;		   // �޼���� GVORDER_MACROS_RUN

		}macros; // Marco key GVORDER_FUN_MACROSONCE/GVORDER_FUN_MACROSLOOP/GVORDER_FUN_MACROCSFIRE

		struct  
		{
			BYTE x; 
			BYTE y;
			BYTE ms; // only GVORDER_FUN_FIREDPI
		}dpi;	// DPI GVORDER_FUN_FIREDPI/GVORDER_FUN_SWITCHDPI

		struct
		{
			GVORDER_MEDIA_KEY key; // ý�w�I
		}media; // ý�w�IFunction GVORDER_FUN_MEDIA

		struct
		{
			BYTE x; // 1 = lock, 0 = unlock
			BYTE y;
		}lock;	// �i��DPI GVORDER_FUN_LOCKXY

		struct
		{
			int nProfile;
		}profile;
	}value;

}GVORDER_KEYFUN, *PGVORDER_KEYFUN;

//////////////////////////////////////////////////////////////////////////
/// �޼�ָ������
typedef enum _GVORDER_MACROS_TYPE
{
	GVORDER_MACROS_KEYBOARDUP = 0,	// ���I����
	GVORDER_MACROS_KEYBOARDOWN,		// ���I����
	GVORDER_MACROS_MEDIAUP,			// ��ý�w�I����
	GVORDER_MACROS_MEDIADOWN,		// ��ý�w�I����
	GVORDER_MACROS_MOUSEUP,			// �������
	GVORDER_MACROS_MOUSEDOWN,		// �������
	GVORDER_MACROS_MOUSEX,			// �������X
	GVORDER_MACROS_MOUSEY,			// �������Y
	GVORDER_MACROS_SCROLLUP,		// ��˝L݆��
	GVORDER_MACROS_SCROLLDOWN,		// ��˝L݆��
	GVORDER_MACROS_DELAY,			// �r�gDelay

} GVORDER_MACROS_TYPE, *PGVORDER_MACROS_TYPE;

//////////////////////////////////////////////////////////////////////////
/// �޼��趨��Ԫ
#define GVORDER_MACROS_MAX	192 // ���ɰ�����Ԫ = 0x0240��Marco Size�� / 3 ��Unit Size��
typedef struct _GVORDER_MACROS_UNIT
{
	GVORDER_MACROS_TYPE nType;
	DWORD dwValue;

} GVORDER_MACROS_UNIT, *PGVORDER_MACROS_UNIT;

//////////////////////////////////////////////////////////////////////////
/// �޼�����ģʽ
typedef enum _GVORDER_MACROS_RUN
{
	GVORDER_MACROS_EXEC = 0,	// ����һ��
	GVORDER_MACROS_LOOP,		// ���·��_��ѭ�h���У��ٰ��·��_��ֹͣ
	GVORDER_MACROS_FIRE,		// ������ѭ�h���У����_��ֹͣ

}GVORDER_MACROS_RUN, *PGVORDER_MACROS_RUN;

//////////////////////////////////////////////////////////////////////////
/// �޼��r�g��uģʽ
typedef enum _GVORDER_MACROS_TIME
{
	GVORDER_MACROS_AUTO = 0,	// Ĭ�J���c���H�r�gһ��
	GVORDER_MACROS_FIXEDTIME,	// �̶��r�g
	GVORDER_MACROS_NONE,		// ��ӛ䛕r�g

}GVORDER_MACROS_TIME, *PGVORDER_MACROS_TIME;

//////////////////////////////////////////////////////////////////////////
/// �޼�����
typedef struct _GVORDER_MACROS_ATTR
{
	int nIcon;						// ��ʹ�õ�Icon Index
	GVORDER_MACROS_RUN  RunType;	// �\��ģʽ
	GVORDER_MACROS_TIME TimeMode;	// �r�gģʽ
	TCHAR szName[15];				// ����

} GVORDER_MACROS_ATTR, *PGVORDER_MACROS_ATTR;

//////////////////////////////////////////////////////////////////////////
/// �޼����w
typedef struct _GVORDER_MACROS
{
	int nIndex;										// �޼�����
	int nCount;										// �޼���Ԫ����
	GVORDER_MACROS_ATTR attr;						// �޼�����
	GVORDER_MACROS_UNIT macros[GVORDER_MACROS_MAX]; // �޼���Ԫ���M
	void Insert(GVORDER_MACROS_UNIT nMacro, int iIdx)
	{
		for (int i = nCount; i > iIdx; i--)
			macros[i] = macros[i - 1];
		macros[iIdx] = nMacro;
		nCount++;
	}
	void Append(GVORDER_MACROS_UNIT nMacro, int iIdx)
	{
		nCount++;
		for (int i = nCount; i >  iIdx; i--)
			macros[i + 1] = macros[i];
		macros[iIdx + 1] = nMacro;
	}
} GVORDER_MACROS, *PGVORDER_MACROS;
///
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
/// LoadMemory����
typedef enum _GVORDER_DEVICE_TYPE
{
	GVORDER_DEVICE_KEYBOARD = 0,	// �I�P
	GVORDER_DEVICE_MOUSE,			// ���
	GVORDER_DEVICE_HEADSET,			// ���C
	GVORDER_DEVICE_POWER,			// �Դ
	GVORDER_DEVICE_CHASSIS,			// �C��

}GVORDER_DEVICE_TYPE, *PGVORDER_DEVICE_TYPE;

typedef struct _GVORDER_MEMORY_PARAM
{
	GVORDER_DEVICE_TYPE type;
	int nProfileCount;
	int nMarcoCount;

} GVORDER_MEMORY_PARAM, *PGVORDER_MEMORY_PARAM;
///
//////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
extern "C" {
#endif

	/****************************************************************************************
	 * ����������
	 * ��ʼ���O��
	 *
	 * ���������
	 * [in]  device      ��Ҫ�B���b�õČ���
	 * [out] nIndex      �����O��Index����ͬID�߂���ͬIndex
	 * 
	 * ����ֵ��
	 * ����GVAPI_OK��ʾ���óɹ���GVAPI_FWERR_ERR_NOBOARD��ʾ�]���ҵ��b�ã�
	 ****************************************************************************************/
	GV_ORDERLIB_API DWORD GvOrderInit(GVORDER_DEVICE device, int& nIndex);

	/****************************************************************************************
	 * ����������
	 * ���d�O��Flash���֔���������^�����h���ھQ���У����d�ꮅ���_ʼܛ�w������Ĳ���
	 *
	 * ���������
	 * [in]  param       ���d����
	 * [in]  nIndex      �O��Index
	 * [in]  nBrd        �b������
	 * 
	 * ����ֵ��
	 * ����GVAPI_OK��ʾ���óɹ���GVAPI_CMDERR_DEVNOFOUND��ʾ��δInit��
	 ****************************************************************************************/
	GV_ORDERLIB_API DWORD GvOrderLoadMemory(GVORDER_MEMORY_PARAM param, int& nIndex, int nBrd = 0);

	/****************************************************************************************
	 * ����������
	 * ጷ��O���YԴ
	 *
	 * ���������
	 * [in]  nIndex      �O��Index
	 * 
	 * ����ֵ��
	 * ����GVAPI_OK��ʾ���óɹ���GVAPI_CMDERR_DEVNOFOUND��ʾ��δInit��
	 ****************************************************************************************/
	GV_ORDERLIB_API DWORD GvOrderFree(int nIndex);

	/****************************************************************************************
	 * ����������
	 * �@ȡԓ�O��ID���Ўׂ��b��
	 *
	 * ���������
	 * [in]  nIndex      �O��Index
	 * [out] nCount      �b�Ô���
	 * 
	 * ����ֵ��
	 * ����GVAPI_OK��ʾ���óɹ���GVAPI_CMDERR_DEVNOFOUND��ʾ��δInit��
	 ****************************************************************************************/
	GV_ORDERLIB_API DWORD GvOrderDeviceCount(int nIndex, int& nCount);

	/****************************************************************************************
	 * ����������
	 * �@ȡ�b��FW�汾
	 *
	 * ���������
	 * [out] szVersion   FW�汾�ַ���   
	 * [in]  nIndex      �O��Index
	 * [in]  nBrd        �b������
	 * 
	 * ����ֵ��
	 * ����GVAPI_OK��ʾ���óɹ���GVAPI_CMDERR_DEVNOFOUND��ʾ��δInit��
	 ****************************************************************************************/
	GV_ORDERLIB_API DWORD GvOrderVersionW(wchar_t* szVersion, int nIndex, int nBrd = 0);
	GV_ORDERLIB_API DWORD GvOrderVersionA(char* szVersion, int nIndex, int nBrd = 0);

#ifdef _UNICODE
#define GvOrderVersion GvOrderVersionW
#else
#define GvOrderVersion GvOrderVersionA
#endif

	/****************************************************************************************
	 * ����������
	 * �ГQProfile
	 *
	 * ���������
	 * [in]  nProfile    Profile Index   
	 * [in]  nIndex      �O��Index
	 * [in]  nBrd        �b������
	 * 
	 * ����ֵ��
	 * ����GVAPI_OK��ʾ���óɹ���GVAPI_CMDERR_DEVNOFOUND��ʾ��δInit��
	 ****************************************************************************************/
	GV_ORDERLIB_API DWORD GvOrderSelProfile(int nProfile, int nIndex, int nBrd = 0);

	/****************************************************************************************
	 * ����������
	 * �@ȡ��ǰProfile�YӍ
	 *
	 * ���������
	 * [out] profile     Profile�YӍ   
	 * [in]  nIndex      �O��Index
	 * [in]  nBrd        �b������
	 * 
	 * ����ֵ��
	 * ����GVAPI_OK��ʾ���óɹ���GVAPI_CMDERR_DEVNOFOUND��ʾ��δInit��
	 ****************************************************************************************/
	GV_ORDERLIB_API DWORD GvOrderGetCurProfile(GVORDER_PROFILE& profile, int nIndex, int nBrd = 0);

	/****************************************************************************************
	 * ����������
	 * �ГQDPI
	 *
	 * ���������
	 * [in]  nDpiIndex   DPI Index   
	 * [in]  nIndex      �O��Index
	 * [in]  nBrd        �b������
	 * 
	 * ����ֵ��
	 * ����GVAPI_OK��ʾ���óɹ���GVAPI_CMDERR_DEVNOFOUND��ʾ��δInit��
	 ****************************************************************************************/
	GV_ORDERLIB_API DWORD GvOrderSelDPI(int nDpiIndex, int nIndex, int nBrd = 0);

	/****************************************************************************************
	 * ����������
	 * �@ȡ��ǰDPI
	 *
	 * ���������
	 * [out] dpi		 DPI��Ϣ
	 * [in]  nIndex      �O��Index
	 * [in]  nBrd        �b������
	 * 
	 * ����ֵ��
	 * ����GVAPI_OK��ʾ���óɹ���GVAPI_CMDERR_DEVNOFOUND��ʾ��δInit��
	 ****************************************************************************************/
	GV_ORDERLIB_API DWORD GvOrderGetCurDPI(GVORDER_DPI& dpi, int nIndex, int nBrd = 0);

	/****************************************************************************************
	 * ����������
	 * �����O�����ї���
	 *
	 * ���������
	 * [in]  nProfile    ����Profile
	 * [in]  nIndex      �O��Index
	 * [in]  nBrd        �b������
	 * 
	 * ����ֵ��
	 * ����GVAPI_OK��ʾ���óɹ���GVAPI_CMDERR_DEVNOFOUND��ʾ��δInit��
	 ****************************************************************************************/
	GV_ORDERLIB_API DWORD GvOrderApply(int nProfile, int nIndex, int nBrd = 0);

	/****************************************************************************************
	 * ����������
	 * �O��ReportRate
	 *
	 * ���������
	 * [in]  nReportRate ReportRate
	 * [in]  nIndex      �O��Index
	 * [in]  nBrd        �b������
	 * 
	 * ����ֵ��
	 * ����GVAPI_OK��ʾ���óɹ���GVAPI_CMDERR_DEVNOFOUND��ʾ��δInit��
	 ****************************************************************************************/
	GV_ORDERLIB_API DWORD GvOrderSetReportRate(int nReportRate, int nIndex, int nBrd = 0);

	/****************************************************************************************
	 * ����������
	 * �@ȡ��ǰReportRate
	 *
	 * ���������
	 * [out] nReportRate ReportRate
	 * [in]  nIndex      �O��Index
	 * [in]  nBrd        �b������
	 * 
	 * ����ֵ��
	 * ����GVAPI_OK��ʾ���óɹ���GVAPI_CMDERR_DEVNOFOUND��ʾ��δInit��
	 ****************************************************************************************/
	GV_ORDERLIB_API DWORD GvOrderGetReportRate(int& nReportRate, int nIndex, int nBrd = 0);

	/****************************************************************************************
	 * ����������
	 * �O��Profile
	 *
	 * ���������
	 * [in]  profile     Profile��Ϣ
	 * [in]  nIndex      �O��Index
	 * [in]  nBrd        �b������
	 * 
	 * ����ֵ��
	 * ����GVAPI_OK��ʾ���óɹ���GVAPI_CMDERR_DEVNOFOUND��ʾ��δInit��
	 ****************************************************************************************/
	GV_ORDERLIB_API DWORD GvOrderSetProfile(GVORDER_PROFILE profile, int nIndex, int nBrd = 0);

	/****************************************************************************************
	 * ����������
	 * �@ȡProfile
	 *
	 * ���������
	 * [in]  profile     Profile��Ϣ�����A���xֵIndex
	 * [in]  nIndex      �O��Index
	 * [in]  nBrd        �b������
	 * 
	 * ����ֵ��
	 * ����GVAPI_OK��ʾ���óɹ���GVAPI_CMDERR_DEVNOFOUND��ʾ��δInit��
	 ****************************************************************************************/
	GV_ORDERLIB_API DWORD GvOrderGetProfile(GVORDER_PROFILE& profile, int nIndex, int nBrd = 0);

	/****************************************************************************************
	 * ����������
	 * �O��ָ��Index DPI
	 *
	 * ���������
	 * [in]  dpi		 DPI
	 * [in]  nIndex      �O��Index
	 * [in]  nBrd        �b������
	 * 
	 * ����ֵ��
	 * ����GVAPI_OK��ʾ���óɹ���GVAPI_CMDERR_DEVNOFOUND��ʾ��δInit��
	 ****************************************************************************************/
	GV_ORDERLIB_API DWORD GvOrderSetDPI(GVORDER_DPI dpi, int nIndex, int nBrd = 0);

	/****************************************************************************************
	 * ����������
	 * �xȡָ��Index DPI
	 *
	 * ���������
	 * [out] dpi		 DPI�����A���xֵIndex
	 * [in]  nIndex      �O��Index
	 * [in]  nBrd        �b������
	 * 
	 * ����ֵ��
	 * ����GVAPI_OK��ʾ���óɹ���GVAPI_CMDERR_DEVNOFOUND��ʾ��δInit��
	 ****************************************************************************************/
	GV_ORDERLIB_API DWORD GvOrderGetDPI(GVORDER_DPI& dpi, int nIndex, int nBrd = 0);

	/****************************************************************************************
	 * ����������
	 * �O��Ledģʽ��For K7
	 *
	 * ���������
	 * [in]  led		 LEDģʽ
	 * [in]  nIndex      �O��Index
	 * [in]  nBrd        �b������
	 * 
	 * ����ֵ��
	 * ����GVAPI_OK��ʾ���óɹ���GVAPI_CMDERR_DEVNOFOUND��ʾ��δInit��
	 ****************************************************************************************/
	GV_ORDERLIB_API DWORD GvOrderSetLed(GVORDER_LED led, int nIndex, int nBrd = 0);

	/****************************************************************************************
	 * ����������
	 * �xȡLedģʽ��For K7
	 *
	 * ���������
	 * [out] led		 LEDģʽ
	 * [in]  nIndex      �O��Index
	 * [in]  nBrd        �b������
	 * 
	 * ����ֵ��
	 * ����GVAPI_OK��ʾ���óɹ���GVAPI_CMDERR_DEVNOFOUND��ʾ��δInit��
	 ****************************************************************************************/
	GV_ORDERLIB_API DWORD GvOrderGetLed(GVORDER_LED& led, int nIndex, int nBrd = 0);

	/****************************************************************************************
	 * ����������
	 * �O�ð��IFuntion
	 *
	 * ���������
	 * [in]  fnkey		 ���IFunction
	 * [in]  nIndex      �O��Index
	 * [in]  nBrd        �b������
	 * 
	 * ����ֵ��
	 * ����GVAPI_OK��ʾ���óɹ���GVAPI_CMDERR_DEVNOFOUND��ʾ��δInit��
	 ****************************************************************************************/
	GV_ORDERLIB_API DWORD GvOrderSetKeyMapping(GVORDER_KEYFUN fnkey, int nIndex, int nBrd = 0);

	/****************************************************************************************
	 * ����������
	 * �O�ð��IFuntion
	 *
	 * ���������
	 * [in]  fnkey		 ���IFunction
	 * [in]  nIndex      �O��Index
	 * [in]  nBrd        �b������
	 * 
	 * ����ֵ��
	 * ����GVAPI_OK��ʾ���óɹ���GVAPI_CMDERR_DEVNOFOUND��ʾ��δInit��
	 ****************************************************************************************/
	GV_ORDERLIB_API DWORD GvOrderSetKeyMappingDefault(int nProfile, GVORDER_DEVICE_TYPE type, int nIndex, int nBrd = 0);

	/****************************************************************************************
	 * ����������
	 * �xȡ���IFuntion
	 *
	 * ���������
	 * [out] fnkey		 ���IFunction
	 * [in]  nIndex      �O��Index
	 * [in]  nBrd        �b������
	 * 
	 * ����ֵ��
	 * ����GVAPI_OK��ʾ���óɹ���GVAPI_CMDERR_DEVNOFOUND��ʾ��δInit��
	 ****************************************************************************************/
	GV_ORDERLIB_API DWORD GvOrderGetKeyMapping(GVORDER_KEYFUN& fnkey, int nIndex, int nBrd = 0);

	/****************************************************************************************
	 * ����������
	 * �O��ָ����ַfunction��For K7
	 *
	 * ���������
	 * [out] fnkey		 ���IFunction
	 * [in]  dwAddr      ��ַ
	 * [in]  nIndex      �O��Index
	 * [in]  nBrd        �b������
	 * 
	 * ����ֵ��
	 * ����GVAPI_OK��ʾ���óɹ���GVAPI_CMDERR_DEVNOFOUND��ʾ��δInit��
	 ****************************************************************************************/
	GV_ORDERLIB_API DWORD GvOrderSetKeyToAddr(GVORDER_KEYFUN fnkey, DWORD dwAddr, int nIndex, int nBrd = 0);

	/****************************************************************************************
	 * ����������
	 * �O��Marco Key
	 *
	 * ���������
	 * [in]  macros		 �޼��I
	 * [in]  nIndex      �O��Index
	 * [in]  nBrd        �b������
	 * 
	 * ����ֵ��
	 * ����GVAPI_OK��ʾ���óɹ���GVAPI_CMDERR_DEVNOFOUND��ʾ��δInit��
	 ****************************************************************************************/
	GV_ORDERLIB_API DWORD GvOrderSetMacrosKey(GVORDER_MACROS macros, int nIndex, int nBrd = 0);

	/****************************************************************************************
	 * ����������
	 * �@ȡMarco Key
	 *
	 * ���������
	 * [out] macros		 �@ȡ�޼��I�����A���xֵIndex
	 * [in]  nIndex      �O��Index
	 * [in]  nBrd        �b������
	 * 
	 * ����ֵ��
	 * ����GVAPI_OK��ʾ���óɹ���GVAPI_CMDERR_DEVNOFOUND��ʾ��δInit��
	 ****************************************************************************************/
	GV_ORDERLIB_API DWORD GvOrderGetMacrosKey(GVORDER_MACROS& macros, int nIndex, int nBrd = 0);
	GV_ORDERLIB_API DWORD GvOrderGetMacrosList(GVORDER_MACROS_ATTR lstmacros[], int nCount, int nIndex, int nBrd = 0);

	//////////////////////////////////////////////////////////////////////////
	/// δ���F
	GV_ORDERLIB_API DWORD GvOrderTranslateKey(RAWKEYBOARD keyEvent, GVORDER_MACROS_UNIT& keyValue);
	GV_ORDERLIB_API DWORD GvOrderGetMacrosKeyLength(GVORDER_MACROS& macros, int& nLength);
	///
	//////////////////////////////////////////////////////////////////////////

	/****************************************************************************************
	 * ����������
	 * ����Byte��ָ����ַ������L�Ƞ�64
	 *
	 * ���������
	 * [in]  pBytes		 Ҫ�����Byte
	 * [in]  nLen		 Ҫ������L��
	 * [in]  dwAddr		 Ҫ����ĵ�ַ
	 * [in]  nIndex      �O��Index
	 * [in]  nBrd        �b������
	 * 
	 * ����ֵ��
	 * ����GVAPI_OK��ʾ���óɹ���GVAPI_CMDERR_DEVNOFOUND��ʾ��δInit��
	 ****************************************************************************************/
	GV_ORDERLIB_API DWORD GvOrderWriteByte(BYTE* pBytes, int nLen, DWORD dwAddr, int nIndex, int nBrd = 0);

	/****************************************************************************************
	 * ����������
	 * ��ָ����ַ�xȡByte������L�Ƞ�64
	 *
	 * ���������
	 * [out] pBytes		 ����xȡ��Byte�ľ���^
	 * [in]  nLen		 Ҫ�xȡ���L��
	 * [in]  dwAddr		 Ҫ�xȡ�ĵ�ַ
	 * [in]  nIndex      �O��Index
	 * [in]  nBrd        �b������
	 * 
	 * ����ֵ��
	 * ����GVAPI_OK��ʾ���óɹ���GVAPI_CMDERR_DEVNOFOUND��ʾ��δInit��
	 ****************************************************************************************/
	GV_ORDERLIB_API DWORD GvOrderReadByte(BYTE* pBytes, int& nLen, DWORD dwAddr, int nIndex, int nBrd = 0);

	/****************************************************************************************
	 * ����������
	 * �O�����ҝL��ģʽ
	 *
	 * ���������
	 * [in]  tilt		 ���ҝL��ģʽ
	 * [in]  nIndex      �O��Index
	 * [in]  nBrd        �b������
	 * 
	 * ����ֵ��
	 * ����GVAPI_OK��ʾ���óɹ���GVAPI_CMDERR_DEVNOFOUND��ʾ��δInit��
	 ****************************************************************************************/
	GV_ORDERLIB_API DWORD GvOrderSetScrollType(GVORDER_TILT_TYPE tilt, int nIndex, int nBrd = 0);

	/****************************************************************************************
	 * ����������
	 * �O��Profile�ɫ
	 *
	 * ���������
	 * [in]  clr		 Ҫ�O�����ɫ
	 * [in]  nProfile	 Ҫ�O����Profile
	 * [in]  nIndex      �O��Index
	 * [in]  nBrd        �b������
	 * 
	 * ����ֵ��
	 * ����GVAPI_OK��ʾ���óɹ���GVAPI_CMDERR_DEVNOFOUND��ʾ��δInit��
	 ****************************************************************************************/
	GV_ORDERLIB_API DWORD GvOrderSetProfileClr(COLORREF clr, int nProfile, int nIndex, int nBrd = 0);

	/****************************************************************************************
	 * ����������
	 * ͬ���O���ɫ
	 *
	 * ���������
	 * [in]  clr		 Ҫͬ�����ɫ
	 * [in]  nIndex      �O��Index
	 * [in]  nBrd        �b������
	 * 
	 * ����ֵ��
	 * ����GVAPI_OK��ʾ���óɹ���GVAPI_CMDERR_DEVNOFOUND��ʾ��δInit��
	 ****************************************************************************************/
	GV_ORDERLIB_API DWORD GvOrderSyncClr(COLORREF clr, int nIndex, int nBrd = 0);

	/****************************************************************************************
	 * ����������
	 * �xȡProfile�ɫ
	 *
	 * ���������
	 * [out] clr		 �xȡ�����ɫ
	 * [in]  nProfile	 Ҫ�O����Profile
	 * [in]  nIndex      �O��Index
	 * [in]  nBrd        �b������
	 * 
	 * ����ֵ��
	 * ����GVAPI_OK��ʾ���óɹ���GVAPI_CMDERR_DEVNOFOUND��ʾ��δInit��
	 ****************************************************************************************/
	GV_ORDERLIB_API DWORD GvOrderGetProfileClr(COLORREF& clr, int nProfile, int nIndex, int nBrd = 0);

	/****************************************************************************************
	 * ����������
	 * ���ļ��Ќ���Marco Key
	 *
	 * ���������
	 * [in]  macros		marco key
	 * [in]  szPath		����·��
	 * 
	 * ����ֵ��
	 * ����GVAPI_OK��ʾ���óɹ���GVAPI_CMDERR_DEVNOFOUND��ʾ��δInit��
	 ****************************************************************************************/
	GV_ORDERLIB_API DWORD GvOrderImportMarcoW(GVORDER_MACROS& macros, const wchar_t* szPath);
	GV_ORDERLIB_API DWORD GvOrderImportMarcoA(GVORDER_MACROS& macros, const char* szPath);

#ifdef _UNICODE
#define GvOrderImportMarco GvOrderImportMarcoW
#else
#define GvOrderImportMarco GvOrderImportMarcoA
#endif

	/****************************************************************************************
	 * ����������
	 * ����Marco���ļ���
	 *
	 * ���������
	 * [in]  macros		marco key
	 * [in]  szPath		����·��
	 * 
	 * ����ֵ��
	 * ����GVAPI_OK��ʾ���óɹ���GVAPI_CMDERR_DEVNOFOUND��ʾ��δInit��
	 ****************************************************************************************/
	GV_ORDERLIB_API DWORD GvOrderExportMarcoW(GVORDER_MACROS macros, const wchar_t* szPath);
	GV_ORDERLIB_API DWORD GvOrderExportMarcoA(GVORDER_MACROS macros, const char* szPath);

#ifdef _UNICODE
#define GvOrderExportMarco GvOrderExportMarcoW
#else
#define GvOrderExportMarco GvOrderExportMarcoA
#endif

	/****************************************************************************************
	 * ����������
	 * �i��FW�l��ָ��ܣ���ֹ�cFW��ͨ�^������Ñ��|�l���±���
	 *
	 * ���������
	 * [in]  nIndex      �O��Index
	 * [in]  nBrd        �b������
	 * 
	 * ����ֵ��
	 * ����GVAPI_OK��ʾ���óɹ���GVAPI_CMDERR_DEVNOFOUND��ʾ��δInit��
	 ****************************************************************************************/
	GV_ORDERLIB_API DWORD GvOrderDeviceLock(int nIndex, int nBrd = 0);

	/****************************************************************************************
	 * ����������
	 * ���iFW�l��ָ���
	 *
	 * ���������
	 * [in]  nIndex      �O��Index
	 * [in]  nBrd        �b������
	 * 
	 * ����ֵ��
	 * ����GVAPI_OK��ʾ���óɹ���GVAPI_CMDERR_DEVNOFOUND��ʾ��δInit��
	 ****************************************************************************************/
	GV_ORDERLIB_API DWORD GvOrderDeviceUnLock(int& nProfile, int& nDpiIndex, int nIndex, int nBrd = 0);

	/****************************************************************************************
	 * ����������
	 * ��ʹ׃��Led�@ʾ��For XM300
	 *
	 * ���������
	 * [in]  profile     Profile�O��
	 * [in]  nIndex      �O��Index
	 * [in]  nBrd        �b������
	 * 
	 * ����ֵ��
	 * ����GVAPI_OK��ʾ���óɹ���GVAPI_CMDERR_DEVNOFOUND��ʾ��δInit��
	 ****************************************************************************************/
	GV_ORDERLIB_API DWORD GvOrderChangeLed(GVORDER_PROFILE profile, int nIndex, int nBrd = 0);

	/****************************************************************************************
	 * ����������
	 * ���r׃��Led�@ʾģʽ��For K85/XH300/XC700/CPU Cooler
	 *
	 * ���������
	 * [in]  config      Led�O��
	 * [in]  nIndex      �O��Index
	 * [in]  nBrd        �b������
	 * 
	 * ����ֵ��
	 * ����GVAPI_OK��ʾ���óɹ���GVAPI_CMDERR_DEVNOFOUND��ʾ��δInit��
	 ****************************************************************************************/
	GV_ORDERLIB_API DWORD GvOrderSetLight(GVORDER_LED_CFG  config, int nIndex, int nBrd = 0);

	/****************************************************************************************
	 * ����������
	 * �@ȡLed�@ʾģʽ��For K85/XH300/XC700/CPU Cooler
	 *
	 * ���������
	 * [out] config      Led�O��
	 * [in]  nIndex      �O��Index
	 * [in]  nBrd        �b������
	 * 
	 * ����ֵ��
	 * ����GVAPI_OK��ʾ���óɹ���GVAPI_CMDERR_DEVNOFOUND��ʾ��δInit��
	 ****************************************************************************************/
	GV_ORDERLIB_API DWORD GvOrderGetLight(GVORDER_LED_CFG& config, int nIndex, int nBrd = 0);

	/****************************************************************************************
	 * ����������
	 * ����Led�O����For K85/XH300/XC700/CPU Cooler
	 *
	 * ���������
	 * [in]  nIndex      �O��Index
	 * [in]  nBrd        �b������
	 * 
	 * ����ֵ��
	 * ����GVAPI_OK��ʾ���óɹ���GVAPI_CMDERR_DEVNOFOUND��ʾ��δInit��
	 ****************************************************************************************/
	GV_ORDERLIB_API DWORD GvOrderSaveLight(int nIndex, int nBrd = 0);

	/****************************************************************************************
	 * ����������
	 * �����M�ƴa�D��Marco Key List��Fro XK700
	 *
	 * ���������
	 * [in]  pAttr			����Byte
	 * [out] lstmacros      Marco List
	 * [in]  nCount			�����
	 * 
	 * ����ֵ��
	 * ����GVAPI_OK��ʾ���óɹ���GVAPI_CMDERR_DEVNOFOUND��ʾ��δInit��
	 ****************************************************************************************/
	GV_ORDERLIB_API DWORD GvOrderGetMacrosListFromByte(BYTE* pAttr, GVORDER_MACROS_ATTR lstmacros[], int nCount);

	/****************************************************************************************
	 * ����������
	 * �����M�ƴa�D��Marco Key��Fro XK700
	 *
	 * ���������
	 * [in]  pUnit			Marco����Byte
	 * [in]  pAttr			Marco����Byte
	 * [out] macros			Macro Key
	 * 
	 * ����ֵ��
	 * ����GVAPI_OK��ʾ���óɹ���GVAPI_CMDERR_DEVNOFOUND��ʾ��δInit��
	 ****************************************************************************************/
	GV_ORDERLIB_API DWORD GvOrderGetMacrosFromByte(BYTE* pUnit, BYTE* pAttr, GVORDER_MACROS& macros);

	/****************************************************************************************
	 * ����������
	 * ��Marco Key�D�����M�ƴa��Fro XK700
	 *
	 * ���������
	 * [in]  pUnit			Marco����Byte
	 * [in]  pAttr			Marco����Byte
	 * [in]  macros			Macro Key
	 * 
	 * ����ֵ��
	 * ����GVAPI_OK��ʾ���óɹ���GVAPI_CMDERR_DEVNOFOUND��ʾ��δInit��
	 ****************************************************************************************/
	GV_ORDERLIB_API DWORD GvOrderSetMacrosToByte(BYTE* pUnit, BYTE* pAttr, GVORDER_MACROS macros);

	/****************************************************************************************
	 * ����������
	 * �����M�ƴa�D��Key Fun�� Fro XK700
	 *
	 * ���������
	 * [in]  pUnit			Key Function Byte
	 * [out] keyfun			Key Function
	 * 
	 * ����ֵ��
	 * ����GVAPI_OK��ʾ���óɹ���GVAPI_CMDERR_DEVNOFOUND��ʾ��δInit��
	 ****************************************************************************************/
	GV_ORDERLIB_API DWORD GvOrderGetKeyFunFromByte(BYTE* pUnit, GVORDER_KEYFUN& keyfun);

	/****************************************************************************************
	 * ����������
	 * ��Key Fun�D�����M�ƴa�� Fro XK700
	 *
	 * ���������
	 * [in]  pUnit			Key Function Byte
	 * [in]  keyfun			Key Function
	 * 
	 * ����ֵ��
	 * ����GVAPI_OK��ʾ���óɹ���GVAPI_CMDERR_DEVNOFOUND��ʾ��δInit��
	 ****************************************************************************************/
	GV_ORDERLIB_API DWORD GvOrderSetKeyFunToByte(BYTE* pUnit, GVORDER_KEYFUN keyfun);


#ifdef __cplusplus
}
#endif

#endif
