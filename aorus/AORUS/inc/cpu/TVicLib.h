/* ========================================================================
   =================    TVicHW32  DLL interface        ====================
   =======       Copyright (c) 1997..2004 Victor I.Ishikeev        ========
   ========================================================================
   ==========         mail to tools@entechtaiwan.com            ===========
   ==========         http://www.entechtaiwan.com/tools.htm     ===========
   ======================================================================== */


#ifndef _TVICLIB_H
#define _TVICLIB_H


#ifdef _TVIC_INTERNAL
#define VICFN  __declspec(dllexport)
#else
#define VICFN  __declspec(dllimport)
#endif


//-----------------------------------------------------------------------
// Data type declarations 
//-----------------------------------------------------------------------
typedef unsigned long	ULONG;
typedef unsigned long	DWORD;
typedef unsigned short	WORD;
typedef unsigned short	USHORT;
typedef void *			PVOID;
typedef unsigned char	UCHAR;
typedef void *			HANDLE;


typedef struct _IrqClearRec 
{
	UCHAR ClearIrq;        // 1 - Irq must be cleared, 0 - not
	UCHAR TypeOfRegister;  // 0 - memory-mapped register, 1 - port
	UCHAR WideOfRegister;  // Wide of register : 1 - Byte, 2 - Word, 4 - Double Word
	UCHAR ReadOrWrite;     // 0 - read register to clear Irq, 1 - write
	ULONG RegBaseAddress;  // Memory or port i/o register base address to clear
    ULONG RegOffset;       // Register offset
	ULONG ValueToWrite;    // Value to write (if ReadOrWrite=1)

} IrqClearRec, *pIrqClearRec;

//-----------------------------------------------------------------------
// Function pointer declarations
//-----------------------------------------------------------------------
typedef ULONG  (__stdcall * TRing0Function)(PVOID parm);
typedef void   (__stdcall * TOnHWInterrupt)(USHORT IRQNumber);
typedef void   (__stdcall * TOnFastTimer)();
typedef void   (__stdcall * TOnDelphiInterrupt)(HANDLE Component, WORD IRQNumber);

typedef void   (__stdcall * TOnHWInterruptEx)(USHORT IRQNumber, pIrqClearRec IrqRec);
typedef void   (__stdcall * TOnDelphiInterruptEx)(HANDLE Component, WORD IRQNumber, pIrqClearRec IrqRec);

typedef void   (__stdcall * TKbHookHandler)(BYTE scan_code);
typedef void   (__stdcall * TKbDelphiHandler)(HANDLE Componen, BYTE scan_code);
typedef HANDLE (__stdcall * TOpenVxDHandle)(HANDLE); 

typedef BOOL   (__stdcall * TEnumerateCallBack)(HANDLE HW32, BYTE bus, BYTE dev, BYTE func, PVOID pCfg);


//-----------------------------------------------------------------------
// Other declarations
//-----------------------------------------------------------------------
#define LPT_NOT_ACQUIRED         0
#define LPT_ACQUIRE_SUCCESS      1
#define LPT_ACQUIRE_REFUSED      2
#define LPT_ACQUIRE_BAD_PORT     3
#define LPT_ACQUIRE_NOT_OPENED   4

#define cmdIoAccess              0
#define cmdMemoryAccess          1
#define cmdBusMaster             2
#define cmdSpecialCycleMonitor   3
#define cmdWriteAndInvalidate    4
#define cmdPaletteSnoop          5
#define cmdParityErrorResponse   6
#define cmdWaitCycle             7
#define cmdSystemError           8
#define cmdFastBackToBack        9


//-----------------------------------------------------------------------
// Declarations for PCI
//-----------------------------------------------------------------------
#define PCI_TYPE0_ADDRESSES      6
#define PCI_TYPE1_ADDRESSES      2
#define PCI_TYPE2_ADDRESSES      5

