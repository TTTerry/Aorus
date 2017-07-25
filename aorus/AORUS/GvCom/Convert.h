#ifndef _GV_COM_DLL_CONVERT_H_
#define _GV_COM_DLL_CONVERT_H_

#include "Base.h"


namespace Gv {

class GVDLL Cvt	
{
public:
	static COleDateTime ToDateTime(CString sDateTime);  // 'YYYY-MM-DD HH:mm:SS' -> DateTime

	static CString ToString(bool  bValue);  // true -> '1'; false -> '0';
	static CString ToString(int   nValue);	
	static CString ToString(long  nValue);
	static CString ToString(UINT  nValue);
	static CString ToString(DWORD dwValue);
	static CString ToString(float  fValue, int nPrecision=0); // P=0 -> No limited; P=1 -> '0.0'; P=2 -> '0.00'; ...
	static CString ToString(double fValue, int nPrecision=0);	
	static CString ToString(COleDateTime date);  // DateTime -> 'YYYY-MM-DD HH:mm:SS'
};

}

#endif