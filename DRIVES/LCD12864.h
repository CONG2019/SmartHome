#ifndef __LCD12864_H__
#define __LCD12864_H__

#include <reg52.h>
#include <intrins.h>
#include <stdlib.h>

#define uchar unsigned char
#define uint  unsigned int

/*端口定义*/
#define LCD_data P0            //数据口
sbit LCD_RS  = P2^6;           //寄存器选择输入
sbit LCD_RW  = P2^5;           //液晶读/写控制
sbit LCD_EN  = P2^7;           //液晶使能控制
sbit LCD_PSB = P3^2;           //串/并方式控制

extern uchar code dis1[];
extern uchar code dis2[];
extern uchar code dis3[];
extern uchar code dis4[];
extern char Concentration[]; 

void delay_1ms(uint x);
void write_cmd(uchar cmd);		/*写指令数据到LCD,RS=L,RW=L,E=高脉冲，D0-D7=指令码。*/
void write_dat(uchar dat);		/*写显示数据到LCD*/
void lcd_pos(uchar X,uchar Y);	/*设定显示位置*/
void lcd_init();				/*LCD 初始化设定*/
void Clean();				    //清屏
void write_s(uchar X,uchar Y,uchar dat[]);	   //显示字符串
char *ConcentrationTurn(uchar dat);  //将浓度数据转换成浓度

#endif