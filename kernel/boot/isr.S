#include "kernel/hw/intc.h"

.equ MODE_SYS, 0x1F
.equ MODE_IRQ, 0x12
.equ I_BIT, 0x80

.text
.code 32
.extern interruptHandlers
.global IRQHandler

IRQHandler:
        SUB      lr, lr, #4               @ Apply lr correction
        STMFD    sp!, {r0-r3, r12, r14}   @ Save context

        MRS      r12, spsr                @ Copy spsr
        STMFD    sp!, {r12}               @ Save spsr

        LDR      r0, =INTC_THRESHOLD      @ Get the IRQ Threshold
        LDR      r1, [r0, #0]             
        STMFD    sp!, {r1}               @ Save the threshold value

        LDR      r2, =INTC_IRQ_PRIORITY   @ Get the active IRQ priority
        LDR      r3, [r2, #0]
        STR      r3, [r0, #0]             @ Set the priority as threshold   

        LDR      r1, =INTC_SIR_IRQ        @ Get the Active IRQ
        LDR      r2, [r1]
        AND      r2, r2, #INTC_SIR_IRQ_ACTIVEIRQ @ Mask the Active IRQ number

        MOV      r0, #INTC_CONTROL_NEWIRQAGR    @ To enable new IRQ Generation
        LDR      r1, =INTC_CONTROL

        CMP      r3, #0                   @ Check if non-maskable priority 0
        STRNE    r0, [r1]                 @ if > 0 priority, acknowledge INTC
        DSB                               @ Make sure acknowledgement is completed

        @
        @ Enable IRQ and switch to system mode. But IRQ shall be enabled
        @ only if priority level is > 0. Note that priority 0 is non maskable.
        @ Interrupt Service Routines will execute in System Mode.
        @
        MRS      lr, cpsr                 @ Read cpsr
        ORR      lr, lr, #MODE_SYS
        BICNE    lr, lr, #I_BIT           @ Enable IRQ if priority > 0
        MSR      cpsr, lr


        STMFD    sp!, {lr}                @ Save lr_usr

        LDR      r0, =interruptHandlers  @ Load the base of the vector table
        ADD      lr, pc, #0               @ Save return address in LR
        LDR      pc, [r0, r2, lsl #2]     @ Jump to the ISR

        LDMFD    sp!, {lr}                @ Restore lr_usr

        @
        @ Disable IRQ and change back to IRQ mode
        @
        CPSID    i, #MODE_IRQ

        LDR      r0, =INTC_THRESHOLD      @ Get the IRQ Threshold

        LDR      r1, [r0, #0]
        CMP      r1, #0                   @ If priority 0
        MOVEQ    r2, #INTC_CONTROL_NEWIRQAGR    @ Enable new IRQ Generation
        LDREQ    r1, =INTC_CONTROL
        STREQ    r2, [r1]

        LDMFD    sp!, {r1}
        STR      r1, [r0, #0]             @ Restore the threshold value
        LDMFD    sp!, {r3}
        MSR      spsr, r3                 @ Restore spsr

        LDMFD    sp!, {r0-r3, r12, pc}^   @ Restore the context and return
