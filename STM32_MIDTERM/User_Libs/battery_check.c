#include "battery_check.h"

void battery_init(BATTERY *battery, ADC_HandleTypeDef *adc_battery)
{
	battery->adc_battery = adc_battery;
	
	battery->time_start_check = HAL_GetTick();
}
void baterry_check(BATTERY *battery)
{
	float adc_value = 0.0f;
	HAL_ADC_Start(battery->adc_battery);
	HAL_ADC_PollForConversion(battery->adc_battery, 1000);
	adc_value = HAL_ADC_GetValue(battery->adc_battery);
	HAL_ADC_Stop(battery->adc_battery);
	HAL_Delay(10);
	
	battery->battery_now = ((adc_value * 3.3f) / 4095.0f) * 3.0f;
}
void show_battery_state(BATTERY *battery)
{
	if (battery->battery_now < 7.5f)
	{
		battery->battery_state = BATTERY_HIGH;
	}
	else
	{
		battery->battery_state = BATTERY_LOW;
	}
}