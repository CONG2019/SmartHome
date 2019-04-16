#ifndef __SMOKE_H__
#define __SMOKE_H__

#include "sys.h"

#define uint unsigned int
#define uchar unsigned char
#define Data_ADC0809 P1

extern uchar k;

uchar ADC0809();
void delay(uint t);
void exter0() interrupt 1 ;


#endif