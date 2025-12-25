.equ DDRB,  0x04       
.equ PORTB, 0x05     
.equ LED,   7           

.org 0x0000             
    rjmp RESET           

RESET:
    ldi r16, (1 << LED)  
    out DDRB, r16        

loop:
    ldi r16, (1 << LED)  
    out PORTB, r16       
    rcall delay_1s       

    ldi r17, (1 << LED)  
    com r17              
    and r16, r17         
    out PORTB, r16      
    rcall delay_500ms    

    rjmp loop            

delay_1s:
    ldi r18, 4          
d1_outer:
    rcall delay_250ms  
    dec r18
    brne d1_outer
    ret

delay_500ms:
    ldi r18, 2           
d2_outer:
    rcall delay_250ms
    dec r18
    brne d2_outer
    ret

delay_250ms:
    ldi r20, 250         
d3_loop:
    rcall delay_1ms
    dec r20
    brne d3_loop
    ret

delay_1ms:
    ldi r22, 20
ms_outer:
    ldi r23, 230
ms_inner:
    nop
    nop
    dec r23
    brne ms_inner
    dec r22
    brne ms_outer
    ret
