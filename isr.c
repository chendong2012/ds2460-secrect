

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
 *     	Handle tmu3112  inrrupt service routine. 
 *
 * DATA STRUCTURES
 *     	None
 *
 * FUNCTIONS
 *		void usbInt0(void)
 *		void USB_Timer1(void)
 *		void usbInt1(void)
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



#define _ISR_C
#include "incfile.h"

//=============================================================================
// Function: void usbInt0(void)
// Purpose: Interrupt 0 service routin
// Input:
// OutPut:
// Author: Johnny 06/15/2006
//=============================================================================
extern unsigned char g_action;
void usbInt0(void) interrupt 0  using 3
{	
	byInt0StatusA = REG1630_INT0A; 
	byInt0StatusB = REG1630_INT0B;

	/*a usb packet finished clear to 0 rdy*/
	/*表示当USB主机取走ep3的数据后，会SIE引发CPU中断到这里
	表示EP3的数据已取走*/
	if(byInt0StatusB & TX3_INT){
		CLR_TX3_RDY;
		CLR_TX3_INT;
		gfInterrptXferDone = 1;
		g_action = 0;
	} 

	/*no handle*/
	if(byInt0StatusB & TX5_INT){
		CLR_TX5_INT;
	}
	
	/*reveive a packet of rc4 from pc*/
	if(byInt0StatusB & RC4_INT){
		CLR_RC4_INT;//now cannot receive packet from rc4
		g_action = 1;//indicate pc send data to xramb ok
	}

	/*no use*/	
	if(byInt0StatusA & TX1_INT){
		CLR_TX1_INT;						//clear TX1_INT
		CLR_TX1_RDY;
		gfTx1Flag = 1;
		gfBulkXferDone = 1;//this flasg for bulk xfer use in Read flash data
//		return;
	} 	
	
	if(byInt0StatusA & RC2_INT){
		CLR_RC2_INT;//clear RC2I interrupt
		gfRC2Flag = 1;
		//return;
	} 

	if(byInt0StatusA & RESET_INT){//USB bus reset
		CLR_RESET_INT;//clear Reset interrupt
		gfResetFlag = 1;
		return;
	} 

	if(byInt0StatusA & SUSPEND_INT){

		CLR_SUSPEND_INT;//clear suspend interrupt
		gfSuspend = 1;   
		return;
	}

	if(byInt0StatusA & RESUME_INT){
		CLR_RESUME_INT;//clear resume interrupt
		USB_Resume();
		return;
	} 

	if(byInt0StatusA & SETUP_INT){//detect setup int
		gbInt0IE |=  SUSPEND_IE;			
		REG1630_INT0_ENA = gbInt0IE;
		CLR_SETUP_INT;//clear setup interrupt
		CLR_OUTI0_INT;//clear OUT0_RDY
		gfRc0Flag = 1;
		return;
	}

	if(byInt0StatusA & TX0_INT){//TX0 interrupt
		CLR_TX0_INT;//write 0 to clear TX0_INT
		CLR_TX0_RDY;//clear TX0_RDY
		bEP0xferDone = 0;//clear TX0 transmit flag in EP0_LoadFIFO funciton
		if(gfSetAddress){	
			REG1630_USB_ADDR =  gbUsbAddr;//gbUsbAddr is stored the address in the last set address Setup.
			gfSetAddress = 0;
			SET_OUT0_RDY;//set OUT0 ready for receive OUT
			return;
        	} else {
			gfTx0Flag = 1;	
			return;
		}
		return;
	}

	if(byInt0StatusA & OUTI0_INT){
		XmtBuff.bLength = 0;
		gfOut0Flag = 1;
		if(DATA1_ZERO_LENGTH){//进入状态阶段,收到为datq1，长度为0，那么为状态阶段
			CLR_TX0_INT;
			REG1630_TX0 = 0;
			XmtBuff.bLength = 0;
		}
		CLR_OUTI0_INT;//clear OUTI0_INT
		CLR_OUT0_RDY;//clear OUT0_RDY
		return;
 	}	
}

//=============================================================================
// Function: void usbInt1(void)
// Purpose: Interrupt 2 service routin,the interrupt source is external interrup
// Input:
// OutPut:
// Author: Johnny 06/15/2006
//=============================================================================
void usbInt1(void) interrupt 2 using 1
{

	byInt1Status =  REG1630_INT1;
//	if(gb_ucPowerDownMode) 
//	{gb_ucPowerDownMode =gb_ucPowerDownMode|byInt1Status;}

	if(byInt1Status&WKTUPI_INT)
	{
		CLR_WKTUPI_INT;
	 
	}
	
	if(byInt1Status & VDD5VRI_INT)							//if 5V exist is flag will be true
	{
		CLR_VDD5VRI_INT;
		gf5VDDFlag = 1;
		
	}
	if(byInt1Status & EXINT0I_INT)							//this interrup use to UART test when this interrup issue set the globle flag to stop UART_RX
	{
		CLR_EXINT0I_INT;	
	//	gfUARTRCstop = 1;

		
	}
	if(byInt1Status & EXINT1I_INT)							//this interrup use to UART test when this interrup issue set the globle flag to stop UART_RX
	{
		CLR_EXINT1I_INT;	
		
	}
	if(byInt1Status & EXINT3I_INT)			//zp
	{
		CLR_EXINT3I_INT;	
		//gb_ucPWRDNCnt = 0;				//press any key,will display 1minutes
				
	}
	if(byInt1Status & EXINT2I_INT)			//zp
	{
		CLR_EXINT2I_INT;	
		//gb_ucPWRDNCnt = 0;				//press touchpad,will display 1minutes
	}
}

//=============================================================================
// Function: void USB_Timer1(void)
// Purpose: Interrupt 3 service routin,the interrupt source is Timer1 interrup
// Input:
// OutPut:
// Author: Johnny 08/15/2006
//=============================================================================

void USB_Timer1(void) interrupt 3 using 2	
{
	TR1 = 0;
//	if(gfFastModeflag || gbModeKey==0 )
	if(gfFastModeflag)
	{	
		TH1 = (65536 - 40000) / 256;						//set timer 20 ms
		TL1 = (65536 - 40000) % 256;						//set timer 20 ms
		if(gfUSBInitEND==0 )
		{
//			gfTimeoutflag=0;							 
			return;	
		} 
		if(gfUSBInitEND)
		{
			gbTimerCnt++;
			if(gbTimerCnt == 0x25)
			{			 	
		//		gfSCSICmdStatus = SCSI_STATUS_MEDIA_CHANGE;	
				gbTimerCnt = 0;
				
			}
			TR1 = 1;										//start timer1		
			return;
		}
		return;				
	}else
	{
		TH1 = (65536 - 450) / 256;							//set timer 900us
		TL1 = (65536 - 450) % 256;							//set timer 900us
		gbTimerCnt++;
		TR1 = 1;											//start timer1	
			
		return;
	}

}





