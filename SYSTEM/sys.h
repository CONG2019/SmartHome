#ifndef __SYS_H__
#define __SYS_H__

#include "reg52.h"

typedef unsigned char u8;
typedef unsigned int u16;
typedef unsigned long int u32;

void init_uster();
void SendData(char Data);	 //·¢ËÍµ¥¸ö×Ö·û
void Send(char s[]);    //·¢ËÍ×Ö·û´®


#endif