#include "I2C.h"
#include <cstdio>

I2CBus::I2CBus(I2C_HandleTypeDef* hi2c)
    : hi2c_(hi2c) {}

bool I2CBus::scan(uint8_t* found, uint8_t& count, uint8_t max) {
    count = 0;
    for (uint8_t addr = 1; addr < 127; addr++)
    {
        if (HAL_I2C_IsDeviceReady(hi2c_, addr << 1, 2, 10) == HAL_OK)
        {
            if (count < max)
            {
                found[count++] = addr;
            }
        }
    }
    return count > 0;
}

HAL_StatusTypeDef I2CBus::write(uint8_t addr, uint8_t reg, uint8_t data) {
    return HAL_I2C_Mem_Write(
        hi2c_,
        addr << 1,
        reg,
        I2C_MEMADD_SIZE_8BIT,
        &data,
        1,
        100
    );
}

HAL_StatusTypeDef I2CBus::read(uint8_t addr, uint8_t reg, uint8_t* data) {
    return HAL_I2C_Mem_Read(
        hi2c_,
        addr << 1,
        reg,
        I2C_MEMADD_SIZE_8BIT,
        data,
        1,
        100
    );
}
