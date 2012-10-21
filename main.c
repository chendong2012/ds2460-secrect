/***************************************************************************
 *                                                                         	*
 * Copyright (c) 2006 tenx technology, Inc. All Rights Reserved.			*	
 *                                                                         	*
 ***************************************************************************/

/****************************************************************************
 *
 * FILENAME
 *     	ISR.c
 *
 * VERSION
 *     	1.0
 *
 * DESCRIPTION
 *     	Tmu3112  AutoRun USB mass storage main program 
 *
 * DATA STRUCTURES
 *     	void initM51CtrlRegs(void)
 * 		
 *
 * FUNCTIONS
 *		void usbInt0(void)
 * 		void Suspend(void)
 * 		void usbBusReset(void)
 * 		void Init_SPIB(void)
 *		void ChangToFastMode(void)
 *		void Init_SPIB(void)
 * 		void main(void)
 * 		void PollingUsbCommand(void)
 *			
 *		 		
 * MACRO
 *		none	
 *
 * HISTORY
 *     	07/07/06		 Ver 1.0 Modify by Johnny
 *
 * 
 **************************************************************************/

#define MAIN_C
//#define SPI
#include "incfile.h"

#include "iicbridge.h"
#include "iic.h"
#include "DS2460.h"
sbit myp30=P3^0;
sbit myp31=P3^1;
sbit myp34=P3^4;


void initM51CtrlRegs(void)
{
	IE = 0;
	TMOD = 0x11;		// Set Timer 0 Timer1 to mode 1 
	IT1 = 0;		// Low level trigger.
	TH1 = (65536 - 450) / 256;
	TL1 = (65536 - 450) % 256;
	IP = 0x05;		// INT0/1 high priority.
	IE = 0x85;		// INT0/1/ enable
}
void Delay800us()
{
	unsigned char i;
	for (i=0; i<255; i++);                //Software loop for time delay
	for (i=0; i<255; i++);                //Software loop for time delay
	for (i=0; i<255; i++);                //Software loop for time delay

}

//=============================================================================
// Function: void ChangToFastMode(void)
// Purpose: Use to in dual mode (RC mode / Fast mode) change tmu3112 clock to fast mode 
// Input:
// OutPut:
// Author: Johnny 06/28/2006
//=============================================================================
void ChangToFastMode(void)
{ 
	gfFastModeflag = 1;
	SET_FCLK_EN; 
	Delay800us(); 			
	ET1 = 1;									//enable Timer1 interrupt
	TR1 = 1;									//timer1 start counter
	SET_CKFAST;	   

} 
	
//==============================================================================
// Function: pollingUsbCommand(void)
// purpose: check & process USB Command
// Update:   2006/06/14 Johnny
//==============================================================================
void PollingUsbCommand(void)
{
	usb_ds2460_loop();
	/*use receive ep0 hid command from pc.this is Ep0Out()*/
	if(gfOut0Flag == 1) {
		gfOut0Flag = 0;
		Ep0Out();	
		SET_OUT0_RDY; //YUAN
	}

	/*this is for usb setup communication*/
	if(gfRc0Flag == 1) {
		gfRc0Flag = 0;
		EP0SetupTask();
		SET_OUT0_RDY; //YUAN
	} 
	
	/*this is for tx0 send finish, and this is for result report*/
	if(gfTx0Flag == 1) {
		gfTx0Flag = 0;
		/*why loadfifo:when need more 8bytes,need loadfifo and send to 
 		pc.*/
		EP0_LoadFIFO();
		SET_OUT0_RDY;
	}
	
	/*this is for suspend handle*/
	if(gfSuspend == 1) {
		Suspend();
	}

	/*this is for 5v detect handle*/
	if(gf5VDDFlag == 1) {
		gf5VDDFlag =0;

		initM51CtrlRegs();
		usbBusReset();	
	}

	/*this is for reset handle*/
	if(gfResetFlag == 1) {
		gfResetFlag = 0;
		usbBusReset();
	}

}

//==============================================================================
// Function: USB_Resume(void)
// purpose:  do TMU3112 resume  
// Update:   2006/08/17 Johnny
//==============================================================================

