#include <lpc21xx.h>
#include "header.h"
#include<string.h>

typedef unsigned char u8;
typedef unsigned int  u32;
volatile u8 rx_flag = 0;
char buf[13];
volatile u32 current_minute = 0;

typedef struct
{
    char id[13];
    char name[20];
    u32 last_time;
    u8  marked;         // NEW FLAG (FIX)
} ID_MAP;

ID_MAP users[] =
{
    {"123456789101", "Mohit", 0, 0},
    {"123456789102", "abhishek", 0, 0},
    {"123456789103", "nishant", 0, 0},
    {"123456789104", "sachin",  0, 0}
};

#define TOTAL_USERS (sizeof(users)/sizeof(users[0]))
#define ATTENDANCE_GAP 5   // min

void config_vic_for_uart0(void);
void timer0_init(void);
int  str_cmp(char *a, char *b);
void mark_attendance(char *id);

int main()
{
    uart0_init(9600);
    timer0_init();
    config_vic_for_uart0();

    uart0_string("Attendance System Started\r\n");

    while(1)
    {
        if(rx_flag == 1)
        {
            rx_flag = 0;
            mark_attendance(buf);
        }
    }
}

void uart0_Handler(void) __irq
{
    u8 temp = U0IIR;
    static u8 i = 0;

    temp &= 0x0E;
    if(temp == 0x04)
    {
        buf[i++] = U0RBR;
        if(i == 12)
        {
            buf[i] = '\0';
            i = 0;
            rx_flag = 1;
        }
    }
    VICVectAddr = 0;
}

//timer handler
void timer0_Handler(void) __irq
{
    current_minute++;
    T0IR = 1;
    VICVectAddr = 0;
}

//timer init
void timer0_init(void)
{
    T0PR  = 60000000 - 1;   // 1 second (60 MHz)
    T0MR0 = 60;             // 60 seconds = 1 minute
    T0MCR = 3;              // interrupt + reset
    T0TCR = 1;

    VICVectCntl1 = 4 | (1 << 5);     
    VICVectAddr1 = (u32)timer0_Handler;
    VICIntEnable |= (1 << 4);
}

void config_vic_for_uart0(void)
{
    VICVectCntl2 = 6 | (1 << 5);
    VICVectAddr2 = (u32)uart0_Handler;
    VICIntEnable |= (1 << 6);
    U0IER = 1;
}

/* ---------------- ATTENDANCE FUNCTION ---------------- */
void mark_attendance(char *id)
{
    u8 i;

    for(i = 0; i < TOTAL_USERS; i++)
    {
        if(strcmp(id, users[i].id)==0)
        {
            if(users[i].marked == 1 &&(current_minute - users[i].last_time) < ATTENDANCE_GAP)
            {
                uart0_string("Already Marked\r\n\r\n");
								return;
            }
						
            else
            {
                users[i].last_time = current_minute;
                users[i].marked = 1;

                uart0_string("Attendance Marked\r\nName: ");
                uart0_string(users[i].name);
                uart0_string("\r\n\r\n");
							  return;
            }
        }
    }
    uart0_string("Unknown ID\r\n\r\n");
}
