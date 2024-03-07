#include "BMP280.h"

BMP280::BMP280(int sda_pin, int sdl_pin)
{
    init(sda_pin, sdl_pin);
}

uint8_t BMP280::init(int sda_pin, int sdl_pin)
{
    i2c_init(I2C_PORT, 400000);
    gpio_set_function(sda_pin, GPIO_FUNC_I2C);
    gpio_set_function(sdl_pin, GPIO_FUNC_I2C);
    gpio_pull_up(sda_pin);
    gpio_pull_up(sdl_pin);

    sleep_ms(1000);
    uint8_t reg = 0xD0;
    uint8_t chipID[1];

    i2c_write_blocking(I2C_PORT, m_addr, &reg, 1, true);
    i2c_read_blocking(I2C_PORT, m_addr, chipID, 1, false);

    // use the "handheld device dynamic" optimal setting (see datasheet)
    uint8_t buf[2];

    // 500ms sampling time, x16 filter
    const uint8_t reg_config_val = ((0x04 << 5) | (0x05 << 2)) & 0xFC;

    // send register number followed by its corresponding value
    buf[0] = 0xF5;
    buf[1] = reg_config_val;
    i2c_write_blocking(I2C_PORT, m_addr, buf, 2, false);

    // osrs_t x1, osrs_p x4, normal mode operation
    const uint8_t reg_ctrl_meas_val = (0x01 << 5) | (0x03 << 2) | (0x03);
    buf[0] = 0xF4;
    buf[1] = reg_ctrl_meas_val;
    i2c_write_blocking(I2C_PORT, m_addr, buf, 2, false);

    loadTempComp();

    return chipID[0];
}

void BMP280::loadTempComp()
{
    uint8_t buf[6], reg;

    reg = 0x88 | 0x80;

    i2c_write_blocking(I2C_PORT, m_addr, &reg, 1, true);
    i2c_read_blocking(I2C_PORT, m_addr, buf, 6, false);

    dig_t1 = buf[0] | (buf[1] << 8);
    dig_t2 = buf[2] | (buf[3] << 8);
    dig_t3 = buf[4] | (buf[5] << 8);
}

int32_t BMP280::getRawTemp()
{
    uint8_t reg = 0xFA;
    uint8_t temp[3];

    i2c_write_blocking(I2C_PORT, m_addr, &reg, 1, true);
    i2c_read_blocking(I2C_PORT, m_addr, temp, 3, false);

    return ((uint32_t) temp[0] << 12) | ((uint32_t) temp[1] << 4) | ((uint32_t) temp[2] >> 4);
}

int32_t BMP280::getTemp()
{
    int32_t adc_T = getRawTemp();

    int32_t var1, var2, T;
    
    var1 = ((((adc_T >> 3) - ((int32_t) dig_t1 << 1))) * ((int32_t) dig_t2)) >> 11;
    var2 = (((((adc_T >> 4) - ((int32_t) dig_t1)) * ((adc_T >> 4) - ((int32_t) dig_t1))) >> 12) * ((int32_t) dig_t3)) >> 14;

    t_fine = var1 + var2;
    T = (t_fine * 5 + 128) >> 8;
    
    return T;
}

uint8_t BMP280::readRegister(uint8_t reg)
{
    uint8_t val = 0;

    i2c_write_blocking(I2C_PORT, m_addr, &reg, 1, true);
    i2c_read_blocking(I2C_PORT, m_addr, &val, 1, false);

    return val;
}