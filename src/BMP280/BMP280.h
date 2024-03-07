#pragma once

#include <iostream>
#include "pico/stdlib.h"
#include "hardware/i2c.h"

#define I2C_PORT i2c0

class BMP280
{
    private:
        int m_addr = 0x77;

        uint8_t chipID;

        int32_t t_fine;
        uint16_t dig_t1;
        int16_t dig_t2, dig_t3;

        uint8_t init(int sda_pin, int scl_pin);
        void loadTempComp();
    public:
        BMP280(int sda_pin, int scl_pin);

        int32_t getRawTemp();
        int32_t getTemp();
        uint8_t readRegister(uint8_t reg);
};