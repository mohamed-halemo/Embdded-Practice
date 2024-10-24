/**
 * Copyright (C) PlatformIO <contact@platformio.org>
 * See LICENSE for details.
 */

#include "ADC.h"
#include "LCD.h"
#include "avr/io.h"

#define leftSen PD0
#define rightSen PD1

int main(void) {
  // make PD0, PD1 as input for both sensors 0b11111100
  DDRD=0xFC;
  //  make port B as an output to connect motor bins
  DDRB= 0xFF;

  while (1) {
  //  initialize PD0,PD1
  PIND=0x03;
  //  check if left sensor if off
  if (bit_is_clear(PIND,leftSen)){
  //  check if right sensor is off
    if (bit_is_clear(PIND,rightSen))
    {
      // if both sensors are zero then stop the motors
      PORTB=0x00; 
    }
    else{
      //  if right is on then take left
      PORTB=0x01;
    }

  }
  else     //  if left sensor is on 

  {
    if (bit_is_clear(PIND,rightSen)) //check if right sensor is off
    {
      // take right if left sensor is on and right sensor is off
      PORTB=0x02; 
    }
    else 
    { // if both sensors are on keep moving the robot 
      PORTB=0x03;


    }

  }


  }                                                         
  return 0;
}
