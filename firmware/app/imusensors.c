#include "kernel/hw/soc_AM335x.h"
#include "kernel/drivers/hsi2c.h"
#include "kernel/beaglebone.h"
#include "imusensors.h"

#define I2C_SLAVE_ADDR 0x00

static StateRotationalShort sensor_gyro;
static StateRotationalShort sensor_accelero;
static StateRotationalShort sensor_magneto;

void IMUSensorsInit(void) {
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

    // Set bus speed
    I2CMasterInitExpClk(SOC_I2C_1_REGS, 48000000, 12000000, 100000);

    // Set slave address
    I2CMasterSlaveAddrSet(SOC_I2C_1_REGS, I2C_SLAVE_ADDR);

    // Bring out of reset
    I2CMasterEnable(SOC_I2C_1_REGS);
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
