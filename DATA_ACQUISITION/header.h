typedef unsigned int u32;
typedef unsigned char u8;
typedef char s8;


//delay
extern void delay_ms(unsigned int ms);


//spi drivers
extern void spi0_init(void);
extern u8 spi0_data(u8);


//ext adc drivers
extern u32 mcp3204_adc_read(u8);


//uart0 drivers
void uart0_init(u32);
void uart0_tx(u8);
u8 uart0_rx(void);
void uart0_tx_string(char *);
void uart0_tx_integer(u32);
void uart0_tx_float(float);

//i2c drivers
extern void i2c_init(void);
extern void i2c_send(u8 sa,u8 mr,u8 data);
extern u8 i2c_read(u8 sa,u8 mr);


//lcd driveres
void lcd_init(void);
void lcd_data(unsigned char data);
void lcd_cmd(unsigned char cmd);
void lcd_string(char *ptr);
void lcd_cmd(unsigned char);
void lcd_integer(int num);
void lcd_float(float f);



//ADC DRIVERS
void adc_init(void);
u32 adc_read(u8);
