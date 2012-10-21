
#include "main.h"
#include "incfile.h"
#include "iic.h"
//#define MS_DEBUG
#define IIC_USE_51
#define IIC_USE_TENX

#if 1
sbit MS_SENSOR_SCK=P1^1;
sbit MS_SENSOR_SDA=P1^0;

#define SET_I2C_CLK_OUTPUT	MS_SENSOR_SCK = 1
#define SET_I2C_CLK_HIGH	MS_SENSOR_SCK = 1 
#define SET_I2C_CLK_LOW		MS_SENSOR_SCK = 0

#define SET_I2C_DATA_OUTPUT	MS_SENSOR_SDA = 1  
#define SET_I2C_DATA_INPUT	MS_SENSOR_SDA = 1
#define SET_I2C_DATA_HIGH	MS_SENSOR_SDA = 1
#define SET_I2C_DATA_LOW	MS_SENSOR_SDA = 0
#define GET_I2C_DATA_BIT	GPIO_READ()
#endif

#if 0
#define SET_I2C_CLK_OUTPUT	SET_GPIO_PA5
#define SET_I2C_CLK_HIGH	SET_PA5 
#define SET_I2C_CLK_LOW		CLR_PA5

#define SET_I2C_DATA_OUTPUT	SET_GPIO_PA4  
#define SET_I2C_DATA_INPUT	SET_PA4
#define SET_I2C_DATA_HIGH	SET_PA4
#define SET_I2C_DATA_LOW	CLR_PA4
#define GET_I2C_DATA_BIT	GPIO_READ()
#endif


#if 0
#define SET_I2C_CLK_OUTPUT	SET_GPIO_PB0
#define SET_I2C_CLK_HIGH	SET_PB0 
#define SET_I2C_CLK_LOW		CLR_PB0

#define SET_I2C_DATA_OUTPUT	SET_GPIO_PB1  
#define SET_I2C_DATA_INPUT	SET_PB1
#define SET_I2C_DATA_HIGH	SET_PB1
#define SET_I2C_DATA_LOW	CLR_PB1
#define GET_I2C_DATA_BIT	GPIO_READ()
#endif


#define Delay20us  		0//95
#define Delay10us       0//  	45
#define Delay5us        0//	21
#define Delay2p5us 		0//10


static unsigned char GPIO_READ(void)
{
#if 0
	SET_PA4;//very important
#endif

#if 0
	SET_PB1;//very important

	if (REG1630_PB_GPIO_9B & 0x02) {
		return 1;
	}
	return 0;

#endif

#if 1
//	 MS_SENSOR_SDA = 1;
	 if (MS_SENSOR_SDA == 1) {
	 	return 1;
	 }
	 return 0;
#endif	
}

#if 0
static void GPIO_ModeSetup(bit gpio, char mode)
{
	;
}
#endif

static void mma_delay(unsigned char time)
{
	unsigned char i;
	for (i=0; i<time; i++);                //Software loop for time delay
}

void IIC_Init(void)
{
	//GPIO_ModeSetup(MS_SENSOR_SCK, 0x00);
	SET_I2C_CLK_OUTPUT;

	SET_I2C_CLK_HIGH;

	//GPIO_ModeSetup(MS_SENSOR_SDA, 0x00);   //Set I2C DATA pin as GPIO
	SET_I2C_DATA_OUTPUT;
	SET_I2C_DATA_HIGH;
}

/**
*  describe: I2C Start signal generation:
*  Data pin falls down when clock is high
*/
void IIC_Start(void)
{
	//GPIO_ModeSetup(MS_SENSOR_SCK, 0x00);   //Set I2C CLK pin as GPIO
	SET_I2C_CLK_OUTPUT;                     //Set I2C CLK pin as output
	//GPIO_ModeSetup(MS_SENSOR_SDA, 0x00);   //Set I2C DATA pin as GPIO
	SET_I2C_DATA_OUTPUT;                    //Set I2C DATA pin as output

	SET_I2C_DATA_HIGH;                     //I2C DATA pin output high(1)
	SET_I2C_CLK_HIGH;                     //I2C CLK pin output high(1)
	mma_delay(Delay20us);                   //Delay 20uS
	SET_I2C_DATA_LOW;                       //I2C DATA pin output low(0)
	mma_delay(Delay10us);                   //Delay 10uS
	SET_I2C_CLK_LOW;                        //I2C CLK pin output low(0)
	mma_delay(Delay10us);                   //Delay 10uS
}

void IIC_Stop (void)
{
	mma_delay(Delay10us);                   //Delay 10uS
	SET_I2C_CLK_HIGH;                     //I2C CLK pin output high(1)
	mma_delay(Delay10us);                   //Delay 10uS
	SET_I2C_DATA_HIGH;                     //I2C DATA pin output high(1)
}

/**
*  describe: I2C Repeat Start signal generation: 
*  Data pin falls down when clock is high 
*
*
*_________||||||||||||||____ SLK
*
*______|||||||||||||________ SDA
*
**/
void IIC_RepeatedStart(void)
{
	mma_delay(Delay20us);                   //Delay 20uS
	mma_delay(Delay20us);                   //Delay 20uS
	SET_I2C_DATA_HIGH;                     //I2C DATA pin output high(1)
	mma_delay(Delay10us);                   //Delay 10uS
	SET_I2C_CLK_HIGH;                     //I2C CLK pin output high(1)
	mma_delay(Delay20us);                   //Delay 20uS
	mma_delay(Delay20us);                   //Delay 20uS
	SET_I2C_DATA_LOW;                       //I2C DATA pin output low(0)
	mma_delay(Delay10us);                   //Delay 10uS
	SET_I2C_CLK_LOW;                        //I2C CLK pin output low(0)
	mma_delay(Delay10us);                   //Delay 10uS 
}

