#include "stm32f10x.h"                  // Device header
#include "PWM.h"
#include "Motor.h"

void Car_Init()
{
	Motor_Init();
}

void Go_Ahead()
{
	Motor_setLeftspeed(70);
	Motor_setRightspeed(70);
}

void Go_Back()
{
	Motor_setLeftspeed(-70);
	Motor_setRightspeed(-70);
}

void Turn_Left()
{
	Motor_setLeftspeed(0);
	Motor_setRightspeed(50);
}
void Turn_Right()
{
	Motor_setLeftspeed(50);
	Motor_setRightspeed(0);
}
void Stop()
{
	Motor_setLeftspeed(50);
	Motor_setRightspeed(0);
}