#include<LPC21XX.H>
#include<stdio.h>
#include"header.h"
void uart0_init(u32 baud)
{
unsigned int result=0,pclk;
int a[]={15,40,30,15,15};
pclk=a[VPBDIV]*1000000;
result=pclk/(16*baud);
PINSEL0|=5;
U0LCR=0x83;
U0DLM=(result>>8)&0xff;
U0DLL=result & 0xff;
U0LCR=3;
}
#define THRE ((U0LSR>>5)&1)
void uart0_tx(u8 data)
{
U0THR=data;
while(THRE==0);
}
#define RDR (U0LSR&1)
u8 uart0_rx(void)
{
while(RDR==0);
return U0RBR;
}
void uart0_tx_string(char *p)
{
while(*p)
 {
U0THR=*p;
while(THRE==0);
p++;
}
}
void uart0_tx_integer(u32 temp)
{
char arr[10];
sprintf(arr,"%d",temp);
uart0_tx_string(arr);
}
void uart0_tx_float(float temp)
{
char arr[10];
sprintf(arr,"%.2f",temp);
uart0_tx_string(arr);
}
