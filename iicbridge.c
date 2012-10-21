#include "incfile.h"
#include "ds2460.h"

unsigned char g_cmd = 0;
unsigned char g_flag=0;
unsigned char g_action=0;
unsigned char g_fifo5 = 0;
unsigned char g_fifo4 = 0;		

void SetTx3Transfer(unsigned char data_length)
{
	unsigned char ucToggle;	
	REG1630_TX3_CNT = data_length;
	ucToggle = REG1630_TX3;
	ucToggle^=EP3_TGL;
	REG1630_TX3 = ucToggle;
		
	SET_TX3_RDY;
}

void INTERRUPT_EP0Handler()
{
	  switch (REG1630_OUT0_FIFO[7]) {
	  	case USB_READ_DS2460_CMD:
			g_cmd = USB_READ_DS2460_CMD;
	  		g_flag = REG1630_OUT0_FIFO[6];
			g_fifo5	= REG1630_OUT0_FIFO[5];
			g_fifo4 = REG1630_OUT0_FIFO[4];		
			g_action = 1;
			return;
			   	
		case USB_WRITE_DS2460_CMD:
			g_cmd = USB_WRITE_DS2460_CMD;
			g_flag = REG1630_OUT0_FIFO[6];
			g_action = 0;

			SET_XRAMBUSB;  
			SET_RC4_RDY;//now can receive data from rc4		
			return;

		default:
			 return;	  
	   } 
}

/*
 *ok 1
 *fail 0
 * */
static unsigned char usb_readds2460_handle(void)
{
/*完成：首先是分析读到的命令字，然后操作*/
	unsigned char *buf;
	unsigned char ret = 0;
	if (g_cmd != USB_READ_DS2460_CMD) {
		 return ret;
	}

	CLR_XRAMAUSB;

	switch (g_flag) {
		case 0x01://read rom id
			
			buf = REG1630_XRAMA+2;
			ret = DS2460_ReadSerialNumber(buf, 8);
			if (ret) {
				REG1630_XRAMA[0]=8;
				REG1630_XRAMA[1]=1;
			} else {
				REG1630_XRAMA[0]=0;
				REG1630_XRAMA[1]=0;				
			}	
			break;

		case 0x02://read mac code
			buf = REG1630_XRAMA+2;
			ret = DS2460_ReadMAC(buf, 20);
			if (ret) {
				  REG1630_XRAMA[0]=20;
				  REG1630_XRAMA[1]=1;
			} else {

				  REG1630_XRAMA[0]=0;
				  REG1630_XRAMA[1]=0;							
			}			
			break;

		case 0x03://read input buffer data
			buf = REG1630_XRAMA+2;
			ret = DS2460_ReadInputSHA(buf, 55);	
			if (ret) {
				  REG1630_XRAMA[0]=55;
				  REG1630_XRAMA[1]=1;
			} else {

				  REG1630_XRAMA[0]=0;
				  REG1630_XRAMA[1]=0;							
			}		
			break;
	   case 0x04:
	   		buf = REG1630_XRAMA+2;
	   		ret = DS2460_ReadEeprom(g_fifo5, buf, g_fifo4);
			if (ret) {
				  REG1630_XRAMA[0]=g_fifo4;
				  REG1630_XRAMA[1]=1;
			} else {

				  REG1630_XRAMA[0]=0;
				  REG1630_XRAMA[1]=0;							
			}		
			break;
		default:
			break;
	}
	SetTx3Transfer(64);
	SET_XRAMAUSB;

	return ret;
}

static unsigned char usb_writeds2460_handle(void)
{
	char ret=0;
	if (g_cmd != USB_WRITE_DS2460_CMD) {
		 return ret;
	}

	CLR_RC4_RDY;
	CLR_XRAMBUSB;
 	switch (g_flag) {
		case 0x01:
			ret = DS2460_WriteInputSHA(&REG1630_XRAMB[1], REG1630_XRAMB[0]);
			break;

		case 0x02:
			ret = DS2460_WriteSSecret(REG1630_XRAMB,8);
			break;

		case 0x03:
			ret = DS2460_WriteESecret1(REG1630_XRAMB,8);
			break;

		case 0x04:
			ret = DS2460_WriteESecret2(REG1630_XRAMB,8);
			break;

		case 0x05:
			ret = DS2460_WriteESecret3(REG1630_XRAMB,8);
			break;
/////
		case 0x06:
			ret = DS2460_ComputeSHA(0, REG1630_XRAMB[0], REG1630_XRAMB[1]);
			break;

	    case 0x07:
			ret = DS2460_TransferSecret(REG1630_XRAMB[0]);
			break;

		case 0x08:
			ret = DS2460_MatchMAC(REG1630_XRAMB,20);
			break;

		case 0x09:
             ret = DS2460_WriteEEPROM(REG1630_XRAMB[0], &REG1630_XRAMB[2], REG1630_XRAMB[1]);
			break;

//定制		
		case 0xFE:
			ret = DS2460_WriteInputSHA_Custom(REG1630_XRAMB);
			break;

		default:
			break;
	}
//	SET_XRAMBUSB; ////////????
	CLR_XRAMAUSB;//important!!!
	if (ret == 0) {
		REG1630_XRAMA[0] = 0x00;
	} else {
		REG1630_XRAMA[0] = 0x01;		
	}
	SET_XRAMAUSB;//important!!!		
	SetTx3Transfer(64);
	return 0;
}

void usb_ds2460_loop(void)
{
	if ( g_action == 0) {
		return;
	}
	g_action = 0;
	usb_readds2460_handle();
	usb_writeds2460_handle();
}