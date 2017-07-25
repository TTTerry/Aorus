#ifndef _GV_COM_DLL_BASE_H_
#define _GV_COM_DLL_BASE_H_

#ifdef  GVCOM_EXPORT
#define GVDLL  __declspec(dllexport)
#else
#define GVDLL  __declspec(dllimport)
#endif

#include <map>
#include <list>
#include <vector> 
#include "shlwapi.h"
using namespace std;

#ifdef _UNICODE
#define _ttof _wtof
#else
#define _ttof atof
#endif 

namespace Gv {

enum Align  { Left = 0, Right, Center };
enum AlignV { Top = 0, Bottom, CenterV };
enum DB { KM = 0, KM_TEST, GUI, GUI_TEST, PUB, PUB_TEST, VGA, VGADATER, DB_QTY };
/////////////////////////////////////////////////
// PointF structure
/////////////////////////////////////////////////
struct GVDLL PointF // float point
{
	float x;
	float y;
	
	PointF();
	PointF(float _x, float _y);

	CPoint ToPoint();
};

/////////////////////////////////////////////////
// RectF structure
/////////////////////////////////////////////////
struct GVDLL RectF // float rect
{
	float left;
	float top;
	float right;
	float bottom;

	RectF();
	RectF(float l, float t, float r, float b);
	float Width();
	float Height();

	CRect ToRect();
};
/////////////////////////////////////////////////
// Line structure
/////////////////////////////////////////////////
struct LineF;
struct GVDLL Line // int line
{
	CPoint ptStart;
	CPoint ptEnd;

	Line();
	Line(CPoint _ptStart, CPoint _ptEnd);
	Line(int nStartX, int nStartY, int nEndX, int nEndY);

	LineF ToLineF();
};

/////////////////////////////////////////////////
// LineF structure
/////////////////////////////////////////////////
struct GVDLL LineF // float line
{
	PointF ptStart;
	PointF ptEnd;

	LineF();
	LineF(PointF _ptStart, PointF _ptEnd);
	LineF(float fStartX, float fStartY, float fEndX, float fEndY);

	Line ToLine();
};

class GVDLL Base
{
public:
	Base();
	CString GetLastError();

	static CString FormatLastError(DWORD dwLastError/*Call GetLastError() API to get last error*/);

protected:
	void GetSystemError();

protected:
	CString m_sLastError;	// Last error information
};
}

#endif

