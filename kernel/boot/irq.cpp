#include "kernel/hw/irq.h"
#include "kernel/sysdefs.h"

#define NUM_INTERRUPTS (128u)

void irq_handler(void) {
}

void irq_init(void) {

    REGP(IRQ_IRQ_HANDLER) = (uint32_t)irq_handler;
}

