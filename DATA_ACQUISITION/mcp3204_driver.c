#include <LPC21xx.H>     //spi
#include "header.h"
u32 mcp3204_adc_read(u8 ch_num){
 u8 byteH,byteL;
 u32 result=0;
 ch_num<<=6;//set ch_num //cs=0 select slave
 IOCLR0=(1<<7);//CS0=0     enable MCP3204 communication.
 spi0_data(0x06);    
 byteH=spi0_data(ch_num);
 byteL=spi0_data(0x00);      //Send Dummy Byte & Receive Low Data
 IOSET0=(1<<7);//CS0=1     Disable MCP3204 communication.
 byteH&=0x0F;						//Remove Unwanted Upper Bits
 result=(byteH<<8)|byteL;
 return result;
}

