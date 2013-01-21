#include "kernel/interrupt.h"

void (*interrupt_handlers[INTERRUPT_CNT])(void);

/* Default handler which does nothing */
void interrupt_default_handler(void) {
}

void interrupt_init(void) {
    int i;

    // Load default handlers
    for(i = 0; i < INTERRUPT_CNT; ++i)
        interrupt_handlers[i] = interrupt_default_handler;
}

