#ifndef _GV_COM_DLL_VERIFY_H_
#define _GV_COM_DLL_VERIFY_H_

#include "Base.h"

namespace Gv {

class GVDLL Verify : public Base
{
public:
	//
	// ��Cܛ�����. ÿ����͒��^һ��ܛ��. 
	// ܛ���_�l�^����, �����Ă������ܛ�w���T�ˆT����.
	// 
	enum Type {
		SW01 =  1, SW02 =  2, SW03 =  3, SW04 =  4, SW05 =  5, SW06 =  6, SW07 =  7, SW08 =  8, SW09 =  9, SW10 = 10, 
		SW11 = 11, SW12 = 12, SW13 = 13, SW14 = 14, SW15 = 15, SW16 = 16, SW17 = 17, SW18 = 18, SW19 = 19, SW20 = 20, };

public:
	//
	// �z�y��ǰƽ�_�Ƿ���ͨ�^��C, δͨ�^�t
	// �@ʾ��C��Ԓ��, ������C, ��C��ͨ�^�r�tֱ���˳�����ʽ;
	// 
	static void Verification(Type sw, UINT nAllowUsedTime/*Days, 0 means always has authority*/); 	
};

}

#endif

