#include "kernel/hw/irq.h"
#include "kernel/hw/intc.h"
#include "kernel/sysdefs.h"

#define NUM_INTERRUPTS (128u)

void irq_handler(void) {
    // lr correction
    __asm__("SUB      r14, r14, #4");

    // Save state
    __asm__("STMFD    r13!, {r0-r3, r12, r14}");

    // Save spsr
    __asm__("MRS      r12, spsr\n\t"
            "STMFD    r13!, {r12}\n\t");

    // Set IRQ priority to current threshold
    uint32_t thresh = REGP(INTC_THRESHOLD);
    REGP(INTC_IRQ_PRIORITY) = thresh;
}

void irq_init(void) {

    REGP(IRQ_IRQ_HANDLER) = (uint32_t)irq_handler;
}

