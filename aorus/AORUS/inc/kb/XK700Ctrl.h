#pragma once
#define CLR_COUNT 32
#define CLR_DEF_COUNT 8
static COLORREF s_defaultclr[CLR_DEF_COUNT] = {
	RGB(255,   0,   0),
	RGB(255,  90,   0),
	RGB(255, 200,   0),
	RGB(  0, 255,   0),
	RGB(  0, 255, 255),
	RGB(  0,   0, 255),
	RGB(255,   0, 255),
	RGB(255, 255, 255),
};

typedef struct _CLR_LST
{
	int nCount;
	COLORREF lstClr[128];

}CLR_LST, *PCLR_LST;

class CXK700Ctrl
{
public:
	CXK700Ctrl(void);
	~CXK700Ctrl(void);

	//void ToCircle(int i, int j, int nClr, int nBright, int nSpeed);
	void ToWave(int nAngle, int nClr, int nBright, int nSpeed);
	void ToConsistent(COLORREF clr, int nBright, int nSpeed);
	void ToPulsing(COLORREF clr1, COLORREF clr2, int nBright, int nSpeed, bool bRandom);
	void ToCycling(int nBright, int nSpeed);

protected:
	void ToByte(int nClrCount, int nTimer, int nClrIndex);
	bool SetClr(int i, int j, int nClr);
	bool SetClr(int i, int j, int nClr, int nKey[KEY_ROW][KEY_COL]);
	void ToIndex(WORD dwKey, int& i, int& j);
	WORD ToKey(int& i, int& j);
	int TokeyByteIndex(int i, int j);
	bool RectInRect(CRect rcSrc, CRect rcInc);
	BYTE* ToByte(BYTE* bt, COLORREF clr[]);

private:
	int m_nClrList;
	int m_nClrCount;
	CLR_LST s_lstClr[360];
	DWORD m_dwClrLastAddr;
#define MEM_SIZE 0x11000
	BYTE m_Memory[MEM_SIZE];
	BYTE m_LedMemory[MEM_SIZE];
};
