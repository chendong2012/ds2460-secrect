

#define BIT0                  		0x01
#define BIT1                  		0x02
#define BIT2                  		0x04
#define BIT3                  		0x08
#define BIT4                  		0x10
#define BIT5                  		0x20
#define BIT6                  		0x40
#define BIT7                  		0x80

#define XRAM0_HI					0x10	
#define XRAM1_HI					0x11
#define XRAM2_HI					0x12
#define XRAM3_HI					0x13
#define XRAMA_HI					0x14
#define XRAMB_HI					0x15

#define TX1630REG_BASE 				0x1f00
#define TMU3112REG_BASE 			0x1f00
#define REG1630_XRAM0				((BYTE volatile xdata *)0x1000 )	//64 Bytes
#define REG1630_XRAM1				((BYTE volatile xdata *)0x1100 )	//64 bytes	
#define REG1630_XRAM2				((BYTE volatile xdata *)0x1200 )	//64 bytes
#define REG1630_XRAM3				((BYTE volatile xdata *)0x1300 )	//64 bytes
#define REG1630_XRAMA				((BYTE volatile xdata *)0x1400 )	//64 bytes
#define REG1630_XRAMB				((BYTE volatile xdata *)0x1500 )	//64 bytes
#define	REG1630_SET0_FIFO			((BYTE volatile xdata *)0x1f20 )	//8 Bytes
#define REG1630_OUT0_FIFO			((BYTE volatile xdata *)0x1f28 )	//8 Bytes
#define REG1630_TX0_FIFO			((BYTE volatile xdata *)0x1f30 )	//8 bytes	
#define REG1630_TX5_FIFO			((BYTE volatile xdata *)0x1f40 )	//8 bytes
#define REG1630_USB_ADDR			(*(BYTE volatile xdata *)(TMU3112REG_BASE+0x00))

//===========================================================================
#define	REG1630_INT0A				(*(BYTE volatile xdata *)(TMU3112REG_BASE+0x01))
#define OUTI0_INT 					BIT7
#define TX0_INT 					BIT6
#define TX1_INT 					BIT5
#define RC2_INT 					BIT4
#define RESET_INT 					BIT3
#define RESUME_INT 					BIT2
#define SUSPEND_INT 				BIT1
#define SETUP_INT 					BIT0

#define CLR_OUTI0_INT				(REG1630_INT0A &= ~BIT7)
#define CLR_TX0_INT					(REG1630_INT0A &= ~BIT6) 
#define CLR_TX1_INT					(REG1630_INT0A &= ~BIT5)
#define CLR_RC2_INT					(REG1630_INT0A &= ~BIT4)
#define CLR_RESET_INT				(REG1630_INT0A &= ~BIT3)
#define CLR_RESUME_INT				(REG1630_INT0A &= ~BIT2)
#define CLR_SUSPEND_INT				(REG1630_INT0A &= ~BIT1)
#define CLR_SETUP_INT				(REG1630_INT0A &= ~BIT0)
//===========================================================================
#define REG1630_INT0_ENA			(*(BYTE volatile xdata *)(TMU3112REG_BASE+0x02))
#define OUTI0_IE 					BIT7
#define TX0_IE 						BIT6
#define TX1_IE 						BIT5
#define RC2_IE 						BIT4
#define RESET_IE 					BIT3
#define RESUME_IE 					BIT2
#define SUSPEND_IE 					BIT1
#define SETUP_IE					BIT0
//===========================================================================
#define REG1630_PWR_CTRL			(*(BYTE volatile xdata *)(TMU3112REG_BASE+0x03))
#define SET_OUT0_RDY				(REG1630_PWR_CTRL |= BIT0)
#define CLR_OUT0_RDY				(REG1630_PWR_CTRL &= 0xfe)
#define SUSPEND_MODE				(REG1630_PWR_CTRL |= BIT7)
#define RESUME						(REG1630_PWR_CTRL |= BIT6)	


#define SET_OUT0_RDY				(REG1630_PWR_CTRL |= BIT0)
#define CLR_OUT0_RDY				(REG1630_PWR_CTRL &= 0xfe)
#define SET_SUSPEND_MODE			(REG1630_PWR_CTRL |= BIT7)
#define CLR_SUSPEND_MODE			(REG1630_PWR_CTRL &= ~BIT7)
#define SET_RESUME					(REG1630_PWR_CTRL |= BIT6)
#define CLR_RESUME					(REG1630_PWR_CTRL &= ~BIT6)	
//===========================================================================
#define REG1630_RC0					(*(BYTE volatile xdata *)(TMU3112REG_BASE+0x04))
#define OUT0_TGL					BIT7
#define RC0_ERR 					BIT6
#define RC0_CNT 					0x0f
#define DATA1_ZERO_LENGTH			((REG1630_RC0 & 0x0f) == 0)

