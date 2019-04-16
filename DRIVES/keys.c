#include "keys.h"

unsigned char code InitialPassword[] = {0x00,0x01,0x02,0x04,0x05,0x06,0x08,0x09,0x0e};
unsigned char Password[16];

char ReadKeys()
{   
	u8 t=0XF7;	    
	char i,KeyValue;
	
	for(i=0;i<4;i++)	 //逐列扫描键盘
	{	
		 KEYS_PORT=t;    //让某一列为0
		 if(row0==0)	//逐行扫描有没有键被按下，如果有，则该行为0
		 {
		 	delay_ms(15);	  //延时去抖动
			if(row0==0)		   //判断是不是真的有按键按下
			{
				KeyValue=i;		//确定键值
				while(!row0);	 //等待松开按键
				//SendData(KeyValue);
				return KeyValue;	//返回键值
			}
		 }else if(row1==0)
		 {
		 	delay_ms(15);
			if(row1==0)
			{
				KeyValue=i+4;
				while(!row1);
				//SendData(KeyValue);
				return KeyValue;
			}
		 }else if(row2==0)
		 {
		 	delay_ms(15);
			if(row2==0)
			{
				KeyValue=i+8;
				while(!row2);
				//SendData(KeyValue);
				return KeyValue;
			}
		 }else if(row3==0)
		 {
		 	  delay_ms(15);
			if(row3==0)
			{
				KeyValue=i+12;
				while(!row3);
				//SendData(KeyValue);
				return KeyValue;
			}
		 }else
		 {
		 	t=_cror_(t,1);	  //没有扫描到按键被按下，扫面下一列
		 }
	}

	return -1;		//都没有按键按下，返回一个负值
}

void Init_PassWord()
{
	u8 i;
	for(i=0;i<9;++i)
	{
		 Password[i]=InitialPassword[i];		//将保存在程序存储器的密码加载到内存中，来初始化密码
	}

}

char GetKeys()
{
	 char key;
	 key = ReadKeys();

	 switch(key)
	 {
	 	case -1:
			return 0;
			break;
		case 0:
		case 1:
		case 2:
		case 4:				//如果输入的是数字，说明正在输入密码，进入输入密码函数
		case 5:
		case 6:
		case 8:
		case 9:
		case 10:
		case 13:
			GetPassword(key);
			Clean();
			write_s(0,0,dis1);
	     	write_s(0,6,ConcentrationTurn(temp));
			break;
		case 3:
			SetPassword();		   //设置密码函数
			Clean();
		    write_s(0,0,dis1);
     	    write_s(0,6,ConcentrationTurn(temp));
			break;
		case 7:
			flag=!flag;
			Clean();
			if(!flag)
			{
			     write_s(1,0,"已关人体红外报警");
			}else
			{
				 write_s(1,0,"已开人体红外报警");
			}
			delay_ms(1000);
			Clean();
		    write_s(0,0,dis1);
     	    write_s(0,6,ConcentrationTurn(temp));
			return 0;
			break;
		default :
			break;
	 }
	 return 0;
}

char GetPassword(char key)
{
	u8 times=3;
	u8 i;
	unsigned char Password2[16];

	
	//write_s(1,0,"输入密码：");

	while(times)
	{
		i=0; 
		Clean();
		write_s(1,0,"输入密码：");
		while(key!=0x0e)		//输入密码
		{
			switch(key)
			{
				case 0x0c:
					if(i>0)
					{
						i--;
						write_dat(0x7f);
					}
					break;
				case 0:
				case 1:
				case 2:
				case 4:
				case 5:
				case 6:
				case 8:
				case 9:
				case 10:
				case 13:
				write_dat('*');
				Password2[i]=key;
				i++;
				if(i>14)
				{
				   i=0;		//超出密码范围，重新输入
				   Clean();
		           write_s(1,0,"超出密码范围，请重新输入");
			 	   delay_ms(1000);
			 	   Clean();
				   write_s(1,0,"输入密码：");
				   //Send("超出密码范围，请重新输入");
				}
					break;
				default :
					break;
			}
			key=ReadKeys();	
		}
		Password2[i]=key;
		key=-1;	 //为下一次进入循环做准备


		for(i=0;Password[i]!=0x0e;i++)
		{
			if(Password2[i]!=Password[i])
			{
				break;
			}
		}
		if((Password[i]==0x0e)&&(Password2[i]==0x0e))
		{
			 Clean();
		     write_s(1,0,"解锁成功");
			 delay_ms(1000);
			 Clean();
			 //Send("密码正确\r\n");
			 return 1;
		}else{
			Clean();
			write_s(1,0,"密码错误");
			write_s(2,0,"请重新输入");
			delay_ms(1000);
			Clean();
			//Send("密码错误\r\n");
			times--;
		}
	}
	Clean();
	write_s(1,0,"报警");
	delay_ms(1000);
	Clean();
	//Send("报警\r\n");
	return 0;
}

void SetPassword()
{	
	u8 i;
	char key=-1;
	//Send("请先输入密码\r\n");
	Clean();
	write_s(1,0,"请先输入密码：");	
	 if(GetPassword(-1))
	 {
	 	i=0;
		Clean();
		write_s(1,0,"解锁成功");
		delay_ms(1000);
	    Clean();
		write_s(1,0,"新密码：");
	 	 while(key!=0x0e)		//输入密码
		{
			switch(key)
			{
				case 0x0c:
					if(i>0)
					{
						i--;
						write_dat(0x7f);
					}
					break;
				case 0:
				case 1:
				case 2:
				case 4:
				case 5:
				case 6:
				case 8:
				case 9:
				case 10:
				case 13:
				write_dat('*');
				Password[i]=key;
				i++;
				if(i>14)
				{
					i=0;		//超出密码范围，重新输入
				   Clean();
		           write_s(1,0,"超出密码范围，请重新输入");
			 	   delay_ms(1000);
			 	   Clean();
				   write_s(1,0,"新密码：");
				   //Send("超出密码范围，请重新输入");
				}
					break;
				default :
					break;
			}
			key=ReadKeys();	
		}
		Password[i]=key;
		Clean();
		write_s(1,0,"设置密码成功");
		delay_ms(1000);
	    Clean();
		//Send("设置密码成功\r\n");
	 }		  
}