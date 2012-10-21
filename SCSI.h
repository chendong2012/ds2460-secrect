//#ifndef _SCSI_H
//#define _SCSI_H

// Format command definition
#define SCSICMD_FORMAT_FACTORY			0
#define SCSICMD_FORMAT_USER_COMPLETE	1
#define SCSICMD_FORMAT_USER_LOWLEVEL	2
#define SCSICMD_FORMAT_ADMIN			3

#define SCSICMD_ERASE_LBA 		0
#define SCSICMD_ERASE_ALL 		1
		// Webkey03_01
#define WEBKEY_DATA_LENGTH  0x5000					
#define VENDOR_NAME_LENGTH  8
#define PASSWORD_LENGTH     8
#define WEB_ADDRESS_LENGTH  64


//extern idata UCHAR g_ucWritePhysicalOption;
extern bit g_bReadPhysical, g_bUN0Start, g_bUN1Start, g_bUN2Start;

///extern idata DWORD g_dwTemp1, g_dwTemp2;



#ifdef _SCSI_C
uint8 skeybuffer;
uint8  ascbuffer;
uint8  ascqbuffer;
uint8  errorflag;
//idata UCHAR g_ucWritePhysicalOption;
data UCHAR g_ucLUN;

BYTE 	bdata gfscsistatus1;

			sbit g_bLun1MediumChanged = gfscsistatus1^7;
			sbit g_bLun0MediumChanged = gfscsistatus1^6;
			sbit g_bNotReady = gfscsistatus1^5;
			sbit g_bCDROMEnable = gfscsistatus1^4;
			sbit g_bCDROM2k = gfscsistatus1^3;
			sbit g_bCDBoot = gfscsistatus1^2;
			sbit g_bWriteProtect = gfscsistatus1^1;
			sbit g_bNextIsSuspend = gfscsistatus1^0;

BYTE 	bdata gfscsistatus2;
			sbit g_bNormalMode = gfscsistatus2^7;
			sbit g_bTestLED = gfscsistatus2^6;
			sbit g_bReadPhysical = gfscsistatus2^5;
			sbit g_bUN0Start = gfscsistatus2^4;
			sbit g_bUN1Start = gfscsistatus2^3;
			sbit g_bUN2Start = gfscsistatus2^2;
			sbit g_bCDROMLUN = gfscsistatus2^1;
			sbit g_bSetRemovable = gfscsistatus2^0;

			
data 	UCHAR g_ucCDROMStart;
//data 	DWORD g_dwCDROMStartSector = 0;
idata 	UCHAR g_ucCDROMLun;
//WORD 	idata BulkSetCnt; 
//WORD	idata	bulkinbyte;


//#endif

#else
extern uint8  skeybuffer;
extern uint8  ascbuffer;
extern uint8  ascqbuffer;
extern uint8  errorflag;
//extern idata UCHAR g_ucWritePhysicalOption;
extern data UCHAR g_ucLUN;
//extern idata BulkSetCnt;
//extern xdata bulkinbyte;

extern BYTE  volatile data gfscsistatus1;
			extern bit g_bLun1MediumChanged;
			extern bit g_bLun0MediumChanged;
			extern bit g_bNotReady;
			extern bit g_bCDROMEnable;
			extern bit g_bCDROM2k;
			extern bit g_bCDBoot;
			extern bit g_bWriteProtect;
			extern bit g_bNextIsSuspend;

extern BYTE volatile data gfscsistatus2;
			extern bit g_bNormalMode7;
			extern bit g_bTestLED6;
			extern bit g_bReadPhysical;
			extern bit g_bUN0Start;
			extern bit g_bUN1Start;
			extern bit g_bUN2Start;
			extern bit g_bCDROMLUN;
			extern bit g_bSetRemovable;


extern data UCHAR g_ucCDROMStart;
//extern data DWORD g_dwCDROMStartSector;
extern idata 	UCHAR g_ucCDROMLun;
//extern BYTE	ucOemInquireData[28];
//extern code ucVerdorIdenStr[7];

#endif

void SetOEMInquiryData();
bit IsCDROMLUN();
bit IsLUNStart();
//void SCSICMD_Write10(void);
void SCSICMD_Read10(void);
//void SCSICMD_Read10_ICE25P05(void);
//void SCSICMD_Read10_WINBOND25P16(void);
void SCSICMD_ReadCapacity(void);
void SetTx1Transfer(unsigned char ucLength);
//void SCSICMD_RWInit(void);
//void SCSICMD_ModeSense(void);
unsigned char SCSICMD_ModeSense(void);
void SCSICMD_TestUnitReady(void);
void SCSICMD_GetTENXInfo(void);
void SCSICMD_23(void);
void SCSICMD_ReadTOC(void);
void SCSICMD_PreventAMR(void);							//Johnny:06/12/20 
void SCSICMD_RequestSense(void);
//void CMD_Inquiry();
void SET_SCSI_ERR_INVALID_COMM_OP_CODE();
void SET_SCSI_ERR_MEDIUM_NOT_PRESENT();
void SET_SCSI_ERR_INVALID_FIELD_IN_CDB();
void SET_SCSI_MEDIA_CHANGE();
//void setstall();

void copy_data_x2data_sp(unsigned char xdata *target,unsigned char *source,BYTE length); 
void copy_data_x2xb_sp(unsigned char xdata *target,unsigned char xdata *source,BYTE length); //from Jacky by Johnny add
void copy_code2xdata(BYTE xdata *target,BYTE code *source,BYTE length); //from Jacky by Johnny add
void setXramData(unsigned char xRamHiAddress, unsigned char ucSetData, unsigned char ucCount);

#define SCSI_INVALID_COMMMAND_CODE					0x13
#define	SCSI_INVALID_FIELD_IN_COMMMAND_PACKET		0x15
#define SCSI_STATUS_MEDIA_CHANGE					0x1b
#define SCSI_STATUS_NO_MEDIA						0x21

 
