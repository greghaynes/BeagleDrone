#ifndef HW_INTC_H
#define HW_INTC_H

#define INTC_SYSCONFIG                      0x48200010
#define INTC_SYSCONFIG_SOFTRESET            0x2u

#define INTC_SYSSTATUS                      0x48200014
#define INTC_SYSSTATUS_RESETDONE            0x1u

#define INTC_SIR_IRQ                        0x48200040
#define INTC_SIR_IRQ_ACTIVEIRQ              0x7F

#define INTC_CONTROL                        0x48200048
#define INTC_CONTROL_NEWIRQAGR              0x1

#define INTC_IRQ_PRIORITY                   0x48200060

#define INTC_THRESHOLD                      0x48200068
#define INTC_THRESHOLD_PRIORITYTHRESHOLD    0xFFu


#endif