//===========================================================================
#define REG1630_TX0					(*(BYTE volatile xdata *)(TMU3112REG_BASE+0x05))
#define TX0_RDY						BIT6
#define TX0_TGL 					BIT5
#define EP0_STALL					BIT4
#define TX0_CNT 					0x0f

#define SET_TX0_RDY 				(REG1630_TX0 |= BIT6)
#define CLR_TX0_RDY					(REG1630_TX0 &= 0xbf)
#define SET_EP0_STALL				(REG1630_TX0 |= BIT4)
#define CLR_EP0_STALL				(REG1630_TX0 &= ~BIT4)					//Johnny 06.12.26 add for USB CV 
#define CLR_EP0_TGL					(REG1630_TX0 &= ~BIT5)					//Johnny 06.12.26 add for USB CV 
//============================================================================
#define REG1630_TX1					(*(BYTE volatile xdata *)(TMU3112REG_BASE+0x06))
#define EP1_STALL					BIT7
#define EP1_CFG						BIT6
#define TX1_RDY						BIT5
#define TX1_TGL						BIT4

#define SET_EP1_STALL				(REG1630_TX1 |= BIT7)
#define CLR_EP1_CFG					(REG1630_TX1 &= ~BIT6)
#define SET_EP1_CFG					(REG1630_TX1 |= BIT6)
#define SET_TX1_RDY                	(REG1630_TX1 |= BIT5)
#define CLR_TX1_RDY					(REG1630_TX1 &= ~BIT5)
#define CLR_TX1_STALL				(REG1630_TX1 &= ~BIT7)					//Johnny 06.12.26 add for USB CV 
#define CLR_TX1_TGL					(REG1630_TX1 &= ~BIT4)					//Johnny 06.12.26 add for USB CV 
#define SET_TX1_TGL					(REG1630_TX1 |= BIT4)

//============================================================================
#define REG1630_RC2					(*(BYTE volatile xdata *)(TMU3112REG_BASE+0x07))
#define EP2_STALL					BIT7
#define EP2_CFG						BIT6
#define RC2_RDY						BIT5
#define RC2_TGL						BIT4
#define RC2_ERR						BIT3

#define SET_RC2_STALL				(REG1630_RC2 |= BIT7)
#define CLR_RC2_STALL				(REG1630_RC2 &= ~BIT7)
#define SET_RC2_CFG					(REG1630_RC2 |= BIT6)
#define CLR_RC2_CFG					(REG1630_RC2 &= ~BIT6)
#define SET_RC2_RDY					(REG1630_RC2 |= BIT5)
#define CLR_RC2_RDY					(REG1630_RC2 &= ~BIT5)
#define CLR_RC2_TGL					(REG1630_RC2 &= ~BIT4)					//Johnny 06.12.26 add for USB CV 		


//============================================================================

#define REG1630_TX1_CNT				(*(BYTE volatile xdata *)(TMU3112REG_BASE+0x08))

//============================================================================

#define	REG1630_RC2_CNT				(*(BYTE volatile xdata *)(TMU3112REG_BASE+0x09))

//============================================================================
#define REG1630_TX5					(*(BYTE volatile xdata *)(TMU3112REG_BASE+0x0a))
#define EP5_STALL					BIT7
#define	EP5_CFG						BIT6
#define EP5_RDY						BIT5
#define TX5_TGL						BIT4
#define TX5_CNT						0x0F
#define SET_EP5_STALL				(REG1630_TX5 |= BIT7)////////7.31
//============================================================================
#define REG1630_INT0B				(*(BYTE volatile xdata *)(TMU3112REG_BASE+0x0b))	
#define TX3_INT 					BIT7
#define RC4_INT 					BIT6
#define TX5_INT 					BIT5
#define CLR_TX3_INT					(REG1630_INT0B &= ~BIT7)
#define CLR_RC4_INT					(REG1630_INT0B &= ~BIT6)
#define CLR_TX5_INT					(REG1630_INT0B &= ~BIT5)

