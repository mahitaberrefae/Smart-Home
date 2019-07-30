/*
 * LCD.c
 *
 * Created: 10/22/2016 6:05:29 PM
 *  Author: Dr
 */ 
#include <avr/io.h>
#include "types.h"
#include "Header.h"
#include <util/delay.h>





extern void LCD_voidInit()
{
		  DDRA=0xFF;
		  DDRB=0xFF;
		  PORTB&=~(1<<LCD_EN);

		  Command_LCD(0x33);
		  Command_LCD(0x32);
		  Command_LCD(0x28);
		  Command_LCD(0x0E);
		  Clear_LCD_Display();
		  _delay_us(2000);
		  Command_LCD(0x06); //incCursor
}

extern void Enable_LCD()
{
	DIO_statusWritePin(3,1,1);
	DIO_statusWritePin(3,1,0);
}

extern void Command_LCD(u8 value)
{
	//DIO_statusWritePin(2,2,0);
	PORTA=(value & 0xF0);
	PORTB&=~(1<<LCD_RS);
	PORTB&=~(1<<LCD_RW);
	PORTB|=(1<<LCD_EN);
	_delay_us(5);
	//Enable_LCD();
	PORTB&=~(1<<LCD_EN);
	_delay_us(100);
	PORTA=(value<<4);
	PORTB|=(1<<LCD_EN);
	_delay_us(5);
	PORTB&=~(1<<LCD_EN);
	_delay_us(100);

}

extern void Clear_LCD_Display()
{
	Command_LCD(0x01);
}

extern void Display_Char_LCD (u8 data)
{
	PORTA=data&0xF0;
	PORTB|=(1<<LCD_RS);
	PORTB &=~ (1<<LCD_RW);
	PORTB|=(1<<LCD_EN);
	_delay_us(5);
	PORTB&=~(1<<LCD_EN);
	PORTA=data<<4;
	PORTB|=(1<<LCD_EN);
	_delay_us(5);
	PORTB&=~(1<<LCD_EN);
	_delay_us(100);

}


extern void Display_String_LCD(u8 ARR[])
{
	int i=0;
	
	while(ARR[i]!='\0')
	{
		Display_Char_LCD(ARR[i]);
		i++;
		
		_delay_ms(125);
	}
}

extern status ReadKeyPad(u8 *Val)

{ 
	PORTC=0xf0;
	u8 i, j, Val1,x;
	u8 flag=0;
	u8 Array[4]={0b01111111, 0b10111111, 0b11011111, 0b11101111};
	u8 LockArr[4][4]={{10, 3, 2, 1},{11, 6, 5 , 4},{12, 9, 8, 7}, {13, 15 , 0, 14}};
	
	for (i=0; i<4; i++)
	{
		PORTC = Array[i];
		for(j=1; j<=4; j++)
		{
			DIO_statusReadPin(3, j, &Val1);
			if(Val1==1)
			{
				flag=1;
				break;
			}
		}
		if(flag==1)
		{
			*Val= LockArr[i][j-1];
			
			break;
			
		}
		
		
	}
	
}