typedef struct _PCI_COMMON_CONFIG {

    USHORT  VendorID;                   // 0 (ro)
    USHORT  DeviceID;                   // 2 (ro)
    USHORT  Command;                    // 4 Device control
    USHORT  Status;                     // 6   
    UCHAR   RevisionID;                 // 8 (ro)
    UCHAR   ProgIf;                     // 9 (ro)
    UCHAR   SubClass;                   //10 (ro)
    UCHAR   BaseClass;                  //11 (ro)
    UCHAR   CacheLineSize;              //12 (ro+)
    UCHAR   LatencyTimer;               //13 (ro+)
    UCHAR   HeaderType;                 //14 (ro)
    UCHAR   BIST;                       //15 Built in self test

    union {

		//
        // Non - Bridge
        //

        struct PCI_HEADER_TYPE_0 {

            ULONG   BaseAddresses[PCI_TYPE0_ADDRESSES];
            ULONG   CardBus_CIS;
            USHORT  subsystem_vendorID;
			USHORT  subsystem_deviceID;
            ULONG   ROMBaseAddress;
            UCHAR   CapabilitiesPtr;
            UCHAR   Reserved1[3];
            ULONG   Reserved2;

            UCHAR   InterruptLine;      //
            UCHAR   InterruptPin;       // (ro)
            UCHAR   MinimumGrant;       // (ro)
            UCHAR   MaximumLatency;     // (ro)

        } type0;

        //
        // PCI to PCI Bridge
        //

        struct _PCI_HEADER_TYPE_1 {

            ULONG   BaseAddresses[PCI_TYPE1_ADDRESSES];
            UCHAR   PrimaryBus;
            UCHAR   SecondaryBus;
            UCHAR   SubordinateBus;
            UCHAR   SecondaryLatency;
            UCHAR   IOBase;
            UCHAR   IOLimit;
            USHORT  SecondaryStatus;
            USHORT  MemoryBase;
            USHORT  MemoryLimit;
            USHORT  PrefetchBase;
            USHORT  PrefetchLimit;
            ULONG   PrefetchBaseUpper32;
            ULONG   PrefetchLimitUpper32;
            USHORT  IOBaseUpper16;
            USHORT  IOLimitUpper16;
            UCHAR   CapabilitiesPtr;
            UCHAR   Reserved1[3];
            ULONG   ROMBaseAddress;
            UCHAR   InterruptLine;
            UCHAR   InterruptPin;
            USHORT  BridgeControl;

        } type1;

        //
        // PCI to CARDBUS Bridge
        //

        struct _PCI_HEADER_TYPE_2 {

            ULONG   SocketRegistersBaseAddress;
            UCHAR   CapabilitiesPtr;
            UCHAR   Reserved;
            USHORT  SecondaryStatus;
            UCHAR   PrimaryBus;
            UCHAR   SecondaryBus;
            UCHAR   SubordinateBus;
            UCHAR   SecondaryLatency;
            struct  {
                ULONG   Base;
                ULONG   Limit;
            }       Range[PCI_TYPE2_ADDRESSES-1];
            UCHAR   InterruptLine;
            UCHAR   InterruptPin;
            USHORT  BridgeControl;

        } type2;


        ULONG AsUlong;

	} u;

    UCHAR   DeviceSpecific[192];

} PCI_COMMON_CONFIG, * PPCI_COMMON_CONFIG;

//-----------------------------------------------------------------------
// Declarations for Ports
//-----------------------------------------------------------------------
typedef struct _FIFO_RECORD 
{
    ULONG PortAddr;
    ULONG NumPorts;
    UCHAR Buf[1];

} FIFO_RECORD, *PFIFO_RECORD;

typedef struct _FIFO_RECORDW 
{
    ULONG  PortAddr;
    ULONG  NumPorts;
    USHORT Buf[1];

} FIFO_RECORDW, *PFIFO_RECORDW;

typedef struct _FIFO_RECORDL 
{
    ULONG   PortAddr;
    ULONG   NumPorts;
    ULONG   Buf[1];

} FIFO_RECORDL, *PFIFO_RECORDL;

//-----------------------------------------------------------------------
// Declarations for Hdds
//-----------------------------------------------------------------------
typedef struct _HDDInfo {

	DWORD      BufferSize;
	DWORD      DoubleTransfer;
	DWORD      ControllerType;
	DWORD      ECCMode;
	DWORD      SectorsPerInterrupt;
	DWORD      Cylinders;
	DWORD      Heads;
	DWORD      SectorsPerTrack;
	char       Model[41];
	char       SerialNumber[21];
	char       Revision[9];

} HDDInfo, *pHDDInfo;

//-----------------------------------------------------------------------
// Declarations for Dma
//-----------------------------------------------------------------------
typedef struct _DMA_BUFFER_REQUEST 
{
	ULONG LengthOfBuffer;
	ULONG AlignMask;
	ULONG PhysDmaAddress;
	ULONG LinDmaAddress;
	ULONG PMemHandle;
	ULONG Rezerved1;
	ULONG KernelDmaAddress;
	ULONG Rezerved2;

} DMA_BUFFER_REQUEST, *PDMA_BUFFER_REQUEST;