void USB_Resume(void)
{
	gfSuspend = 0;
	CLR_RESUME_INT;
	CLR_SUSPEND_INT;
	gbInt0IE |= (SETUP_IE | TX0_IE |TX1_IE|RC2_IE|RESET_IE|OUTI0_IE|TX1_IE|SUSPEND_IE); //enable EP0 SETUP,TX0_IE,RESET_IE
 	gbInt1IE = (VDD5VRIE_INT|EXINT0IE|WKTUPIE);							//Johnny 2006/08/17 add extern interrupt1
	CLR_SUSPEND_MODE;
	REG1630_INT0_ENA = gbInt0IE;
	REG1630_INT1_EN = gbInt1IE; //Johnny 06.12.04:add recover INT1 status


//	REG1630_PC_GPIO_CON_AC = 0xf0;		//MUST SET PC0 HIGH FIRST
//	REG1630_PC_GPIO_9C = 0x0f;			//blue LED ON,POWER ON ,0xff  
	
//	REG1630_PA_GPIO_9A = 0xf6;//0xff;8.9 PA4 =0, FOR SET USB VDD ON PA3 =1 CHARGE ENABLE
//    Init_SPIB();
	REG1630_INT0A = 0;											//clear interrupt 0
	REG1630_INT0B = 0;											//clear interrupt 0
	REG1630_INT1 = 0;											//clear interrupt 1
	REG1630_RC0 = 0;
	REG1630_TX0 = 0;
	REG1630_TX1 = 0;
	REG1630_RC2 = 0;
	REG1630_TX3	= 0;
	REG1630_RC4	= 0;
	REG1630_TX5	= 0;
	gfResume = 1;		  
	
}

//==============================================================================
// Function: Suspend(void)
// purpose: let TMU3112 into suspend mode
// Update:   2006/08/17 Johnny
//==============================================================================
void Suspend(void)				
{

	if(gfUSBInitEND ==1)		// 0319version
	{
////		REG1630_PB_GPIO_CON_AB = 0xff;//0xff;
////		REG1630_PB_GPIO_9B = 0x00;
////		REG1630_PC_GPIO_CON_AC = 0xf0;		//PC4,PC5->GPIO
////	    REG1630_PWM_CTRL =0x00;        //close PWMA
////		REG1630_PC_GPIO_9C = 0x00;			//0x08,EL OFF PC0= 0,SVDD=0,PC2=0 PC6=PC7=pc1=0 SAVE POWER
		
////		REG1630_PA_GPIO_CON_AA = 0xff;		//zp 1029version, for PA5 -DP FLOATING
		
////	   	REG1630_PA_GPIO_9A = 0x04;		//0xf6,PA3=0,DISABLE CHARGE
		//P1=0x00;   //yuan add test		

		gbInt0IE = (RESET_IE|RESUME_IE);
		REG1630_INT0_ENA = gbInt0IE;
		REG1630_INT1_EN = 0; 			// must be 0,if open wakeup,only sleep 0.5s.so  suspend clock stop.
		
		SET_SUSPEND_MODE; //force USB interface into suspend mode

		SET_PWR_DN; //Into suspend mode
		gfUSBInitEND = 0;
	}
}

