/*
 * Final_Project.c
 *
 * Created: 10/24/2016 1:27:13 AM
 *  Author: Dr
 */ 


#include <avr/io.h>
#include "types.h"
#include "Header.h"
#include <util/delay.h>

main()
{   u8 Push_Button_0;
	u8 PinCode;
	u8 i;
	u8 x;
	u8 ARR[4];
	LCD_voidInit();
	DIO_voidInit();
	
	

	while(1)
	{
		DIO_statusReadPin(4,1,&Push_Button_0);
		if(Push_Button_0==1)
		{
			Command_LCD(0x80);
			Display_String_LCD (" Entre Pin code ");
	    	_delay_ms(100);
     		Command_LCD(0xC0);
	    
		 
		 for(i=0;i<4;i++)
		{
			 x=ReadKeyPad(&PinCode);
		  	 _delay_ms(350);
			 
			  ARR[i]=PinCode;
		      Display_Char_LCD(ARR[i]); 
			  
		
		}
		 
		
	    if (ARR[0]==1) 
			{
				DIO_statusWritePin(4,4,1);
			}
		else 
		{ 
			DIO_statusWritePin(4,7,1);
			}
		}
		
		}
	}
	