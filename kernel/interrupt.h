#ifndef INTERRUPT_H
#define INTERRUPT_H

#define INTERRUPT_CNT (128u)

typedef void (*interrupt_handler)(void);

void interrupt_init(void);
interrupt_handler interrupt_get_handler(int ndx);
void interrupt_set_handler(int ndx, void (*handler)(void));

#endif
