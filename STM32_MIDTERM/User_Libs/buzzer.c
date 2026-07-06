#include "buzzer.h"

void buzzer_init(BUZZER *buzzer, TIM_HandleTypeDef *htim_buzzer, uint32_t htim_channel_buzzer)
{
	buzzer->htim_buzzer = htim_buzzer;
	buzzer->htim_channel_buzzer = htim_channel_buzzer;
	
	buzzer->buzzer_state = off;
	
	buzzer->time_start = HAL_GetTick();
}

static void pwm_set_duty(BUZZER *buzzer, uint8_t duty_cycle)
{
	if (duty_cycle > 90)
	{
		duty_cycle = 90;
	}
	HAL_TIMEx_PWMN_Start(buzzer->htim_buzzer, buzzer->htim_channel_buzzer);
	uint32_t arr = buzzer->htim_buzzer->Instance->ARR + 1;
	uint32_t ccr = (uint32_t)((arr * duty_cycle) / 100);
	__HAL_TIM_SET_COMPARE(buzzer->htim_buzzer, buzzer->htim_channel_buzzer, ccr);
}

void buzzer_SetState(BUZZER *buzzer, BUZZER_STATE buzzer_state)
{
	buzzer->buzzer_state = buzzer_state;
	
	switch (buzzer->buzzer_state)
	{
		case on:
			pwm_set_duty(buzzer, 50);
			break;
		case off:
			pwm_set_duty(buzzer, 0);
			break;
		default:
			break;
	}
}
	
void buzzer_toggle(BUZZER *buzzer)
{	
	if (buzzer->buzzer_state == on)
	{
		buzzer->buzzer_state = off;
	}
	else
	{
		buzzer->buzzer_state = on;
	}
	buzzer_SetState(buzzer, buzzer->buzzer_state);
}

void buzzer_BeepTick(BUZZER *buzzer, uint32_t time_ms)
{
	if (HAL_GetTick() - buzzer->time_start >= time_ms)
	{
		buzzer_toggle(buzzer);
		buzzer->time_start = HAL_GetTick();
	}
}