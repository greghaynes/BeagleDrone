#include "utils/uartStdio.h"
#include "kernel/interrupt.h"
#include "kernel/sysdelay.h"
#include "app/communication.h"
#include "app/log.h"
#include "app/motors.h"

int main() {
    SysDelayTimerSetup();
    CommunicationInit();
    IntMasterIRQEnable();
    MotorsInit();

    while(1) {
        //CommunicationSend("Hello, world!\r\n", 15);
        LogCString(LOG_LEVEL_ERROR, "LogMessage\r\n");
        Sysdelay(1000);
    }
    return 0;
}
