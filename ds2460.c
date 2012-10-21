#include "ds2460.h"
#include "iic.h"
/////////////////////////////////////
#define DS2460_ADDR 0x80

static unsigned char I2CBus_write(unsigned char *txBytes, unsigned char len);
static unsigned char I2CBus_packetRead(unsigned char memAddr, unsigned char *rxBytes, unsigned char len);
static unsigned char I2CBus_packetWrite(unsigned char memAddr, unsigned char *buffer, unsigned char len);
static unsigned char send_header(unsigned char memAddr);

static void msDelay(unsigned char ti)
{
	unsigned char i,j;
	for (i=0; i < 255; i++) {
		for (j = 0; j < ti; j++);
	}
}

unsigned char DS2460_ReadSerialNumber(unsigned char* buffer, unsigned char len)
{
   return I2CBus_packetRead(DS2460_MEM_SERIAL, buffer, len);
}

unsigned char DS2460_WriteInputSHA(unsigned char *buffer, unsigned char len)
{
   return I2CBus_packetWrite(DS2460_MEM_SHA, buffer, len);
}


unsigned char DS2460_ReadInputSHA(unsigned char* buffer, unsigned char len)
{
   return I2CBus_packetRead(DS2460_MEM_SHA, buffer, len);
}

unsigned char DS2460_ReadEeprom(unsigned char addr, unsigned char* buffer, unsigned char len)
{
	if (addr < 0x80 || addr > 0xef || (addr+len) > 0xf0) {
		return 0;
	}
/*
	if (addr & 0x07) {
		return 0;
	}
*/
   return I2CBus_packetRead(addr, buffer, len);
}




// gpSHA - 0 for dallas SHA or 1 for general purpose SHA
// srcSecret - 0, 1, 2, or 3 for SSecret, ESecret1, ESecret2, or ESecret3
// toMACBuffer - 0 to put MAC in SSecret or 1 to put MAC in buffer
unsigned char DS2460_ComputeSHA(unsigned char gpSHA, unsigned char srcSecret, unsigned char toMACBuffer)
{
   unsigned char success = 0;
   // address for command buffer, compute command
   unsigned char buffer[] = {DS2460_MEM_CMD, DS2460_CMD_COMPUTE};
   //printf("Compute SHA: gpSHA=%01X, srcSecret=%01X, toMACBuffer=%01X\n",
   //   (int)gpSHA, (int)srcSecret, (int)toMACBuffer);
   if(gpSHA)
      buffer[1] |= 0x20;
   buffer[1] |= (srcSecret<<3);
   if(toMACBuffer)
      buffer[1] |= 0x04;
   // **** **** **** **** **** **** **** **** **** **** **** **** **** 
   // bug fix in emulator (used 0x02 instead of 0x04 for output to MAC)
//   if(toMACBuffer)
//      buffer[1] |= 0x02;
   // **** **** **** **** **** **** **** **** **** **** **** **** **** 
   success = I2CBus_write(buffer, 2);
   msDelay(100);
   return success;
}

unsigned char DS2460_MatchMAC(unsigned char* buffer, unsigned char len)
{
   return I2CBus_packetWrite(DS2460_MEM_MATCHMAC, buffer, len);
}

unsigned char DS2460_ReadMAC(unsigned char* buffer, unsigned char len)
{
   return I2CBus_packetRead(DS2460_MEM_MAC, buffer, len);
}
/*
unsigned char DS2460_WriteMAC(unsigned char* buffer, unsigned char len)
{
   return I2CBus_packetWrite(DS2460_MEM_MAC, buffer, len);
}
*/
// dstSecret - 1, 2, or 3 for ESecret1, ESecret2, or ESecret3
unsigned char DS2460_TransferSecret(unsigned char dstSecret)
{
   unsigned char success = 1;
   // address for command buffer, transfer command
   unsigned char buffer[] = {DS2460_MEM_CMD, DS2460_CMD_TXSECRET};
   buffer[1] |= (dstSecret<<4);
   success = I2CBus_write(buffer, 2);
   msDelay(100);
   return success;
}

