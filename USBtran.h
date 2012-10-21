#ifndef _USBTRAN_H
#define _USBTRAN_H

// USB standard device request offset 
#define bmRequestType  	0
#define bRequest       	1
#define wValue         	2
#define wValueHi       	3
#define wIndex         	4
#define wIndexHi       	5
#define wLength        	6
#define wLengthHi      	7

// USB SET_CONFIGURATION  configuration value
#define CONFIGURED                      0x01 /* configuration status values */
#define UNCONFIGURED                    0x00       

// USB Bulk-Only device request
#define USB_GET_STATUS                  0x00 /*bRequestTypes*/
#define USB_CLEAR_FEATURE               0x01
#define USB_SET_FEATURE                 0x03
#define USB_SET_ADDRESS                 0x05
#define USB_GET_DESCRIPTOR              0x06
#define USB_SET_DESCRIPTOR              0x07
#define USB_GET_CONFIGURATION        	0x08
#define USB_SET_CONFIGURATION        	0x09
#define USB_GET_INTERFACE              	0x0A
#define USB_SET_INTERFACE              	0x0B
#define USB_SYNCH_FRAME                	0x0C
//#define USB_GET_MAX_LUN					0xfe
//#define USB_BULK_ONLY_RESET				0xff

// USB device request type definition
#define HOST_TO_DEVICE                  	0x00      //0b00000000
#define DEVICE_TO_HOST                  	0x80      //0b10000000
#define STANDARD                        	0x00      //0b00000000
#define CLASS                           	0x20      //0b00100000
#define VENDOR                          	0x40      //0b01000000
#define DEVICE                          	0x00      //0b00000000
#define INTERFACE                       	0x01      //0b00000001
#define ENDPOINT                        	0x02      //0b00000010
#define OTHER                           	0x03      //0b00000011

/* standard descriptor types */
#define USB_DEVICE                      0x01
#define USB_CONFIGURATION               0x02
#define USB_STRING                      0x03
#define USB_INTERFACE                   0x04
#define USB_ENDPOINT                    0x05
//#define USB_DEVICE_QUALIFIER         	0x06
//#define USB_OTHERSPEED_CONFIG       	0x07
#define USB_HidClass					0x21
#define USB_HidReport					0x22


/* standard feature selectors */
#define USB_ENDPOINT_STALL              	0x00 /* recipient endpoint */
#define USB_DEVICE_REMOTE_WAKEUP        	0x01 /* recipient device */
#define USB_TEST_MODE						0x02 /* HS test mode */


// Device status 
#define DEVICE_STATUS_CONFIGURED   	0x30		
#define DEVICE_STATUS_EP4_STALL		0x10
#define DEVICE_STATUS_EP3_STALL		0x08
#define DEVICE_STATUS_EP2_STALL		0x04
#define DEVICE_STATUS_EP1_STALL		0x02
#define DEVICE_STATUS_EP0_STALL		0x01

#define DEVICE_STATUS_ANDMASK_UNCONFIGURED	0xcf
#define DEVICE_STATUS_ANDMASK_EP4_UNSTALL	0xEF
#define DEVICE_STATUS_ANDMASK_EP3_UNSTALL	0xf7
#define DEVICE_STATUS_ANDMASK_EP2_UNSTALL	0xfb
#define DEVICE_STATUS_ANDMASK_EP1_UNSTALL	0xfd
#define DEVICE_STATUS_ANDMASK_EP0_UNSTALL	0xfe

//HID class specific request codes from section 7.2 Class Specific Requests
#define GetReport 	0x01
#define GetIdle 	0x02
#define GetProtocol 0x03

#define SetReport   0x09
#define SetIdle     0x0a
#define SetProtocol 0x0b

#define LedValue    0x02
#define UnConfig	0x00     
#define Config		0x01

//-class specific request codes from section  Class Specific Requests

#define SET_CUR     0x01  
#define SET_MIN     0x02  
#define SET_MAX     0x03  
#define SET_RES     0x04  
#define GET_CUR     0x81  
#define GET_MIN     0x82  
#define GET_MAX     0x83  
#define GET_RES     0x84  

#define USB_GET_MAX_LUN			0xfe
#define USB_BULK_ONLY_RESET		0xff
#define MAX_PACKET_SIZE			0x08

#define USB_RAM0			0x0
#define USB_RAM1			0x1
#define USB_RAM2			0x0
#define USB_RAM3			0x1


void UsbInitialize(void);
void usbBusReset(void);
void Suspend(void);								//Johnny 2006/08/07
void USB_Resume(void);							//Johnny 2006/08/07
void ChangToFastMode(void);						//Johnny 2006/08/08
void initM51CtrlRegs(void);						//Johnny 2006/08/08
void Init_SPIB(void);							//Johnny 2006/08/08
// Endpoint 0 transfer handler function.
//void USB_Resume(void);
void EP0_SetupHandler(void);
//void EP0Out(void);							
void Ep0Out(void);	
// Endpoint 0 helper function.
void EP0_HandleSetup(void);
void EP0_SetupResponse(void);
void EP0_LoadFIFO(void);
void EP0_TransmitSetup(UCHAR ucCount);
//void EP0_Stall(void);
void EP0_Receive_Ready(void);
void EP0SetupTask(void);
//void RC0Task(void);
//void EP0OUT(void);
//void NoDataControl(void);						-Johnny 2006/06/23
//void EmptyPackage(void);
// USB standard request handler
void GetDescriptor(void);
void SetAddress(void);
void GetStatus(void);
void ClearFeature(void);
void SetFeature(void);
void GetConfiguration(void);
void SetConfiguration(void);
void GetInterface(void);
void SetInterface(void);
void NotSupported(void);
void SetRequest(void);
//void GetRequest(void);
void SetupCommand(void);

//USB EP1 
void BULK_EP1Handler(void);								//Johnny 2006/06/16 

//USB EP2 
void BULK_EP2Handler(void);								//Johnny 2005/06/15

//USB EP3 
//void TX3Task(void);

//Timer0 Interrupt
void Tm0iTask(void);
void USB_REQUEST_GetRequest(void);						//Johnny add for HID
void USB_REQUEST_SetRequest(void);						//Johnny add for HID
void PollingUsbCommand(void); 
void  xM_EP0StartXfer(void);

#endif

