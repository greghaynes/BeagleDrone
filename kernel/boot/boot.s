.section .kernel, "ax"
.global __kernel
.global __main
.code 32
        
__kernel:
   ldr r0,=0x44e09000
   ldr r1,=0x21
   strb r1,[r0]
_call_main:
   ldr r1, =main /* Jump to c entry */
   mov lr, pc
   bx r1
