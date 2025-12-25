#pragma once
#include "stm32f7xx_hal.h"
#include <cstdint>

class I2CBus {
public:
    explicit I2CBus(I2C_HandleTypeDef* hi2c);

    virtual void init(){};

    bool scan(uint8_t* found, uint8_t& count, uint8_t max);
    HAL_StatusTypeDef write(uint8_t addr, uint8_t reg, uint8_t data);
    HAL_StatusTypeDef read(uint8_t addr, uint8_t reg, uint8_t* data);

private:
    I2C_HandleTypeDef* hi2c_;
};
