#ifndef __INFRARED_H__
#define __INFRARED_H__

#include <reg52.h>
#include "delay.h"

#define uint unsigned int

sbit PLAYL=P2^0; //播放录音引脚
sbit hw_out=P2^1; //热释电红外传感器OUT引脚
sbit hw_led=P2^2;
void hw_detect_alarm();
void voice();
void delay_s(uint x_s);

#endif