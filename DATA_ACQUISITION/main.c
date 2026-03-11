#include<LPC21XX.H>
#include"header.h"
int main()
{
	u8 hr, min, sec, day, date, month, year, t;
	char am_pm_flag=0;
	float vout1, tempr, vout2;
	unsigned long int adcout1, adcout2, light_perc;
	u32 ret;
	char arr[][4]={"","SUN","MON","TUE","WED","THU","FRI","SAT"};
	lcd_init();
	i2c_init();
	spi0_init();
	adc_init();
	uart0_init(9600);
	 delay_ms(100);
	//setting time
	i2c_send(0xD0,0x2,0x66); //6pm
	i2c_send(0xD0,0x1,0x5); // 5min
	i2c_send(0xD0,0x0,0x5); //5sec
	i2c_send(0xD0,0x3,0x3); 
	i2c_send(0xD0, 0x04, 0x07); // 07^M
	i2c_send(0xD0, 0x05, 0x01); // Jan^M
	i2c_send(0xD0, 0x06, 0x26); // 26
	uart0_tx_string("DATA ACQUISITION SYSTEM \n\r");
	while(1)
	{
			// RTC READ DATA
			hr = i2c_read(0xD1, 0x2); // read hrs
			min = i2c_read(0xD1, 0x1); // read mins
			sec = i2c_read(0xD1, 0x0); // read secs
			day = i2c_read(0xD1, 0x3); // read day^M
			date = i2c_read(0xD1, 0x04);
			month = i2c_read(0xD1, 0x05);
			year = i2c_read(0xD1, 0x06);
			t=hr;
			if(((hr>>6)&1)==1)
			{
				hr=hr&0x1f;
				am_pm_flag=1;
			}
			
			lcd_cmd(0x80);
			lcd_data((hr/0x10)+48);
			lcd_data((hr%0x10)+48);
			lcd_data(':');
			lcd_data((min/0x10)+48);
			lcd_data((min%0x10)+48);
			lcd_data(':');
			lcd_data((sec/0x10)+48);
			lcd_data((sec%0x10)+48);
			lcd_data(':');
			
			uart0_tx_string("\r\n");
			uart0_tx_string(" Date: ");
			uart0_tx((date/0x10)+48);
			uart0_tx((date%0x10)+48);
			uart0_tx('/');
			uart0_tx((month/0x10)+48);
			uart0_tx((month%0x10)+48);
			uart0_tx('/');
			uart0_tx((year/0x10)+48);
			uart0_tx((year%0x10)+48);
			
			uart0_tx_string(" ");
			uart0_tx((hr/0x10)+48);
			uart0_tx((hr%0x10)+48);
			uart0_tx(':');
			uart0_tx((min/0x10)+48);
			uart0_tx((min%0x10)+48);
			uart0_tx(':');
			uart0_tx((sec/0x10)+48);
			uart0_tx((sec%0x10)+48);
			//uart0_tx_string(" ")
			
			if(am_pm_flag==1)
			{
				if(((t>>5)&1)==1)
				{
					uart0_tx_string("PM");
				}
				
				else
				{
					uart0_tx_string("AM");
				}
				
				uart0_tx_string(" ");
				uart0_tx_string("\r\n");
				//uart0_tx_string("\r\n");
				
				if(((t>>5)&1)==1)
				{
					lcd_string("PM");
				}
				else
				{
				 lcd_string("AM");
				}
		}
		//lcd_cmd(0xc0);
		lcd_data(' ');
		lcd_string(arr[day]);
		uart0_tx_string(" ");
		uart0_tx_string(arr[day]);
		
			
		// ONBOARD TEMPERATURE SENSOR
		adcout1 = adc_read(1);
		vout1 = (adcout1 * 3.3) / 1023;
		tempr = (vout1 - 0.5) / 0.01;
		uart0_tx_string(" Temp=");
		uart0_tx_float(tempr);
		uart0_tx_string(".c");
		lcd_cmd(0xc0);
		lcd_string("T");
		lcd_integer(tempr);
		lcd_string("c");

		
		// ONBOARD voltage
		uart0_tx_string(" ");
		uart0_tx_string("voltage=");
		adcout2 = adc_read(1);
		vout2 = (adcout2 * 3.3) / 1023;
		uart0_tx_float(vout2);
		uart0_tx_string("V");


		// lcd_data(' ');
		lcd_string("V:");
		lcd_float(vout2);
		lcd_data('V');


		// LDR-MCP3204(SPI)
		ret = mcp3204_adc_read(2);
		light_perc = 100-((ret * 100) / 4095);
		uart0_tx_string(" Light Intensity=");
		uart0_tx_integer(light_perc);
		uart0_tx_string("%");
		uart0_tx_string("\r\n");
		lcd_data(' ');
		lcd_string("L:");
		lcd_integer(light_perc);
		lcd_data('%');
		delay_ms(100);
	}
}