//============================================================================
#define REG1630_INT0_ENB			(*(BYTE volatile xdata *)(TMU3112REG_BASE+0x0c))
#define TX3IE						BIT7
#define RC4IE						BIT6
#define TX5IE						BIT5

//============================================================================
#define REG1630_TX3					(*(BYTE volatile xdata *)(TMU3112REG_BASE+0x0d))
#define EP3_STALL					BIT7
#define	EP3_CFG						BIT6
#define EP3_TX_RDY					BIT5
#define EP3_TGL						BIT4

#define SET_EP3_STALL				(REG1630_TX3 |= BIT7)
#define SET_EP3_CFG					(REG1630_TX3 |= BIT6)
#define SET_TX3_RDY					(REG1630_TX3 |= BIT5)
#define SET_EP3_TGL					(REG1630_TX3 |= BIT4)

#define CLR_EP3_STALL				(REG1630_TX3 &= ~BIT7)
#define CLR_EP3_CFG					(REG1630_TX3 &= ~BIT6)
#define CLR_TX3_RDY					(REG1630_TX3 &= ~BIT5)
#define CLR_EP3_TGL					(REG1630_TX3 &= ~BIT4)

//============================================================================

#define REG1630_RC4					(*(BYTE volatile xdata *)(TMU3112REG_BASE+0x0e))
#define EP4_STALL					BIT7
#define EP4_CFG						BIT6
#define EP4_RDY						BIT5
#define EP4_TGL						BIT4
#define EP4_ERR						BIT3

#define SET_EP4_STALL				(REG1630_RC4 |= BIT7)
#define	SET_EP4_CFG					(REG1630_RC4 |= BIT6)
#define SET_RC4_RDY					(REG1630_RC4 |= BIT5)

#define CLR_EP4_STALL				(REG1630_RC4 &= ~BIT7)
#define CLR_EP4_CFG					(REG1630_RC4 &= ~BIT6)
#define CLR_RC4_RDY					(REG1630_RC4 &= ~BIT5)

//============================================================================

#define REG1630_TX3_CNT				(*(BYTE volatile xdata *)(TMU3112REG_BASE+0x0f))

//============================================================================

#define	REG1630_RC4_CNT				(*(BYTE volatile xdata *)(TMU3112REG_BASE+0x10))

//============================================================================

#define REG1630_XRAM_CTRL			(*(BYTE volatile xdata *)(TMU3112REG_BASE+0x80))
#define XRAM0USB					BIT7
#define XRAM1USB					BIT6
#define XRAM2USB					BIT5
#define XRAM3USB					BIT4
#define XRAMAUSB					BIT3
#define XRAMBUSB					BIT2

#define SET_XRAM0USB				(REG1630_XRAM_CTRL |= BIT7)
#define CLR_XRAM0USB				(REG1630_XRAM_CTRL &= ~BIT7)
#define SET_XRAM1USB				(REG1630_XRAM_CTRL |= BIT6)
#define CLR_XRAM1USB				(REG1630_XRAM_CTRL &= ~BIT6)	
#define SET_XRAM2USB				(REG1630_XRAM_CTRL |= BIT5)
#define CLR_XRAM2USB				(REG1630_XRAM_CTRL &= ~BIT5)
#define SET_XRAM3USB				(REG1630_XRAM_CTRL |= BIT4)
#define CLR_XRAM3USB				(REG1630_XRAM_CTRL &= ~BIT4)
#define SET_XRAMAUSB				(REG1630_XRAM_CTRL |= BIT3)
#define CLR_XRAMAUSB				(REG1630_XRAM_CTRL &= ~BIT3)
#define	SET_XRAMBUSB				(REG1630_XRAM_CTRL |= BIT2)
#define	CLR_XRAMBUSB				(REG1630_XRAM_CTRL &= ~BIT2)
//=======================        PER					============================
#define REG1630_INT1				(*(BYTE volatile xdata *)(TMU3112REG_BASE+0x81))
#define VDD5VRI_INT					BIT7
#define SPIA_SCAVE_INT				BIT6
#define UART_RX_ERRI_INT			BIT5
#define WKTUPI_INT					BIT4
#define EXINT3I_INT					BIT3
#define EXINT2I_INT					BIT2
#define EXINT1I_INT					BIT1
#define EXINT0I_INT					BIT0

