#ifndef _GV_COM_DLL_DISTANCE_H_
#define _GV_COM_DLL_DISTANCE_H_

#include "Base.h"

namespace Gv {

class GVDLL Distance	// Min distance between two objects.
{
public:
	// Point to ...
	static float PointToPoint(PointF pt1, PointF pt2);
	static float PointToLine(PointF pt, LineF line);
	static float PointToLine(PointF pt, PointF ptLineStart, PointF ptLineEnd);
	static float PointToRect(PointF pt, RectF rcBox);
	static float PointToCircle(PointF pt, PointF ptCenter, float fRadius);

	// Line to ...
	static float LineToLine(LineF line1, LineF line2);
	static float LineToLine(PointF ptLine1Start, PointF ptLine1End, PointF ptLine2Start, PointF ptLine2End);
	static float LineToRect(LineF line, RectF rcBox);
	static float LineToRect(PointF ptLineStart, PointF ptLineEnd, RectF rcBox);
	static float LineToCircle(LineF line, PointF ptCircleCenter, float fRadius);
	static float LineToCircle(PointF ptLineStart, PointF ptLineEnd, PointF ptCircleCenter, float fRadius);

	// Rect to ...
	static float RectToRect(RectF rcBox1, RectF rcBox2);
	static float RectToCircle(RectF rcBox, PointF ptCircleCenter, float fRadius);

	// Circle to ...
	static float CircleToCircle(PointF ptCenter1, float fRadius1, PointF ptCenter2, float fRadius2);
};

}

#endif