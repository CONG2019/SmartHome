#ifndef __KEYS_H__
#define __KEYS_H__

#include "sys.h"
#include "delay.h"
#include "intrins.h"
#include "LCD12864.h"

#define KEYS_PORT P0

sbit row0=P0^7;
sbit row1=P0^6;
sbit row2=P0^5;
sbit row3=P0^4;
unsigned char code InitialPassword[];
unsigned char Password[];
extern char temp;
extern char flag;

char ReadKeys();	  //��ȡ�����ļ�ֵ��û�а���ʱ����-1
void Init_PassWord();   //���ڳ�ʼ������
char GetKeys();		//��ȡ�����ļ�ֵ�������ݲ�ͬ�ļ�ֵ���벻ͬ���ܵĺ���
char GetPassword(char key);		//��ȡ���룬���ж��Ƿ���ȷ
void SetPassword();		//��������

#endif