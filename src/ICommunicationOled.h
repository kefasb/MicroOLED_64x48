/*
 * ICommunicationOled.h
 *
 * Author: Piotr Borkowski
 * 2017
 * https://github.com/kefasb/MicroOLED_64x48
 *
 * Refactored original version from:
 * https://github.com/sparkfun/SparkFun_Micro_OLED_Arduino_Library
 *
 */

#ifndef ICOMMUNICATION_OLED_H_
#define ICOMMUNICATION_OLED_H_

class ICommunicationOled {
public:
    virtual ~ICommunicationOled() {
    }

    virtual void setup() const = 0;
    virtual void writeData(uint8_t data) const = 0;
    virtual void writeCommand(uint8_t command) const = 0;
};

#endif /* ICOMMUNICATION_OLED_H_ */
