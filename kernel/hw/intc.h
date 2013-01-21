#ifndef HW_INTC_H
#define HW_INTC_H

#define INTC_SYSCONFIG                      0x48200010
#define INTC_SYSCONFIG_SOFTRESET            0x2u

#define INTC_SYSSTATUS                      0x48200014
#define INTC_SYSSTATUS_RESETDONE            0x1u


#define INTC_THRESHOLD                      0x48200068
#define INTC_THRESHOLD_PRIORITYTHRESHOLD    0xFFu

#define INTC_IRQ_PRIORITY                   0x48200060

#endif
