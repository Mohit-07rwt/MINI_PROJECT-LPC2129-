#include <lpc21xx.h>
#include "header.h"
#define THRE ((U0LSR>>5)&1)
#define RDR ((U0LSR)&1)

// UART0 INITIALISATION //
void uart0_init(unsigned int baud)
{
	int a[]={15,60,30,0,15};
	unsigned int pclk=a[VPBDIV]*1000000; // set pclk
	unsigned int res=0;
	res=pclk/(16*baud);
	PINSEL0|=0x5; // set p0.0=tx and p0.1=rx
	U0LCR=0x83; // unlock baudrate settings
	U0DLL=res&0xFF; //set value for baud rate (LSB)
	U0DLM=(res>>8)&0xFF; // set value for baud rate (MSB)
	U0LCR=0x03; // lock baudrate settings
}

// UART0 TRANSMIT DATA //
void uart0_tx (unsigned char data)
{
	U0THR=data; // tranfer data to U0THR
	while(THRE==0); // wait till data transmit and U0THR is empty.
}

// UART0 STRING TRANSMIT //
void uart0_tx_string (char *ptr)
{
	while (*ptr)
		{
			uart0_tx(*ptr);
			ptr++;
		}
}

// UART0 INTEGER TRANSMIT //
void uart0_tx_int (s32 num)
{
	s32 a[100],i=0;
	if (num==0)
	{
		uart0_tx('0');
		return;
	}
	if (num<0)
	{
		uart0_tx('-');
		num=-num;
	}
	while (num>0)
	{
		a[i]=num%10;
		num=num/10;
		i++;
	}
	for (--i ; i>=0 ; i--)
	{
		uart0_tx(a[i]+48);
	}
}
