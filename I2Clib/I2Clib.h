#include "stm32f10x_i2c.h"

void I2C_Single_Write(I2C_TypeDef* I2Cx, uint8_t HW_address, uint8_t addr, uint8_t data);
uint8_t I2C_single_read(I2C_TypeDef* I2Cx, uint8_t HW_address, uint8_t addr);


