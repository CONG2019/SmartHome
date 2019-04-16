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

char ReadKeys();	  //读取按键的键值，没有按键时返回-1
void Init_PassWord();   //用于初始化密码
char GetKeys();		//获取按键的键值，并根据不同的键值进入不同功能的函数
char GetPassword(char key);		//获取密码，并判断是否正确
void SetPassword();		//设置密码

#endif