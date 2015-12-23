/*********************************************************************/
/*******	Управляющие сигналы на тиристоры и симистор		**********/
#define THYRISTOR_VS1_ON	GPIO_SetBits(GPIOD,GPIO_Pin_10)
#define THYRISTOR_VS1_OFF	GPIO_ResetBits(GPIOD,GPIO_Pin_10)
#define THYRISTOR_VS2_ON	GPIO_SetBits(GPIOD,GPIO_Pin_11)
#define THYRISTOR_VS2_OFF	GPIO_ResetBits(GPIOD,GPIO_Pin_11)
#define THYRISTOR_VS3_ON	GPIO_SetBits(GPIOD,GPIO_Pin_12)
#define THYRISTOR_VS3_OFF	GPIO_ResetBits(GPIOD,GPIO_Pin_12)
#define THYRISTOR_VS4_ON	GPIO_SetBits(GPIOD,GPIO_Pin_13)
#define THYRISTOR_VS4_OFF	GPIO_ResetBits(GPIOD,GPIO_Pin_13)
#define THYRISTOR_VS5_ON	GPIO_SetBits(GPIOD,GPIO_Pin_14)
#define THYRISTOR_VS5_OFF	GPIO_ResetBits(GPIOD,GPIO_Pin_14)
#define THYRISTOR_VS6_ON	GPIO_SetBits(GPIOD,GPIO_Pin_15)
#define THYRISTOR_VS6_OFF	GPIO_ResetBits(GPIOD,GPIO_Pin_15)

#define THYRISTOR_IMPULS_TIME		100
#define THYRISTOR_ON_INTERVAL 		3233

/*********************************************************************/
/***********	Цифровые входа: включение и отключение		**********/
#define	DIGITAL_OUT_1_ON	GPIO_SetBits(GPIOE,GPIO_Pin_6)
#define	DIGITAL_OUT_1_OFF	GPIO_ResetBits(GPIOE,GPIO_Pin_6)
#define	DIGITAL_OUT_2_ON	GPIO_SetBits(GPIOE,GPIO_Pin_5)
#define	DIGITAL_OUT_2_OFF	GPIO_ResetBits(GPIOE,GPIO_Pin_5)
#define	DIGITAL_OUT_3_ON	GPIO_SetBits(GPIOE,GPIO_Pin_4)
#define	DIGITAL_OUT_3_OFF	GPIO_ResetBits(GPIOE,GPIO_Pin_4)
#define	DIGITAL_OUT_4_ON	GPIO_SetBits(GPIOC,GPIO_Pin_13)
#define	DIGITAL_OUT_4_OFF	GPIO_ResetBits(GPIOC,GPIO_Pin_13)

/*********************************************************************/
/***********	Переключатели для конфигурации		******************/
#define DIP_SWITCH_PIN_1	(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_2)
#define DIP_SWITCH_PIN_2	(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7)
#define DIP_SWITCH_PIN_3	(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_8)
#define DIP_SWITCH_PIN_4	(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_9)
#define DIP_SWITCH_PIN_5	(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_10)
#define DIP_SWITCH_PIN_6	(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_11)
#define DIP_SWITCH_PIN_7	(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_12)
#define DIP_SWITCH_PIN_8	(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_8)

/*********************************************************************/
/***********	Адрес I2C микросхемы на пульте управления	**********/
#define	PCA9555_I2C_ADDRESS		0x40

/*********************************************************************/
/***********	Адреса регистров микросхемы PCA9555		**************/
#define	PCA9555_READ_PORT0		0x00
#define	PCA9555_READ_PORT1		0x01
#define	PCA9555_SET_PORT0		0x02
#define	PCA9555_SET_PORT1		0x03
#define	PCA9555_INVERT_PORT0	0x04
#define	PCA9555_INVERT_PORT1	0x05
#define	PCA9555_CONFIG_PORT0	0x06
#define	PCA9555_CONFIG_PORT1	0x07

/*********************************************************************/
/************	Номера портов PORT0 микросхемы PCA9555	**************/
#define	PCA_PORT0_PIN_0		0x01
#define	PCA_PORT0_PIN_1		0x02
#define	PCA_PORT0_PIN_2		0x04
#define	PCA_PORT0_PIN_3		0x08
#define	PCA_PORT0_PIN_4		0x10
#define	PCA_PORT0_PIN_5		0x20
#define	PCA_PORT0_PIN_6		0x40
#define	PCA_PORT0_PIN_7		0x80

/*********************************************************************/
/************	Номера портов PORT1 микросхемы PCA9555 ***************/
#define	PCA_PORT1_PIN_0		0x01
#define	PCA_PORT1_PIN_1		0x02
#define	PCA_PORT1_PIN_2		0x04
#define	PCA_PORT1_PIN_3		0x08
#define	PCA_PORT1_PIN_4		0x10
#define	PCA_PORT1_PIN_5		0x20
#define	PCA_PORT1_PIN_6		0x40
#define	PCA_PORT1_PIN_7		0x80

/*********************************************************************/
/************	Номера портов PORT1 микросхемы PCA9555 ***************/
#define	BUTTON_S1	0xFE
#define	BUTTON_S2	0xFD
#define	BUTTON_S3	0xFB
#define	BUTTON_S4	0xF7
#define	BUTTON_S5	0x7F
#define	BUTTON_S6	0xBF
#define	BUTTON_S7	0xDF
#define	BUTTON_S8	0xEF
#define	BUTTON_OFF	0xFF

