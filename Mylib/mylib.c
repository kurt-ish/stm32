#include "stm32f10x.h"
#include "stm32f10x_tim.h"
#include "mylib.h"
#include "defines.h"



//static DriveState_t DriveState;

static angle_error_t error;


void Delay(__IO uint32_t nCount)
{
    for (; nCount != 0; nCount--);
}


/************************************************************************************************/
/****************	������ ��������� ������������� dip.2	*************************************/
/*if (GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7)==ENABLE) {
	I2C_Single_Write(I2C1, PCA9555_I2C_ADDRESS, PCA9555_SET_PORT0, 0x5F);		// �������� ����������
}
else {
	I2C_Single_Write(I2C1, PCA9555_I2C_ADDRESS, PCA9555_SET_PORT0, 0xBF);		// �������� ����������
}*/



/******		������ ����� �� ������� ����	***********************/


uint16_t interrupt_time_count (void){
	uint16_t wer;
	TIM_Cmd(TIM6, DISABLE);                                     // ���������� ������.
    wer = TIM_GetCounter(TIM6);									// ��������� ������� �������.
    if (wer<MIN_ANGLE){
        error=ANGLE_MIN_ERROR;
    }
    else if (wer>MAX_ANGLE){
        error=ANGLE_MAX_ERROR;
    }
    else{
        error=ANGLE_NOT_ERROR;
        TIM_SetCounter(TIM6, 0);									// ������������� ������� ������� � ��������.
    }
    TIM_Cmd(TIM6, ENABLE);   									// ������ ������.
    return wer;
}

uint8_t interrupt_time_value (void){
	return TIM_GetCounter(TIM6);
}

uint8_t interrupt_time_error (void){
    return error;
}

void First_Pulse_Sequence (void){
    if (impuls_timer_2 == 11) {
            THYRISTOR_VS3_ON; THYRISTOR_VS6_ON;
            TIM_SetCounter(TIM2, THYRISTOR_IMPULS_TIME);		// Выставляем угол открытия тиристора.
            TIM_Cmd(TIM2, ENABLE);								// Старт таймера.
            impuls_timer_2 = 12;
    } else if (impuls_timer_2 == 12) {
            THYRISTOR_VS3_OFF; THYRISTOR_VS6_OFF;
            TIM_SetCounter(TIM3, THYRISTOR_ON_INTERVAL);		// Выставляем угол открытия тиристора 60гр
            TIM_Cmd(TIM3, ENABLE);								// Старт таймера.
            impuls_timer_2 = 0;
            impuls_timer_3 = 13;

    } else if (impuls_timer_2 == 21) {
            THYRISTOR_VS5_ON; THYRISTOR_VS2_ON;
            TIM_SetCounter(TIM2, THYRISTOR_IMPULS_TIME);		// Выставляем угол открытия тиристора
            TIM_Cmd(TIM2, ENABLE);								// Старт таймера.
            impuls_timer_2 = 22;
    } else if (impuls_timer_2 == 22) {
            THYRISTOR_VS5_OFF; THYRISTOR_VS2_OFF;
            TIM_SetCounter(TIM3, THYRISTOR_ON_INTERVAL);		// Выставляем угол открытия тиристора 60гр
            TIM_Cmd(TIM3, ENABLE);								// Старт таймера.
            impuls_timer_2 = 0;
            impuls_timer_3 = 23;

    } else if (impuls_timer_2 == 31) {
            THYRISTOR_VS1_ON; THYRISTOR_VS4_ON;
            TIM_SetCounter(TIM2, THYRISTOR_IMPULS_TIME);		// Выставляем угол открытия тиристора
            TIM_Cmd(TIM2, ENABLE);								// Старт таймера.
            impuls_timer_2 = 32;
    } else if (impuls_timer_2 == 32) {
            THYRISTOR_VS1_OFF; THYRISTOR_VS4_OFF;
            TIM_SetCounter(TIM3, THYRISTOR_ON_INTERVAL);		// Выставляем угол открытия тиристора 60гр
            TIM_Cmd(TIM3, ENABLE);								// Старт таймера.
            impuls_timer_2 = 0;
            impuls_timer_3 = 33;

    }
}
void Second_Pulse_Sequence (void){
    if (impuls_timer_3 == 13) {
            THYRISTOR_VS3_ON; THYRISTOR_VS2_ON;
            TIM_SetCounter(TIM3, THYRISTOR_IMPULS_TIME);		// Выставляем угол открытия тиристора
            TIM_Cmd(TIM3, ENABLE);
            impuls_timer_3 = 14;
    } else if (impuls_timer_3 == 14) {
            THYRISTOR_VS3_OFF; THYRISTOR_VS2_OFF;
            impuls_timer_3 = 0;

    } else if (impuls_timer_3 == 23) {
            THYRISTOR_VS5_ON; THYRISTOR_VS4_ON;
            TIM_SetCounter(TIM3, THYRISTOR_IMPULS_TIME);		// Выставляем угол открытия тиристора
            TIM_Cmd(TIM3, ENABLE);
            impuls_timer_3 = 24;
    } else if (impuls_timer_3 == 24) {
            THYRISTOR_VS5_OFF; THYRISTOR_VS4_OFF;
            impuls_timer_3 = 0;

    } else if (impuls_timer_3 == 33) {
            THYRISTOR_VS1_ON; THYRISTOR_VS6_ON;
            TIM_SetCounter(TIM3, THYRISTOR_IMPULS_TIME);		// Выставляем угол открытия тиристора
            TIM_Cmd(TIM3, ENABLE);
            impuls_timer_3 = 34;
    } else if (impuls_timer_3 == 34) {
            THYRISTOR_VS1_OFF; THYRISTOR_VS6_OFF;
            impuls_timer_3 = 0;
    }
}



