#define CLR_VDD5VRI_INT				(REG1630_INT1 &= ~BIT7)
#define CLR_SPIA_SCAVE_INT			(REG1630_INT1 &= ~BIT6)
#define CLR_UART_RX_ERRI_INT		(REG1630_INT1 &= ~BIT5)
#define CLR_WKTUPI_INT				(REG1630_INT1 &= ~BIT4)
#define CLR_EXINT3I_INT				(REG1630_INT1 &= ~BIT3)
#define CLR_EXINT2I_INT				(REG1630_INT1 &= ~BIT2)
#define CLR_EXINT1I_INT				(REG1630_INT1 &= ~BIT1)
#define CLR_EXINT0I_INT				(REG1630_INT1 &= ~BIT0)

//============================================================================

#define REG1630_INT1_EN				(*(BYTE volatile xdata *)(TMU3112REG_BASE+0x82))
#define VDD5VRIE_INT				BIT7
#define SPIA_SLAVEIE				BIT6
#define UART_RX_ERRIE				BIT5
#define WKTUPIE						BIT4
#define EXINT3IE					BIT3
#define EXINT2IE					BIT2
#define EXINT1IE					BIT1
#define EXINT0IE					BIT0

//=============================================================================

#define REG1630_PWR_DN				(*(BYTE volatile xdata *)(TMU3112REG_BASE+0x8B))
#define	SET_PWR_DN					REG1630_PWR_DN=0xff;	

//=============================================================================

#define REG1630_USB_PLUG_OUT		(*(BYTE volatile xdata *)(TMU3112REG_BASE+0x8C))
#define VDD5V_EXIST_FLG				BIT7	
#define VDD5V_FALL_FLG				BIT6
#define WDT_FLG						BIT5

#define CLR_VDD5V_FALL_FLG			(REG1630_USB_PLUG_OUT &= ~BIT6) 

//============================================================================

#define REG1630_SET_CRYSTAL			(*(BYTE volatile xdata *)(TMU3112REG_BASE+0x8D))
#define FCLK_EN						BIT1	
#define CKFAST						BIT0	


#define SET_VIO_18					(REG1630_SET_CRYSTAL &= ~(BIT3|BIT2))
#define	SET_VIO_30					(REG1630_SET_CRYSTAL |= BIT2)					
#define	SET_VIO_50					(REG1630_SET_CRYSTAL |= BIT3)	
#define SET_FCLK_EN					(REG1630_SET_CRYSTAL |= BIT1)
#define CLR_FCLK_EN					(REG1630_SET_CRYSTAL &= ~BIT1)
#define SET_CKFAST					(REG1630_SET_CRYSTAL |= BIT0)
#define CLR_CKFAST					(REG1630_SET_CRYSTAL &= ~BIT0)

//====================			SPIA SLAVE/MASTER		=============================
#define REG1630_FIFO_WR				(*(BYTE volatile xdata *)(TMU3112REG_BASE+0x50))

#define REG1630_FIFO_RD				(*(BYTE volatile xdata *)(TMU3112REG_BASE+0x51))
#define REG1630_SPIA_FIFO_RD		(*(BYTE volatile xdata *)(TX1630REG_BASE+0x51))

#define REG1630_SPIA_CTRL1			(*(BYTE volatile xdata *)(TMU3112REG_BASE+0x52))
#define SPIA_CPOL					BIT6
#define SPIA_CPHA					BIT5
#define SPIA_BUSY					BIT0

#define REG1630_SPIA_CTRL2			(*(BYTE volatile xdata *)(TMU3112REG_BASE+0x53))
#define SPIA_EN						BIT7


#define REG1630_SPIA_RC_TX_FIFO_CNT		(*(BYTE volatile xdata *)(TMU3112REG_BASE+0x52))	
#define SPIA_TX_FIFO_CUR_CNT		(REG1630_SPIA_RC_TX_FIFO_CNT&0xE0)>>4
#define SPIA_RC_FIFO_CUR_CNT		(REG1630_SPIA_RC_TX_FIFO_CNT&0x0F)&0x0F

#define REG1630_SPIA_CTRL3			(*(BYTE volatile xdata *)(TMU3112REG_BASE+0x55))
#define SPIA_MODE_SELECT			BIT7
#define SPIA_CLR_FIFO_CUR_CNT		BIT1
#define SPIA_RC_FIFO_OVERRUN		BIT0

//============================================================================

