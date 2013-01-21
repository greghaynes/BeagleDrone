#ifndef INTERRUPT_H
#define INTERRUPT_H

void interrupt_init(void);
void interrupt_get_handler(int ndx);
void interrupt_set_handler(int ndx, void (*handler)(void));

#endif
