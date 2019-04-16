#include "LCD12864.h"

uchar code dis1[]={"有害气体浓度:"};
uchar code dis2[]={"输入密码："};
uchar code dis3[]={"无误！欢迎回家！"};
uchar code dis4[]={"错误！重新输入！"};
char Concentration[5];

void delay_1ms(uint x)
{
  uint i,j;
  for(j=0;j<x;j++)
      for(i=0;i<110;i++);
}

/*写指令数据到LCD*/
/*RS=L,RW=L,E=高脉冲，D0-D7=指令码。*/
void write_cmd(uchar cmd)
{
    LCD_RS=0;
	LCD_RW=0;
	LCD_EN=0;
	P0=cmd;
	delay_1ms(5);
	LCD_EN=1;
	delay_1ms(5);
	LCD_EN=0;
}

/*写显示数据到LCD*/
/*RS=H,RW=L,E=高脉冲，D0-D7=数据。*/
void write_dat(uchar dat)
{
    LCD_RS=1;
	LCD_RW=0;
	LCD_EN=0;
	P0=dat;
	delay_1ms(5);
	LCD_EN=1;
	delay_1ms(5);
	LCD_EN=0;
}

/*设定显示位置*/
void lcd_pos(uchar X,uchar Y)
{
   uchar  pos;
   if(X==0)
     {X=0x80;}
   else if(X==1)
     {X=0x90;}
   else if(X==2)
     {X=0x88;}
   else if(X==3)
     {X=0x98;}
   pos=X+Y;
   write_cmd(pos);           //显示地址
} 

/*LCD 初始化设定*/
void lcd_init()
{
   LCD_PSB=1;               //并口方式
   write_cmd(0x30);         //基本指令操作
   delay_1ms(5);
   write_cmd(0x0C);         //显示开，关光标
   delay_1ms(5);
   write_cmd(0x01);         //清除LCD的显示内容
   delay_1ms(5);
}

void Clean()
{
	LCD_PSB=1; 
	write_cmd(0x01);         //清除LCD的显示内容
    delay_1ms(5);
}

void write_s(uchar X,uchar Y,uchar dat[])
{
	uchar i;
	i=0;
	lcd_pos(X,Y);
	while(dat[i]!='\0')
	{ 
	   write_dat(dat[i]);   //显示字符
	   i++;
	}
}

char *ConcentrationTurn(uchar dat)
{	
	uchar i=0;
	dat=dat*100/255;
	/*Concentration[0]=dat/10+'0';
	Concentration[1]=dat%10+'0';
	Concentration[2]='%';
	Concentration[3]='\0';
    if(dat==100)
	{
		Concentration[0]='1';
		Concentration[1]='0';
		Concentration[2]='0';
		Concentration[3]='%';
		Concentration[4]='\0';	
	}*/
	if(dat<10)
	{
		Concentration[0]='0'+dat;
		Concentration[1]='%';
		Concentration[2]='\0';
	}else if(dat<100)
	{
		Concentration[0]=dat/10+'0';
		Concentration[1]=dat%10+'0';
		Concentration[2]='%';
		Concentration[3]='\0';
	}else
	{
		Concentration[0]='1';
		Concentration[1]='0';
		Concentration[2]='0';
		Concentration[3]='%';
		Concentration[4]='\0';
	}	
	
	return Concentration;
}
