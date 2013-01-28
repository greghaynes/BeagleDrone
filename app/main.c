#include "utils/delay.h"
#include "utils/uartStdio.h"

int main() {
    DelayTimerSetup();
    UARTStdioInit();

    while(1) {
        UARTPutc('.');
        delay(1000);
    }
    return 0;
}
