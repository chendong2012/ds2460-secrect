#ifndef _TYPEDEF_H
#define _TYPEDEF_H

typedef unsigned char UCHAR;
typedef unsigned char BYTE;
typedef unsigned char uint8;
typedef unsigned int WORD;
typedef unsigned int uint16;
typedef unsigned long ULONG;
typedef unsigned long DWORD;
typedef bit FLAG;

typedef struct _XMT_BUF{  	
	BYTE bLength;		//Length of data remaining to be returned		
	BYTE *p;				//Pointer to the data
}XMT;						//EP0 transmit buffer parameters


typedef struct	_TCMD_FORMAT{
	
	BYTE	bDeviceSet;		//device set
	WORD	wdDataLen;		//data length
	BYTE	bDataType;		//data tpye
	BYTE	bCustormerType;	//cust

}TCMD;
#endif

