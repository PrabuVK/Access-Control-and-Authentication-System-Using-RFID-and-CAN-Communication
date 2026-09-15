#include <LPC21xx.h>
#include "delay.h"
#include "can.h"

CAN2_MSG m1;

void PWM_Init(void)
{
    PINSEL1 &= ~(3<<10);
    PINSEL1 |=  (1<<10);       // Configure P0.21 as PWM5 output

    VPBDIV = 1;                // PCLK = 60MHz

    PWMTCR = 0x02;             // Reset PWM counter

    PWMPR = 59;                // 60MHz/(59+1) = 1MHz
                                // 1 count = 1us

    PWMMR0 = 20000;             // 20ms period = 50Hz

    PWMMR5 = 1000;              // Initially 0 degree

    PWMMCR = (1<<1);            // Reset counter on MR0

    PWMPCR = (1<<13);           // Enable PWM5 output

    PWMLER = (1<<0) | (1<<5);   // Load MR0 and MR5

    PWMTCR = 0x09;              // Enable PWM and start counter
}

void Gate_Open(void)
{
    PWMMR5 = 1500;              // 1.5ms pulse = 90 degree OPEN
    PWMLER = (1<<5);            // Update PWM5

    delay_ms(5000);             // Keep gate open for 5 seconds
}

void Gate_Close(void)
{
    PWMMR5 = 1000;              // 1ms pulse = 0 degree CLOSE
    PWMLER = (1<<5);            // Update PWM5

    delay_ms(2000);             // Wait for gate closing
}

int main()
{
    can2_init();                // Initialize CAN2
    PWM_Init();                 // Initialize PWM5

    Gate_Close();               // Initially gate is closed

    while(1)
    {
        can2_rx(&m1);            // Receive CAN message

        if(m1.id == 0x101)       // RFID CAN ID
        {
            if(m1.byteA == 0x01) // VALID RFID
            {
                Gate_Open();     // Open gate for 5 seconds
                Gate_Close();    // Close gate
            }

            else if(m1.byteA == 0x02) // INVALID RFID
            {
                Gate_Close();    // Keep gate closed
            }
        }
    }
}

