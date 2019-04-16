#include <reg52.h>
#include "sys.h"
#include "delay.h"
#include "keys.h"
#include "Infrared.h"
#include "LCD12864.H"
#include "Smoke.h"

unsigned char code table[16]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};	

char temp2;
unsigned char Dat=0;
char flag=1;

void main()
{	
     delay_ms(10);           //延时
	 init_uster();
	 Init_PassWord();
	 lcd_init();              //初始化LCD
	 //ESP_init();
	 //P2=table[1];
	 temp=0;
	 temp2=temp;

	 write_s(0,0,dis1);
	 write_s(0,6,ConcentrationTurn(Dat));

	 
	 while(1)
	 { 
		 GetKeys();
		 //SendData(temp);
		 if(flag)
		 {
			 hw_detect_alarm();
		 }
		 //
		 if((temp2-Dat>5)||(temp2-Dat<-5))
		 {
		 Clean();
		 write_s(0,0,dis1);
     	 write_s(0,6,ConcentrationTurn(Dat));			 //浓度有大于5的变化才刷新
		 temp2=Dat;	
		 }
		 Dat=ADC0809();
		 //ESP_Send(Dat);
		 //delay_ms(2000);	 
	 }
}


