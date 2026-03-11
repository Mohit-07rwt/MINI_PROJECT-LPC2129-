#include<LPC21XX.H>
#include"header.h"
#define SPIF ((S0SPSR>>7)&1)		//If result = 1(Transfer complete)  	If result = 0 (Transfer not complete)
void spi0_init(void)
{
		//select p0.4,p0.5,p0.6 as clk,miso mosi
		PINSEL0|=0x1500;
			
		//select p0.7 as cs
		IODIR0|=(1<<7);
		//CS=1 DISSELECT SLAVE
		IOSET0=(1<<7);
		//MASTER MODE ENABLED
		S0SPCR=0x20; //cpol and cphase0			

			//1 MBPS
		S0SPCCR=150;	///Set SPI Clock Speed
}



u8 spi0_data(u8 data)
{
		//place data in data register
		S0SPDR=data;
		//w8ing for data transfer to complete
		while(SPIF==0);								//This waits until:	SPIF (bit 7 of S0SPSR) becomes 1.
			//data frm s->m
		return S0SPDR;
}

