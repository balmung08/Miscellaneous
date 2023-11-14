#ifndef __PWM_H
#define __PWM_H

#include "stm32f10x.h"	 

void TIM1_PWM_Init(u16 arr,u16 psc);
void TIM4_PWM_Init();
void Motorspeed_set(int speed1,int speed2,int speed3,int speed4);
#endif