#include "stm32f10x.h"                  // Device header

// 对 PWM 进行初始化：TIM2 CH1 -> PA0（舵机），CH2 -> PA1（呼吸灯）
void PWM_Init(void)
{
    /* 初始化时钟 */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); // 使能 TIM2 时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); // 使能 GPIOA 时钟

    /* PA0 (TIM2_CH1) 和 PA1 (TIM2_CH2) 配置为复用推挽输出 */
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    /* TIM2 CH2 对应 PA1 -> 使用 GPIO_Pin_1 */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* 配置 TIM2 基本参数：1MHz 计数（72MHz/72），周期 20000 -> 20ms */
    TIM_InternalClockConfig(TIM2);
	
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseStructure.TIM_Period = 100 - 1;
    TIM_TimeBaseStructure.TIM_Prescaler = 36 - 1;
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

    /* 初始化输出比较单元 OC1 (CH1) */
    TIM_OCInitTypeDef oc2;
    TIM_OCStructInit(&oc2);
    oc2.TIM_OCMode = TIM_OCMode_PWM1;
    oc2.TIM_OCPolarity = TIM_OCPolarity_High;
    oc2.TIM_OutputState = TIM_OutputState_Enable;
    oc2.TIM_Pulse = 0;
    TIM_OC2Init(TIM2, &oc2);

    TIM_Cmd(TIM2, ENABLE);
}

void PWM_SetCompare2(uint16_t comper)
{
    TIM_SetCompare2(TIM2, comper); // 设置 TIM2 的比较寄存器 2 的值
}