//=============================================================================
// Function: void usbBusReset(void)
// Purpose: Reset USB Bus & clear some h/w register
//			need enable EP0 setup/Reset/Tx0 interrupt
// Input:
// OutPut:
// Author: Johnny 07/28/2006
//=============================================================================
void usbBusReset(void)
{
//0x1f01
	REG1630_INT0A = 0;											//clear interrupt 0
//0x1f0b
	REG1630_INT0B = 0;											//clear interrupt 0
//above is usb interrupt register

//0x1f81
	REG1630_INT1 = 0;											//clear interrupt 1
//above is 5v spi_slave uart wakeuptimer pc3~0 interrupte reg

//0x1f03	
	REG1630_PWR_CTRL = 0;										//clear power control register

//0x1f00
	REG1630_USB_ADDR = 0;										//clear usb device address

//0x1f90
	REG1630_PWM_CTRL = 0;										//disable PWM function

//0x1f04\5		
	REG1630_RC0 = 0;
	REG1630_TX0 = 0;

//0x1f06
	REG1630_TX1 = 0;

//0x1f07
	REG1630_RC2 = 0;

//0x1f0d
	REG1630_TX3	= 0;

//0x1f0e
	REG1630_RC4	= 0;

//0x1f0a
	REG1630_TX5	= 0;
	

	byUSBAddr = 0;		//5-23
	gfSuspend = 0;

	gbInt0IE = (SETUP_IE | TX0_IE | TX1_IE | RC2_IE| RESET_IE | OUTI0_IE | SUSPEND_IE); //enable EP0 SETUP,TX0_IE,RESET_IE
	REG1630_INT0_ENA = gbInt0IE;
	gbInt1IE = (VDD5VRIE_INT);//|WKTUPIE);							//Johnny 2006/08/17 add extern interrupt1
	REG1630_INT1_EN = gbInt1IE; 								//Johnny 2006/08/07 

	gfTx1RAMFlag =  USB_RAM0;									//init TX Ram flag to RAM0 use to write data tx to pc  
	SET_EP1_CFG;
	SET_RC2_CFG;
	SET_EP3_CFG;
// assign xram1 xram2 to tx1 rc2
	REG1630_XRAM_CTRL = 0x60;

////    REG1630_PA_GPIO_9A &= 0xff;		 							//0xff set PA3 to high charge BAT

	gfFastModeflag = 0;											//Johnny 2006/08/08
	gfFastModeflag =1;  //update by yuan 2008-11-14
	gbTimerCnt = 0;												//Johnny 2006/08/08
	gfUSBInitEND = 0;	//????????								//Johnny 2006/08/10 
	//Init_SPIB();
//	gfFlashIDDataValid = 0;	
//	gfFlashSTRDataValid = 0;
//	ToDetectFlashValid();		// 1029version for serial no string
	gfUSEinitGetDescriptor = 0;	

	gfTestunitcnt = 0;											//Johnny:test unit ready counter

	ucHIDstatus=0;
	gfEntryGetConfig=0;
//	gfMSCPowerTest = 0;

}  
//-----------------------------------------------------
//-----------------------------------------------------		
void PowerOn_sub(void)
{	
////	REG1630_PC_GPIO_CON_AC = 0xf0;		//MUST SET PC0 HIGH FIRST
////	REG1630_PC_GPIO_9C = 0x0f;			//blue LED ON,POWER ON   PC6=PC7=0 SAVE POWER
////	REG1630_PA_GPIO_CON_AA = 0xff;		//PA=GPIO ,0xdf
////	REG1630_PA_GPIO_9A = 0xf6;			//PA3 LOW,PA0 LOW,
	REG1630_INT0_ENA = gbInt0IE=0;					//disable all USB interrupt
	gbInt1IE =(VDD5VRIE_INT);//|WKTUPIE);		//enable 0.5s ,KEY,Touchpad interrupt
	REG1630_INT1_EN = gbInt1IE; 		
}
 sbit re=P1^0;
//char code dx516[3] _at_ 0x003b;//注意在烧写到IC里，要把这句话去掉
void main(void)
{
	initM51CtrlRegs();			
	ChangToFastMode();
	PowerOn_sub();
	usbBusReset();	 			
	ET1 = 0;							//disable timer0 intrrupt 	
	TR1 = 0;							//timer 0 stop				
	gfFastModeflag = 1;
//	ToDetectFlashValid();
	SET_VIO_50;
	IIC_Init();
	//	   re = 1;
	//	   re = 0;
	//	   re = 1;
	//	   re = 0;
	SET_GPIO_PC7;
	REG1630_PB_GPIO_CON_AB = 0xff;
	REG1630_PB_GPIO_9B = 0xff;

//CLR_PC3;

	while(REG1630_USB_PLUG_OUT & VDD5V_EXIST_FLG)
	{
		PollingUsbCommand();
	}
}
