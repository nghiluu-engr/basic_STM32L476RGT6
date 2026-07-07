#include "motor.h"

void motor_init(MOTOR *motor, TIM_HandleTypeDef *htim_motor, uint32_t htim_channel_motor, GPIO_TypeDef *STSP_RST_port, uint16_t STSP_RST_pin,
	GPIO_TypeDef *PHx_port, uint16_t PHx_pin)
{
	motor->htim_motor = htim_motor;
	motor->htim_channel_motor = htim_channel_motor;
	
	motor->STSP_RST_port = STSP_RST_port;
	motor->STSP_RST_pin = STSP_RST_pin;
	
	motor->PHx_port = PHx_port;
	motor->PHx_pin = PHx_pin;
	
//	motor->motor_state = MOTOR_OFF;
//	disable_motor(motor);
}
void enable_motor(MOTOR *motor)
{
	HAL_GPIO_WritePin(motor->STSP_RST_port, motor->STSP_RST_pin, 1);
}
void disable_motor(MOTOR *motor)
{
	HAL_GPIO_WritePin(motor->STSP_RST_port, motor->STSP_RST_pin, 0);
}

static void pwm_set_duty(MOTOR *motor, int duty_cycle)
{
	if (duty_cycle < 0)
	{
		duty_cycle = -duty_cycle;
	}
	if (duty_cycle > 90)
	{
		duty_cycle = 90;
	}
	HAL_TIM_PWM_Start(motor->htim_motor, motor->htim_channel_motor);
	uint32_t arr = motor->htim_motor->Instance->ARR + 1;
	uint32_t ccr = (uint32_t)((duty_cycle * arr) / 100);
	__HAL_TIM_SET_COMPARE(motor->htim_motor, motor->htim_channel_motor, ccr);
}

void set_motor_state(MOTOR *motor, MOTOR_STATE motor_state)
{
	motor->motor_state = motor_state;
	
	switch (motor->motor_state)
	{
		case MOTOR_ON:
			motor->duty_cycle = 50;
			pwm_set_duty(motor, motor->duty_cycle);
			break;
		case MOTOR_OFF:
			motor->duty_cycle = 0;
			pwm_set_duty(motor, motor->duty_cycle);
			break;
		default:
			break;
	}
}
//void motor_set_speed(MOTOR *motor, int duty_cycle)
//{
//	motor->duty_cycle = duty_cycle;
//	if (motor->duty_cycle < 0)
//	{
//		pwm_set_duty(motor, motor->duty_cycle);
//		HAL_GPIO_WritePin(motor->PHx_port, motor->PHx_pin, 0);
//		motor->motor_state = MOTOR_ON;
//	}
//	else if (motor->duty_cycle > 0)
//	{
//		pwm_set_duty(motor, motor->duty_cycle);
//		HAL_GPIO_WritePin(motor->PHx_port, motor->PHx_pin, 1);
//		motor->motor_state = MOTOR_ON;
//	}
//	else
//	{
//		__HAL_TIM_SET_COMPARE(motor->htim_motor, motor->htim_channel_motor, 0);
//		motor->motor_state = MOTOR_OFF;
//	}
//}