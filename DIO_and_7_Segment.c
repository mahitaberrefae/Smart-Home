/*
 * DIO.c
 *
 * Created: 9/23/2016 10:25:15 AM
 *  Author: Dr
 */ 
#include <avr/io.h>
#include "types.h"
#include "Header.h"
#include <util/delay.h>


extern void DIO_voidInit()
{
	DDRA=PortA_Direction;
	DDRB=PortB_Direction;
	DDRC=PortC_Direction;
	DDRD=PortD_Direction;
	
	PORTA=PortA_Val&PortA_Direction;
	PORTB=PortB_Val&PortB_Direction;
	PORTC=PortC_Val&PortC_Direction;
	PORTD=PortD_Val&PortD_Direction;
	
}

extern status DIO_statusWritePort(u8 port, u8 val)
{
	status Value_Return=OK;
	if(val<=255)
	 { switch(port)
        {case 1:PORTA=val&DDRA;
			break;
		 case 2: PORTB=val&DDRB;
		    break;
		 case 3: PORTC=val&DDRC;
		    break;
		case 4: PORTD=val&DDRD;
		    break;			
		default: Value_Return=NOK;
		}
 	 } 
		else 			
		{
		  Value_Return=NOK; 
		}
 
 return Value_Return;
}


extern status DIO_statusReadPort(u8 port,u8 *val)
{
	status Value_Return=OK;
	switch(port)
	{
		case 1:*val=PINA&~(DDRA);
		  break;
		case 2: *val=PINB&~(DDRB);
		  break;
		case 3: *val=PINC&~(DDRB);
		  break;
		case 4: *val=PIND&~(DDRD);
		  break;
		default: Value_Return=NOK;        
	
	}
	return Value_Return;
}

extern status DIO_statusWritePin(u8 Port, u8 Pin, u8 Val)
{
	status Value_Return = OK;
	
	switch(Port)
	{ case 1: switch(Val) 
		      {
				  case 0: PORTA&=~(1<<(Pin-1));
				  break;
				  case 1: PORTA|=(1<<(Pin-1));
				  break;
			      default: Value_Return=NOK;  
		       }

       case 2: switch(Val)
			   {
				   case 0: PORTB&=~(1<<(Pin-1));
				   break;
				   case 1: PORTB|=(1<<(Pin-1));
				   break;
				   default: Value_Return=NOK;  
			   }
	 
	  case 3: switch(Val)
			  {
				  case 0: PORTC&=~(1<<(Pin-1));
				  break;
				  case 1: PORTC|=(1<<(Pin-1));
				  break;
				  default: Value_Return=NOK;  
			  }
   
      case 4: switch(Val)
			  {
				  case 0: PORTD&=~(1<<(Pin-1));
				  break;
				  case 1: PORTD|=(1<<(Pin-1));
				  break;
				  default: Value_Return=NOK;  
			  } 
 
	  default: Value_Return=NOK;
	  break;  }
return Value_Return;
}

extern status DIO_statusReadPin(u8 Port, u8 Pin, u8*Val)
{ //u8 Val;
	status Value_Return = OK;
	switch(Port)
	{  case 1: 
		*Val=(PINA)&(1<<(Pin-1));
		*Val=*Val>>(Pin-1);
		break;
		
	  case 2:
		*Val=(PINB)&(1<<(Pin-1));
		*Val=*Val>>(Pin-1);
	    break;
		  
	  case 3:
		  *Val=(PINC)&(1<<(Pin-1));
		  *Val=*Val>>(Pin-1);
	      break;
		  
	  case 4:
		*Val=(PIND)&(1<<(Pin-1));
		*Val=(*Val>>(Pin-1));
	    break;
		
	  default: Value_Return=NOK; 	
	  break;
	}
	return Value_Return;
	
}

/*extern void Ssegemnt_Display(u8 value)
{ 
	PORTC&=0x0f;
	value <<=4;
	PORTC|=value;
	
}*/

extern status Segm_Display(u8 Val,u8 *X,u8 *Y)
{
	*X= Val % 10;
	Val/=10;
	*Y=Val % 10;
	
	
}

extern status Segm_Refresh( u8 X, u8  Y)
{  u8 n, i, j;

	DIO_statusWritePin(3, 3, 0);
	DIO_statusWritePin(3, 4, 0);
	
	Ssegemnt_Display(Y);
	DIO_statusWritePin(3, 4, 1);
	DIO_statusWritePin(3, 3, 0);
	
	_delay_ms(10);
	
	DIO_statusWritePin(3, 3, 0);
	DIO_statusWritePin(3, 4, 0);

	Ssegemnt_Display(X);
	
	
	DIO_statusWritePin(3, 3, 1);
	DIO_statusWritePin(3, 4, 0);
	
	_delay_ms(10);
}