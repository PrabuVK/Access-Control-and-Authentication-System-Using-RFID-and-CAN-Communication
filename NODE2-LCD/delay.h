#ifndef DELAY_H
#define DELAY_H


void delay_ms(unsigned int ms);


void delay_ms(unsigned int ms)
{
    T0PR = 60000 - 1;

    T0TCR = 0x02;
    T0TCR = 0x01;

    while(T0TC < ms);

    T0TCR = 0x00;
}

#endif
