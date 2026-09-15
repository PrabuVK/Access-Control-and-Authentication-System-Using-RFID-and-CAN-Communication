#include <LPC21xx.H>
#include "can.h"
#include "lcd.h"

#define LED     (1<<21)     // P0.21
#define BUZZER  (1<<22)     // P0.22

int main()
{
    CAN2_MSG m1;
    IODIR1|= LED | BUZZER;
    IOSET1 = LED | BUZZER;
    can2_init();
    LCD_INIT();
	//LCD_COMMAND(0x80);
	LCD_COMMAND(0x80);
	LCD_STR("BattleGuard: Advance");
	LCD_COMMAND(0xC0);
	LCD_STR("MILITARY ACCESS");
	LCD_COMMAND(0x94);
	LCD_STR("RFID AUTHENTICATION");
	LCD_COMMAND(0xD4);
	LCD_STR("CAN COMMUNICATION");
	delay_ms(2000);
	LCD_COMMAND(0X01);
		LCD_COMMAND(0x80);

        LCD_STR("BATTLE GUARD");
		LCD_COMMAND(0xC0);
	  LCD_STR("SCAN RFID");
		while(1)
    {  	   
      can2_rx(&m1);
        if(m1.id == 0x101)
        {  
	//	LCD_COMMAND(0x01);
           if(m1.byteA == 0x01)	
		{
		    LCD_COMMAND(0x94);
		    LCD_STR("VALID RFID        ");
		
		    LCD_COMMAND(0xD4);
		    LCD_STR("ACCESS GRANTED     ");
		}
				
				else if(m1.byteA == 0x02)
				{
				    LCD_COMMAND(0x94);
				    LCD_STR("INVALID RFID       ");
				
				    LCD_COMMAND(0xD4);
				    LCD_STR("ACCESS DENIED      ");
					    IOCLR1 = LED | BUZZER;
				    	delay_ms(500);
					   IOSET1 = LED | BUZZER;

				}
			
        }
    }
}

