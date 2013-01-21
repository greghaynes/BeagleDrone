#include "kernel/sysdefs.h"

#define IRQC_IRQ_HANDLER (*(pREG32 (0x4030CE38)))

void irq_handler(void) {
}

void setup_irq(void) {
    IRQC_IRQ_HANDLER = (uint32_t)irq_handler;
}

