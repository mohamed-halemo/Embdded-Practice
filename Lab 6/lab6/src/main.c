/**
 * Copyright (C) PlatformIO <contact@platformio.org>
 * See LICENSE for details.
 */
#if 0


    #include "ADC.h"
#include "LCD.h"
#include"util/delay.h"
#include <math.h>
#include <stdio.h>
void reverse(char* str, int len)
{
    int i = 0, j = len - 1, temp;
    while (i < j) {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++;
        j--;
    }
}
  
// Converts a given integer x to string str[]. 
// d is the number of digits required in the output. 
// If d is more than the number of digits in x, 
// then 0s are added at the beginning.
int intToStr(int x, char str[], int d)
{
    int i = 0;
    while (x) {
        str[i++] = (x % 10) + '0';
        x = x / 10;
    }
  
    // If number of digits required is more, then
    // add 0s at the beginning
    while (i < d)
        str[i++] = '0';
  
    reverse(str, i);
    str[i] = '\0';
    return i;
}
  
// Converts a floating-point/double number to a string.
void ftoa(float n, char* res, int afterpoint)
{
    // Extract integer part
    int ipart = (int)n;
  
    // Extract floating part
    float fpart = n - (float)ipart;
  
    // convert integer part to string
    int i = intToStr(ipart, res, 0);
  
    // check for display option after point
    if (afterpoint != 0) {
        res[i] = '.'; // add dot
  
        // Get the value of fraction part upto given no.
        // of points after dot. The third parameter 
        // is needed to handle cases like 233.007
        fpart = fpart * pow(10, afterpoint);
  
        intToStr((int)fpart, res + i + 1, afterpoint);
    }
}

// int main(){
//   LCD_Init();
//   LCD_Print("hello");
//   return 0;
// }

int main(void) {
   float temp=0.0;

  unsigned short adc_value;
    char charVal[30];                

ADC_Init();
LCD_Init();

ADC_SelectChannel(0);

  // DIO_SetPortDirection('D',1);
  while (1) {
      _delay_ms(2000);
      LCD_SetCursorAt(1,1);
      LCD_Print("Halemo");

    // adc_value=ADC_ReadChannel(0);
    // val=((adc_value*1000*5)/1024);
    // temp=val/10;
    LCD_SetCursorAt(1,2);
    // adc_value= ADC_ReadChannel(0);
    temp=(float)((((float)adc_value*(5.0/1024)*1000))/10);
    ftoa(temp,charVal,2);//4 is mininum width, 3 is precision; float value is copied onto buff

    LCD_Print(charVal);
// DIO_WritePort('D',temp);
    _delay_ms(3000);
  }
  return 0;
}

    
}

# elif 1
#include "ADC.h"
#include "LCD.h"
#include "DIO.h"
#include "avr/io.h"
#include <avr/interrupt.h>
#include"util/delay.h"
#include <math.h>
#include <stdio.h>
#include"avr/interrupt.h"
void reverse(char* str, int len)
{
    int i = 0, j = len - 1, temp;
    while (i < j) {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++;
        j--;
    }
}
  
// Converts a given integer x to string str[]. 
// d is the number of digits required in the output. 
// If d is more than the number of digits in x, 
// then 0s are added at the beginning.
int intToStr(int x, char str[], int d)
{
    int i = 0;
    while (x) {
        str[i++] = (x % 10) + '0';
        x = x / 10;
    }
  
    // If number of digits required is more, then
    // add 0s at the beginning
    while (i < d)
        str[i++] = '0';
  
    reverse(str, i);
    str[i] = '\0';
    return i;
}
  
// Converts a floating-point/double number to a string.
void ftoa(float n, char* res, int afterpoint)
{
    // Extract integer part
    int ipart = (int)n;
  
    // Extract floating part
    float fpart = n - (float)ipart;
  
    // convert integer part to string
    int i = intToStr(ipart, res, 0);
  
    // check for display option after point
    if (afterpoint != 0) {
        res[i] = '.'; // add dot
  
        // Get the value of fraction part upto given no.
        // of points after dot. The third parameter 
        // is needed to handle cases like 233.007
        fpart = fpart * pow(10, afterpoint);
  
        intToStr((int)fpart, res + i + 1, afterpoint);
    }
}

// int main(){
//   LCD_Init();
//   LCD_Print("hello");
//   return 0;
// }
float adc_value=0;
ISR(ADC_vect){
    adc_value=ADC;
    ADCSRA |= (1 << 6);
}

int main(void) {
   float temp=0.0;

//   unsigned short adc_value;
    char charVal[30];                
    
ADC_Init();

LCD_Init();
//ENABLE
ADCSRA |= (1 << 3);

ADC_SelectChannel(0);
//START CONVERSION
    ADCSRA |= (1 << 6);
    sei();
  // DIO_SetPortDirection('D',1);
  while (1) {
      _delay_ms(2000);
      LCD_SetCursorAt(1,1);
      LCD_Print("Halemo");

    // adc_value=ADC_ReadChannel(0);
    // val=((adc_value*1000*5)/1024);
    // temp=val/10;
    LCD_SetCursorAt(1,2);
    // adc_value= ADC_ReadChannel(0);
    temp=(float)((((float)adc_value*(5.0/1024)*1000))/10);
    ftoa(temp,charVal,2);//4 is mininum width, 3 is precision; float value is copied onto buff

    LCD_Print(charVal);
// DIO_WritePort('D',temp);
    _delay_ms(3000);
  }
  return 0;
}
#else
#endif