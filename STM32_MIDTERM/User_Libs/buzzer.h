#ifndef BUZZER_H
#define BUZZER_H
#include "main.h"

typedef enum
{
	on,
	off,
} BUZZER_STATE;

typedef struct
{
	TIM_HandleTypeDef *htim_buzzer;
	uint32_t htim_channel_buzzer;
	
	BUZZER_STATE buzzer_state;
	
	uint32_t time_start;
} BUZZER;

void buzzer_init(BUZZER *buzzer, TIM_HandleTypeDef *htim_buzzer, uint32_t htim_channel_buzzer);
void buzzer_SetState(BUZZER *buzzer, BUZZER_STATE buzzer_state);
void buzzer_toggle(BUZZER *buzzer);
void buzzer_BeepTick(BUZZER *buzzer, uint32_t time_ms);

#endif