#ifndef __DELAY_H__
#define __DELAY_H__

#include "sys.h"

void init_delay();
void delay_min10us(u16 t);
//void delay_max255us(u8 t);
void delay_ms1();
void delay_ms(u16 t);

#endif
