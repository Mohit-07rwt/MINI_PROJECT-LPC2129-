#include<lpc21xx.h>
#include"header.h"
void lcd_init()
{
	IODIR1=(0xfe<<16);
	PINSEL2=0X0;
	//IOCLR1=1<<19;
	lcd_cmd(0x02);
	lcd_cmd(0x28);
	lcd_cmd(0x0e);
	lcd_cmd(0x01);
}
void lcd_data(unsigned char data)
{
	//HIGHER NIBBLE
	IOCLR1=(0xfe<<16);
	IOSET1=((data & 0XF0)<<16);
	IOSET1=(1<<17);
	IOCLR1=(1<<18);
	IOSET1=(1<<19);
	delay_ms(2);
	IOCLR1=(1<<19);
	//LOWER NIBBLE
	IOCLR1=(0xfe<<16);
	IOSET1=((data & 0X0F)<<20);
	IOSET1=(1<<17);
	IOCLR1=(1<<18);
	IOSET1=(1<<19) ;
	delay_ms(2);
	IOCLR1=(1<<19);
}
void lcd_cmd(unsigned char cmd)
{
	IOCLR1=(0xfe<<16);
	IOSET1=((cmd & 0xf0)<<16);
	IOCLR1=(1<<17);
	IOCLR1=(1<<18);
	IOSET1=(1<<19) ;
	delay_ms(2);
	IOCLR1=(1<<19);
	IOCLR1=(0xfe<<16);
	IOSET1=((cmd & 0x0f)<<20);
	IOCLR1=(1<<17);
	IOCLR1=(1<<18);
	IOSET1=(1<<19);
	delay_ms(2);
	IOCLR1=(1<<19);
}
void lcd_string(char *ptr)
{
	while(*ptr!=0)
	{
		lcd_data(*ptr);
		ptr++;
	}
}
void lcd_integer(int num)
{
	int i;
	char a[10];
	if(num<0)
	{
		lcd_data('-');
		num=-num;
	}
	
	if(num==0)
	{
		lcd_data('0');
		return;
	}
	
	for(i=0;num;i++,num=num/10)
	a[i]=num%10+48;
	for(i=i-1;i>=0;i--)
	lcd_data(a[i]);
}


void lcd_float(float f)
{
	int num;
	if(f<0)
	{
		lcd_data('-');
		f=-f;
	}
	
	if(f==0)
	{
		lcd_string("0.0");
		return;
	}
	
	num=f;
	lcd_integer(num);
	lcd_data('.');
	num=(f-num)*100;
	lcd_integer(num);
}

