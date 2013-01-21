#include "kernel/boot/irq.h"

extern void start(void);

void main(void) {
    irq_init();

    start();
    while(1);
}
