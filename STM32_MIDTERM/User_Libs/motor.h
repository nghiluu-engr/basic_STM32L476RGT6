#ifndef MOTOR_H
#define MOTOR_H
#include "main.h"

typedef enum
{
	MOTOR_ON,
	MOTOR_OFF,
} MOTOR_STATE;


typedef struct
{
	TIM_HandleTypeDef *htim_motor;
	uint32_t htim_channel_motor;
	
	GPIO_TypeDef *STSP_RST_port;
	uint16_t STSP_RST_pin;
	
	GPIO_TypeDef *PHx_port;
	uint16_t PHx_pin;
	
	MOTOR_STATE motor_state;
	
	int duty_cycle;
	
} MOTOR;

void motor_init(MOTOR *motor, TIM_HandleTypeDef *htim_motor, uint32_t htim_channel_motor, GPIO_TypeDef *STSP_RST_port, uint16_t STSP_RST_pin,
	GPIO_TypeDef *PHx_port, uint16_t PHx_pin);
void enable_motor(MOTOR *motor);
void disable_motor(MOTOR *motor);
void set_motor_state(MOTOR *motor, MOTOR_STATE motor_state);
//void motor_set_speed(MOTOR *motor, int duty_cycle);

#endif