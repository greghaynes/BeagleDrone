#include "utils/uartStdio.h"
#include "kernel/interrupt.h"
#include "kernel/sysdelay.h"
#include "app/communication.h"
#include "app/log.h"
#include "app/motors.h"
#include "app/imusensors.h"

int main() {
    // Setup sysdelay timer
    SysDelayTimerSetup();

    // Initialize communication
    CommunicationInit();

    // Enable master IRQ
    IntMasterIRQEnable();

    // Enable arm interrupt controller
    IntAINTCInit();

    // Init motors
    MotorsInit();

    // Init IMU Sensors
    IMUSensorsInit();

    while(1) {
        LogCString(LOG_LEVEL_ERROR, "LogMessage\r\n");
        Sysdelay(1000);
    }
    return 0;
}
