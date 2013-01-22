#include "kernel/hw/irq.h"
#include "kernel/hw/intc.h"
#include "kernel/sysdefs.h"

#define NUM_INTERRUPTS (128u)

extern void IRQHandler(void);

void irq_init(void) {
    REGP(IRQ_IRQ_HANDLER) = (uint32_t)IRQHandler;
}

