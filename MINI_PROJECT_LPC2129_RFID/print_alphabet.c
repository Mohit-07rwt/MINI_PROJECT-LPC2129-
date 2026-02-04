#include<lpc21xx.h>
#include"header.h"
int main()
{
	int temp;
	uart0_init(9600);
	while(1)
	{
		uart0_string("enter char: ");
		temp=uart0_rx();
		uart0_tx(temp);
		uart0_tx(' ');
		uart0_int(temp);
		uart0_string("\r\n");
	}
}
