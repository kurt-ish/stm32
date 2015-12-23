#include "ili9341.h"
#include "stm32f10x.h"
#include "stm32f10x_i2c.h"
#include "fonts/DroidSansMono.h"
#include "img/pic16.h"
#include "Mylib/defines.h"







char TFT_sendByte(char byte) {
	char rxbyte;
	while (!(SPI1->SR & SPI_SR_TXE))
		;
	SPI1->DR = byte;
	while (!(SPI1->SR & SPI_SR_RXNE))
		;
	rxbyte = SPI1->DR;
	return rxbyte;
}

void TFT_sendCMD(char cmd) {
	TFT_DC_L
	TFT_CS_L
	TFT_sendByte(cmd);
	TFT_CS_H
}

void TFT_sendDATA(char data) {
	TFT_DC_H
	TFT_CS_L
	TFT_sendByte(data);
	TFT_CS_H
}

void TFT_init(void) {
	unsigned short int i;

	TFT_RST_L		// ����������� RESET
	TFT_RST_H		// ��������� RESET
	TFT_CS_H
	TFT_DC_H

	for (i = 0; i < 0x0FFFF; i++);
	for (i = 0; i < 0x0FFFF; i++);


	TFT_sendCMD(0x36); // Memory Access Control
	TFT_sendDATA(0xE8); // BGR, MX

	TFT_sendCMD(0x3A); // COLMOD: Pixel Format Set
	TFT_sendDATA(0x05); // MCU: 16 bit/pixel

	TFT_sendCMD(0x11); // Sleep Out
	TFT_sendCMD(0x29); // Display ON

	for (i = 0; i < 0x0FFFF; i++)
		;

	TFT_clearScreen();
}

void TFT_setFrame(unsigned short int x1, unsigned char y1,
		unsigned short int x2, unsigned char y2) {
	TFT_DC_L
	TFT_CS_L
	TFT_sendByte(0x2a);
	TFT_CS_H
	TFT_DC_H
	TFT_CS_L
	TFT_sendByte(x1 >> 8);
	TFT_sendByte(x1 & 0xff);
	TFT_sendByte(x2 >> 8);
	TFT_sendByte(x2 & 0xff);
	TFT_CS_H

	TFT_DC_L
	TFT_CS_L
	TFT_sendByte(0x2b);
	TFT_CS_H
	TFT_DC_H
	TFT_CS_L
	TFT_sendByte(y1 >> 8);
	TFT_sendByte(y1 & 0xff);
	TFT_sendByte(y2 >> 8);
	TFT_sendByte(y2 & 0xff);
	TFT_CS_H

	TFT_DC_L
	TFT_CS_L
	TFT_sendByte(0x2c);
	TFT_CS_H
}

unsigned short int TFT_rgb2color(unsigned char r, unsigned char g,
		unsigned char b) {
	return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
}

void TFT_setPixel(unsigned short int x, unsigned char y,
		unsigned short int color) {
	TFT_setFrame(x, y, x, y);
	TFT_DC_H
	TFT_CS_L
	TFT_SPI_SEND(color >> 8)
	TFT_SPI_SEND(color & 0xff)
	TFT_CS_H
}

void TFT_clearScreen(void) {
	int i;

	TFT_setFrame(0, 0, 319, 239);

	TFT_DC_H
	TFT_CS_L
	for (i = 0; i < 76800; i++) {
		TFT_SPI_SEND(0x05)
		TFT_SPI_SEND(0x05)
	}
	TFT_CS_H
}

void TFT_fill(unsigned short int x1, unsigned char y1, unsigned short int x2,
		unsigned char y2, unsigned short int color) {
	int i, max;
	char Hcolor = color >> 8;
	char Lcolor = color & 0xff;

	max = (x2 - x1 + 1) * (y2 - y1 + 1);
	TFT_setFrame(x1, y1, x2, y2);
	TFT_DC_H
	TFT_CS_L
	for (i = 0; i < max; i++) {
		TFT_SPI_SEND(Hcolor)
		TFT_SPI_SEND(Lcolor)
	}
	TFT_CS_H
}

void TFT_drawHLine(unsigned short int x, unsigned char y,
		unsigned short int length, unsigned short int color) {
	unsigned short int i;
	char Hcolor = color >> 8;
	char Lcolor = color & 0xff;

	TFT_setFrame(x, y, x + length - 1, y);
	TFT_DC_H
	TFT_CS_L
	for (i = 0; i < length; i++) {
		TFT_SPI_SEND(Hcolor)
		TFT_SPI_SEND(Lcolor)
	}
	TFT_CS_H
}

