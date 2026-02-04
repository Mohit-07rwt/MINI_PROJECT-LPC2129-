#include<lpc21xx.h>
#include"header.h"
int main()
{
	unsigned int temp;
	lcd_init();
	lcd_data('A');
	lcd_data('B');
	uart0_init(9600);
	while(1)
	{
		temp=uart0_rx();
		uart0_tx(temp);
		lcd_data(temp);
	}
}
