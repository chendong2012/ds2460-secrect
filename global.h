
#ifdef MAIN_C
DWORD 	data		gb_uiMacOffset;
DWORD   data        gb_uiWin32Offset;
DWORD   data        gb_uiCDROMOffset;
BYTE 	idata		gb_UsbUsageTemp;
//BYTE 	idata		gb_ucPowerDownMode;
//BYTE 	idata		gb_ucLastKey;
//BYTE 	idata		gb_ucDebounceCnt;
BYTE  	data		gbInt0IE; 
BYTE	data		gbInt1IE;
BYTE	data		gbTimerCnt;
BYTE	data		gfSCSICmdStatus;
BYTE	data		gfTestunitcnt;
//BYTE	data 		gbModeKey;						

BYTE    data        gbPWMtemp;	
		bit		bEP0xferDone;			
		bit		bDataOutFlag;	
//		bit		gfClearFeature; 	
		bit		gfUSBInitEND;	
//		bit		gfFlashSTRDataValid; 	
//		bit		gfFlashIDDataValid; 		
		bit		gfUSEinitGetDescriptor;	
		bit		gfMSCvalid;	 
		

#else
extern	DWORD	data	gb_uiMacOffset;
extern  DWORD   data        gb_uiWin32Offset;
extern  DWORD   data        gb_uiCDROMOffset;
extern	BYTE 	idata	gb_UsbUsageTemp;
//extern	BYTE 	idata	gb_ucPowerDownMode;
//extern	BYTE 	idata	gb_ucLastKey;
//extern	BYTE 	idata	gb_ucDebounceCnt;
extern	BYTE 	data	gbInt0IE; 
extern	BYTE	data	gbInt1IE;
extern  BYTE	data	gbTimerCnt;				//Johnny 2006/06/28
extern  BYTE	data	gfSCSICmdStatus;		//Johnny:for record SCSI status
extern 	BYTE	data	gfTestunitcnt;			//Johnny:
//extern 	BYTE	data	gbModeKey;



extern		bit		bEP0xferDone;			
extern		bit		bDataOutFlag;	
//extern		bit		gfClearFeature; 	
extern		bit		gfUSBInitEND;	
//extern		bit		gfFlashSTRDataValid; 	
//extern		bit		gfFlashIDDataValid; 		
extern		bit		gfUSEinitGetDescriptor;	
extern		bit		gfMSCvalid;	  			



#endif

#ifdef _Usbtran_C
XMT		XmtBuff;
BYTE	idata	tx0_data_tgl;
BYTE	idata 	g_ucBuffer[2];   //mainly used for return buffer for endpoint 1
BYTE 	data 	byInt0StatusA;
BYTE	data	byInt0StatusB;
BYTE	idata	byInt1Status;
BYTE	idata	ucConfigurationStatus;
BYTE	data    ucHidProtocolStatus;
BYTE	data	ucIdlePeriodStatus;
BYTE	idata	ucIdlePeriodTemp;
BYTE	idata	ucRemoteWakeupStatus;
BYTE	idata	ucCurAlternate;
BYTE	idata	ucCurAlternateTable[2];
BYTE    data    gb_ucAlarmP;
BYTE	idata 	byUSBAddr;
BYTE    data    ucHIDstatus;  //yuan
//BYTE    data    ucDeviceStatus;
//BYTE    data    gcWrite_Read_flag;
BYTE    data    gcEraseFlashBusy;
DWORD    data  gbReadWriteCnt;
DWORD   data  wSectorAddr;
DWORD    data  ucDataPacketCnt;//yuan
//BYTE    data   temp_data[8];   //yuan add for test
//bit     gbStatus;
//BYTE    data   testcount;

#else
extern	XMT		XmtBuff;
extern	BYTE	idata		tx0_data_tgl;
extern	BYTE	idata 		g_ucBuffer[2];   //mainly used for return buffer for endpoint 1
extern	BYTE 	data 		byInt0StatusA;
extern	BYTE	data		byInt0StatusB;
extern	BYTE	idata		byInt1Status;
extern	BYTE	idata		ucConfigurationStatus;
extern 	BYTE	data    	ucHidProtocolStatus;
extern	BYTE	idata		ucIdlePeriodStatus;
extern	BYTE	idata		ucIdlePeriodTemp;
extern	BYTE	idata		ucRemoteWakeupStatus;
extern	BYTE	idata		ucCurAlternate;
extern	BYTE	idata		ucCurAlternateTable[2];
extern	BYTE	idata 		byUSBAddr;
extern  BYTE    data    gb_ucAlarmP;
extern  BYTE    data    ucHIDstatus;
//extern 	BYTE    data    ucDeviceStatus;
//extern  BYTE    data    gcWrite_Read_flag;
extern  BYTE    data    gcEraseFlashBusy;
extern  DWORD    data  gbReadWriteCnt;
extern  DWORD   data  wSectorAddr;
extern  DWORD    data  ucDataPacketCnt;//yuan
//extern  BYTE    data   temp_data[8];   //yuan add for test
//extern   bit    gbStatus;

