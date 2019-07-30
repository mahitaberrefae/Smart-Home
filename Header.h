/*
 * DIOregisters.h
 *
 * Created: 9/3/2016 12:56:18 PM
 *  Author: Dr
 */ 




u8 PinValue;
typedef enum
   { NOK,
	 OK  
	}status;
extern void LCD_voidInit(void);
extern void DIO_voidInit(void);
extern status DIO_statusReadPort(u8 port,u8 *val);
extern status DIO_statusWritePort(u8 port, u8 val);
extern status DIO_statusReadPin(u8 port, u8 pin, u8* val);
extern status DIO_statusWritePin(u8 port, u8 pin, u8 val);
extern status DIO_statusChangeDirection(u8 port, u8 Direction);
extern void Ssegemnt_Display(u8 value);
extern void Display_Char_LCD (u8 x);
extern void Clear_LCD_Display();
extern void Command_LCD(u8 value);
extern void Enable_LCD();
extern void Display_String_LCD(u8 ARR[]);



#define PortA_Direction  0xff
#define PortB_Direction  0x0f
#define PortC_Direction  0x00
#define PortD_Direction  0xff

#define PortA_Val 0x00
#define PortB_Val 0x00
#define PortC_Val 0x00
#define PortD_Val 0x00

# define F_CPU 1000000UL


#define	LCD_RS 1
#define	LCD_RW 2
#define	LCD_EN 3