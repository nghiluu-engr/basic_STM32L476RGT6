#ifndef ROBOT_CONTROL_H
#define ROBOT_CONTROL_H
#include "main.h"
#include "led_rgb.h"
#include "button.h"
#include "buzzer.h"
#include "battery_check.h"
#include "motor.h"

typedef enum
{
	ROBOT_IDLE,
	ROBOT_READY,
	ROBOT_RUN,
} ROBOT_STATE;

typedef struct
{
	LED_RGB *robot_led_rgb;
	BUTTON *robot_button;
	BUZZER *robot_buzzer;
	BATTERY *robot_battery;
	MOTOR *robot_motor_a;
	MOTOR *robot_motor_b;
	
	ROBOT_STATE robot_state;
} ROBOT;

void robot_init(ROBOT *robot, LED_RGB *robot_led_rgb, BUTTON *robot_button, BUZZER *robot_buzzer, 
	BATTERY *robot_battery, MOTOR *robot_motor_a, MOTOR *robot_motor_b);
void robot_idle(ROBOT *robot);
void robot_ready(ROBOT *robot);
void robot_run(ROBOT *robot);



#endif
