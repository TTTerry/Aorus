#ifndef _GV_COM_DLL_HEADER_
#define _GV_COM_DLL_HEADER_

/////////////////// !!!!!NOTE ///////////////////
//
// Project which calls this DLL, must use [Use MFC in a Shared DLL] setting, not [Use MFC in a Static Library].
// See: project -> Properities -> Configuration Properities -> General -> Use of MFC -> Use MFC in a Shared DLL
// 
/////////////////// !!!!!NOTE ///////////////////

#include "Convert.h"		//  1) �����c�ַ���, ���ڵ�֮�g���D�Q
#include "IniFile.h"		//  2) �x��*.Ini
#include "Excel.h"			//  3) �x��Excel�ęn
#include "Encode.h"			//  4) ����atxt�n��
#include "Sql.h"			//  5) �������x���L��
#include "SqlCmd.h"			//  6) �x��Excel�ęn
#include "DataTable.h"		//  7) �C#��DataTable�
#include "HwTool.h"			//  8) HwTool���P�Y�ώ��x��
#include "DataLink.h"		//  9) HwTool�Y�ώ�朽��x��
#include "Distance.h"		// 10) �c, ��, ����, �A��֮�g���xӋ��
#include "User.h"			// 11) KM_SYS_User�Y�ώ��L��
#include "Menus.h"			// 12) KM_SYS_Menus�Y�ώ��L��
#include "Ftp.h"			// 13) FTP���d�c�ς�
#include "Http.h"			// 14) HTTP���d�c�ς�
#include "Registry.h"		// 15) �x���]�Ա�
#include "Verify.h"			// 16) AP��ʽ���޹ܿ�
#include "OS.h"				// 17) ����ϵ�y���P��Ϣ, ���ʽ�汾, OS�汾, 32/64bits�Єe, �@ȡ�R�r·����
#include "Driver.h"			// 18) ͨ�^���bDriver, ���F�xȡOS�׌Ӄȴ��ַ����
#include "Device.h"			// 19) ���N�O����Ϣ�xȡ, ���@��, BIOS��.
#include "Shell.h"			// 20) ��ShellExecuteEx()�Mһ�����b�c�Uչ����(���/�I�P�c��)
#include "LiveUpdate.h"		// 21) ���F�@���پW��Ϣ�@ȡ, �ھ�Update��. ��پWBIOS, ModelҎ��
#endif

