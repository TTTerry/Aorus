#ifndef _GV_COM_DLL_VERIFY_H_
#define _GV_COM_DLL_VERIFY_H_

#include "Base.h"

namespace Gv {

class GVDLL Verify : public Base
{
public:
	//
	// 驗證軟件類型. 每個類型掛鉤一個軟件. 
	// 軟件開發過程中, 對應哪個類型由軟體部門人員分配.
	// 
	enum Type {
		SW01 =  1, SW02 =  2, SW03 =  3, SW04 =  4, SW05 =  5, SW06 =  6, SW07 =  7, SW08 =  8, SW09 =  9, SW10 = 10, 
		SW11 = 11, SW12 = 12, SW13 = 13, SW14 = 14, SW15 = 15, SW16 = 16, SW17 = 17, SW18 = 18, SW19 = 19, SW20 = 20, };

public:
	//
	// 檢測當前平臺是否已通過驗證, 未通過則
	// 顯示驗證對話框, 執行驗證, 驗證不通過時則直接退出主程式;
	// 
	static void Verification(Type sw, UINT nAllowUsedTime/*Days, 0 means always has authority*/); 	
};

}

#endif

