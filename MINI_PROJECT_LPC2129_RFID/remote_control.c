#include<lpc21xx.h>
#include"header.h"
#define LED1 (1<<17)
#define LED2 (1<<18)
int main()
{
	unsigned int temp;
	IODIR0=LED1 | LED2;
	IOSET0=LED1 | LED2;
	uart0_init(9600);
	while(1)
	{
		uart0_string("enter option :");
		uart0_string("\n turn on LED1");
		uart0_string("\n turn on LED2");
		uart0_string("\n turn off LED1");
		uart0_string("\n turn off LED2");
		uart0_string("\r\n");
		
		temp=uart0_rx();
		uart0_tx(temp);
		
		switch(temp)
		{
			case 'a':
					IOCLR0=LED1;
					break;
		
			case 'b':
					IOSET0=LED1;
					break;
			
			case 'c':
					IOCLR0=LED2;
					break;
			
			case 'd':
					IOSET0=LED2;
					break;
			default:
					uart0_string("invalid option !!");
		}
	}
}
