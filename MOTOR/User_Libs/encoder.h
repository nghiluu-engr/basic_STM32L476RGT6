#ifndef ENCODER_H
#define ENCODER_H
#include "motor.h"

#define PI 3.14159265358
#define NUM_OF_TICKS_PER_REV 1400 // 7*4*50

typedef struct
{
	TIM_HandleTypeDef *htim_encoder;

	float velocity;
	float position;
} ENCODER;

void encoder_init(ENCODER *encoder);
void get_encoder_data(ENCODER *encoder);
void reset_encoder(ENCODER *encoder);


#endif