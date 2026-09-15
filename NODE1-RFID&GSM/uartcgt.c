#ifndef UART_H
#define UART_H

#include <LPC21xx.H>

/* UART0 declaration */
void uart0_init(unsigned int baud);
void uart0_tx(unsigned char data);
unsigned char uart0_rx(void);
void uart0_tx_string(char *ptr);

/* UART1 declaration */
void uart1_init(unsigned int baud);
void uart1_tx(unsigned char data);
unsigned char uart1_rx(void);
void uart1_tx_string(char *ptr);


/* UART0 definition */

void uart0_init(unsigned int baud)
{
    VPBDIV = 1;                 // PCLK = 60 MHz

    PINSEL0 |= 0x00000005;      // P0.0 TXD0, P0.1 RXD0

    U0LCR = 0x83;               // Enable DLAB

    switch(baud)
    {
        case 9600:
            U0DLM = 1;
            U0DLL = 135;
            break;

        case 115200:
            U0DLM = 0;
            U0DLL = 32;
            break;

        case 921600:
            U0DLM = 0;
            U0DLL = 4;
            break;

        default:
            U0DLM = 0;
            U0DLL = 32;
    }

    U0LCR = 0x03;               // 8-bit, 1 stop, no parity
}


void uart0_tx(unsigned char data)
{
    U0THR = data;

    while((U0LSR & (1<<5)) == 0);
}


unsigned char uart0_rx(void)
{
    while((U0LSR & 0x01) == 0);

    return U0RBR;
}


void uart0_tx_string(char *ptr)
{
    while(*ptr != '\0')
    {
        U0THR = *ptr;

        while((U0LSR & (1<<5)) == 0);

        ptr++;
    }
}


/* UART1 definition */

void uart1_init(unsigned int baud)
{
    VPBDIV = 1;                 // PCLK = 60 MHz

    PINSEL0 |= 0x00050000;      // P0.8 TXD1, P0.9 RXD1

    U1LCR = 0x83;               // Enable DLAB

    switch(baud)
    {
        case 9600:
            U1DLM = 1;
            U1DLL = 135;
            break;

        case 115200:
            U1DLM = 0;
            U1DLL = 32;
            break;

        case 921600:
            U1DLM = 0;
            U1DLL = 4;
            break;

        default:
            U1DLM = 0;
            U1DLL = 32;
    }

    U1LCR = 0x03;               // 8-bit, 1 stop, no parity
}


void uart1_tx(unsigned char data)
{
    U1THR = data;

    while((U1LSR & (1<<5)) == 0);
}


unsigned char uart1_rx(void)
{
    while((U1LSR & 0x01) == 0);

    return U1RBR;
}


void uart1_tx_string(char *ptr)
{
    while(*ptr != '\0')
    {
        U1THR = *ptr;

        while((U1LSR & (1<<5)) == 0);

        ptr++;
    }
}

#endif



