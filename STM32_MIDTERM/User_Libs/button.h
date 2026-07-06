#ifndef BUTTON_H
#define BUTTON_H
#include "main.h"

typedef struct
{
	GPIO_TypeDef *button_port;
	uint16_t button_pin;
	
	uint8_t button_current;
	uint8_t button_state;
	uint32_t time_debouncing;
	uint8_t button_filter;
	uint8_t button_handling;
} BUTTON;

void button_init(BUTTON *button, GPIO_TypeDef *button_port, uint16_t button_pin);
__weak void button_pressing_callback();
__weak void button_release_callback();
void button_handle(BUTTON *button);

#endif