//extern  BYTE    data   testcount;


#endif


#ifdef _ISR_C
		BYTE		data		gbInt0Status;
		BYTE		data		gbInt1Status;
		BYTE		idata		gbUsbAddr;
		BYTE		bdata	IntCtrlFlag;
		sbit		gfRc0Flag			= IntCtrlFlag^7;
		sbit		gfTx0Flag			= IntCtrlFlag^6;
		sbit		gfSetAddress		= IntCtrlFlag^5;
		sbit		gfOut0Flag			= IntCtrlFlag^4;	
	//	sbit		gfTimer0Overflow	= IntCtrlFlag^3;
		sbit		gfTx3Flag			= IntCtrlFlag^2;
		sbit		gfRC2Flag			= IntCtrlFlag^1;
		sbit		gfTx1Flag			= IntCtrlFlag^0;

//		bit		gfMSCPowerTest;
//		bit		gf0x12; 
//		bit		gf0x25; 
	//	bit		gf0x28; 
//		bit		gf0x5a;
//		bit		gf0x1a; 
		bit		gfResetFlag;
//		BYTE data     gb_person_on_off_2;  //yuan
		bit		gfResume;
		bit		gfFastModeflag;
//		bit		gfTimeoutflag; 
		bit 	gfSuspend; 
		bit	  	gfTimeOut; 
		bit		gf5VDDFlag; 

		bit		gfTx1RAMFlag; 
		bit		gfBulkXferDone;
//		bit		gfRc2RAMFlag; 	
		bit		gfInterrptXferDone; 

		bit		gfEntryGetConfig; 
//		bit		gfRc4Flag; 

		bit		gfMAC;	
		bit		gfEntrySuspend; 

		
#else

		extern	BYTE	data		gbInt0Status;
		extern	BYTE	data		gbInt1Status;
		extern	BYTE	idata		gbUsbAddr;			//if define "data" , over address


		extern  BYTE		bdata	IntCtrlFlag;
		extern	BYTE	bdata	IntCtrlFlag;
		extern	bit		gfRc0Flag;	
		extern	bit		gfTx0Flag;		
		extern	bit		gfSetAddress;	
		extern	bit		gfOut0Flag;	
//		extern	bit		gfTimer0OverFlow;
		extern  bit		gfTx3Flag;
		extern 	bit 	gfRC2Flag;
		extern 	bit   	gfTx1Flag;


//		extern  bit		gfMSCPowerTest;
		extern  bit		gf0x12;
		extern  bit		gf0x25;	
		extern 	bit		gf0x28;
		extern 	bit		gf0x5a;
		extern 	bit		gf0x1a;
		extern  bit		gfResetFlag;	
//		extern  BYTE  data  gb_person_on_off_2;
		extern	bit		gfResume;
		extern 	bit 	gfFastModeflag;					//Johnny 2006/08/08
//		extern 	bit 	gfTimeoutflag; 					//Johnny 2006/08/08
		extern	bit		gfSuspend;
		extern	bit  	gfTimeOut;
		extern 	bit		gf5VDDFlag;

//		extern  bit 	gfRc2RAMFlag;					//Johnny 2006/08/28 RC XRAM Flag only use in spi write
		extern 	bit		gfTx1RAMFlag;					//Johnny 2006/06/21 TX XRAM Flag
		extern	bit		gfBulkXferDone;	
		extern  bit 	gfInterrptXferDone;
		extern 	bit 	gfEntryGetConfig;
		extern 	bit		gfEntrySuspend;
		extern 	bit		gfMAC;
//		extern 	bit		gfRc4Flag;
#endif



#define FLASH 	1
#define ROM		0


#define _ACTIVE_WINBOND_FLASH_

#define CBW_lenth	(*(DWORD volatile  xdata *)(REG1630_XRAM2+8))
#define CBW_len0   	(*(BYTE  xdata *)(CBW_lenth))
#define CBW_len1  	(*(BYTE  xdata *)(CBW_lenth+1))
#define CBW_len2  	(*(BYTE  xdata *)(CBW_lenth+2))
#define CBW_len3  	(*(BYTE  xdata *)(CBW_lenth+3)) 

#define	INFO_FATaddr		32
#define	INFO_settingaddr	33
#define	INFO_tenxInfo_StartAddress	48		//zp,page no must <256 page,production information
#define	INFO_LCMdata		49

//#define	OEM_Vendor		0x04
#define	OEM_Vendor		    12
//#define	OEM_chargeflag		50
//#define	OEM_MacOffset		51			//ZP
#define	OEM_MacOffset		16			//YUAN
#define	OEM_Win32Offset		8			//YUAN
#define	OEM_CDROMOffset		0			//YUAN
//#define	OEM_flashtype		53
//#define ISO_START	0x00000			//ZP
#define ISO_START	0x00100		//YUAN
//#define ISO_START	0x10000		//YUAN

//#define	PicStartPage		0x500		//NOTE 
#define	PicStartPage		0xc00		//NOTE 





