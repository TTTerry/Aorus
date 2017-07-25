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

//WM_GVKM_HKYSTROKE��Ϣ��wParam��������
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
	 * ����������
	 * ��ʼ��GvKm.dll
	 *
	 * ���������
	 * hWnd   ����GvKm.dll�ĳ�ʽ�����ھ��
	 * dwHook Hook����, ָ������GvKm.dll�й��ڼ��̻�����API. ��ֵ��ΪGVKM_MOUSE/GVKM_KEYBOARD, ������(|����)
	 *
	 * ����ֵ��
	 * ����TRUE��ʾ���óɹ�
	 ****************************************************************************************/
	GVKMEXPORT bool GvKmInstallHook(HWND hWnd, DWORD dwHook=GVKM_KEYBOARD);

	/****************************************************************************************
	 * ����������
	 * �ͷ�GvKm.dll
	 ****************************************************************************************/
	GVKMEXPORT void GvKmUninstallHook();

	/****************************************************************************************
	 * ����������
	 * ���ù�ע���ȼ�, ���ú�, ���ȼ���������, ��ᷢ��WM_GVKM_HKYSTROKE֪ͨ����GvKm.dll�Ĵ���,
	 * ���ߵ���GvKmIsHotKeyPressed()������ѯ�ȼ�״̬.���߷�ʽ����.������WM_GVKM_HKYSTROKE֪ͨʱ,
	 * ��ON_REGISTERED_MESSAGE(WM_GVKM_HKYSTROKE, OnHotKeyPressed)����Ϣ������Ӧ.
	 * ��Ӧ����ԭ��Ϊ:
	 * afx_msg LRESULT OnHotKeyPressed(WPARAM wParam, LPARAM lParam);
	 * ����, wParam�����ȼ��Լ�������Ϣ,���������˵��.lParamΪHWND���,��ʾ�ȼ��������ĸ�����. 
	 *
	 * ���������
	 * vk       �ȼ���������, ��VK_F1
	 * bAlt     ��ǰ�ȼ����Ƿ����Alt��
	 * bShift   ��ǰ�ȼ����Ƿ����Shift��
	 * bCtrl    ��ǰ�ȼ����Ƿ����Ctrl��
	 * bMaskHKY �Ƿ����θ��ȼ�, ��:���Ը��ȼ���������ʱ,ֻ�е���GvKm.dll�Ĵ����ܹ���֪�ȼ���
	 *          ����,ƽ̨���������̴��ڶ��޷���֪�ȼ�������(��������). 
	 * 
	 * ����ֵ��
	 * ���óɹ�ʱ, ���ظ��ȼ���indexֵ. ʧ��ʱ����-1.
	 *
	 * ע�⣺
	 * ��֮ǰ�ѵ�����GvKmSetHotKey()����ĳHotKey, ������������, ��ס����GvKmResetHotKey()�ͷ���Դ.
	 ****************************************************************************************/
	GVKMEXPORT int GvKmSetHotKey(BYTE vk, bool bCtrl=false, bool bAlt=false, bool bShift=false, bool bMaskHKY=false); 

	/****************************************************************************************
	 * ����������
	 * �������GvKmSetHotKey���õ��ȼ�.
	 *
	 * ���������
	 * nIndex   ��־ĳ���ȼ���Indexֵ, ��ֵΪ�ɵ���GvKmSetHotKey()���ص�ֵ
	 * 
	 * ����ֵ��
	 * ����TRUE��ʾ���óɹ�
	 ****************************************************************************************/
	GVKMEXPORT bool GvKmResetHotKey(int nIndex);

	/****************************************************************************************
	 * ����������
	 * ѯ�����õ��ȼ��Ƿ񱻰���. 
	 *
	 * ���������
	 * nIndex ��־ĳ���ȼ���Indexֵ, ��ֵΪ�ɵ���GvKmSetHotKey()���ص�ֵ
	 * 
	 * ����ֵ��
	 * ����TRUE��ʾ���ȼ�������. ����FALSE��ʾδ������, �����ڵ���GvKmIsHotKeyPressed()֮ǰ,����
	 * ��������KEY������(��֮ǰ�ȼ������µ�״̬�ѱ����ǵ�)
	 ****************************************************************************************/
	GVKMEXPORT bool GvKmIsHotKeyPressed(int nIndex);

	/****************************************************************************************
	 * ����������
	 * ģ�ⷢ�ͼ����ȼ�������
	 *
	 * ���������
	 * vk       �ȼ���������, ��VK_F1
	 * bAlt     ��ǰ�ȼ����Ƿ����Alt��
	 * bShift   ��ǰ�ȼ����Ƿ����Shift��
	 * bCtrl    ��ǰ�ȼ����Ƿ����Ctrl��
	 * 
	 * ����ֵ��
	 * ����TRUE��ʾ���óɹ�
	 ****************************************************************************************/
	GVKMEXPORT bool GvKmSimulateHotKey(BYTE vk, bool bAlt, bool bShift, bool bCtrl);

	/****************************************************************************************
	 * ����������
	 * �ƶ���굽ָ��λ��
	 *
	 * ���������
	 * nXCoord   Ŀ��X����, ������Ϊ��������(�������Ļ����)
	 * nYCoord   Ŀ��Y����, ������Ϊ��������(�������Ļ����), ע��, nXCoord, nYCoord���Ե���
	 *           GvKmInstallHook()ʱƽ̨����Ļ�ֱ���Ϊ��׼
	 ****************************************************************************************/
	GVKMEXPORT void GvKmMouseMove(int nXCoord, int nYCoord);

	/****************************************************************************************
	 * ����������
	 * ģ���������(Ĭ��Ϊ���)���, ����ǰ�����������Ϊ�Ҽ�, ��ú���ģ������Ҽ����
	 *
	 * ���������
	 * nXCoord    Ŀ��X����, ������Ϊ��������(�������Ļ����)
	 * nYCoord    Ŀ��Y����, ������Ϊ��������(�������Ļ����), ע��, nXCoord, nYCoord���Ե���
	 *            GvKmInstallHook()ʱƽ̨����Ļ�ֱ���Ϊ��׼
	 * bMouseMove �Ƿ���ģ������������в��ƶ����, TRUE���ƶ�, FALSE���ƶ��������λ��
	 ****************************************************************************************/
	GVKMEXPORT void GvKmMouseLButtonClick(int nXCoord, int nYCoord, bool bMouseMove=false);

	/****************************************************************************************
	 * ����������
	 * ģ����긱��(Ĭ��Ϊ�Ҽ�)���, ����ǰ��긱������Ϊ���, ��ú���ģ�����������
	 *
	 * ���������
	 * nXCoord    Ŀ��X����, ������Ϊ��������(�������Ļ����)
	 * nYCoord    Ŀ��Y����, ������Ϊ��������(�������Ļ����), ע��, nXCoord, nYCoord���Ե���
	 *            GvKmInstallHook()ʱƽ̨����Ļ�ֱ���Ϊ��׼
	 * bMouseMove �Ƿ���ģ������������в��ƶ����, TRUE���ƶ�, FALSE���ƶ��������λ��
	 ****************************************************************************************/
	GVKMEXPORT void GvKmMouseRButtonClick(int nXCoord, int nYCoord, bool bMouseMove=false);
}

#endif  //_GVKM_abc123_H

