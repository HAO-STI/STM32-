#include "stm32f10x.h"                  
#include "Delay.h"
#include "OLED.h"
#include "PWM.h"
#include "Servo.h"
#include "key.h"
#include "Motor.h"


uint8_t KeyNum;
int16_t speed = 0;

int main(void)
{
	Motor_Init();
	OLED_Init();
	Key_Init();
	OLED_ShowString(1,1,"speed:");
	
	while (1)
	{
		KeyNum = Key_GetNum();
		if(KeyNum == 1)
		{
			speed += 10;
			if(speed>30)
			{
				speed = -10;
			}
		}
		Motor_setspeed(speed);
		OLED_ShowSignedNum(1,7,speed,3);
	}
}