/**
 *
 * ____||||||____ SLK
 */
void IIC_OneClk(void)
{
	mma_delay(Delay5us);
	SET_I2C_CLK_HIGH;            //I2C CLK pin output high(1) 
	mma_delay(Delay10us);                  //Delay 10uS
	SET_I2C_CLK_LOW;                        //I2C CLK pin output low(0)
	mma_delay(Delay5us); 
}


/**
*  Subroutine: Check I2C Acknowledgement signal
*  return:   1 - Return 1 if read 1 from I2C DATA pin
*            0 - Return 0 if read 0 from I2C DATA pin
*            
*
* _________---------______________ sck
*
* ---------_______________________sda
*
*
**/
unsigned char IIC_ChkAck(void)
{
	SET_I2C_DATA_INPUT;                     //Set I2C DATA pin as input
	mma_delay(Delay5us);                    //Delay 5uS
	SET_I2C_CLK_HIGH;                     //I2C CLK pin output high(1) 
	mma_delay(Delay5us);                    //Delay 5uS again
	if (GET_I2C_DATA_BIT) {                 //Read I2C DATA pin
		mma_delay(Delay5us);                  //Delay 5uS
		SET_I2C_CLK_LOW;                      //I2C CLK pin output low(0)
		mma_delay(Delay5us);                  //Delay 5us again
		SET_I2C_DATA_OUTPUT;                  //Set I2C DATA pin as output
		SET_I2C_DATA_LOW;                     //I2C DATA pin output low(0)
		return 1;                             //Return 1 if read 1 from I2C DATA pin
	} else {                              //If I2C DATA pin is invalid for acknowledgement signal
		mma_delay(Delay5us);                  //Delay 5uS
		SET_I2C_CLK_LOW;                      //I2C CLK pin output low(0)
		mma_delay(Delay5us);                  //Delay 5uS again
		SET_I2C_DATA_OUTPUT;                  //Set I2C DATA pin as output
		SET_I2C_DATA_LOW;                     //I2C DATA pin output low(0)
		return 0;                             //Return 0 if read 0 from I2C DATA pin
	} 
}

/**
* 
*  Subroutine: Read one byte and send an acknowledgement signal
*
**/
unsigned char IIC_ReadByteACK(void)
{
	char i;
	unsigned char dat;

	SET_I2C_DATA_INPUT;                     //Set I2C DATA pin as input
	dat = 0;                               //Prepare to receive data
	for (i=7; i>=0; i--) {                  //Loop 8 times to receive 8 bits
		if (GET_I2C_DATA_BIT) 
			dat |= (0x01<<i);    //If read a 1, set to data bit
		IIC_OneClk();
	}                                 //Output one clock pulse after a bit is read

	SET_I2C_DATA_OUTPUT;                    //Set I2C DATA pin as output
	SET_I2C_DATA_LOW;                       //I2C DATA pin output low(0): the acknowledgement signal
	IIC_OneClk();                           //Output one clock pulse after data pin is ready

	return dat;                            //Return eceived data
}

/*
 * Subroutine: Read one byte but do not send acknowledgement signal
 *
 **/
unsigned char  IIC_ReadByteNCK(void)
{
	char i;
	unsigned char dat;

	SET_I2C_DATA_INPUT;                     //Set I2C DATA pin as input
	dat = 0;                               //Prepare to receive data
	for (i=7; i>=0; i--) {                  //Loop 8 times to receive 8 bits
		if (GET_I2C_DATA_BIT) dat |= (0x01<<i);    //If read a 1, set to data bit
		IIC_OneClk();
	}                                 //Output one clock pulse after a bit is read

	SET_I2C_DATA_OUTPUT;                    //Set I2C DATA pin as output
	SET_I2C_DATA_HIGH;                     //I2C DATA pin output high(1): no acknowledge
	IIC_OneClk();                           //Output one clock pulse after data pin is ready
	SET_I2C_DATA_LOW;                       //I2C DATA pin output low(0)

	return dat;                            //Return received data
}

/**
*  Subroutine: I2C send one byte out
*  
*  
*
* _____|||||||______|||||||||_____ ....
*
*--<===========>--<==========> ........
*/
void IIC_SendByte(unsigned char sData)
{
	char i;
	for (i=7; i>=0; i--) {
		if ((sData>>i)&0x01) {
			SET_I2C_DATA_HIGH;
		} else {
			SET_I2C_DATA_LOW;
		}
		IIC_OneClk();
	} 
}

unsigned char IIC_SendBytes(kal_uint8 *pData, unsigned char len)
{
	unsigned char i;
	for (i = 0; i < len; i++) {
		IIC_SendByte(pData[i]);
		if (IIC_ChkAck()) {
			IIC_Stop();
			return EEPROM_ACK_ERR;
		}
	}
	return EEPROM_RDWR_OK; 
}

unsigned char IIC_ReadBytes(kal_uint8 *pData, unsigned char len)
{
	unsigned char i;
	for(i=0; i<(len-1); i++)
		pData[i] = IIC_ReadByteACK();

	pData[len-1] = IIC_ReadByteNCK();
	return 1; 
}
