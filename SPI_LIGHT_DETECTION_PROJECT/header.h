typedef unsigned int u32;
typedef unsigned char u8;
typedef signed int s32;
typedef signed char s8;

extern void delay_sec(unsigned int, unsigned int);
extern void delay_ms(unsigned int, unsigned int);

extern void lcd_data(unsigned char);
extern void lcd_cmd(unsigned char);
extern void lcd_init(void);
extern void lcd_string(char *);
extern void lcd_int(int);
extern void lcd_cgram(char *);

extern void uart0_init(unsigned int);
extern void uart0_tx(unsigned char);
extern void uart0_tx_string(char *);
extern void uart0_tx_int(s32);

void adc_init(void);
u32 adc_read(int);
void adc_uart_tx_int(s32);

void spi0_init(void);
unsigned char spi0(unsigned char);
unsigned short int mcp3204_adc_read(unsigned int);

void config_vic(void);
__irq void SW1_INT(void);
__irq void SW2_INT(void);

