#include <LPC21xx.h>
#include <string.h>

#include "can.h"
#include "uartcgt.c"
#include "gsm.h"
#include "delay.h"

#define LED (1<<2)

int main()
{
    CAN2_MSG m1;
    int i;

    char valid_tag[] = "060067E061E0";
    char tag_id[13];
    unsigned char ch;

    /* RFID - UART1 */
    uart1_init(9600);

    /* Debug - UART0 */
    uart0_init(115200);

    /* CAN initialization */
    can2_init();

    IODIR0 = LED;
    IOSET0 = LED;

    while(1)
    {
        /* Read RFID continuously */
        i = 0;

        while(i < 12)
        {
            ch = uart1_rx();

            /* Accept only hexadecimal characters */
            if((ch >= '0' && ch <= '9') ||
               (ch >= 'A' && ch <= 'F') ||
               (ch >= 'a' && ch <= 'f'))
            {
                tag_id[i] = ch;
                i++;
            }
        }

        /* End of string */
        tag_id[12] = '\0';

        /* Display RFID */
        uart0_tx_string("RFID: ");
        uart0_tx_string(tag_id);
        uart0_tx_string("\r\n");

        /* Compare RFID */
        if(strcmp(valid_tag, tag_id) == 0)
        {
            /* VALID RFID */

            IOCLR0 = LED;

            /* CAN VALID MESSAGE */
            m1.id = 0x101;
            m1.rtr = 0;
            m1.dlc = 1;
            m1.byteA = 0x01;       /* VALID */
            m1.byteB = 0x00;

            can2_tx(m1);

            uart0_tx_string("VALID\r\n");
            uart0_tx_string("CAN VALID SENT\r\n");

            IOSET0 = LED;
        }
        else
        {
            /* INVALID RFID */

            IOSET0 = LED;

            /* CAN INVALID MESSAGE */
            m1.id = 0x101;
            m1.rtr = 0;
            m1.dlc = 1;
            m1.byteA = 0x02;       /* INVALID */
            m1.byteB = 0x00;

            can2_tx(m1);

            uart0_tx_string("INVALID\r\n");
            uart0_tx_string("CAN INVALID SENT\r\n");

            /* GSM disabled during RFID testing */
            gsm_code();
        }
    }
}

