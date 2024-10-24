#include <util/delay.h>
#include "DIO.h"
#include "ADC.h"

int main() {
  
  // program();
  unsigned int i;
  unsigned char temp=0;
  unsigned long val;
  unsigned long adc_value;

ADC_Init();
ACD_SelectChannel(0);

  for(i=0;i<8;i++){
  DIO_SetDirection('D',i,OUTPUT);
  }

  while (1) {
    adc_value=ADC_Read(0);
    val=((adc_value*1000*5)/1024);
    temp=val/10;
    DIO_WritePort('D',temp);
     
  }
  return 0;
}