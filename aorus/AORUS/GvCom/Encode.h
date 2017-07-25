#ifndef _GV_COM_DLL_ENCODE_H_
#define _GV_COM_DLL_ENCODE_H_

#include "Base.h"

namespace Gv {

class GVDLL Code
{

public:
	static bool Encode(CString sSrcFile, CString sDstFile, CString* pError=NULL); // Encode file simply
	static bool Decode(CString sSrcFile, CString sDstFile, CString* pError=NULL);
};


}

#endif

