#include "motor.h"




void TIM1_PWM_Init(u16 arr,u16 psc)
{		 		
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	//
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);    
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);  

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_11;   //TIM_CH1 //TIM_CH4
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;         
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	TIM_TimeBaseStructure.TIM_Period = arr;               
	TIM_TimeBaseStructure.TIM_Prescaler =psc;              
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;           
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);        

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;      
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
	TIM_OCInitStructure.TIM_Pulse = 0;                            
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;     
//	
	TIM_OC1Init(TIM1, &TIM_OCInitStructure);
  TIM_OC4Init(TIM1, &TIM_OCInitStructure);

	TIM_CtrlPWMOutputs(TIM1,ENABLE);	                  
//
	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);     //CH1
	TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);     //CH2

	TIM_ARRPreloadConfig(TIM1, ENABLE);                   
	TIM_Cmd(TIM1, ENABLE);                                
 
} 


void TIM4_PWM_Init()
{  
 GPIO_InitTypeDef GPIO_InitStructure;
 TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
 TIM_OCInitTypeDef  TIM_OCInitStructure;
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); 
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO, ENABLE);  
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9; 
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 GPIO_Init(GPIOB, &GPIO_InitStructure); 

 TIM_TimeBaseStructure.TIM_Period = 99; 
 TIM_TimeBaseStructure.TIM_Prescaler =0; 
 TIM_TimeBaseStructure.TIM_ClockDivision = 0; 
 TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
 TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); 
 //???TIM4 Channel/2/3/4 PWM??  
 TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //???????:TIM????????2
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //??????
 TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //????:TIM???????
 TIM_OC1Init(TIM4, &TIM_OCInitStructure);  //??T??????????TIM4 OC1
 TIM_OC2Init(TIM4, &TIM_OCInitStructure);  //??T??????????TIM4 OC2
 TIM_OC3Init(TIM4, &TIM_OCInitStructure);  //??T??????????TIM4 OC3
 TIM_OC4Init(TIM4, &TIM_OCInitStructure);  //??T??????????TIM4 OC4 
  TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);  //??TIM4?CCR1????????
 TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);  //??TIM4?CCR2????????
 TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);  //??TIM4?CCR3????????
 TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);  //??TIM4?CCR4???????? 
 TIM_ARRPreloadConfig(TIM4,ENABLE);
 TIM_Cmd(TIM4, ENABLE);  //??TIM4
}




 void Motorspeed_set(int speed1,int speed2,int speed3,int speed4)
 {
      TIM_SetCompare1(TIM1,speed1); 
      TIM_SetCompare3(TIM4,speed2);
		  TIM_SetCompare4(TIM4,speed3); 
      TIM_SetCompare4(TIM1,speed4);
 }

/*    TIM4_PWM_Init(99£¬719);
      TIM_SetCompare1(TIM1,0); 
      TIM_SetCompare2(TIM1,0);
		  TIM_SetCompare3(TIM1,0); 
      TIM_SetCompare4(TIM1,0);


*/
