#include "kernel/interrupt.h"
#include "kernel/hw/intc.h"
#include "kernel/sysdefs.h"

void (*volatile interruptHandlers[INTERRUPT_CNT])(void);

/* Default handler which does nothing */
void interrupt_default_handler(void) {
}

void interrupt_init(void) {
    unsigned int i;

    // Reset intc
    REGP(INTC_SYSCONFIG) = INTC_SYSCONFIG_SOFTRESET;

    // Wait for reset completion
    while(!(REGP(INTC_SYSSTATUS) & INTC_SYSSTATUS_RESETDONE));

    // Set interrupt priority threshold
    REGP(INTC_THRESHOLD) = INTC_THRESHOLD_PRIORITYTHRESHOLD;

    // Load default handlers
    for(i = 0; i < INTERRUPT_CNT; ++i)
        interruptHandlers[i] = interrupt_default_handler;
}

interrupt_handler interrupt_get_handler(int ndx) {
    return interruptHandlers[ndx];
}

void interrupt_set_handler(int ndx, void (*handler)(void)) {
    interruptHandlers[ndx] = handler;
}
