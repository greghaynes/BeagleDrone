#include "utils/delay.h"
#include "utils/uartStdio.h"
#include "kernel/interrupt.h"

int main() {
    UARTStdioInit();
    IntMasterIRQEnable();
    DelayTimerSetup();

    while(1) {
        UARTPutc('!');
        delay(1000);
    }
    return 0;
}
