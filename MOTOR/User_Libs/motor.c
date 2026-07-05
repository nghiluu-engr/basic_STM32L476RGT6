#include "motor.h"

void motor_init(MOTOR *motor, TIM_HandleTypeDef *htim_motor, uint32_t channel, GPIO_TypeDef *STSP_RST_port, uint16_t STSP_RST_pin, 
	GPIO_TypeDef *PHx_port, uint16_t PHx_pin, GPIO_TypeDef *PWMx_port, uint16_t PWMx_pin)
{
	motor->htim_motor = htim_motor;
	motor->htim_channel_motor = channel;
	
	motor->STSP_RST_port = STSP_RST_port;
	motor->STSP_RST_pin = STSP_RST_pin;
	
	motor->PHx_port = PHx_port;
	motor->PHx_pin = PHx_pin;
	
	motor->PWMx_port = PWMx_port;
	motor->PWMx_pin = PWMx_pin;
	
	motor->duty_cycle = 0;
	
	HAL_TIM_PWM_Start(motor->htim_motor, motor->htim_channel_motor);
	__HAL_TIM_SET_COMPARE(motor->htim_motor, motor->htim_channel_motor, 0);

}

void enable_motor(MOTOR *motor)
{
	HAL_GPIO_WritePin(motor->STSP_RST_port, motor->STSP_RST_pin, 1);
}
void disable_motor(MOTOR *motor)
{
	HAL_GPIO_WritePin(motor->STSP_RST_port, motor->STSP_RST_pin, 0);
}


static void pwm_set_duty(MOTOR *motor)
{
	uint32_t arr = motor->htim_motor->Instance->ARR + 1;
	uint32_t ccr = 0;
	
	if (motor->duty_cycle < 0)
	{
		motor->duty_cycle = -motor->duty_cycle;
	}
	if (motor->duty_cycle > 90)
	{
		motor->duty_cycle = 90;
	}
	
	ccr = (uint32_t)((motor->duty_cycle * arr) / 100);
	__HAL_TIM_SET_COMPARE(motor->htim_motor, motor->htim_channel_motor, ccr);
	
	
	
	
}
void set_speed(MOTOR *motor, int duty_cycle)
{
	motor->duty_cycle = duty_cycle;
	if (motor->duty_cycle < 0)
	{
		pwm_set_duty(motor);
		HAL_GPIO_WritePin(motor->PHx_port, motor->PHx_pin, 0);
	}
	else if (motor->duty_cycle > 0)
	{
		pwm_set_duty(motor);
		HAL_GPIO_WritePin(motor->PHx_port, motor->PHx_pin, 1);
	}
	else
	{
		__HAL_TIM_SET_COMPARE(motor->htim_motor, motor->htim_channel_motor, 0);
	}
}
