#ifndef __LCD12864_H__
#define __LCD12864_H__

#include <reg52.h>
#include <intrins.h>
#include <stdlib.h>

#define uchar unsigned char
#define uint  unsigned int

/*�˿ڶ���*/
#define LCD_data P0            //���ݿ�
sbit LCD_RS  = P2^6;           //�Ĵ���ѡ������
sbit LCD_RW  = P2^5;           //Һ����/д����
sbit LCD_EN  = P2^7;           //Һ��ʹ�ܿ���
sbit LCD_PSB = P3^2;           //��/����ʽ����

extern uchar code dis1[];
extern uchar code dis2[];
extern uchar code dis3[];
extern uchar code dis4[];
extern char Concentration[]; 

void delay_1ms(uint x);
void write_cmd(uchar cmd);		/*дָ�����ݵ�LCD,RS=L,RW=L,E=�����壬D0-D7=ָ���롣*/
void write_dat(uchar dat);		/*д��ʾ���ݵ�LCD*/
void lcd_pos(uchar X,uchar Y);	/*�趨��ʾλ��*/
void lcd_init();				/*LCD ��ʼ���趨*/
void Clean();				    //����
void write_s(uchar X,uchar Y,uchar dat[]);	   //��ʾ�ַ���
char *ConcentrationTurn(uchar dat);  //��Ũ������ת����Ũ��

#endif