//-----------------------------------------------------------------------
// Declarations for other APIs
//-----------------------------------------------------------------------
typedef struct _KEYBOARD_INPUT_DATA 
{
	USHORT UnitId;
	USHORT MakeCode;
	USHORT Flags;
	USHORT Reserved;
	ULONG ExtraInformation;

} KEYBOARD_INPUT_DATA, * PKEYBOARD_INPUT_DATA;

typedef struct _MSR_DATA 
{
	ULONG MSR_LO;
	ULONG MSR_HI;

} MSR_DATA, * PMSR_DATA;

typedef struct _CPUID_RECORD 
{
	ULONG EAX;
	ULONG EBX;
	ULONG ECX;
	ULONG EDX;

} CPUID_RECORD;


#ifdef __cplusplus
extern "C" {
#endif

//-----------------------------------------------------------------------
// Inits API
//-----------------------------------------------------------------------
VICFN BOOL	 __stdcall OpenTVicHW();
VICFN BOOL   __stdcall GetActiveHW();
VICFN BOOL	 __stdcall CloseTVicHW();

//-----------------------------------------------------------------------
// Ports API
//-----------------------------------------------------------------------
VICFN BOOL   __stdcall GetHardAccess();
VICFN void   __stdcall SetHardAccess(BOOL bNewValue);

VICFN UCHAR  __stdcall GetPortByte(ULONG PortAddr); 
VICFN void   __stdcall SetPortByte(ULONG PortAddr, UCHAR nNewValue);
VICFN USHORT __stdcall GetPortWord(ULONG PortAddr);
VICFN void   __stdcall SetPortWord(ULONG PortAddr, USHORT nNewValue);
VICFN ULONG  __stdcall GetPortLong(ULONG PortAddr);
VICFN void   __stdcall SetPortLong(ULONG PortAddr, ULONG nNewValue);

VICFN void	 __stdcall ReadPortFIFO(PFIFO_RECORD pPortRec);
VICFN void	 __stdcall ReadPortWFIFO(PFIFO_RECORDW pPortRec);
VICFN void	 __stdcall ReadPortLFIFO(PFIFO_RECORDL pPortRec);
VICFN void	 __stdcall WritePortFIFO(PFIFO_RECORD pPortRec);
VICFN void	 __stdcall WritePortWFIFO(PFIFO_RECORDW pPortRec);
VICFN void	 __stdcall WritePortLFIFO(PFIFO_RECORDL pPortRec);

//-----------------------------------------------------------------------
// Mems API
//-----------------------------------------------------------------------
VICFN ULONG  __stdcall MapPhysToLinear(ULONG PhAddr, ULONG PhSize);
VICFN void   __stdcall UnmapMemory(ULONG PhAddr, ULONG PhSize);

VICFN UCHAR  __stdcall GetMem(ULONG MappedAddr, ULONG Offset);
VICFN void   __stdcall SetMem(ULONG MappedAddr, ULONG Offset, UCHAR nNewValue);
VICFN USHORT __stdcall GetMemW(ULONG MappedAddr, ULONG Offset);
VICFN void   __stdcall SetMemW(ULONG MappedAddr, ULONG Offset, USHORT nNewValue);
VICFN ULONG  __stdcall GetMemL(ULONG MappedAddr, ULONG Offset);
VICFN void   __stdcall SetMemL(ULONG MappedAddr, ULONG Offset, ULONG nNewValue);

VICFN short  __stdcall GetMappedAreas();
VICFN PVOID  __stdcall GetLockedMemory();
VICFN ULONG  __stdcall GetTempVar();

//-----------------------------------------------------------------------
// Irps API
//-----------------------------------------------------------------------
VICFN void   __stdcall UnmaskIRQ(USHORT IRQNumber, TOnHWInterrupt HWHandler);
VICFN void   __stdcall UnmaskIRQEx(USHORT IRQNumber, ULONG IrqShared, TOnHWInterrupt HWHandler, pIrqClearRec IrqRec);

VICFN void   __stdcall UnmaskDelphiIRQ(HANDLE Component, USHORT IRQNumber, TOnHWInterrupt HWHandler);
VICFN void   __stdcall UnmaskDelphiIRQEx(HANDLE Component, USHORT IRQNumber, ULONG IrqShared, TOnHWInterrupt HWHandler, pIrqClearRec IrqRec);

VICFN ULONG  __stdcall MaskIRQ(USHORT IRQNumber);
VICFN ULONG  __stdcall GetIRQCounter(USHORT IRQNumber);
VICFN BOOL   __stdcall IsIRQMasked(USHORT IRQNumber);

//-----------------------------------------------------------------------
// Kbds API
//-----------------------------------------------------------------------
VICFN void	 __stdcall PutScanCode(UCHAR Code);
VICFN WORD	 __stdcall GetScanCode();

VICFN void	 __stdcall HookKeyboard(TKbHookHandler HWHandler);
VICFN void	 __stdcall HookDelphiKeyboard(HANDLE Component, TKbHookHandler HWHandler);
VICFN void	 __stdcall UnhookKeyboard();

VICFN void	 __stdcall PulseKeyboard();
VICFN void	 __stdcall PulseKeyboardLocal();

//-----------------------------------------------------------------------
// Lpts API
//-----------------------------------------------------------------------
VICFN UCHAR  __stdcall GetLPTNumber();
VICFN void   __stdcall SetLPTNumber(UCHAR nNewValue);
VICFN UCHAR  __stdcall GetLPTNumPorts();
VICFN ULONG  __stdcall GetLPTBasePort();
VICFN UCHAR  __stdcall AddNewLPT(USHORT PortBaseAddress);

VICFN BOOL   __stdcall GetPin(UCHAR nPin);
VICFN void   __stdcall SetPin(UCHAR nPin, BOOL bNewValue);

VICFN BOOL   __stdcall GetLPTAckwl();
VICFN BOOL   __stdcall GetLPTBusy();
VICFN BOOL   __stdcall GetLPTPaperEnd();
VICFN BOOL   __stdcall GetLPTSlct();
VICFN BOOL   __stdcall GetLPTError();

VICFN void   __stdcall LPTInit();
VICFN void   __stdcall LPTSlctIn();
VICFN void   __stdcall LPTStrobe();
VICFN void   __stdcall LPTAutofd(BOOL Flag);

VICFN BOOL   __stdcall LPTPrintChar(UCHAR Char);
VICFN void   __stdcall ForceIrqLPT(BOOL IrqEnable);

VICFN void   __stdcall SetLPTReadMode();
VICFN void   __stdcall SetLPTWriteMode();

VICFN USHORT __stdcall AcquireLPT(USHORT LPTNumber);
VICFN void   __stdcall ReleaseLPT(USHORT LPTNumber);
VICFN USHORT __stdcall IsLPTAcquired(USHORT LPTNumber);	

//-----------------------------------------------------------------------
// Ring0 API
//-----------------------------------------------------------------------
VICFN ULONG  __stdcall RunRing0Function(TRing0Function R0func, PVOID pParm);

//-----------------------------------------------------------------------
// Pci API
//-----------------------------------------------------------------------
VICFN USHORT __stdcall GetLastPciBus();
VICFN USHORT __stdcall GetHardwareMechanism();

VICFN BOOL   __stdcall GetPciDeviceInfo(USHORT BusNum, USHORT DeviceNum, USHORT FuncNum, PPCI_COMMON_CONFIG pPciCfg);
VICFN BOOL   __stdcall GetPciHeader(ULONG VendorId, ULONG DeviceId, ULONG OffsetInBytes, ULONG LengthInBytes, 
									PPCI_COMMON_CONFIG pPciCfg);
VICFN BOOL   __stdcall SetPciHeader(ULONG VendorId, ULONG DeviceId, ULONG OffsetInBytes, ULONG LengthInBytes, 
									PPCI_COMMON_CONFIG pPciCfg);

//-----------------------------------------------------------------------
// Hdds API
//-----------------------------------------------------------------------
VICFN void   __stdcall GetHDDInfo(USHORT IdeNumber, USHORT Master, pHDDInfo Info);

//-----------------------------------------------------------------------
// Dma API
//-----------------------------------------------------------------------
VICFN BOOL   __stdcall GetSysDmaBuffer(DMA_BUFFER_REQUEST * BufReq);
VICFN BOOL   __stdcall GetBusMasterDmaBuffer(PDMA_BUFFER_REQUEST BufReq);
VICFN void   __stdcall FreeDmaBuffer(PDMA_BUFFER_REQUEST BufReq);

//-----------------------------------------------------------------------
// Other API
//-----------------------------------------------------------------------
VICFN void   __stdcall GetMsrValue(ULONG RegNumber, PMSR_DATA MsrData);
VICFN void   __stdcall CPUID(CPUID_RECORD * Rec);
VICFN ULONG  __stdcall GetLocalInstance();
VICFN ULONG  __stdcall DebugCode();

#ifdef __cplusplus
}
#endif

#endif
