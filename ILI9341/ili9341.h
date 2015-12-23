#include "stm32f10x_gpio.h"
#include "Mylib/mylib.h"

extern void I2C_Single_Write(I2C_TypeDef* I2Cx, uint8_t HW_address, uint8_t addr, uint8_t data1 /*uint8_t data2*/ );

#define key_addr 0x41

#define TFT_RST_L		I2C_Single_Write(I2C1, PCA9555_I2C_ADDRESS, 0x02, 0xBE);	// ����������� RESET
#define TFT_RST_H		I2C_Single_Write(I2C1, PCA9555_I2C_ADDRESS, 0x02, 0xBF);	// ��������� RESET

#define TFT_DC_L		GPIOB->BRR = 0x10;					//DC - Port B4
#define TFT_DC_H		GPIOB->BSRR = 0x10;					//DC - Port B4

#define TFT_CS_L		GPIOA->BRR = 0x8000;				//CS - Port A15
#define TFT_CS_H		GPIOA->BSRR = 0x8000;				//CS - Port A15

#define TFT_SPI_SEND(data) 	while (!(SPI1->SR & SPI_SR_TXE)); SPI1->DR = data;

char TFT_sendByte(char byte);
void TFT_sendCMD(char cmd);
void TFT_sendDATA(char data);

void TFT_init(void);

void TFT_setFrame(unsigned short int x1, unsigned char y1, unsigned short int x2,
		unsigned char y2);
unsigned short int TFT_rgb2color(unsigned char r, unsigned char g, unsigned char b);
void TFT_setPixel(unsigned short int x, unsigned char y, unsigned short int color);

void TFT_clearScreen(void);
void TFT_fill(unsigned short int x1, unsigned char y1, unsigned short int x2,
		unsigned char y2, unsigned short int color);
void TFT_drawHLine(unsigned short int x, unsigned char y, unsigned short int length,
		unsigned short int color);
void TFT_drawVLine(unsigned short int x, unsigned char y, unsigned short int length,
		unsigned short int color);

void TFT_showChar(unsigned short int x, unsigned char y, unsigned char chars,
		char Hcolor, char Lcolor, char Hbg, char Lbg);
void TFT_showChar8(unsigned short int x, unsigned char y, unsigned char chars,
		char Hcolor, char Lcolor, char Hbg, char Lbg);

void TFT_showPic(unsigned short int x, unsigned char y, unsigned char pic,
		unsigned short int color, unsigned short int bg);

unsigned char I2C_key_read(void);
unsigned char key_read(void);

void I2C_led_test(void);
void I2C_led_test2(void);
