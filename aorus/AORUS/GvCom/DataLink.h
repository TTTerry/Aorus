#ifndef _GV_COM_DLL_DATALINK_H_
#define _GV_COM_DLL_DATALINK_H_

#include "Base.h"


namespace Gv {
class GVDLL DataLink  
{
	class GVDLL _PinNameNode {
	public:
		 CString		Name;	//R234
		 CString		Comp;	//R
		 CString		Pin;	//234
		 CString		Layer;	//top,bottom
		 int			Type;	
		 int			State;
		 float			x;
		 float			y;
		 CString		Sheet;
		_PinNameNode	*Next;

	public:	
		_PinNameNode();
		~_PinNameNode();
	}; // Pin Node Struct

	class GVDLL _LineNameNode{
	public:
		CString			Name;
		CString			Name1;
		CString			Name2;
		CString			Name3;
		CString			ModelName;	//2005/2/21 celia
		CString			COMM;	//2005/2/21 celia
		CString			Level;	//2005/2/21 celia
		BOOL			Mount;		//上件否
		CString			Number;		//料號
		CString			PN;			//料號中第3碼(大類)
		CString			CompName;
		double			Value;
		CString			Size;
		CString			Voltage;	//電壓
		CString			X7R;		
		CString			Percent;	//%
		int				CAP;		//有極/無極電容
		int				Check;
		DWORD			jTotalPin;	//location 數量
		double			MCount;		//上件數量 2004/11/30 add; 05/09/29 DWORD->double
		CString			Color;		
		CString			Dip_Smd;
		CString			Type;
		CString			Current;	//電流(安培)
		CString			LineCount;	//線數
		CString			Layer;		//層(暫存)
		CString			XTAL;
		double			ESR;
		double			MOS_RDSON;
		CString			LeadFree;
		CString			Verify;
		double			pfValue;	//XTAL用 05/09/29 add 
		CString			MPackage;    //元件包裝 05/09/29 add
		CString			FootPrint;	 //05/09/29 add
		CString			Tolerance;	 //05/09/29 add
		CString			CompAttr[20];//2005/06/24 改為20
		_LineNameNode	*NextLine;
		_LineNameNode	*SubLine;	//second source
		_PinNameNode	*NextPin;
	public:
		_LineNameNode();
		~_LineNameNode();
	};  

protected:
	void UniversalFormat(_LineNameNode **pBomFile);
	bool IsNumeral(CString sStr);
	void GetTipTopFile(_LineNameNode **pLineNode);
	void DebugInfo(CString sStr);
	void SetOtherBOMValue(_LineNameNode **pBomFile);
	void CutOtherBOMDescValue(CString sDesc,CString * ValueTable);
	void GetATISourceBOM(_LineNameNode **pBomFile);
	void AddSubLine(int iState,_LineNameNode **pSubLine,_LineNameNode **pLine,int pinnum1,int pinnum2,int pinnum3);
	//==parameter=======
	_LineNameNode	*pHead;
	_LineNameNode	*pLine;
	_LineNameNode	*pSub;
	_PinNameNode	*pPin;
	_LineNameNode	*kRuleTable; //Value 格式table表
	BOOL			m_LineTail;
	BOOL			m_PinTail;
	BOOL			m_SubTail;
	CString			sRuleTableWarning;
	CString			m_ModelName;//2005/2/21

	//==== Public ========================================================
	DWORD	GetLink(CString jCStr,_LineNameNode **jCapHead,
					CString jLineLabel, CString jPinLabel);
	DWORD	GetLink(TCHAR *jCapBuffer,DWORD jFileLength,
					_LineNameNode **jCapHead,CString _LineLabel, CString jPinLabel);
	DWORD	GetLink(TCHAR *_CapBuffer,DWORD _FileLength, 
					_LineNameNode **_CapHead);
	void	KGetDataLink(int iState,CString sFileName, CString UserStr,CString jLineLabel, CString jPinLabel, _LineNameNode **pLineNode);
	void	JFixFrontEndSpace(_LineNameNode *jHead,int jPos);
	void	JSeperateStrNum(CString PartNum, CString *PartName, CString * PartCount);
	void	KInsertPinNode(_PinNameNode **pPinNode, CString Name);
	void	JDelLineNode(_LineNameNode** jHead,_LineNameNode** jList);
	void	JDeleteXComp(_LineNameNode **jBHead);
	void	DeleteList();
	void	DeleteLineNode(_LineNameNode* pa);
	void	DeletePin(_PinNameNode* pa);
	CString	JCutSpace(CString jStr,int jPos);
	_PinNameNode *GetNextLayer(int iLayer, _PinNameNode * jComHead);


	//====for EBOM=======================================================
	void	JCutNoUse(_LineNameNode **jBHead);
	void	KGetArgument(_LineNameNode **pLineNode);
	int		JCompName(CString jName, CString* jCompName, int jNum);
	DWORD	KFindCompBOM(TCHAR *jCapBuffer, DWORD jFileLength);
	DWORD	GetLineLink(TCHAR *jCapBuffer,DWORD jFileLength,
						_LineNameNode **jCapHead );
	CString KGetColorStr(CString sName);

