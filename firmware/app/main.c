#include "kernel/interrupt.h"
#include "kernel/sysdelay.h"
#include "app/communication.h"
#include "app/log.h"
#include "app/motorcontrol.h"
#include "app/imusensors.h"

int main() {
    CommunicationState commState;

    // Setup sysdelay timer
    SysDelayTimerSetup();

    // Initialize communication
    CommunicationInit(&commState);

    // Enable master IRQ
    IntMasterIRQEnable();

    // Enable arm interrupt controller
    IntAINTCInit();

    // Init motors
    MotorControlInit();

    // Init IMU Sensors
    IMUSensorsInit();

    while(1) {
        LogCString(LOG_LEVEL_ERROR, "LogMessage\r\n");
        Sysdelay(1000);
    }
    return 0;
}
