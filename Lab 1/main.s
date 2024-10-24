.globl main
main: 
    LDI R16,0x20
    STS 0x24,R16
    ;Write your code here 
loop: jmp loop
