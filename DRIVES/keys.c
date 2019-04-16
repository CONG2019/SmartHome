#include "keys.h"

unsigned char code InitialPassword[] = {0x00,0x01,0x02,0x04,0x05,0x06,0x08,0x09,0x0e};
unsigned char Password[16];

char ReadKeys()
{   
	u8 t=0XF7;	    
	char i,KeyValue;
	
	for(i=0;i<4;i++)	 //����ɨ�����
	{	
		 KEYS_PORT=t;    //��ĳһ��Ϊ0
		 if(row0==0)	//����ɨ����û�м������£�����У������Ϊ0
		 {
		 	delay_ms(15);	  //��ʱȥ����
			if(row0==0)		   //�ж��ǲ�������а�������
			{
				KeyValue=i;		//ȷ����ֵ
				while(!row0);	 //�ȴ��ɿ�����
				//SendData(KeyValue);
				return KeyValue;	//���ؼ�ֵ
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
		 	t=_cror_(t,1);	  //û��ɨ�赽���������£�ɨ����һ��
		 }
	}

	return -1;		//��û�а������£�����һ����ֵ
}

void Init_PassWord()
{
	u8 i;
	for(i=0;i<9;++i)
	{
		 Password[i]=InitialPassword[i];		//�������ڳ���洢����������ص��ڴ��У�����ʼ������
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
		case 4:				//�������������֣�˵�������������룬�����������뺯��
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
			SetPassword();		   //�������뺯��
			Clean();
		    write_s(0,0,dis1);
     	    write_s(0,6,ConcentrationTurn(temp));
			break;
		case 7:
			flag=!flag;
			Clean();
			if(!flag)
			{
			     write_s(1,0,"�ѹ�������ⱨ��");
			}else
			{
				 write_s(1,0,"�ѿ�������ⱨ��");
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

	
	//write_s(1,0,"�������룺");

	while(times)
	{
		i=0; 
		Clean();
		write_s(1,0,"�������룺");
		while(key!=0x0e)		//��������
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
				   i=0;		//�������뷶Χ����������
				   Clean();
		           write_s(1,0,"�������뷶Χ������������");
			 	   delay_ms(1000);
			 	   Clean();
				   write_s(1,0,"�������룺");
				   //Send("�������뷶Χ������������");
				}
					break;
				default :
					break;
			}
			key=ReadKeys();	
		}
		Password2[i]=key;
		key=-1;	 //Ϊ��һ�ν���ѭ����׼��


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
		     write_s(1,0,"�����ɹ�");
			 delay_ms(1000);
			 Clean();
			 //Send("������ȷ\r\n");
			 return 1;
		}else{
			Clean();
			write_s(1,0,"�������");
			write_s(2,0,"����������");
			delay_ms(1000);
			Clean();
			//Send("�������\r\n");
			times--;
		}
	}
	Clean();
	write_s(1,0,"����");
	delay_ms(1000);
	Clean();
	//Send("����\r\n");
	return 0;
}

void SetPassword()
{	
	u8 i;
	char key=-1;
	//Send("������������\r\n");
	Clean();
	write_s(1,0,"�����������룺");	
	 if(GetPassword(-1))
	 {
	 	i=0;
		Clean();
		write_s(1,0,"�����ɹ�");
		delay_ms(1000);
	    Clean();
		write_s(1,0,"�����룺");
	 	 while(key!=0x0e)		//��������
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
					i=0;		//�������뷶Χ����������
				   Clean();
		           write_s(1,0,"�������뷶Χ������������");
			 	   delay_ms(1000);
			 	   Clean();
				   write_s(1,0,"�����룺");
				   //Send("�������뷶Χ������������");
				}
					break;
				default :
					break;
			}
			key=ReadKeys();	
		}
		Password[i]=key;
		Clean();
		write_s(1,0,"��������ɹ�");
		delay_ms(1000);
	    Clean();
		//Send("��������ɹ�\r\n");
	 }		  
}