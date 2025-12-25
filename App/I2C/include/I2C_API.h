#pragma once
#include "stm32f7xx_hal.h"
#include "Config.h"

#ifdef __cplusplus
extern "C" {
#endif

void i2c_bus_init(I2C_HandleTypeDef* hi2c);
int  i2c_scan(uint8_t* found, uint8_t max);

#ifdef __cplusplus
}
#endif
