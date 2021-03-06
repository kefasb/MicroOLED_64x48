/****************************************************************************** 
 SFE_MicroOLED.h
 Header file for the MicroOLED Arduino Library

 Jim Lindblom @ SparkFun Electronics
 October 26, 2014
 https://github.com/sparkfun/Micro_OLED_Breakout/tree/master/Firmware/Arduino/libraries/SFE_MicroOLED

 Modified by:
 Emil Varughese @ Edwin Robotics Pvt. Ltd.
 July 27, 2015
 https://github.com/emil01/SparkFun_Micro_OLED_Arduino_Library/

 Modified by:
 Piotr Borkowski
 2017
 https://github.com/kefasb/MicroOLED_64x48

 This file defines the hardware interface(s) for the Micro OLED Breakout. Those
 interfaces include SPI, I2C and a parallel bus.

 Development environment specifics:
 Arduino 1.0.5
 Arduino Pro 3.3V
 Micro OLED Breakout v1.0

 This code was heavily based around the MicroView library, written by GeekAmmo
 (https://github.com/geekammo/MicroView-Arduino-Library), and released under
 the terms of the GNU General Public License as published by the Free Software
 Foundation, either version 3 of the License, or (at your option) any later
 version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
 ******************************************************************************/

#ifndef SFE_MICROOLED_H
#define SFE_MICROOLED_H

#include <stdio.h>
#include <Arduino.h>

#if defined(__AVR__) || defined(__arm__)
#include <avr/pgmspace.h>
#else
#include <pgmspace.h>
#endif

#include "ICommunicationOled.h"

#define swap(a, b) { uint8_t t = a; a = b; b = t; }

enum class OledDrawColor {
    BLACK = 0, WHITE = 1
};

#define LCDWIDTH			64
#define LCDHEIGHT			48
#define FONTHEADERSIZE		6

enum class OledDrawMode {
    NORM = 0, XOR = 1
};

enum class OledClearMode {
    PAGE = 0, ALL = 1
};

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

enum class OledCommand {
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
};

enum class OledCommunicationMode {
    MODE_SPI, MODE_I2C, MODE_PARALLEL
};

/**
 * Defines clockwise rotation of OLED display
 */
enum class OledRotationMode {
    NONE, DEGREE90, DEGREE180, DEGREE270
};

enum class OledLineFoldMode {
    ALWAYS, // Fold on new line character or when text does not fit a line
    NEW_LINE_ONLY, // Fold only when new line character is to be printed
    NEW_LINE_OPTIONAL // Fold on new line when it is not at the end of line what would cause inserting two lines. First because of line folding itself and second because of new line character
};

class MicroOLED: public Print {
public:
// Constructor(s)
    MicroOLED(ICommunicationOled& communication, uint8_t rstPin);
    MicroOLED(ICommunicationOled& communication, uint8_t rstPin,
            OledRotationMode rotation, OledLineFoldMode lineFoldMode);
    virtual ~MicroOLED() {
    }

    void begin(void);
    virtual size_t write(uint8_t);

// RAW LCD functions
    void command(uint8_t c);
    void data(uint8_t c);
    void setColumnAddress(uint8_t add);
    void setPageAddress(uint8_t add);

// LCD Draw functions
    void clear(OledClearMode mode);
    void clear(OledClearMode mode, uint8_t character);
    void invert(boolean inv);
    void contrast(uint8_t contrast);
    void display(void);
    void setCursor(uint8_t x, uint8_t y);
    void pixel(uint8_t x, uint8_t y);
    void pixel(uint8_t x, uint8_t y, OledDrawColor color, OledDrawMode mode);
    void line(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1);
    void line(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1,
            OledDrawColor color, OledDrawMode mode);
    void lineH(uint8_t x, uint8_t y, uint8_t width);
    void lineH(uint8_t x, uint8_t y, uint8_t width, OledDrawColor color,
            OledDrawMode mode);
    void lineV(uint8_t x, uint8_t y, uint8_t height);
    void lineV(uint8_t x, uint8_t y, uint8_t height, OledDrawColor color,
            OledDrawMode mode);
    void rect(uint8_t x, uint8_t y, uint8_t width, uint8_t height);
    void rect(uint8_t x, uint8_t y, uint8_t width, uint8_t height,
            OledDrawColor color, OledDrawMode mode);
    void rectFill(uint8_t x, uint8_t y, uint8_t width, uint8_t height);
    void rectFill(uint8_t x, uint8_t y, uint8_t width, uint8_t height,
            OledDrawColor color, OledDrawMode mode);
    void circle(uint8_t x, uint8_t y, uint8_t radius);
    void circle(uint8_t x, uint8_t y, uint8_t radius, OledDrawColor color,
            OledDrawMode mode);
    void circleFill(uint8_t x0, uint8_t y0, uint8_t radius);
    void circleFill(uint8_t x0, uint8_t y0, uint8_t radius, OledDrawColor color,
            OledDrawMode mode);
    void drawChar(uint8_t x, uint8_t y, uint8_t c);
    void drawChar(uint8_t x, uint8_t y, uint8_t c, OledDrawColor color,
            OledDrawMode mode);
    void drawBitmap(uint8_t * bitArray);
    uint8_t getLCDWidth(void);
    uint8_t getLCDHeight(void);
    void setColor(OledDrawColor color);
    void setDrawMode(OledDrawMode mode);
    uint8_t *getScreenBuffer(void);

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

private:
    const ICommunicationOled& communication;
    const uint8_t rstPin;
    const OledRotationMode rotation;
    const OledLineFoldMode lineFoldMode;

    volatile uint8_t *wrport, *wrreg, *rdport, *rdreg;
    uint8_t wrpinmask, rdpinmask;
    volatile uint8_t *ssport, *dcport, *ssreg, *dcreg; // use volatile because these are fixed location port address
    uint8_t mosipinmask, sckpinmask, sspinmask, dcpinmask;
    OledDrawMode drawMode;
    OledDrawColor foreColor;
    uint8_t fontWidth, fontHeight, fontType, fontStartChar, fontTotalChar,
            cursorX, cursorY;
    uint16_t fontMapWidth;
    static const unsigned char *fontsPointer[];

    OledDrawColor invertColor(OledDrawColor color);

// Communication
    void spiTransfer(byte data);
    void spiSetup();
    void i2cSetup();
    void i2cWrite(byte address, byte control, byte data);
    void parallelSetup();
    void parallelWrite(byte data, byte dc);

    void initDisplaySequence();
    void initDisplayReset();
    uint8_t softwareLcdWidth() const;
    uint8_t softwareLcdHeight() const;
};
#endif