unsigned char DS2460_WriteSSecret(unsigned char* buffer, unsigned char len)
{
   return I2CBus_packetWrite(DS2460_MEM_SSECRET, buffer, len);
}

unsigned char DS2460_WriteESecret1(unsigned char* buffer, unsigned char len)
{
   return I2CBus_packetWrite(DS2460_MEM_ESECRET1, buffer, len);
}

unsigned char DS2460_WriteESecret2(unsigned char* buffer, unsigned char len)
{
   return I2CBus_packetWrite(DS2460_MEM_ESECRET2, buffer, len);
}

unsigned char DS2460_WriteESecret3(unsigned char* buffer, unsigned char len)
{
   return I2CBus_packetWrite(DS2460_MEM_ESECRET3, buffer, len);
}

/*addr 不能大于EF*/
unsigned char DS2460_WriteEEPROM(unsigned char addr, unsigned char* buffer, unsigned char len)
{
	if (addr < 0x80 || addr > 0xef || (addr+len) > 0xf0) {
		return 0;
	}
/*
	if (addr & 0x07) {
		return 0;
	}
*/
	return I2CBus_packetWrite(addr, buffer, len);
}

/*
把MAC读出来，然后再写到SHA输入缓冲里去，进行一下步的运算
*/
unsigned char DS2460_WriteInputSHA_Custom(unsigned char* buffer)
{
	idata char buf[64];
	unsigned char ret=0;
	unsigned char i=0;
	for (i = 0; i < 64; i++) {
		buf[i] = 0;
	}

	for (i = 0; i < buffer[0]; i++) {
		buf[i] = buffer[i+1];
	}

	ret = DS2460_ReadMAC(buf, 20);	
	if (ret == 1) {
		return DS2460_WriteInputSHA(buf, 64);
	} else {
		return 0;	
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////
/*
*desc: write device address and register addr(8 bits addr or 16 bits addr)
*
*0.send start iic flag
*1.send device address to iic device
*2.send device register address
*3.if transfer success will not issue stop command
*/
static unsigned char send_header(unsigned char memAddr)
{
	IIC_Start();

	/*send device address to iic device*/
	IIC_SendByte(DS2460_ADDR);

	if (IIC_ChkAck())
		goto err1;

	/*send device register address*/
	IIC_SendByte(memAddr);//low 8 bits
	if (IIC_ChkAck())
		goto err1;
	return EEPROM_RDWR_OK;

err1:
	IIC_Stop();
	return EEPROM_ACK_ERR;	
}

static unsigned char I2CBus_packetWrite(unsigned char memAddr, unsigned char *buffer, unsigned char len)
{
	send_header(memAddr);

//send buffer content
	if (IIC_SendBytes(buffer, len) == EEPROM_ACK_ERR)
		return EEPROM_ACK_ERR;
//ok
	IIC_Stop();
	msDelay(10);
	return EEPROM_RDWR_OK;
}

static unsigned char I2CBus_packetRead(unsigned char memAddr, unsigned char *rxBytes, unsigned char len)
{
	/*send register addr to device*/
	send_header(memAddr);

	// Repeated Start
	IIC_RepeatedStart();

        // Device hardware address
        IIC_SendByte(DS2460_ADDR | 0x01);
        if (IIC_ChkAck()) {
		IIC_Stop();
		return EEPROM_ACK_ERR;
        }

	if (IIC_ReadBytes(rxBytes, len) == EEPROM_ACK_ERR)
		return EEPROM_ACK_ERR;
	//ok
	IIC_Stop();
	msDelay(1);
	return EEPROM_RDWR_OK;
}

/*
 *only send txBytes Buffer datas into device.
 *send start-->device address --> send txBytes-->stop
 *
 */
static unsigned char I2CBus_write(unsigned char* txBytes, unsigned char len)
{

	IIC_Start();

	/*send device address to iic device*/
	IIC_SendByte(DS2460_ADDR);

	if (IIC_ChkAck()) {
		IIC_Stop();
		return EEPROM_ACK_ERR;
	}

	if (IIC_SendBytes(txBytes, len) == EEPROM_ACK_ERR)
		return EEPROM_ACK_ERR;
	IIC_Stop();
	msDelay(2);
	return EEPROM_RDWR_OK;
}






