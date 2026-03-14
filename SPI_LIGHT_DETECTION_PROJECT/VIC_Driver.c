#include <lpc21xx.h>
#include"header.h"
int manflag,autoflag;

void config_vic (void)
{
	manflag=0;
	autoflag=1;
  EXTMODE = 0x6;
  EXTPOLAR &= ~(0x6);
  PINSEL0 |= 0xA0000000;
  
  VICIntSelect &= ~ ((1<<16)|(1<<15));            // EINT2 selected as IRQ 16 and EINT1 as IRQ 15
  VICVectAddr5 = (unsigned int) SW1_INT;
	VICVectAddr4 = (unsigned int) SW2_INT;
  VICVectCntl5 = (1<<5) | 15;
  VICVectCntl4 = (1<<5) | 16;
  VICIntEnable = ((1<<16) | (1<<15));
  EXTINT &= ~(0x6);
}

__irq void SW1_INT (void)
{
	manflag=!manflag;
	uart0_tx_string("MANFLAG=");
	uart0_tx_int (manflag);
	uart0_tx_string("\r\n");
	EXTINT |= 0x6;  
	VICVectAddr = 0;
}
__irq void SW2_INT (void)
{
	autoflag=!autoflag;
	uart0_tx_string("AUTOFLAG=");
	uart0_tx_int (autoflag);
	uart0_tx_string("\r\n");
	 EXTINT |= 0x6;  
	 VICVectAddr = 0;
}
