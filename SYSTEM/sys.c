#include "sys.h"

void init_uster()
{
	/*TMOD=0X20;
	SCON= 0X40;   //方式一不允许接收
	PCON=0X00;
	TH1=0XFD;
	TL1=0XFD;
	TR1=1; */
	EA = 1; //总中断打开
	TH0=(65536-1000)/256;
	TL0=(65536-1000)%256;
	ET0=1;//开定时器0中断
	TR0=1;//启动定时器0
	TMOD=0x21;
	SCON=0x40;	
	TH1=0xFD;
	TL1=0xFD;
	TR1=1;
}

void SendData(unsigned char Data)
{
	SBUF= Data;
	while(!TI);
	TI=0;
}

void Send(unsigned char s[])    //发送字符串
{
	u8 i;
	for(i=0;s[i]!='\0';i++)
	{
		 SendData(s[i]);
	}
}

