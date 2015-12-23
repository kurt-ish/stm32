#ifndef MYLIB_H
#define MYLIB_H

#define MIN_ANGLE 6560
#define MAX_ANGLE 6760
/*********************************************************************/
/***************	��������� ������� 	******************************/

typedef enum{
	DriveInitial = 0,
	DriveDetection = 1,
	DriveReadyForw = 2,
	DriveReadyBack = 3,
	DriveRunForv = 4,
	DriveRunBack = 5,
	DriveAlarm = 6,
	DriveNotPhasA = 7,
	DriveNotPhasB = 8,
	DriveNotPhasC = 9,
}DriveState_t;


enum {
	OverFrequency = 1,
	UnderFrequency = 2,
	OverLoad_A = 34,
	OverLoad_C = 35,
}Alarm;

typedef enum{
ANGLE_MIN_ERROR = 1,
ANGLE_NOT_ERROR = 2,
ANGLE_MAX_ERROR = 3,
}angle_error_t;

extern uint8_t impuls_timer_2, impuls_timer_3;

/*
 * GPIO_Mode_Out_PP � ����� push-pull, �����������
 * GPIO_Mode_Out_OD � ����� open-drain (�������� ����)
 * GPIO_Mode_AF_PP � �������������� �������, push-pull
 * GPIO_Mode_AF_OD � �������������� �������, open-drain
 * GPIO_Mode_AIN � ���������� ������������������ ����
 * GPIO_Mode_IN_FLOATING � ������������������ ����
 * GPIO_Mode_IPU � ���� � ��������� � �������
 * GPIO_Mode_IPD � ���� � ��������� � �����
 */

/*********************************************************************/
/*******************	������� �������� �������	******************/
void Delay(__IO uint32_t nCount);

/*
void I2C_Cmd(I2C_TypeDef* I2Cx, FunctionalState NewState)
{

 *** Check the parameters ***
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
  ��������� ����
 *** Enable the selected I2C peripheral ***
    I2Cx->CR1 |= CR1_PE_Set; (0x0001)
  }
  else
  {
  ����� ����
 *** Disable the selected I2C peripheral ***
    I2Cx->CR1 &= CR1_PE_Reset; (0xFFFE)
  }
}
*/

/******		������ ����� �� ������� ����	***********************/






uint16_t interrupt_time_count (void);

uint8_t interrupt_time_value (void);

uint8_t interrupt_time_error (void);

void Second_Pulse_Sequence (void);
void First_Pulse_Sequence (void);       
//void open_tiristor(alfa_pid);
#endif
