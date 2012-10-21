#define INT_bCBWSIGNATURE		0x55534243
#define INT_SECTOR_ERASE		0xf1	//zp
#define	INT_SECTOR4K_ERASE	0xf2	//zp
#define INT_READ_DATA_BY_SECTOR	0xf3	//zp
#define	INT_WRITE_DATA			0xf4	//zp
#define INT_GET_STATUS          0xf5

#define INT_CBW_OPERATION_CODE	6

#define VIDPID 0X11306807	
void Do_tenxIdentifyCheck(void); 
void INTERRUPT_EP0Handler(void);
void ReadBySector(DWORD tempSectorAddr);
void WriteBySector(void);
void EraseBySector(DWORD tempADDR);
void SetTx3Transfer(unsigned char);	
void EraseBySector4K(DWORD tempADDR);
void SpiSectorErase(void);
void WriteDATA_TO_flash(void);
void ReadDATA_FROM_FLASH(void);	
void SetDeviceStatus(void);
void Status_to_AP(void);
unsigned char  PollingSPIBusy(void);
void Delay800us(void);


							 
