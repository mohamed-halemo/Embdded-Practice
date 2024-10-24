

#include "LCD.h"

#include "DIO.h"
#include "util/delay.h"

#define LCD_DPRT 'D'  // LCD DATA PORT
#define LCD_CPRT 'B'  // LCD COMMANDS PORT
#define LCD_RS 0      // LCD RS
#define LCD_RW 1      // LCD RW
#define LCD_EN 2      // LCD EN

static void LCD_LatchSignal(void);

void LCD_Init() {
    #if LCD_MODE == LCD_8BIT_MODE
        DIO_SetPortDirection(LCD_DPRT, OUTPUT);
        DIO_SetPinDirection(LCD_CPRT, LCD_RS, OUTPUT);
        DIO_SetPinDirection(LCD_CPRT, LCD_RW, OUTPUT);
        DIO_SetPinDirection(LCD_CPRT, LCD_EN, OUTPUT);
        LCD_SendCommand(0x38);
        LCD_SendCommand(0x0E);
        LCD_SendCommand(0x01);
        _delay_ms(2);
    #elif LCD_MODE == LCD_4BIT_MODE

        // TODO:
        DIO_SetPortDirection(LCD_DPRT, OUTPUT);
        _delay_ms(20);
        DIO_SetPinDirection(LCD_CPRT, LCD_RS, OUTPUT);
        DIO_SetPinDirection(LCD_CPRT, LCD_RW, OUTPUT);
        DIO_SetPinDirection(LCD_CPRT, LCD_EN, OUTPUT);
        LCD_SendCommand(0x33); // init with 0x33
        LCD_SendCommand(0x32);  // init with 0x34
        LCD_SendCommand(0x28); // 2 lines and 5 × 7 matrix (D4–D7, 4-bit)
        LCD_SendCommand(0x0E);//Display on, cursor off
        LCD_SendCommand(0x01); //Clear display screen
        LCD_SendCommand(0x06);
        _delay_ms(100);
      
    #else
        #error Please Select The Correct Mode of LCD
    #endif
}

void LCD_SendCommand(unsigned char Command) {
    #if LCD_MODE == LCD_8BIT_MODE
        DIO_WritePort(LCD_DPRT, Command);

        DIO_WritePin(LCD_CPRT, LCD_RS, 0);
        DIO_WritePin(LCD_CPRT, LCD_RW, 0);
        LCD_LatchSignal();
    #elif LCD_MODE == LCD_4BIT_MODE
     //TODO:
     unsigned char Command_pt;

    Command_pt=Command & 0xf0; //4 bit work from D4 TO D7 high nibble
    DIO_WritePort(LCD_DPRT, Command_pt);  //Dprt=command_pt

        DIO_WritePin(LCD_CPRT, LCD_RS, 0); //command
        DIO_WritePin(LCD_CPRT, LCD_RW, 0); // write
        LCD_LatchSignal(); // high to low pulse 
        _delay_us(100);
        Command_pt= Command<<4; //sending the other low 4 bits
        DIO_WritePort(LCD_DPRT, Command_pt);  //low nibble
        LCD_LatchSignal(); //h-l
        _delay_ms(2);
    #else
        #error Please Select The Correct Mode of LCD
    #endif
}

void LCD_SendData(unsigned char Data) {
    #if LCD_MODE == LCD_8BIT_MODE
        DIO_WritePort(LCD_DPRT, Data);

        DIO_WritePin(LCD_CPRT, LCD_RS, 1);
        DIO_WritePin(LCD_CPRT, LCD_RW, 0);
        LCD_LatchSignal();
    #elif LCD_MODE == LCD_4BIT_MODE
        // TODO:
        unsigned char Data_pt;
        Data_pt=Data&0xf0; //high nibble D4-D7
        DIO_WritePort(LCD_DPRT, Data_pt); 

        DIO_WritePin(LCD_CPRT, LCD_RS, 1); // rs = data register 
        DIO_WritePin(LCD_CPRT, LCD_RW, 0); //write data 
        LCD_LatchSignal(); 
        _delay_us(100);
        Data_pt=Data<<4; //sending the other 4 bits
        DIO_WritePort(LCD_DPRT, Data_pt);
        LCD_LatchSignal();
        _delay_ms(2);
    #else
        #error Please Select The Correct Mode of LCD
    #endif
}

void LCD_SetCursorAt(unsigned char x, unsigned char y) {
  /// TODO: 
  
unsigned char firstCharAdr[] = {0x80, 0xC0, 0x94, 0xD4};  // appear line 1,col1  line2 col1   line 3 col1 line 4 col 1   there are 4 cols
LCD_SendCommand(firstCharAdr[y-1] + x - 1);
_delay_us(100);
}

void LCD_Print(const char* Str) {
    unsigned char i = 0;
     while(Str[i]!='\0')  //print untill find null value
  {
 LCD_SendData(Str[i]);
 i++;
}
  /// TODO: 
}

static void LCD_LatchSignal(void) { // h-l pulse
  DIO_WritePin(LCD_CPRT, LCD_EN, 1);
  _delay_us(1);
  DIO_WritePin(LCD_CPRT, LCD_EN, 0);
  _delay_us(100);
}