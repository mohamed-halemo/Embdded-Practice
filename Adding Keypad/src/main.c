/**
 * Copyright (C) PlatformIO <contact@platformio.org>
 * See LICENSE for details.
 */


#include "LCD.h"
#include"util/delay.h"
#include <math.h>
#include <stdio.h>
#include"avr/io.h"
#include"DIO.h"
#include"keypad.h"

int main(void) {
    keypadinit();
    
unsigned char key;
LCD_Init();

  while (1) {
    _delay_ms(200);

    key=getkey();
      LCD_SetCursorAt(1,1);
      LCD_Print("Halemo");

    
    LCD_SetCursorAt(1,2);
   
    _delay_ms(200);
    LCD_SendData(key);
  }
  return 0;
}

    

