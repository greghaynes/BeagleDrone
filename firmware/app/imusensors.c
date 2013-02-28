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

#define GYRO_SENSOR_ID 1
#define ACCELERO_SENSOR_ID 2
#define MAGNETO_SENSOR_ID 3

// Bitmask for sensors that are ready for a read
static unsigned int sensor_do_read;

#define GYRO_DO_READ_MASK (1 << GYRO_SENSOR_ID)
#define ACCELERO_DO_READ_MASK (1 << ACCELERO_SENSOR_ID)
#define MAGNETO_DO_READ_MASK (1 << MAGNETO_SENSOR_ID)

typedef enum IMUI2CState {
    IMU_I2C_STATE_STARTING,
    IMU_I2C_STATE_READY,
    IMU_I2C_STATE_GYRO_UPDATE,
    IMU_I2C_STATE_ACCELERO_UPDATE,
    IMU_I2C_STATE_MAGNETO_UPDATE,
} IMUI2CState;
static IMUI2CState imu_i2c_state = IMU_I2C_STATE_STARTING;

static void I2CIsr(void) {
    unsigned int status;

    // Get i2c interrupt status
    status = I2CMasterIntStatus(SOC_I2C_0_REGS);

    // Clear all int status flags but recv and transmit rdy
    I2CMasterIntClearEx(SOC_I2C_0_REGS, (status &
        ~(I2C_INT_RECV_READY | I2C_INT_TRANSMIT_READY)));

    if(status & I2C_INT_RECV_READY) {
        
    }
}

static void UpdateNextSensor(void) {
    if(imu_i2c_state != IMU_I2C_STATE_READY)
        return;
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

    // Set local imu state machine to ready
    imu_i2c_state = IMU_I2C_STATE_READY;

    UpdateNextSensor();
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

void IMUSensorsUpdateGyro(void) {
    sensor_do_read |= GYRO_DO_READ_MASK;
}

void IMUSensorsUpdateAccelero(void) {
    sensor_do_read |= ACCELERO_DO_READ_MASK;
}

void IMUSensorsUpdateMagneto(void) {
    sensor_do_read |= MAGNETO_DO_READ_MASK;
}
