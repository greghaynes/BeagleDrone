#include "kernel/timers/dmtimer.h"
#include "kernel/hw/cm_per.h"
#include "kernel/sysdefs.h"

void dmtimer_clk_enable(int timer_num) {
    if (timer_num >= 2 && timer_num <= 7) {
        // Start l3s timer wakeup
        REGP(CM_PER_L3S_CLKSTCTRL) =
            CM_PER_L3S_CLKSTCTRL_CLKTRCTRL_SW_WKUP;

        // Wait for wakeup to complete
        while((REGP(CM_PER_L3S_CLKSTCTRL) &
            CM_PER_L3S_CLKSTCTRL_CLKTRCTRL) !=
                CM_PER_L3S_CLKSTCTRL_CLKTRCTRL_SW_WKUP);

        // Start l3 timer wakeup
        REGP(CM_PER_L3_CLKSTCTRL) = CM_PER_L3_CLKSTCTRL_CLKTRCTRL_SW_WKUP;
            
        // Wait for wakeup to complete
        while((REGP(CM_PER_L3_CLKSTCTRL) &
            CM_PER_L3_CLKSTCTRL_CLKTRCTRL) !=
                CM_PER_L3_CLKSTCTRL_CLKTRCTRL_SW_WKUP);

        switch(timer_num) {
            case 2:

                break;
        }
    }
}