	//====for ATI BOM ===================================================
	void KGetATIRefDesLink(_LineNameNode **pBomFile);

	//====for Nvidia BOM ================================================
	void KGetNvidiaRefDesLink(_LineNameNode **pBomFile);

	//====for USI BOM ===================================================
	void KGetUSIRefDesLink(_LineNameNode **pBomFile);

	//====for Captur BOM ================================================
	void KGetCaptureRefDesLink(_LineNameNode **pBomFile);
	void JChangeValueToLink(_LineNameNode *jHead);
	void JConnectSameNode(_LineNameNode *jBHead);

	//====for Rule Table ================================================
	void KInitRuleTable(int iState);
	_LineNameNode* KCheckRuleTable(DataLink::_LineNameNode **pLineNode);
	void KPutValue(_LineNameNode **pLineNode);

	/*====for Capture->Allegro NetList->Part(value_footprint)(.NET)======
		  Allegro->Netin(non-back)(.rpt)				   */
	void KGetCapturePartLink(_LineNameNode **pLineNode);
	void KGetAllegroPartLink(_LineNameNode **pLineNode);
	int  KCheckCAPName(CString sName,double dValue);
	DWORD KFindAllegroPart(TCHAR *jCapBuffer,DWORD jFileLength);
	//====for Allegro Netin file (NET)(.rpt)  ===========================
	DWORD KFindAllegroNet_Netin(TCHAR *_CapBuffer,DWORD _FileLength);

	//====for Capture->Allegro NetList->Net(value_footprint)(.NET)=======
	DWORD KFindAllegroNet(TCHAR *_CapBuffer,DWORD _FileLength);
	void JChangePointToSlash(_LineNameNode *jBHead);

	//====for Allegro Symbol file (x,y info)(.rpt) ======================
	void KGetSymbolLink(_LineNameNode **pLineNode);

	//====for Allegro Comp. file (top/bottom info)(.rpt) ================
	void KDelGridLine(_LineNameNode **pLineNode);



public:
	//==== Outside ======================================================
	
	BOOL isNoData(){
		if(pHead)
			return true;
		else
			return false;
	;}//2007/05/08
	CString GetCAPSize1(CString size);
	CString GetCAPSize2(CString size);
	CString ConvertTolerance(CString sPercent);
	double CheckRDSON(CString Dsp);//2004/09/15 celia
	BOOL JUniMatch(CString Name, CString UniStr);
	void CutCaptureValue(CString sValue, CString *ValueTable);//2004/08/20 celia
	void CutDescValue(CString sDesc,CString* ValueTable);//2004/08/20 celia
	CString CheckPercent(CString Percent);//2004/08/20 celia
	CString CheckType(CString Type);//2004/08/20 celia
	BOOL CheckVoltage(CString Voltage);//2004/08/20 celia
	CString CheckSize(CString Size);//2004/08/20 celia
	CString CheckSize1(CString Size);//2005/09/30 celia	
	BOOL    CheckValueStr(CString Source,CString Str);//2005/09/30 celia	
	CString ConvertCAPSize(CString CAPSize);
	CString GetRuleTableWarning(){return sRuleTableWarning;}//2004/07/29 celia
	CString CutSpace(CString sStr);
	BOOL    GetDataLink(CString FileName, int Kind,CString UserStr,CString jLineLabel, CString jPinLabel);
/*	0://EBOM 1://ATI 2://Nvidia 3://USI 4://Capture BOM 5://allegro comp. 6://Capture->Allegro file(Parts部份)資料
	7://Capture->Allegro file(NET部份)資料 8://Allegro Net List file(Parts部份)資料 9://Allegro Symbol part	
	10://Allegro Netin file (NET) 11://other(/t) 12://user 13://user file 14:TipTop 15:ThirParty Universal Format*/
	float   StrToFloat(CString jStr);
	double	JStrToVal(CString jString);
	void    Release() {DeleteList();}
	//Line data====
	void	 LineHead();
	void	 NextLine();
	BOOL	 LineEOF()		{if(!pLine) m_LineTail = TRUE;return m_LineTail;}
	void	 DeleteLine()   {JDelLineNode(&pHead,&pLine);}
	void	 SetName(CString sStr)	{pLine->Name=sStr;}
	void	 SetName1(CString sStr)	{pLine->Name1=sStr;}
	void	 SetName2(CString sStr)	{pLine->Name2=sStr;}
	void	 SetName3(CString sStr)	{pLine->Name3=sStr;}
	CString  GetName()		{return pLine->Name;}
	CString	 GetName1()		{return pLine->Name1;}
	CString	 GetName2()		{return pLine->Name2;}
	CString  GetName3()		{return pLine->Name3;}
	BOOL	 GetMount()		{return pLine->Mount;} //上件否
	CString	 GetNumber()	{return pLine->Number;}//料號
	CString	 GetPN()		{return pLine->PN;}    //料號中第3碼(大類)
	CString	 GetCompName()	{return pLine->CompName;}
	double	 GetValue()		{return pLine->Value;}
	CString	 GetSize()		{return pLine->Size;}
	CString	 GetVoltage()	{return pLine->Voltage;}//電壓
	CString	 GetX7R()		{return pLine->X7R;}
	CString	 GetPercent()	{return pLine->Percent;}	//%
	int		 GetCAP()		{return pLine->CAP;}		//有極/無極電容
	int		 GetCheck()		{return pLine->Check;}
	DWORD	 GetTotalPin()	{return pLine->jTotalPin;}//location 數量
	double	 GetMCount()	{return pLine->MCount;}//上件數 2004/12/20 070307 DWORD->double
	CString	 GetColor()		{return pLine->Color;}		
	CString	 GetDipSMD()	{return pLine->Dip_Smd;}
	CString	 GetType()		{return pLine->Type;}
	CString	 GetCurrent()	{return pLine->Current;}	//電流(安培)
	CString	 GetLineCount() {return pLine->LineCount;}	//線數
	CString	 GetXTAL()		{return pLine->XTAL;}
	CString  GetCOMM()		{return pLine->COMM;} //2005/02/23
	CString  GetModelName()	{return pLine->ModelName;} //2005/02/23
	CString  GetLevel()		{return pLine->Level;} //2005/02/23
	CString  GetVerify()	{return pLine->Verify;} //2005/10/07
	CString  GetMPackage()	{return pLine->MPackage;} //2005/10/07
	double   GetpfValue()	{return pLine->pfValue;}//XTAL用 05/09/29 add 
	double   GetESR()		{return pLine->ESR;}
	double   GetMOS_RDSON()	{return pLine->MOS_RDSON;}	
	CString	 GetFootPrint() {return pLine->FootPrint;};	 //05/09/29 add
	CString	 GetTolerance() {return pLine->Tolerance;};	 //05/09/29 add
	void	 SetLineCheck(int iCheck){pLine->Check = iCheck;}
	CString	 GetFactory()   { 
		int i = 0;
		for(i= 0;pLine->CompAttr[i]!="Non";i++){  //celia 2004/07/22
		}
		return pLine->CompAttr[i-1];
	}
	CString GetLayer() {return pLine->Layer;}

