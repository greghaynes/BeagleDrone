#include "kernel/hw/soc_AM335x.h"
#include "kernel/drivers/hsi2c.h"
#include "kernel/interrupt.h"
#include "kernel/beaglebone.h"
#include "imusensors.h"

#define GYRO_I2C_WRITE_ADDR 0xD0
#define GYRO_I2C_READ_ADDR 0xD1

static StateRotationalShort sensor_gyro;
static StateRotationalShort sensor_accelero;
static StateRotationalShort sensor_magneto;

static void I2CIsr(void) {
}

static void SetupI2C(void) {
    // Zero our sensors
    StateZeroRotationalShort(&sensor_gyro);
    StateZeroRotationalShort(&sensor_accelero);
    StateZeroRotationalShort(&sensor_magneto);

    // Enable the clock for I2C1
    I2C1ModuleClkConfig();

    // Set pin mux for I2C1
    I2CPinMuxSetup(1);

    // Put I2C1 in reset/disabled state
    I2CMasterDisable(SOC_I2C_1_REGS);

    // Disable auto idle
    I2CAutoIdleDisable(SOC_I2C_1_REGS);

    // Set bus speed to 400khz
    I2CMasterInitExpClk(SOC_I2C_1_REGS, 48000000, 12000000, 400000);

    // Set slave address
    I2CMasterSlaveAddrSet(SOC_I2C_1_REGS, GYRO_I2C_WRITE_ADDR);

    // Bring out of reset
    I2CMasterEnable(SOC_I2C_1_REGS);

    // Set I2C ISR
    IntRegister(SYS_INT_I2C1INT, I2CIsr);

    // Set ISR Priority
    IntPrioritySet(SYS_INT_I2C1INT, 1, AINTC_HOSTINT_ROUTE_IRQ );

    // Enable I2C Interrupt
    IntSystemEnable(SYS_INT_I2C1INT);
}

void IMUSensorsInit(void) {
    SetupI2C();
}

const StateRotationalShort *IMUSensorsGetGyro(void) {
    return &sensor_gyro;
}

const StateRotationalShort *IMUSensorsGetAccelero(void) {
    return &sensor_accelero;
}

const StateRotationalShort *IMUSensorsGetMagneto(void) {
    return &sensor_magneto;
}
