/*
 * Author : Abdullah Drwesh
 * Date   : 12/12/2021
 * Version: 1.0.0
 */
#include "avr/io.h"
#include "DIO.h"


void ADC_Init(void)
{
//0>4 channel in admux we take input here put zeros then NO.5 left or right (0) right /,6,7>>Vref,Vcc,2.56? put zero,1 >VCC/
//0x40> 0 1 0 0 0 0 0 0 
//LDI R16,0X40    >> STS ADMUX,R16  
//ADCSRA >> first 3 bits(ones)>pre scalar e2sm frequency el avr(16Mhz) / first 3 bits (128) 3,4,5,6 zeros,7>one to enable 
//10000111>0X87    >>LDI R17,0X87   >>STS ADCSRA,R17
//PORT D OUTPUT PORT C INPUT   
//ref works left and 2.56 
//L:ADCSRA>>Start conversion bit No.6 >> LDS R18,ADCSRA   ORI R18,0X40 STS ADCSRA,R18   (PUT ALL THAT IN LABEL TO REPEAT)
//LOOP ON THE CONVERSION BIT NO.6 ONCE IT'S ZERO GETOUT AND PUT THAT VALUE ON OUTPUT PORT WHICH IS D 
//L2: IF CONVERSION IS 1 (BRNE) CHECK BIT 6 (CONVERSION) //ADC LOW 8BITS ADC HIGH 8BITS
//DIVIDE ADC OVER 2 LSR ONCE (RIGHT ADJST Y3NY WA5DEN KOL EL LOW W AWEL 2 HIGH) LSR ADCL 
//SHIFT RIGHT THE LOW AND SHIFT RIGHT THE HIGH TO PUT WHAT IS LEAVING HIGH IN LOW AS IT'S LIKE 2REGISTER SHIFT
// LOAD HIGH IN REGISTER AND SHIFT IT AND LOAD LOW IN REGISTER AND SHIFT IT AND CHECK  CARRY OF HIGH IF 1 PUT IT 
// afte shiftin low , shift high and take carry put in first bit in adc low use brcc L3 to check carry if zero jump to label
//if not zero do oring of value of ORI ADCHIGH,0X80
//L3:OUT Register got from LOW , portD
//RJMP L1
    /// TODO:

    // Enable ADC
    ADCSRA |= (1 << 7);
    // Select Reference (to be AVCC)
    ADMUX &= ~(1 << 6);
    ADMUX |= (1 << 7);

    // Configure the RIGHT adjust
    ADMUX &= ~(1 << 5);
    // Select frequency prescaler (max input frequency of AVR ADC is 200 KHZ )
    ADCSRA |= (0X07);
}

void ACD_SelectChannel(unsigned char ChannelNum)
{
    /// TODO:
    // configure it as input
    DIO_SetDirection('C', ChannelNum, INPUT);
    // Select channel
    ADMUX &= ~(0X1F); //leeh msh 0x3f 
    ADMUX |= (ChannelNum);
}

unsigned short ADC_Read(unsigned char ChannelNum)
{
    /// TODO:
    // Check if channel selected
    // if selected
    // Start conversion(Start ADC read)
    // wait until conversion is complete
    // else
    // return -1
    if ((ADMUX & 0X1F) == ChannelNum)
    {
        ADCSRA |= (1 << 6);
        while (ADCSRA & (1 << 6))
        {}
        return ADC;
    }
    else
    {

        return -1;
    }
}