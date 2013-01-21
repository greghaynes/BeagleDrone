#ifndef INTERRUPT_H
#define INTERRUPT_H

#define INTERRUPT_CNT (128u)

extern void (*interrupt_handlers[INTERRUPT_CNT])(void);

void interrupt_init(void);

#endif
