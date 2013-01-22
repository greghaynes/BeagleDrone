#include "kernel/boot/irq.h"

extern void main(void);

void start(void) {
    irq_init();

    start();
    while(1);
}
