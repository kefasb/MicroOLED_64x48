/*
    MicroView Arduino Library
    Copyright (C) 2014 GeekAmmo

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef SFE_MICROOLED_H
#define SFE_MICROOLED_H

#include <stdio.h>
#include <Arduino.h>
#include <avr/pgmspace.h>

#define swap(a, b) { uint8_t t = a; a = b; b = t; }

#define DC_DEFAULT		8
#define RST_DEFAULT		7
#define CS_DEFAULT		10
#define MODE_DEFAULT	MODE_SPI

#define I2C_ADDRESS_SA0_0 0b0111100
#define I2C_ADDRESS_SA0_1 0b0111101
#define I2C_COMMAND 0x00
#define I2C_DATA 0x40

// SS, SCK, MOSI already defined by original pins_arduino.h
//#define CS 		10
//#define SCK		13
//#define MOSI	11

#define BLACK 0
#define WHITE 1

#define LCDWIDTH			64
#define LCDHEIGHT			48
#define FONTHEADERSIZE		6

#define NORM				0
#define XOR					1

#define PAGE				0
#define ALL					1

#define WIDGETSTYLE0			0
#define WIDGETSTYLE1			1
#define WIDGETSTYLE2			2

#define SETCONTRAST 		0x81
#define DISPLAYALLONRESUME 	0xA4
#define DISPLAYALLON 		0xA5
#define NORMALDISPLAY 		0xA6
#define INVERTDISPLAY 		0xA7
#define DISPLAYOFF 			0xAE
#define DISPLAYON 			0xAF
#define SETDISPLAYOFFSET 	0xD3
#define SETCOMPINS 			0xDA
#define SETVCOMDESELECT		0xDB
#define SETDISPLAYCLOCKDIV 	0xD5
#define SETPRECHARGE 		0xD9
#define SETMULTIPLEX 		0xA8
#define SETLOWCOLUMN 		0x00
#define SETHIGHCOLUMN 		0x10
#define SETSTARTLINE 		0x40
#define MEMORYMODE 			0x20
#define COMSCANINC 			0xC0
#define COMSCANDEC 			0xC8
#define SEGREMAP 			0xA0
#define CHARGEPUMP 			0x8D
#define EXTERNALVCC 		0x01
#define SWITCHCAPVCC 		0x02

// Scroll
#define ACTIVATESCROLL 					0x2F
#define DEACTIVATESCROLL 				0x2E
#define SETVERTICALSCROLLAREA 			0xA3
#define RIGHTHORIZONTALSCROLL 			0x26
#define LEFT_HORIZONTALSCROLL 			0x27
#define VERTICALRIGHTHORIZONTALSCROLL	0x29
#define VERTICALLEFTHORIZONTALSCROLL	0x2A

typedef enum CMD {
	CMD_CLEAR,			//0
	CMD_INVERT,			//1
	CMD_CONTRAST,		//2
	CMD_DISPLAY,		//3
	CMD_SETCURSOR,		//4
	CMD_PIXEL,			//5
	CMD_LINE,			//6
	CMD_LINEH,			//7
	CMD_LINEV,			//8
	CMD_RECT,			//9
	CMD_RECTFILL,		//10
	CMD_CIRCLE,			//11
	CMD_CIRCLEFILL,		//12
	CMD_DRAWCHAR,		//13
	CMD_DRAWBITMAP,		//14
	CMD_GETLCDWIDTH,	//15
	CMD_GETLCDHEIGHT,	//16
	CMD_SETCOLOR,		//17
	CMD_SETDRAWMODE		//18
} commCommand_t;

typedef enum COMM_MODE{
	MODE_SPI,
	MODE_I2C,
	MODE_PARALLEL
} micro_oled_mode;

class MicroView : public Print{
public:
	//MicroView(void);
	MicroView(micro_oled_mode mode = MODE_DEFAULT, uint8_t rst = RST_DEFAULT, uint8_t dc = DC_DEFAULT, uint8_t cs = CS_DEFAULT);
	
	void begin(void);

//#if ARDUINO >= 100

	virtual size_t write(uint8_t);

//#else
//	virtual void   write(uint8_t);
//#endif

	// RAW LCD functions
	void command(uint8_t c);
	void data(uint8_t c);
	void setColumnAddress(uint8_t add);
	void setPageAddress(uint8_t add);
	
	// LCD Draw functions
	void clear(uint8_t mode);
	void clear(uint8_t mode, uint8_t c);
	void invert(boolean inv);
	void contrast(uint8_t contrast);
	void display(void);
	void setCursor(uint8_t x, uint8_t y);
	void pixel(uint8_t x, uint8_t y);
	void pixel(uint8_t x, uint8_t y, uint8_t color, uint8_t mode);
	void line(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1);
	void line(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t color, uint8_t mode);
	void lineH(uint8_t x, uint8_t y, uint8_t width);
	void lineH(uint8_t x, uint8_t y, uint8_t width, uint8_t color, uint8_t mode);
	void lineV(uint8_t x, uint8_t y, uint8_t height);
	void lineV(uint8_t x, uint8_t y, uint8_t height, uint8_t color, uint8_t mode);
	void rect(uint8_t x, uint8_t y, uint8_t width, uint8_t height);
	void rect(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t color , uint8_t mode);
	void rectFill(uint8_t x, uint8_t y, uint8_t width, uint8_t height);
	void rectFill(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t color , uint8_t mode);
	void circle(uint8_t x, uint8_t y, uint8_t radius);
	void circle(uint8_t x, uint8_t y, uint8_t radius, uint8_t color, uint8_t mode);
	void circleFill(uint8_t x0, uint8_t y0, uint8_t radius);
	void circleFill(uint8_t x0, uint8_t y0, uint8_t radius, uint8_t color, uint8_t mode);
	void drawChar(uint8_t x, uint8_t y, uint8_t c);
	void drawChar(uint8_t x, uint8_t y, uint8_t c, uint8_t color, uint8_t mode);
	void drawBitmap(void);
	uint8_t getLCDWidth(void);
	uint8_t getLCDHeight(void);
	void setColor(uint8_t color);
	void setDrawMode(uint8_t mode);

	// Font functions
	uint8_t getFontWidth(void);
	uint8_t getFontHeight(void);
	uint8_t getTotalFonts(void);
	uint8_t getFontType(void);
	uint8_t setFontType(uint8_t type);
	uint8_t getFontStartChar(void);
	uint8_t getFontTotalChar(void);

	// LCD Rotate Scroll functions	
	void scrollRight(uint8_t start, uint8_t stop);
	void scrollLeft(uint8_t start, uint8_t stop);
	void scrollVertRight(uint8_t start, uint8_t stop);
	void scrollVertLeft(uint8_t start, uint8_t stop);
	void scrollStop(void);
	void flipVertical(boolean flip);
	void flipHorizontal(boolean flip);
	
	//void doCmd(uint8_t index);
	
private:
	uint8_t csPin, dcPin, rstPin;
	uint8_t wrPin, rdPin, dPins[8];
	volatile uint8_t *wrport, *wrreg, *rdport, *rdreg;
	uint8_t wrpinmask, rdpinmask;
	micro_oled_mode interface;
	//volatile uint8_t *mosiport, *sckport;
	volatile uint8_t *ssport, *dcport, *ssreg, *dcreg;	// use volatile because these are fixed location port address
	uint8_t mosipinmask, sckpinmask, sspinmask, dcpinmask;
	uint8_t foreColor,drawMode,fontWidth, fontHeight, fontType, fontStartChar, fontTotalChar, cursorX, cursorY;
	uint16_t fontMapWidth;
	//unsigned char *fontsPointer[TOTALFONTS];
	static const unsigned char *fontsPointer[];
	
	void setup(micro_oled_mode mode, uint8_t rst, uint8_t dc, uint8_t cs);
	void setup(micro_oled_mode mode, uint8_t rst, uint8_t dc, uint8_t cs,
                      uint8_t wr, uint8_t rd, uint8_t d0, uint8_t d1, uint8_t d2, 
					  uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7);
					  
	// Communication
	void spiTransfer(byte data);
	void spiSetup();
	void i2cSetup();
	void i2cWrite(byte address, byte control, byte data);
	void parallelSetup();
	void parallelWrite(byte data, byte dc);
};

/*#define SPI_CLOCK_DIV4 0x00
#define SPI_CLOCK_DIV16 0x01
#define SPI_CLOCK_DIV64 0x02
#define SPI_CLOCK_DIV128 0x03
#define SPI_CLOCK_DIV2 0x04
#define SPI_CLOCK_DIV8 0x05
#define SPI_CLOCK_DIV32 0x06
//#define SPI_CLOCK_DIV64 0x07

#define SPI_MODE0 0x00
#define SPI_MODE1 0x04
#define SPI_MODE2 0x08
#define SPI_MODE3 0x0C

#define SPI_MODE_MASK 0x0C  // CPOL = bit 3, CPHA = bit 2 on SPCR
#define SPI_CLOCK_MASK 0x03  // SPR1 = bit 1, SPR0 = bit 0 on SPCR
#define SPI_2XCLOCK_MASK 0x01  // SPI2X = bit 0 on SPSR

class MVSPIClass {
public:
brief Transfer data byte via SPI port. 
  inline static byte transfer(byte _data);

  // SPI Configuration methods

  inline static void attachInterrupt();
  inline static void detachInterrupt(); // Default

  static void begin(); // Default
  static void end();

  static void setBitOrder(uint8_t);
  static void setDataMode(uint8_t);
  static void setClockDivider(uint8_t);
};

//extern MVSPIClass MVSPI;

byte MVSPIClass::transfer(byte _data) {
  SPDR = _data;
  while (!(SPSR & _BV(SPIF)))
    ;
  return SPDR;
}

void MVSPIClass::attachInterrupt() {
  SPCR |= _BV(SPIE);
}

void MVSPIClass::detachInterrupt() {
  SPCR &= ~_BV(SPIE);
}*/
#endif