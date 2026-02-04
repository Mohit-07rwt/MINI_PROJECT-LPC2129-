#include<lpc21xx.h>
#include"header.h"
int main()
{
	int temp,num;
	uart0_init(9600);
	while(1)
	{
		num=0;
		uart0_string("enter digit: ");
		while(1)
		{
			temp=uart0_rx();
			if(temp==13)
				break;
			
			uart0_tx(temp);
			temp=temp-48;
			num=num*10+temp;			
		}
		uart0_string("binary : ");
		uart0_string("  ");
		uart0_binary(num);
		uart0_string("\n");
		
	}
}
