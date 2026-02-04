#include<lpc21xx.h>
void uart0_init(unsigned int baud)
{
	int result,pclk;
	int a[]={15,60,30};
	pclk=a[VPBDIV]*1000000;
	result=pclk/(16*baud);
	PINSEL0 =0X5;
	U0LCR=0X83;
	U0DLL=result&0XFF;
	U0DLM=(result>>8)&0XFF;
	U0LCR=0X03;
}

//transmit data
#define THRE ((U0LSR>>5)&1)
void uart0_tx(unsigned char data)
{
	U0THR=data;
	while(THRE==0);
}

//recieve data
#define RDR (U0LSR & 1)
unsigned char uart0_rx(void)
{
	while(RDR==0);
	return U0RBR;
}


//binary
void uart0_binary(int num)
{
	int pos,temp;
	for(pos=7;pos>=0;pos--)
	{
		temp=num>>pos&1;
		uart0_tx(temp+48);
	}
}


//uart0_string
void uart0_string(char *p)
{
	while(*p!=0)
	{
		uart0_tx(*p);
		p++;
	}
}


//uart_ascii
void uart0_int(int num)
{
	int a[10],i=0;
	if(num==0)
	{
		uart0_tx('0');
		return;
	}
	if(num<0)
	{
		num=-num;
		uart0_tx('-');
	}
	while(num>0)
	{
		a[i]=num%10+48;
		num=num/10;
		i++;
	}
	for(i=i-1;i>=0;i--)
	{
		uart0_tx(a[i]);
	}
}


