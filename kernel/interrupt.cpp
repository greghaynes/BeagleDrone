#include "kernel/interrupt.h"
#include "kernel/hw/intc.h"

#define INTERRUPT_CNT (128u)

void (*interrupt_handlers[INTERRUPT_CNT])(void);

/* Default handler which does nothing */
void interrupt_default_handler(void) {
}

void interrupt_init(void) {
    int i;

    // Reset intc
    REGP(INTC_SYSCONFIG) = INTC_SYSCONFIG_SOFTRESET;

    // Wait for reset completion
    while(!(REGP(INTC_SYSSTATUS) & INTC_SYSSTATUS_RESETDONE));

    // Set interrupt priority threshold
    REGP(INTC_THRESHOLD) = INTC_THRESHOLD_PRIORITYTHRESHOLD;

    // Load default handlers
    for(i = 0; i < INTERRUPT_CNT; ++i)
        interrupt_handlers[i] = interrupt_default_handler;
}

void interrupt_get_handler(int ndx) {
    return interrupt_handlers[ndx];
}

void interrupt_set_handler(int ndx, void (*handler)(void)) {
    interrupt_handlers[ndx] = handler;
}