	//Sub data========
	void	 SubHead();
	void	 NextSubLine();
	BOOL	 SubEOF()		{return m_SubTail;}
	CString  GetSName()		{return pSub->Name;}
	CString	 GetSName1()	{return pSub->Name1;}
	CString	 GetSName2()	{return pSub->Name2;}
	CString  GetSName3()	{return pSub->Name3;}
	CString	 GetSNumber()	{return pSub->Number;}//料號
	double	 GetSValue()	{return pSub->Value;}
	CString	 GetSSize()		{return pSub->Size;}
	CString	 GetSType()		{return pSub->Type;}
	CString	 GetSCurrent()	{return pSub->Current;}	//電流(安培)
	CString	 GetSLineCount() {return pSub->LineCount;}	//線數
	CString	 GetSVoltage()	{return pSub->Voltage;}//電壓
	CString	 GetSPercent()	{return pSub->Percent;}	//%
	CString	 GetSXTAL()		{return pSub->XTAL;}
	CString	 GetSColor()	{return pSub->Color;}
	CString	 GetSFactory()  {
		int i = 0;
		for(i= 0;pSub->CompAttr[i]!="Non";i++){ //celia 2004/07/22
		}
		return pSub->CompAttr[i-1];
	}
	CString	 GetSDipSMD()	{return pSub->Dip_Smd;}
	CString  GetSMPackage()	{return pSub->MPackage;} //2005/10/07
	double   GetSpfValue()	{return pSub->pfValue;}//XTAL用 05/09/29 add 
	double   GetSESR()		{return pSub->ESR;}
	double   GetSMOS_RDSON()	{return pSub->MOS_RDSON;}	
	CString	 GetSFootPrint() {return pSub->FootPrint;};	 //05/09/29 add
	CString	 GetSTolerance() {return pSub->Tolerance;};	 //05/09/29 add

	//Pin Data =========
	void	 PinHead(int Kind/*0:LinePin;1:SubPin;2:user Pin*/);
	void	 NextPin();
	BOOL	 PinEOF()  {return m_PinTail;}
	void	 SetPinState(int iState) {pPin->State = iState;}
	void	 SetPinLayer(CString sLayer) {pPin->Layer = sLayer;}
	CString	 GetPinName(int Row);
	CString	 GetPinName()	{return pPin->Name;}
	CString	 GetPinComp()	{return pPin->Comp;}
	CString	 GetPinNumber()	{return pPin->Pin;}
	CString	 GetPinLayer()	{return pPin->Layer;}	//top,bottom
	int		 GetPinType()	{return pPin->Type;}
	int		 GetPinState()	{return pPin->State;}
	float	 GetPinX()		{return pPin->x;}
	float	 GetPinY()		{return pPin->y;}
	CString	 GetSheet()		{return pPin->Sheet;}
public:
	
	DataLink();
	virtual ~DataLink();

};

}

#endif 

