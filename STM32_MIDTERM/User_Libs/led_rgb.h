#ifndef LED_RGB_H
#define LED_RGB_H
#include "main.h"

typedef enum
{
	GREEN,
	RED,
	BLUE,
	YELLOW,
	OFF,
} COLOR;

typedef struct
{
	GPIO_TypeDef *led_green_port;
	GPIO_TypeDef *led_red_port;
	GPIO_TypeDef *led_blue_port;
	
	uint16_t led_green_pin;
	uint16_t led_red_pin;
	uint16_t led_blue_pin;
	
	COLOR color;
} LED_RGB;

void led_rgb_init(LED_RGB *led_rgb, GPIO_TypeDef *led_rgb_port[], uint16_t led_rgb_pin[]);
void led_rgb_SetColor(LED_RGB *led_rgb, COLOR color);

#endif