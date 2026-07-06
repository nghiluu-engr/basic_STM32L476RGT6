#ifndef BATTERY_CHECK_H
#define BATTERY_CHECK_H
#include "main.h"
#include "led_rgb.h"
#include "buzzer.h"

typedef enum
{
	BATTERY_HIGH,
	BATTERY_LOW,
} BATTERY_STATE;

typedef struct
{
	ADC_HandleTypeDef *adc_battery;
	
	BATTERY_STATE battery_state;
	
	uint32_t time_start_check;
	float battery_now;
} BATTERY;

void battery_init(BATTERY *battery, ADC_HandleTypeDef *adc_battery);
void baterry_check(BATTERY *battery);
void show_battery_state(BATTERY *battery);

#endif