#define REG1630_SPIB_FIFO_WR		(*(BYTE volatile xdata *)(TMU3112REG_BASE+0x58))
#define REG1630_SPIB_FIFO_RD		(*(BYTE volatile xdata *)(TMU3112REG_BASE+0x59))

#define REG1630_SPIB_CTRL1_5A		(*(BYTE volatile xdata *)(TMU3112REG_BASE+0x5a))
#define SPIB_CPOL					BIT6
#define SPIB_CPHA					BIT5
#define SPIB_BUSY					BIT0


#define REG1630_SPIB_CTRL2_5B		(*(BYTE volatile xdata *)(TMU3112REG_BASE+0x5b))
#define SPIB_EN						BIT7

#define REG1630_SPIB_RC_TX_FIFO_CNT_5C	 (*(BYTE volatile xdata *)(TMU3112REG_BASE+0x5C))	
#define SPIB_TX_FIFO_CUR_CNT		(REG1630_SPIB_RC_TX_FIFO_CNT_5C&0xE0)>>4
#define SPIB_RC_FIFO_CUR_CNT		(REG1630_SPIB_RC_TX_FIFO_CNT_5C&0x0F)&0x0F								
#define REG1630_SPIB_CTRL3_5D			(*(BYTE volatile xdata *)(TMU3112REG_BASE+0x5d))
#define SPIB_CLR_FIFO_CUR_CNT		BIT1
#define SPIB_RC_FIFO_OVERRUN		BIT0	
#define CLR_SPIB_CLR_FIFO_CUR_CNT	(REG1630_SPIB_CTRL3_5D&= ~BIT1)

//============================================================================

#define REG1630_PWM_CTRL			(*(BYTE volatile xdata *)(TMU3112REG_BASE+0x90))
#define REG1630_PC_PWMA_PRD		(*(BYTE volatile xdata *)(TX1630REG_BASE+0x91))	//!! ONLY WRITE
#define REG1630_PC_PWMA_DT		(*(BYTE volatile xdata *)(TX1630REG_BASE+0x92))	//!! ONLY WRITE//============================================================================
#define REG1630_PC_PWMB_PRD		(*(BYTE volatile xdata *)(TX1630REG_BASE+0x94))	//!! ONLY WRITE
#define REG1630_PC_PWMB_DT		(*(BYTE volatile xdata *)(TX1630REG_BASE+0x95))	//!! ONLY WRITE//===============

//#define REG1630_UTX_BUF				(*(BYTE volatile xdata *)(TMU3112REG_BASE+0xb0))	//8 bytes

//============================================================================	

//#define REG1630_UTX_CTRL_B2			(*(BYTE volatile xdata *)(TMU3112REG_BASE+0xb2))	//8 bytes	
//#define UTX_BUSY					((REG1630_UTX_CTRL &= BIT0) != BIT0)
//#define UTX_ENA						(REG1630_UTX_CTRL |= BIT7)		

//#define REG1630_UTX_CNT_B3				(*(BYTE volatile xdata *)0x1fb3 )
//#define UTX_TX_CNT					(REG1630_UTX_CNT & 0xf0)
//#define UTX_RC_CNT					(REG1630_UTX_CNT & 0x0f)
#define REG1630_PA_GPIO_9A				(*(BYTE volatile xdata *)(TMU3112REG_BASE+0x9A))	//ZP
#define GPIO_PA5					BIT5
#define GPIO_PA4					BIT4
#define GPIO_PA3					BIT3
#define GPIO_PA2					BIT2
#define GPIO_PA1					BIT1
#define GPIO_PA0					BIT0
#define SET_PA5						(REG1630_PA_GPIO_9A |= BIT5) // 7.20
#define SET_PA4						(REG1630_PA_GPIO_9A |= BIT4) // 8.9



#define SET_PA3						(REG1630_PA_GPIO_9A |= BIT3) // 8.9
#define SET_PA2						(REG1630_PA_GPIO_9A |= BIT2) // 8.9
#define SET_PA1						(REG1630_PA_GPIO_9A |= BIT1) // 8.9
#define SET_PA0						(REG1630_PA_GPIO_9A |= BIT0) // 8.9







#define CLR_PA3						(REG1630_PA_GPIO_9A &= ~BIT3) // 8.9
#define CLR_PA2						(REG1630_PA_GPIO_9A &= ~BIT2) // 8.9
#define CLR_PA1						(REG1630_PA_GPIO_9A &= ~BIT1) // 8.9
#define CLR_PA0						(REG1630_PA_GPIO_9A &= ~BIT0) // 8.9

