#include "I2Clib/I2Clib.h"

void I2C_Single_Write(I2C_TypeDef* I2Cx, uint8_t HW_address, uint8_t addr, uint8_t data)
{
	I2C_GenerateSTART(I2Cx, ENABLE);
		while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT));
	I2C_Send7bitAddress(I2Cx, HW_address, I2C_Direction_Transmitter);
		while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
	I2C_SendData(I2Cx, addr);
		while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	I2C_SendData(I2Cx, data);
		while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	I2C_GenerateSTOP(I2Cx, ENABLE);
		while(I2C_GetFlagStatus(I2Cx, I2C_FLAG_BUSY));
}

uint8_t I2C_single_read(I2C_TypeDef* I2Cx, uint8_t HW_address, uint8_t command)
{
	uint8_t data1;
	uint8_t data2;
		while(I2C_GetFlagStatus(I2Cx, I2C_FLAG_BUSY));
	I2C_GenerateSTART(I2Cx, ENABLE);
		while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT));
	I2C_Send7bitAddress(I2Cx, HW_address, I2C_Direction_Transmitter);
		while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
	I2C_SendData(I2Cx, command);
		while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	I2C_GenerateSTART(I2Cx, ENABLE);
		while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT));
	I2C_Send7bitAddress(I2Cx, HW_address, I2C_Direction_Receiver);
		while(!I2C_CheckEvent(I2Cx,I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
	data1 = I2C_ReceiveData(I2Cx);
		while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_RECEIVED));
	data2 = I2C_ReceiveData(I2Cx);
		while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_RECEIVED));
	I2C_AcknowledgeConfig(I2Cx, DISABLE);
	I2C_GenerateSTOP(I2Cx, ENABLE);
		while(I2C_GetFlagStatus(I2Cx, I2C_FLAG_BUSY));
	//return data1;
	return data2;
}
