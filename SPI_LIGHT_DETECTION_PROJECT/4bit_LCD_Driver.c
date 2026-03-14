#include<lpc21xx.h>
#include"header.h"
#define RS 1<<17
#define RW 1<<18
#define EN 1<<19

void lcd_data (unsigned char data)
{
	unsigned int temp;
	IOCLR1=0x00FE0000;
	temp=(data&0xF0)<<16;
	IOSET1=temp;
	IOSET1=RS;
	IOCLR1=RW;
	IOSET1=EN;
	delay_ms(2,1);
	IOCLR1=EN;
	IOCLR1=0x00FE0000;
	temp=(data&0x0F)<<20;
	IOSET1=temp;
	IOSET1=RS;
	IOCLR1=RW;
	IOSET1=EN;
	delay_ms(2,1);
	IOCLR1=EN;
}

void lcd_cmd (unsigned char cmd)
{
	unsigned int temp;
	IOCLR1=0x00FE0000;
	temp=(cmd&0xF0)<<16;
	IOSET1=temp;
	IOCLR1=RS;
	IOCLR1=RW;
	IOSET1=EN;
	delay_ms(2,1);
	IOCLR1=EN;
	IOCLR1=0x00FE0000;
	temp=(cmd&0x0F)<<20;
	IOSET1=temp;
	IOCLR1=RS;
	IOCLR1=RW;
	IOSET1=EN;
	delay_ms(2,1);
	IOCLR1=EN;
}
	
void lcd_init (void)
{
	IODIR1|=0x00FE0000;
	PINSEL2|=0;
	lcd_cmd(0x02);
	lcd_cmd(0x03);
	lcd_cmd(0x0E);
	lcd_cmd(0x28);
	lcd_cmd(0x01);
}

void lcd_string (char*p)
{
	unsigned int c=0;
	while(*p)
	{
		lcd_data(*p);
		if (c==15)
			lcd_cmd(0xc0);
		p++;
		c++;
	}
}

void lcd_int (signed int p)
{
	int arr[100],i=0;
	if (p==0)
	{
		lcd_data('0');
		return;
	}
	else if (p<0)
	{
		lcd_data('-');
		p=-p;
	}
	while (p>0)
	{
		arr[i]=p%10;
		p=p/10;
		i++;
	}
	for (--i ; i>=0 ; i--)
	{
		lcd_data(arr[i]+48);
	}
}


void lcd_cgram (char*a)
{
	unsigned int i=0;
	lcd_cmd(0x40);
	for (i=0 ; i<=7 ; i++)
	{
		lcd_data (a[i]);
	}
}
	
