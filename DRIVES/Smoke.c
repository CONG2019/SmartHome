#include "Smoke.h"

uchar k;
sbit ST=P3^4;
sbit EOC=P3^5;
sbit OE=P3^6;
sbit AD_CLK=P3^7;

uchar ADC0809()
{
	uchar temp_=0x00;
	Data_ADC0809=0xff;
	//初始化高阻态
	OE=0;
	//转化初始化
	ST=0;
	//开始转换
	ST=1;
	ST=0;
	//外部中断等待AD转换结束
	while(EOC==0);
	//temp_=AD_data;
	OE=1;
	temp_=Data_ADC0809;
	OE=0;
	return temp_;
}

void delay(uint t)
{
	uint i,j;
	for(i=0;i<t;i++)
		for(j=0;j<10;j++);
}

void exter0() interrupt 1  
{
 	TH0=(65536-1000)/256;
 	TL0=(65536-1000)%256;//定时器重新赋初值
 	k++;
 	if(k==1)
	{
 		 AD_CLK=~AD_CLK;//波形翻转
 		 k=0;
 	}
}

void ESP_init()
{
	//Send("AT+CWJAP=\"Readmi\",\"88888888\"\r\n");
	//delay_ms(1000);
	delay_ms(2000);
	Send("AT+CIPSTART=\"TCP\",\"183.230.40.33\",80\r\n");
	delay_ms(500);
	Send("AT+CIPSTART=\"TCP\",\"183.230.40.33\",80\r\n");
	delay_ms(1000);
	Send("AT+CIPMODE=1\r\n");
	delay_ms(1000);
	Send("AT+CIPSEND\r\n");
	delay_ms(500);
}

void ESP_Send(unsigned char Data)
{
	Send("POST /devices/514175800/datapoints HTTP/1.1\r\napi-key:BB0kGglsdrC=j32ZPrX5E=4ofPo=\r\nHost:api.heclouds.com\r\nContent-Length:60\r\n\r\n{\"datastreams\":[{\"id\":\"S\",\"datapoints\":[{\"value\":\"");
	SendData(Data/10+'0');
	SendData(Data%10+'0');
    Send("\"}]}]}\"");
}

