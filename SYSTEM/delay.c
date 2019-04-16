#include "sys.h"
#include "delay.h"
//晶振为11.0592MHz可用
void init_delay(){
    TMOD&=0XF0;
	TMOD|=0X01;
    TH0=0;
    TL0=0;
}

void delay_min10us(u16 t){
    u8 L,H;
    //t=t-7;    //减去后面指令耗费的时间
    L=t;
    t>>=8;    
    H=t;
    TL0=0;
    TH0=0;
    TR0=1;   //开始计时
    while(TL0<L);
    while(TH0<H);
    TR0=0;
}

/*void delay_max255us(u8 t){
    #pragma asm
	MOV A,R7
	CLR C						 //大于26us可用
	RRC A
	SUBB A,#0DH
	MOV R7,A;
	loop: DJNZ R7,loop
	#pragma endasm 	
}*/

void delay_ms1(){
    TL0=0;
    TH0=0;
    TR0=1;
    while(TL0<0x9a);
    while(TH0<0x03);
    while(TL0<0x9a);
    TR0=0;
}

void delay_ms(u16 t){
   /*for(;t>0;t--){
        delay_ms1();	   //延时比较准
    }  */
  unsigned int i,j;
  for(j=0;j<t;j++)
      for(i=0;i<110;i++);
}