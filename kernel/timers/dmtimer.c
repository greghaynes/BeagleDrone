#include "kernel/timers/dmtimer.h"
#include "kernel/hw/cm_per.h"
#include "kernel/sysdefs.h"

void dmtimer_clk_enable(int timer_num) {
    switch(timer_num) {
        case 2:
            REGP(CM_PER_L3S_CLKSTCTRL) =
                CM_PER_L3S_CLKSTCTRL_CLKTRCTRL_SW_WKUP;

            break;
    }
}
