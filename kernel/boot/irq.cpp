#include "kernel/sysdefs.h"

#define IRQC_IRQ_HANDLER (*(pREG32 (0x4030CE38)))

#define NUM_INTERRUPTS (128u)

void irq_handler(void) {
}

void irq_init(void) {

    IRQC_IRQ_HANDLER = (uint32_t)irq_handler;
}

