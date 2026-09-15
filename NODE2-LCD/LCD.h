#include"delay.h"
#define LCD_D 0Xff
#include"delay.h"
#include"delay.h"
#define RS 1<<8
#define E 1<<9

void LCD_INIT(void);
void LCD_COMMAND(unsigned char);
void LCD_DATA(unsigned char);
void LCD_INTEGER(int);
void LCD_STR(unsigned char*);
void LCD_FLOAT(float);
void delay_ms(unsigned int ms);


void LCD_INIT(void)
{
IODIR0=LCD_D|RS|E;
LCD_COMMAND(0X01);
LCD_COMMAND(0X02);
LCD_COMMAND(0X0C);
LCD_COMMAND(0X38);
}

void LCD_COMMAND(unsigned char CMD)
{
IOCLR0=LCD_D;
IOSET0=CMD;
IOCLR0=RS;
IOSET0=E;
delay_ms(2);
IOCLR0=E;
}

void LCD_DATA(unsigned char d)
{
IOCLR0=LCD_D;
IOSET0=d;
IOSET0=RS;
IOSET0=E;		 
delay_ms(2);
IOCLR0=E;
}

void LCD_STR(unsigned char*p)
{
while(*p)
{
LCD_DATA(*p++);
}
}