void TFT_drawVLine(unsigned short int x, unsigned char y,
		unsigned short int length, unsigned short int color) {
	unsigned short int i;
	char Hcolor = color >> 8;
	char Lcolor = color & 0xff;

	TFT_setFrame(x, y, x, y + length - 1);
	TFT_DC_H
	TFT_CS_L
	for (i = 0; i < length; i++) {
		TFT_SPI_SEND(Hcolor)
		TFT_SPI_SEND(Lcolor)
	}
	TFT_CS_H
}

void TFT_showChar(unsigned short int x, unsigned char y, unsigned char chars,
		char Hcolor, char Lcolor, char Hbg, char Lbg) {
	unsigned short int temp;
	unsigned char pos;
	char t;

	TFT_setFrame(x, y, x + 15, y + 30);
	TFT_DC_H
	TFT_CS_L
	for (pos = 0; pos < 31; pos++) {
		temp = DroidSansMono16[chars][pos];
		t = 16;
		while (t > 0) {
			t--;
			if ((temp >> t) & 1) {
				TFT_SPI_SEND(Hcolor)
				TFT_SPI_SEND(Lcolor)
			} else {
				TFT_SPI_SEND(Hbg)
				TFT_SPI_SEND(Lbg)
			}
		}
	}
	TFT_CS_H
}

void TFT_showChar8(unsigned short int x, unsigned char y, unsigned char chars,
		char Hcolor, char Lcolor, char Hbg, char Lbg) {
	unsigned char temp, pos;
	char t;

	TFT_setFrame(x, y, x + 7, y + 14);
	TFT_DC_H
	TFT_CS_L
	for (pos = 0; pos < 15; pos++) {
		temp = DroidSansMono8[chars][pos];
		t = 8;
		while (t > 0) {
			t--;
			if ((temp >> t) & 1) {
				TFT_SPI_SEND(Hcolor)
				TFT_SPI_SEND(Lcolor)
			} else {
				TFT_SPI_SEND(Hbg)
				TFT_SPI_SEND(Lbg)
			}
		}
	}
	TFT_CS_H
}

void TFT_showPic(unsigned short int x, unsigned char y, unsigned char pic,
		unsigned short int color, unsigned short int bg) {
	char Hcolor = color >> 8;
	char Lcolor = color & 0xff;
	char Hbg = bg >> 8;
	char Lbg = bg & 0xff;
	unsigned short int temp;
	unsigned char pos;
	char t;

	TFT_setFrame(x, y, x + 15, y + 15);
	TFT_DC_H
	TFT_CS_L
	for (pos = 0; pos < 16; pos++) {
		temp = Pic16[pic][pos];
		t = 16;
		while (t > 0) {
			t--;
			if ((temp >> t) & 1) {
				TFT_SPI_SEND(Hcolor)
				TFT_SPI_SEND(Lcolor)
			} else {
				TFT_SPI_SEND(Hbg)
				TFT_SPI_SEND(Lbg)
			}
		}
	}
	TFT_CS_H
}

unsigned char I2C_key_read(void) {
	unsigned char data;
	while (I2C1->SR2 & I2C_SR2_BUSY); 			// ���� ���� ���� �� �����������

	I2C1->CR1 |= I2C_CR1_START;					// ���������� �����
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));

	I2C1->DR = key_addr;						// �������� ����� � ������� ������ 0b 0100 0000
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED));

	data = I2C1->DR;							// ��������� ����
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED));

	I2C1->CR1 |= I2C_CR1_STOP;					// ���������� ����
	while (I2C1->SR2 & I2C_SR2_BUSY);

	return data;
}

unsigned char key_read(void) {
	return (GPIOA->IDR & 0x0f);
}

