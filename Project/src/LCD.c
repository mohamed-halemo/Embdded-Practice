// /*
//  * Author : Abdullah Drwesh
//  * Date   : 20/12/2021
//  * Version: 1.0.0
//  */

// #include "LCD.h"

// #include "DIO.h"
// #include "util/delay.h"

// #define LCD_DPRT 'D'  // LCD DATA PORT
// #define LCD_CPRT 'B'  // LCD COMMANDS PORT
// #define LCD_RS 0      // LCD RS
// #define LCD_RW 1      // LCD RW
// #define LCD_EN 2      // LCD EN

// static void LCD_LatchSignal(void);

// void LCD_Init() {
//     #if LCD_MODE == LCD_8BIT_MODE
//         DIO_SetPortDirection(LCD_DPRT, OUTPUT);
//         DIO_SetPinDirection(LCD_CPRT, LCD_RS, OUTPUT);
//         DIO_SetPinDirection(LCD_CPRT, LCD_RW, OUTPUT);
//         DIO_SetPinDirection(LCD_CPRT, LCD_EN, OUTPUT);
//         LCD_SendCommand(0x38);
//         LCD_SendCommand(0x0E);
//         LCD_SendCommand(0x01);
//         _delay_ms(2);
//     #elif LCD_MODE == LCD_4BIT_MODE
//         /// TODO:
//         DIO_SetPortDirection(LCD_DPRT, OUTPUT);
//         DIO_WritePin(LCD_CPRT, LCD_EN, 0);

//         LCD_SendCommand(0x33);	             //$33 for 4-bit mode
//         _delay_us(100);

//         LCD_SendCommand(0x32);              //$32 for 4-bit modE
//         _delay_us(100);

//         LCD_SendCommand(0x28);              //$28 for 4-bit mode
//         _delay_us(100);

//         LCD_SendCommand(0x0E);              //display on, cursor on
//         _delay_us(100);


//         LCD_SendCommand(0x06);              /* Increment cursor (shift cursor to right)*/
//         _delay_us(100);

//         LCD_SendCommand(0x01);              /* Clear display screen*/
//         _delay_ms(2);
//     #else
//         #error Please Select The Correct Mode of LCD
//     #endif
// }

// void LCD_SendCommand(unsigned char Command) {
//     #if LCD_MODE == LCD_8BIT_MODE
//         DIO_WritePort(LCD_DPRT, Command);

//         DIO_WritePin(LCD_CPRT, LCD_RS, 0);
//         DIO_WritePin(LCD_CPRT, LCD_RW, 0);
//         LCD_LatchSignal();
//     #elif LCD_MODE == LCD_4BIT_MODE
//         /// TODO:
//         DIO_WritePort(LCD_DPRT, Command);

//         DIO_WritePin(LCD_CPRT, LCD_RS, 0);
//         DIO_WritePin(LCD_CPRT, LCD_RW, 0);

//         LCD_LatchSignal();
//         LCD_DPRT = (LCD_DPRT & 0x0F) | (Command << 4);
//         LCD_LatchSignal();

//     #else
//         #error Please Select The Correct Mode of LCD
//     #endif
// }

// void LCD_SendData(unsigned char Data) {
//     #if LCD_MODE == LCD_8BIT_MODE
//         DIO_WritePort(LCD_DPRT, Data);

//         DIO_WritePin(LCD_CPRT, LCD_RS, 1);
//         DIO_WritePin(LCD_CPRT, LCD_RW, 0);
//         LCD_LatchSignal();
//     #elif LCD_MODE == LCD_4BIT_MODE
//         /// TODO:
//         DIO_WritePort(LCD_DPRT, Data);
//         DIO_WritePin(LCD_CPRT, LCD_RS, 1);
//         DIO_WritePin(LCD_CPRT, LCD_RW, 0);
//         LCD_LatchSignal();
//         LCD_DPRT = (LCD_DPRT & 0x0F) | (Data << 4);
//         LCD_LatchSignal();

//     #else
//         #error Please Select The Correct Mode of LCD
//     #endif
// }

// void LCD_SetCursorAt(unsigned char x, unsigned char y) {
//   /// TODO: 
//     unsigned char firstCharAdr[]={0x80,0xC0,0x94,0xD4};
//     LCD_SendCommand(firstCharAdr[y-1] + x - 1);
//     delay_us(100);
// }

// void LCD_Print(const char* Str) {
//   /// TODO: 
//     unsigned char i = 0;
//     while(Str[i]!=0)
//     {
//     LCD_SendData(Str[i]);
//     i++ ;
//     }

// }

// static void LCD_LatchSignal(void) {
//   DIO_WritePin(LCD_CPRT, LCD_EN, 1);
//   _delay_us(1);
//   DIO_WritePin(LCD_CPRT, LCD_EN, 0);
//   _delay_us(100);
// }