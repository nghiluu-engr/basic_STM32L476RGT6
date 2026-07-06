#include "button.h"
uint8_t count = 0;

void button_init(BUTTON *button, GPIO_TypeDef *button_port, uint16_t button_pin)
{
	button->button_port = button_port;
	button->button_pin = button_pin;
	
	button->button_filter = 1;
	button->button_handling = 0;
}

__weak void button_pressing_callback()
{
}
__weak void button_release_callback()
{
}


void button_handle(BUTTON *button)
{ 
	button->button_current = HAL_GPIO_ReadPin(button->button_port, button->button_pin);
	if (button->button_current != button->button_filter)
	{
		button->button_filter = button->button_current;
		button->time_debouncing = HAL_GetTick();
		button->button_handling = 1;
	}
	
	if (button->button_handling == 1 && HAL_GetTick() - button->time_debouncing > 15)
	{
		button->button_state = button->button_filter;
		button->button_handling = 2;
	}
	
	if (button->button_handling == 2)
	{
		if (button->button_state == 0)
		{
			button_pressing_callback();
		}
		else
		{
			button_release_callback();
			button->button_handling = 0;
		}
	}
}