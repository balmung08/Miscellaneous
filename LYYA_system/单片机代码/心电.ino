#include <Adafruit_SSD1306.h>
#define OLED_Address 0x3C
Adafruit_SSD1306 oled(1);
int x=0;                 /*定义。。。oled有关*/
int lastx=0;            /*定义。。。oled有关*/
int lasty=0;           /*定义。。。oled有关*/
int LastTime=0;          /*定义*/
bool BPMTiming=false;    /*定义bool型变量BPMTiming为”假“*/
bool BeatComplete=false;  /*定义bool型变量BeatComplete为”假“*/
int BPM=0;               /*定义bmp（心率）*/

 
#define UpperThreshold 550/*设置模拟值上限*/
#define LowerThreshold 500/*设置模拟值下限*/
 
void setup()
{
   Serial.begin(9600);    /*设置串口传输波特率9600*/
}

void loop() 
{
  if(x>127)  
  {
    x=0;
    lastx=x;
  }
 
  int value=analogRead(0);   /*定义value：读取模拟引脚0（pin0），返回[0-1023]数值，每次1us*/
  int y=20-(value/45);
  lasty=y;
  lastx=x;
               /*算bmp，但是本质上是去画oled的图，不用就不管*/

  if(value>UpperThreshold)
  {
    if(BeatComplete)                   /**/
    {
      BPM=millis()-LastTime;           /*millis()回传晶片开始执行到目前的毫秒数*/
      BPM=int(60/(float(BPM)/1000));   /**/
      BPMTiming=false;                 /*设置BPMTiming为”假“：还在运行*/
      BeatComplete=false;              /*设置BeatComplete为”假“：还在运行*/
    }
    if(BPMTiming==false)               /**/
    {
      LastTime=millis();               /**/
      BPMTiming=true;                  /*设置BPMTiming为”真“：还在运行*/
    }
    delay(0);

    Serial.println(BPM);

  }
  if((value<LowerThreshold)&(BPMTiming))/**/
    BeatComplete=true;            /**/
    // display bpm

  x++;
}