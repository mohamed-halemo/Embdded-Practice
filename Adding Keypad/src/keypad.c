
#include"util/delay.h"
#include <stdio.h>
#include"avr/io.h"
#include"DIO.h"
#include"keypad.h"
void keypadinit(){
    PORTC=0XFF;
    DDRC=0b00000111;
    PORTC=0b00000111;
     };
char getkey(){
    unsigned char key;

    unsigned char keymap[4][3] = {
{ '1', '2', '3'},
{ '4', '5', '6'},
{ '7', '8', '9'},
{ '*', '0', '#'}};
  for (unsigned char  i=0;i<3;i++)
      {
        PORTC&=~(1<<i);
        for (unsigned char j=3; j<7; j++)
        {
        if(DIO_ReadPin('C',j)==0)
        {
            key=keymap[j-3][i];
        }
        }
        PORTC|=(1<<i);

      }
      return key;
}