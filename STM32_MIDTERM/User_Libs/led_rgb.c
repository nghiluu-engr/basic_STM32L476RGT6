#include "led_rgb.h"


void led_rgb_init(LED_RGB *led_rgb, GPIO_TypeDef *led_rgb_port[], uint16_t led_rgb_pin[])
{
	led_rgb->led_green_port = led_rgb_port[0];
	led_rgb->led_red_port = led_rgb_port[1];
	led_rgb->led_blue_port = led_rgb_port[2];
	
	led_rgb->led_green_pin = led_rgb_pin[0];
	led_rgb->led_red_pin = led_rgb_pin[1];
	led_rgb->led_blue_pin = led_rgb_pin[2];

}
void led_rgb_SetColor(LED_RGB *led_rgb, COLOR color)
{
	led_rgb->color = color;
	
	switch (led_rgb->color)
	{
		case GREEN:
			HAL_GPIO_WritePin(led_rgb->led_green_port, led_rgb->led_green_pin, 1);
			HAL_GPIO_WritePin(led_rgb->led_red_port, led_rgb->led_red_pin, 0);
			HAL_GPIO_WritePin(led_rgb->led_blue_port, led_rgb->led_blue_pin, 0);
			break;
		case RED:
			HAL_GPIO_WritePin(led_rgb->led_green_port, led_rgb->led_green_pin, 0);
			HAL_GPIO_WritePin(led_rgb->led_red_port, led_rgb->led_red_pin, 1);
			HAL_GPIO_WritePin(led_rgb->led_blue_port, led_rgb->led_blue_pin, 0);
			break;
		case BLUE:
			HAL_GPIO_WritePin(led_rgb->led_green_port, led_rgb->led_green_pin, 0);
			HAL_GPIO_WritePin(led_rgb->led_red_port, led_rgb->led_red_pin, 0);
			HAL_GPIO_WritePin(led_rgb->led_blue_port, led_rgb->led_blue_pin, 1);
			break;
		case YELLOW:
			HAL_GPIO_WritePin(led_rgb->led_green_port, led_rgb->led_green_pin, 1);
			HAL_GPIO_WritePin(led_rgb->led_red_port, led_rgb->led_red_pin, 1);
			HAL_GPIO_WritePin(led_rgb->led_blue_port, led_rgb->led_blue_pin, 0);
			break;
		case OFF:
			HAL_GPIO_WritePin(led_rgb->led_green_port, led_rgb->led_green_pin, 0);
			HAL_GPIO_WritePin(led_rgb->led_red_port, led_rgb->led_red_pin, 0);
			HAL_GPIO_WritePin(led_rgb->led_blue_port, led_rgb->led_blue_pin, 0);
			break;
		default: 
			break;
	}
}