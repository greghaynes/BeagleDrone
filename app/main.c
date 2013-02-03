#include "utils/uartStdio.h"
#include "kernel/interrupt.h"
#include "app/communication.h"

int main() {
    UARTStdioInit();
    IntMasterIRQEnable();

    while(1) {
        CommunicationCheck();
    }
    return 0;
}
