#include "m328Pdef.inc"

.globl program
program :
LDI R16,0xFF
OUT DDRD, R16 ;make Port D an output
LDI R16,0
OUT DDRC, R16 ;make Port C an input for ADC
LDI R16,0X40   ;FOR VCC
STS ADMUX,R16 
LDI R16,0x87
STS ADCSRA,R16  ;to enable adc
L1:
LDS R18,ADCSRA 
ORI R18,0X40 ;START CONVERSION BIT NO.6
STS ADCSRA,R18 ;putting in adcsra
L2:
LDS R19,ADCSRA
ANDI R19,0X40 ;looping to check conversion (bit 6)
BRNE L2
LDS R20,ADCL ; LOADING ADCL  8 bits
LDS R21,ADCH ;Loading adch 8bits
LSR R20 ;shifting low dividing by 2
LSR R21 ;shifting high to take carry
BRCC L3  ;output if carry is zero
ORI R20,0X80 ; else put the carry in adcl as we take 8 bits of adcl
L3:
OUT PORTD,R20 ;out
RJMP L1

jmp program