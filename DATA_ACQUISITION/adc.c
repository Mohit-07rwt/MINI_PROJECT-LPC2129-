#include<LPC21XX.H>
#include"header.h"
void adc_init(void)
{
//p0.27-p0.30 as analog pins
PINSEL1|=0x15400000;
ADCR=0x00200400;
}

u32 adc_read(u8 ch_num)
{
u32 result=0;
//select ch_num
ADCR|=1<<ch_num;
//start adc
ADCR|=(1<<24);
//monitor done flag
while(((ADDR>>31)&1)==0);
//stop ADC
ADCR ^=(1<<24);
//Disselect ch_num
ADCR ^=1<<ch_num;
result=((ADDR>>6)&0x3FF);				//10 bit result stores in   Bits 15 to 6 so, addr>>6
return result;
}
