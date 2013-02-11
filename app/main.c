#include "utils/uartStdio.h"
#include "kernel/interrupt.h"
#include "kernel/sysdelay.h"
#include "app/communication.h"
#include "app/log.h"

int main() {
    SysDelayTimerSetup();
    CommunicationsInit();
    IntMasterIRQEnable();

    while(1) {
        CommunicationSend("\r\nHello, world!\r\n", 14);
        Sysdelay(1000);
    }
    return 0;
}