//================================================================================

#define REG1630_PA_GPIO_CON_AA		(*(BYTE volatile xdata *)(TMU3112REG_BASE+0xAA))	//ZP
#define GPIO_PA5CON					BIT5
#define GPIO_PA4CON					BIT4
#define GPIO_PA3CON					BIT3
#define GPIO_PA2CON					BIT2
#define GPIO_PA1CON					BIT1
#define GPIO_PA0CON					BIT0
#define SET_GPIO_PA5				(REG1630_PA_GPIO_CON_AA |= BIT5) //TEST 7.20
#define SET_GPIO_PA4				(REG1630_PA_GPIO_CON_AA |= BIT4) //8.9

#define SET_GPIO_PA5				(REG1630_PA_GPIO_CON_AA |= BIT5) //TEST 7.20
#define SET_GPIO_PA4				(REG1630_PA_GPIO_CON_AA |= BIT4) //8.9


#define SET_GPIO_PA3				(REG1630_PA_GPIO_CON_AA |= BIT3) //TEST 7.20
#define SET_GPIO_PA2				(REG1630_PA_GPIO_CON_AA |= BIT2) //8.9
#define SET_GPIO_PA1				(REG1630_PA_GPIO_CON_AA |= BIT1) //8.9
#define SET_GPIO_PA0				(REG1630_PA_GPIO_CON_AA |= BIT0) //8.9

//=============================================================================

#define REG1630_PB_GPIO_9B				(*(BYTE volatile xdata *)(TMU3112REG_BASE+0x9B))
#define GPIO_PB7					BIT7
#define GPIO_PB6					BIT6
#define GPIO_PB5					BIT5
#define GPIO_PB4					BIT4
#define GPIO_PB3					BIT3
#define GPIO_PB2					BIT2
#define GPIO_PB1					BIT1
#define GPIO_PB0					BIT0
#define CLR_PB0			       (REG1630_PB_GPIO_9B &= ~BIT0) 
#define SET_PB0			       (REG1630_PB_GPIO_9B |= BIT0)
#define CLR_PB1			       (REG1630_PB_GPIO_9B &= ~BIT1) 
#define SET_PB1			       (REG1630_PB_GPIO_9B |= BIT1)
#define CLR_PB2			       (REG1630_PB_GPIO_9B &= ~BIT2) 
#define SET_PB2			       (REG1630_PB_GPIO_9B |= BIT2)
#define CLR_PB3			       (REG1630_PB_GPIO_9B &= ~BIT3) 
#define SET_PB3			       (REG1630_PB_GPIO_9B |= BIT3)
#define CLR_PB4			       (REG1630_PB_GPIO_9B &= ~BIT4) 
#define SET_PB4			       (REG1630_PB_GPIO_9B |= BIT4)
#define CLR_PB5			       (REG1630_PB_GPIO_9B &= ~BIT5) 
#define SET_PB5			       (REG1630_PB_GPIO_9B |= BIT5)
#define CLR_PB6			       (REG1630_PB_GPIO_9B &= ~BIT6) 
#define SET_PB6			       (REG1630_PB_GPIO_9B |= BIT6)
#define CLR_PB7			       (REG1630_PB_GPIO_9B &= ~BIT7) 
#define SET_PB7			       (REG1630_PB_GPIO_9B |= BIT7)

//==============================================================================

#define REG1630_PB_GPIO_CON_AB			(*(BYTE volatile xdata *)(TMU3112REG_BASE+0xAB))
#define GPIO_PB7CON					BIT7
#define GPIO_PB6CON					BIT6
#define GPIO_PB5CON					BIT5
#define GPIO_PB4CON					BIT4
#define GPIO_PB3CON					BIT3
#define GPIO_PB2CON					BIT2
#define GPIO_PB1CON					BIT1
#define GPIO_PB0CON					BIT0

