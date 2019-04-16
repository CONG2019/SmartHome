#include "Infrared.h"

void hw_detect_alarm() //热释电红外传感器检测并报警函数
{
	hw_out=1;
	delay_ms(10);
	if(hw_out==0)
		{
			voice();		
		}			
}

void voice()//语音报警函数
{ 
    PLAYL=0;
	delay_ms(10);
	PLAYL=1;
	delay_s(2);	
}


void delay_s(uint x_s)
{
	uint i;
	for(i=0;i<x_s;i++)
		delay_ms(1000);
}
