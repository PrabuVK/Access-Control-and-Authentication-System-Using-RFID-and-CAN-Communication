#ifndef GSM_H
#define GSM_H

#include "uart.h"
#include "delay.h"


void gsm_code(void);


void gsm_code(void)
{
    uart0_tx_string("AT\r\n");
    delay_ms(200);

    uart0_tx_string("AT+CMGF=1\r\n");
    delay_ms(200);

    uart0_tx_string("AT+CMGS=\"+919704636395\"\r\n");
    delay_ms(200);

    uart0_tx_string("UNAUTHORISED VEHICLE ACCESS...\r\n");
    delay_ms(200);																																																											  

    uart0_tx(0x1A);
    delay_ms(2000);
}

#endif




