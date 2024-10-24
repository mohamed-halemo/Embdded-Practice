#include "m328Pdef.inc"
.globl program
program:

;configuration
    LDI R16, 0xFF
    OUT DDRD, R16
    OUT PORTB , R16
    OUT PORTC, R16
    LDI R16, 0x00
    OUT DDRB, R16
    OUT DDRC, R16

;input 
INPUT: IN R21, PINB
    COM R21
    ANDI R21,0x0F


;checking
    SBIC PINC, 0
    Rjmp INPUT
; rotation
ROTATION: LDI R17,0x81
Again: 
    LDI R20, 0x80
    LSR R17
    BRCC L4
    OR R17,R20
L4: Call Delay
    OUT PORTD , R17
    DEC R21
    BRNE Again

; second checking
    SBIC PINC,1
    Rjmp INPUT
    Rjmp ROTATION
    
loop: jmp program

; Delay
Delay:LDI R23 ,0xFF
L3: LDI R22, 0xFF
L2: LDI R24, 0xFF
L1: DEC R24
    BRNE L1
    DEC R22
    BRNE L2
    DEC R23
    BRNE L3
    RET


    




