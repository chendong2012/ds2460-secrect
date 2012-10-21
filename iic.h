#ifndef __IIC__H__
#define __IIC__H__

#define EEPROM_ACK_ERR		0x00
#define EEPROM_RDWR_OK		0x01
#define EEPROM_HEAD_ERR		0xFC

extern void IIC_Init(void);
extern void IIC_Start(void);
extern void IIC_Stop (void);
extern void IIC_RepeatedStart(void);
extern void IIC_OneClk(void);
extern void IIC_SendByte(unsigned char sData);
extern unsigned char IIC_SendBytes(unsigned char *pData, unsigned char len);
extern unsigned char IIC_ReadBytes(unsigned char *pData, unsigned char len);
extern unsigned char IIC_ChkAck(void);
extern unsigned char IIC_ReadByteACK(void);
extern unsigned char IIC_ReadByteNCK(void);

#endif
