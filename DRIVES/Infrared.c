#include "Infrared.h"

void hw_detect_alarm() //���͵���⴫������Ⲣ��������
{
	hw_out=1;
	delay_ms(10);
	if(hw_out==0)
		{
			voice();		
		}			
}

void voice()//������������
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
