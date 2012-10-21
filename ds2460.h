#ifndef __DS2460_H__
#define __DS2460_H__
#define DS2460_MEM_SHA      0x00
#define DS2460_MEM_MAC      0x40
#define DS2460_MEM_SSECRET  0x54
#define DS2460_MEM_CMD      0x5C
#define DS2460_MEM_MATCHMAC 0x5E
#define DS2460_MEM_ESECRET1 0x60
#define DS2460_MEM_ESECRET2 0x68
#define DS2460_MEM_ESECRET3 0x70
#define DS2460_MEM_EEPROM   0x80
#define DS2460_MEM_SERIAL   0xF0
#define DS2460_CMD_COMPUTE  0x80
#define DS2460_CMD_TXSECRET 0x40

unsigned char DS2460_ReadSerialNumber(unsigned char* buffer, unsigned char len);
unsigned char DS2460_WriteInputSHA(unsigned char* buffer, unsigned char len);
unsigned char DS2460_ReadInputSHA(unsigned char* buffer, unsigned char len);
unsigned char DS2460_ComputeSHA(unsigned char gpSHA,unsigned char srcSecret,unsigned char toMACBuffer);
unsigned char DS2460_MatchMAC(unsigned char* buffer, unsigned char len);
unsigned char DS2460_ReadMAC(unsigned char* buffer, unsigned char len);
//unsigned char DS2460_WriteMAC(unsigned char* buffer, unsigned char len);
unsigned char DS2460_TransferSecret(unsigned char dstSecret);
unsigned char DS2460_WriteSSecret(unsigned char* buffer, unsigned char len);
unsigned char DS2460_WriteESecret1(unsigned char* buffer, unsigned char len);
unsigned char DS2460_WriteESecret2(unsigned char* buffer, unsigned char len);
unsigned char DS2460_WriteESecret3(unsigned char* buffer, unsigned char len);
unsigned char DS2460_WriteInputSHA_Custom(unsigned char *buffer);


/*addr 不能大于EF*/
unsigned char DS2460_WriteEEPROM(unsigned char addr, unsigned char* buffer, unsigned char len);

unsigned char DS2460_ReadEeprom(unsigned char addr, unsigned char* buffer, unsigned char len);







#define USB_READ_DS2460_CMD 0XBB
#define USB_WRITE_DS2460_CMD 0XBD



#endif
