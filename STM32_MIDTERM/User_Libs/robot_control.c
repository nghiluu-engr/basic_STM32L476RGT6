#include "robot_control.h"


void robot_init(ROBOT *robot, LED_RGB *robot_led_rgb, BUTTON *robot_button, BUZZER *robot_buzzer, 
	BATTERY *robot_battery, MOTOR *robot_motor_a, MOTOR *robot_motor_b)
{
	robot->robot_led_rgb = robot_led_rgb;
	robot->robot_button = robot_button;
	robot->robot_buzzer = robot_buzzer;
	robot->robot_battery = robot_battery;
	robot->robot_motor_a = robot_motor_a;
	robot->robot_motor_b = robot_motor_b;
	
	robot->robot_state = ROBOT_IDLE;
}



void robot_idle(ROBOT *robot)
{
	led_rgb_SetColor(robot->robot_led_rgb, GREEN);
	robot->robot_state = ROBOT_READY;
}
void robot_ready(ROBOT *robot)
{
	switch (robot->robot_battery->battery_state)
	{
		case BATTERY_HIGH:
			led_rgb_SetColor(robot->robot_led_rgb, GREEN);
			robot->robot_state = ROBOT_RUN;
			break;
		case BATTERY_LOW:
			led_rgb_SetColor(robot->robot_led_rgb, RED);
			buzzer_BeepTick(robot->robot_buzzer, 50);
			break;
		default:
			break;
	}
}
void robot_run(ROBOT *robot)
{
	led_rgb_SetColor(robot->robot_led_rgb, YELLOW);
	motor_set_speed(robot->robot_motor_a, 50);
	motor_set_speed(robot->robot_motor_b, -50);
}

