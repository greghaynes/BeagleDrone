#include "app/communication.h"
#include "app/log.h"
#include "app/imusensors.h"
#include "glue/motors.h"

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
    }
    return 0;
}
