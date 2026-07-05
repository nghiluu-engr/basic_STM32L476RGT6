#ifndef MOTOR_H
#define MOTOR_H
#include "stm32l4xx_hal.h"
#include "main.h"

typedef struct 
{
	TIM_HandleTypeDef *htim_motor;
	uint32_t htim_channel_motor;
	
	GPIO_TypeDef *STSP_RST_port;
	uint16_t STSP_RST_pin;
	
	GPIO_TypeDef *PHx_port;
	uint16_t PHx_pin;
	
	GPIO_TypeDef *PWMx_port;
	uint16_t PWMx_pin;
	
	int duty_cycle;
} MOTOR;

typedef enum
{
	MOTOR_NULL,
	MOTOR_STAMPED,
	MOTOR_ERROR,
} MOTOR_STATUS;

void motor_init(MOTOR *motor, TIM_HandleTypeDef *htim_motor, uint32_t htim_channel_motor, GPIO_TypeDef *STSP_RST_port, uint16_t STSP_RST_pin, 
	GPIO_TypeDef *PHx_port, uint16_t PHx_pin, GPIO_TypeDef *PWMx_port, uint16_t PWMx_pin);
MOTOR_STATUS motor_status(MOTOR *motor);
void enable_motor(MOTOR *motor);
void disable_motor(MOTOR *motor);
void set_speed(MOTOR *motor, int duty_cycle);



#endif