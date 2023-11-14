#include "stm32f10x.h"
#include "IIC.h"
#include "delay.h"
#include "usart.h"
#include "stdio.h"
#include "math.h"
#include "sys.h"
#include "timer.h"
#include "motor.h"
#include "dac.h"
#include "adc.h"
#include "oled.h"
#include "usart3.h" 			 
#include "hc05.h"
#include "matrix_key.h"

#define PRINT(title, fmt, ...) printf("{"#title":"fmt"}\n", __VA_ARGS__);
/*
Ӳ���ӷ���
GY-39---STM32
CT-PB10
DR-PB11
DAC-PA4
ADC-PA1
*/

int main(void)
{

//���������ݶ���
  u8  raw_data[13]={0};
  uint16_t data_16[2]={0};
  uint32_t Lux=0; 
	float light;
	const double Pi=3.14;
	float I;
	float U;
	float	R=10.959;
	float Initial_light_intensity;//�����ǿ
	float Light_intensity_after_deflection;//ƫת���ǿ
  float angle0=0;//ƫת�Ƕ�
	float angle=0;
	float Target_light_intensity;//��������Ŀ���ǿ
	float Light_intensity;//���������յ��Ĺ�ǿ
	int adcx;
	int n;
	int dac;
	u8 reclen=0;  
	char status;
	int set;
	int start=0;
	float err;
	float err_abs;
  typedef struct
{
    uint32_t P;
    uint16_t Temp;
    uint16_t Hum;
    uint16_t Alt;
} bme;
bme Bme={0,0,0,0};
  
  //���������ղ��ֳ�ʼ��
	delay_init();	 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	uart_init(115200);
	I2C_GPIO_Config();
  delay_ms(200);
 	Adc_Init();		  		//ADC��ʼ��
	Dac1_Init();				//DAC��ʼ��
	OLED_Init();
  OLED_Clear(0);  
  TIM4_PWM_Init(99,719);
  Matrix_Key_Init();

	//��ѭ����
	Target_light_intensity=1700;
	
	while(1)
	{  							
		  //���������ݽ���
			if(Single_ReadI2C(0xb6,0x04,raw_data,10))
			{
				Bme.Temp=(raw_data[0]<<8)|raw_data[1];
				data_16[0]=(((uint16_t)raw_data[2])<<8)|raw_data[3];
				data_16[1]=(((uint16_t)raw_data[4])<<8)|raw_data[5];
				Bme.P=(((uint32_t)data_16[0])<<16)|data_16[1];
				Bme.Hum=(raw_data[6]<<8)|raw_data[7];
				Bme.Alt=(raw_data[8]<<8)|raw_data[9];
			}
			if(Single_ReadI2C(0xb6,0x00,raw_data,4))
			{data_16[0]=(((uint16_t)raw_data[0])<<8)|raw_data[1];
			 data_16[1]=(((uint16_t)raw_data[2])<<8)|raw_data[3];
			 Lux=(((uint32_t)data_16[0])<<16)|data_16[1];}
	n = Lux/100;
			 
err = Target_light_intensity-n;
err_abs=abs(err);
			 
//�������ж�
if(err>=0)
	set = 100;
if(err<0)
	set = 0;

 //���ε���������50���ظ�����
 if(err_abs>=50)
 { 
 dac =err_abs/100*2481;
 if(dac>=2481)
 {dac =2481;
 }}
 
//С��50��΢��				
if(err_abs<=50)
 {
	 if(err>0)
	 {dac=dac-10;}
		if(err<0)
	 {dac=dac+10;}
}
 
 //�ж��ظ�����
 if(err_abs>=50)
 { 
 dac =err_abs/200*2481;
 if(dac>=2481)
 {dac =2481;
 }
 }
 //������̸���
 Matrix_Key_Test();
if(N==1)
		Target_light_intensity -= 5;
if(N==2)
		Target_light_intensity += 5;
if(N==3)
		Target_light_intensity -= 20;
if(N==4)
		Target_light_intensity += 20;
if(N==5)
		Target_light_intensity -= 50;
if(N==6)
		Target_light_intensity += 50;
if(N==7)
		Target_light_intensity -= 100;
if(N==8)
		Target_light_intensity += 100;

			//���ִ�в���			
      TIM_SetCompare1(TIM4,set);
			TIM_SetCompare2(TIM4,set);

 //���ǰ�޷�
 if(dac>=2481)
 dac =2481;
  if(dac<=10)
 dac =10;
			DAC_SetChannel1Data(DAC_Align_12b_R, dac);//2.0v

			PRINT("light", "%d", n);
	
			//�����ʾ����
			OLED_ShowString(10,1,"light:",16);
      OLED_ShowString(10,3,"target:",16);		 
	    OLED_ShowString(10,5,"Vout:",16);
	    OLED_ShowNum(80,1,n,4,16);
			OLED_ShowNum(80,3,Target_light_intensity,4,16);			
			OLED_ShowNum(80,5,dac,5,16);
N = 0;
		}		

	}
