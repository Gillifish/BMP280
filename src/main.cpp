#include <iostream>
#include "pico/stdlib.h"
#include "BMP280/BMP280.h"
#include "hardware/i2c.h"

#define I2C_PORT i2c0

int main(void)
{
    stdio_init_all();

    BMP280 bmp(I2C_PORT, 4, 5);

    int32_t temp = bmp.getTemp();

    while (1)
    {
        temp = bmp.getTemp();
        printf("%.2f\n", temp / 100.00);
        sleep_ms(1000);
    }
}