#define SET_GPIO_PB7				(REG1630_PB_GPIO_CON_AB |= BIT7) 			
#define SET_GPIO_PB6				(REG1630_PB_GPIO_CON_AB |= BIT6) 			
#define SET_GPIO_PB5				(REG1630_PB_GPIO_CON_AB |= BIT5) 			
#define SET_GPIO_PB4				(REG1630_PB_GPIO_CON_AB |= BIT4) 			
#define SET_GPIO_PB3				(REG1630_PB_GPIO_CON_AB |= BIT3) 			
#define SET_GPIO_PB2				(REG1630_PB_GPIO_CON_AB |= BIT2) 			
#define SET_GPIO_PB1				(REG1630_PB_GPIO_CON_AB |= BIT1) 			
#define SET_GPIO_PB0				(REG1630_PB_GPIO_CON_AB |= BIT0) 			

#define CLR_GPIO_PB7				(REG1630_PB_GPIO_CON_AB &= ~BIT7)
#define CLR_GPIO_PB6				(REG1630_PB_GPIO_CON_AB &= ~BIT6)
#define CLR_GPIO_PB5				(REG1630_PB_GPIO_CON_AB &= ~BIT5)
#define CLR_GPIO_PB4				(REG1630_PB_GPIO_CON_AB &= ~BIT4)
#define CLR_GPIO_PB3				(REG1630_PB_GPIO_CON_AB &= ~BIT3)
#define CLR_GPIO_PB2				(REG1630_PB_GPIO_CON_AB &= ~BIT2)
#define CLR_GPIO_PB1				(REG1630_PB_GPIO_CON_AB &= ~BIT1)
#define CLR_GPIO_PB0				(REG1630_PB_GPIO_CON_AB &= ~BIT0)

//===============================================================================

#define REG1630_PC_GPIO_9C			(*(BYTE volatile xdata *)(TMU3112REG_BASE+0x9C))
#define GPIO_PC7					BIT7
#define GPIO_PC6					BIT6
#define GPIO_PC5					BIT5
#define GPIO_PC4					BIT4
#define GPIO_PC3					BIT3	
#define GPIO_PC2					BIT2
#define GPIO_PC1					BIT1
#define GPIO_PC0					BIT0

#define SET_PC0				(REG1630_PC_GPIO_9C |= BIT0)
#define SET_PC5				(REG1630_PC_GPIO_9C |= BIT5)
#define CLR_PC0				(REG1630_PC_GPIO_9C &= ~BIT0) 
#define CLR_PC5				(REG1630_PC_GPIO_9C &= ~BIT5) 
#define SET_PC4				(REG1630_PC_GPIO_9C |= BIT4)
#define CLR_PC4				(REG1630_PC_GPIO_9C &= ~BIT4)
#define CLR_PC7				(REG1630_PC_GPIO_9C &= ~BIT7) 
#define CLR_PC3				(REG1630_PC_GPIO_9C &= ~BIT3) 
#define SET_PC3				(REG1630_PC_GPIO_9C |= BIT3)
#define SET_PC1				(REG1630_PC_GPIO_9C |= BIT1)
#define SET_PC7				(REG1630_PC_GPIO_9C |= BIT7)
//================================================================================

#define REG1630_PC_GPIO_CON_AC		(*(BYTE volatile xdata *)(TMU3112REG_BASE+0xAC))
#define GPIO_PC7CON					BIT7
#define GPIO_PC6CON					BIT6
#define GPIO_PC5CON					BIT5
#define GPIO_PC4CON					BIT4

#define SET_GPIO_PC7				(REG1630_PC_GPIO_CON_AC |= BIT7) 
#define SET_GPIO_PC6				(REG1630_PC_GPIO_CON_AC |= BIT6) 
#define SET_GPIO_PC5				(REG1630_PC_GPIO_CON_AC |= BIT5) 
#define SET_GPIO_PC4				(REG1630_PC_GPIO_CON_AC |= BIT4)

#define CLR_GPIO_PC7				(REG1630_PC_GPIO_CON_AC &= ~BIT7) 
#define CLR_GPIO_PC6				(REG1630_PC_GPIO_CON_AC &= ~BIT6) 
#define CLR_GPIO_PC5				(REG1630_PC_GPIO_CON_AC &= ~BIT5) 
#define CLR_GPIO_PC4				(REG1630_PC_GPIO_CON_AC &= ~BIT4)

 

//===================================================================================

//================================     UART		=====================================

#define REG1630_UART_TX_BUF_B0		(*(BYTE volatile xdata *)(TMU3112REG_BASE+0xb0))		

//===================================================================================

#define REG1630_UART_RX_BUF_B1		(*(BYTE volatile xdata *)(TMU3112REG_BASE+0xb1))	

