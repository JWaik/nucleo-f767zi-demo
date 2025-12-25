#include "I2C_API.h"
#include "I2C.h"
#include <cstdio>

static I2CBus* bus = nullptr;

void i2c_bus_init(I2C_HandleTypeDef* hi2c)
{
    static I2CBus instance(hi2c);
    bus = &instance;
    bus->init();
}

int i2c_scan(uint8_t* found, uint8_t max)
{
    uint8_t count = 0;
    if (bus)
    {
        bus->scan(found, count, max);
    }
    return count;
}
