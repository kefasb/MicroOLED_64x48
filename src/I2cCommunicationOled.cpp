/*
 * I2cCommunicationOled.cpp
 *
 * Author: Piotr Borkowski
 */

#include <Wire.h>
#include "I2cCommunicationOled.h"

I2cCommunicationOled::I2cCommunicationOled() :
        I2cCommunicationOled(OLED_I2C_DEFAULT_ADDRESS) {
}

I2cCommunicationOled::I2cCommunicationOled(uint8_t i2cAddress) :
        i2cAddress(i2cAddress) {
}

I2cCommunicationOled::~I2cCommunicationOled() {
}

void I2cCommunicationOled::setup() const {
    Wire.begin();
}

void I2cCommunicationOled::writeData(uint8_t data) const {
    Wire.beginTransmission(i2cAddress);
    Wire.write(OLED_I2C_DATA);
    Wire.write(data);
    Wire.endTransmission();
}

void I2cCommunicationOled::writeCommand(uint8_t command) const {
    Wire.beginTransmission(i2cAddress);
    Wire.write(OLED_I2C_COMMAND);
    Wire.write(command);
    Wire.endTransmission();
}
