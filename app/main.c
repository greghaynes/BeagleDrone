#include "utils/uartStdio.h"
#include "kernel/interrupt.h"
#include "kernel/sysdelay.h"
#include "app/communication.h"

int main() {
    CommunicationsInit();
    SysDelayTimerSetup();
    IntMasterIRQEnable();

    while(1) {
        CommunicationCheck();
    }
    return 0;
}