//===================================================================================

#define REG1630_UART_TX_BUF_B2		(*(BYTE volatile xdata *)(TMU3112REG_BASE+0xb2))
#define UTX_EN						BIT7
#define URX_EN						BIT6
#define	UTX_BUSY					BIT0

#define	SET_UTX_EN					(REG1630_UART_TX_BUF_B2 |=BIT7)
#define	CLR_UTX_EN					(REG1630_UART_TX_BUF_B2 &=~BIT7)
#define SET_URX_EN					(REG1630_UART_TX_BUF_B2 |=BIT6)
#define CLR_URX_EN					(REG1630_UART_TX_BUF_B2 &=~BIT6)					


#define INTER_DELAY_NONE_STOP_BIT	(REG1630_UART_TX_BUF_B2 &=0xf3)
#define INTER_DELAY_1_STOP_BIT		(REG1630_UART_TX_BUF_B2 |=BIT2)
#define INTER_DELAY_2_STOP_BIT		(REG1630_UART_TX_BUF_B2 |=BIT3)	
#define INTER_DELAY_3_STOP_BIT		(REG1630_UART_TX_BUF_B2 |=(BIT2|BIT3))

//===================================================================================

#define REG1630_UART_TX_RC_COUNT_B3		(*(BYTE volatile xdata *)(TMU3112REG_BASE+0xb3))
#define UART_TX_FIFO_CNT				((REG1630_UART_TX_RC_COUNT_B3 & 0xf0)>>4)
#define UART_RC_FIFO_CNT				(REG1630_UART_TX_RC_COUNT_B3 & 0x0f)

//===================================================================================

#define	REG1630_UART_BAUD_RATE_H	(*(BYTE volatile xdata *)(TMU3112REG_BASE+0xb4))

//====================================================================================

#define REG1630_UART_BAUD_RATE_L	(*(BYTE volatile xdata *)(TMU3112REG_BASE+0xb5))

//===================================================================================

#define REG1630_UART_MODE_B6		(*(BYTE volatile xdata *)(TMU3112REG_BASE+0xb6))
#define STOP_BIT					BIT5
#define	PAR_EN						BIT4
#define EVEN						BIT3
#define STICK						BIT2
#define	BREAK						BIT1

#define SET_UMODE_5BIT				(REG1630_UART_MODE_B6 &= 0x3f)	
#define SET_UMODE_6BIT				(REG1630_UART_MODE_B6 |= BIT7)
#define SET_UMODE_7BIT				(REG1630_UART_MODE_B6 |= BIT6)			
#define SET_UMODE_8BIT				(REG1630_UART_MODE_B6 |= (BIT7|BIT6))

#define SET_STOP_BIT				(REG1630_UART_MODE_B6 |= BIT5)	
#define SET_PAR_EN					(REG1630_UART_MODE_B6 |= BIT4)
#define SET_EVEN					(REG1630_UART_MODE_B6 |= BIT3)
#define SET_STICK					(REG1630_UART_MODE_B6 |= BIT2)
#define SET_BREAK					(REG1630_UART_MODE_B6 |= BIT1)

#define CLR_STOP_BIT				(REG1630_UART_MODE_B6 &= ~BIT5)	
#define CLR_PAR_EN					(REG1630_UART_MODE_B6 &= ~BIT4)
#define CLR_EVEN					(REG1630_UART_MODE_B6 &= ~BIT3)
#define CLR_STICK					(REG1630_UART_MODE_B6 &= ~BIT2)
#define CLR_BREAK					(REG1630_UART_MODE_B6 &= ~BIT1)

//====================================================================================


#define REG1630_CLR_UART_TX_RC_CNT_B7		(*(BYTE volatile xdata *)(TMU3112REG_BASE+0xb7))
#define	CLR_UART_TX_CUR_CNT						(REG1630_CLR_UART_TX_RC_CNT_B7 &= ~BIT1)
#define CLR_UART_RC_CUR_CNT						(REG1630_CLR_UART_TX_RC_CNT_B7 &= ~BIT0)

//======================================================================================

#define REG1630_UART_TX_RC_ERROR_B9			(*(BYTE volatile xdata *)(TMU3112REG_BASE+0xb9))
								
#define PARITY_ERR					BIT7
#define OVERUN_ERR					BIT6
#define FRAME_ERR					BIT5
#define BREAK_ACT					BIT4