void I2C_led_test(void) {

	while (I2C1->SR2 & I2C_SR2_BUSY);		// ���� ���� ���� �� �����������

	I2C1->CR1 |= I2C_CR1_START;				// ���� �����
	while (!(I2C1->SR1 & I2C_SR1_SB));		// ��������� ����� ������� � ����������� ���������� � "�������"

	I2C1->DR = 0x40;						// �������� 0b 0100 0000	�������� ������

	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

	while (!(I2C1->SR1 & I2C_SR1_ADDR));	// ���� ����� �������� ������ �������
	while (!(I2C1->SR2 & I2C_SR2_MSL));		// ���� ��������� ������ "�������"
	while (!(I2C1->SR1 & I2C_SR1_TXE));		//

	I2C1->DR = 0x06;						// �������� 0b 0000 0110	�������� �������
	while (!(I2C1->SR1 & I2C_SR1_TXE));		//

	I2C1->DR = 0xFF;						// �������� 0b 1111 1111
	while (!(I2C1->SR1 & I2C_SR1_TXE));		//

	I2C1->DR = 0x00;						// �������� 0b 0000 0000
	while (!(I2C1->SR1 & I2C_SR1_TXE));

	while (!(I2C1->SR1 & I2C_SR1_BTF));		//

	I2C1->CR1 |= I2C_CR1_STOP;				//


	while (I2C1->SR2 & I2C_SR2_BUSY);		//

	I2C1->CR1 |= I2C_CR1_START;				// ���� �����
	while (!(I2C1->SR1 & I2C_SR1_SB));		// ��������� ����� �������

	I2C1->DR = 0x40;						// �������� 0b 0100 0000

	while (!(I2C1->SR1 & I2C_SR1_ADDR));	//
	while (!(I2C1->SR2 & I2C_SR2_MSL));		//
	while (!(I2C1->SR1 & I2C_SR1_TXE));		//

	I2C1->DR = 0x03;						// �������� 0b 0000 0011
	while (!(I2C1->SR1 & I2C_SR1_TXE));

	I2C1->DR = 0x00;						// �������� 0b 0000 0000
	while (!(I2C1->SR1 & I2C_SR1_TXE));

	while (!(I2C1->SR1 & I2C_SR1_BTF));

	I2C1->CR1 |= I2C_CR1_STOP;

	while (I2C1->SR2 & I2C_SR2_BUSY);
}


void I2C_led_test2(void) {

	while (I2C1->SR2 & I2C_SR2_BUSY);		// ���� ���� ���� �� �����������

	I2C1->CR1 |= I2C_CR1_START;				// ���� �����
	while (!(I2C1->SR1 & I2C_SR1_SB));		// ��������� ����� ������� � ����������� ���������� � "�������"

	I2C1->DR = 0x40;						// �������� 0b 0100 0000	�������� ������

	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

	while (!(I2C1->SR1 & I2C_SR1_ADDR));	// ���� ����� �������� ������ �������
	while (!(I2C1->SR2 & I2C_SR2_MSL));		// ���� ��������� ������ "�������"
	while (!(I2C1->SR1 & I2C_SR1_TXE));		//

	I2C1->DR = 0x06;						// �������� 0b 0000 0110	�������� �������
	while (!(I2C1->SR1 & I2C_SR1_TXE));		//

	I2C1->DR = 0xFF;						// �������� 0b 1111 1111
	while (!(I2C1->SR1 & I2C_SR1_TXE));		//

	I2C1->DR = 0x00;						// �������� 0b 0000 0000
	while (!(I2C1->SR1 & I2C_SR1_TXE));

	while (!(I2C1->SR1 & I2C_SR1_BTF));		//

	I2C1->CR1 |= I2C_CR1_STOP;				//


	while (I2C1->SR2 & I2C_SR2_BUSY);		//

	I2C1->CR1 |= I2C_CR1_START;				// ���� �����
	while (!(I2C1->SR1 & I2C_SR1_SB));		// ��������� ����� �������

	I2C1->DR = 0x40;						// �������� 0b 0100 0000

	while (!(I2C1->SR1 & I2C_SR1_ADDR));	//
	while (!(I2C1->SR2 & I2C_SR2_MSL));		//
	while (!(I2C1->SR1 & I2C_SR1_TXE));		//

	I2C1->DR = 0x03;						// �������� 0b 0000 0011
	while (!(I2C1->SR1 & I2C_SR1_TXE));

	I2C1->DR = 0x00;						// �������� 0b 0000 0000
	while (!(I2C1->SR1 & I2C_SR1_TXE));

	while (!(I2C1->SR1 & I2C_SR1_BTF));

	I2C1->CR1 |= I2C_CR1_STOP;

	while (I2C1->SR2 & I2C_SR2_BUSY);
}




