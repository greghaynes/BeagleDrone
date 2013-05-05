#include "kernel/hw/soc_AM335x.h"
#include "kernel/drivers/hsi2c.h"
#include "kernel/interrupt.h"
#include "kernel/beaglebone.h"
#include "app/mathhelp.h"
#include "imusensors.h"

#define GYRO_I2C_WRITE_ADDR 0xD0
#define GYRO_I2C_READ_ADDR 0xD1

static StateRotationalShort sensor_gyro;
static StateRotationalShort sensor_accelero;

#define GYRO_SENSOR_ID 0
#define ACCELERO_SENSOR_ID 1
#define NUM_SENSORS 2

// Bitmask for determining if sensors need to be read
volatile unsigned int sensor_do_read;
#define GYRO_DO_READ_MASK (1 << GYRO_SENSOR_ID)
#define ACCELERO_DO_READ_MASK (1 << ACCELERO_SENSOR_ID)

typedef enum IMUI2CState {
    IMU_I2C_STATE_STARTING,
    IMU_I2C_STATE_IDLE,
    IMU_I2C_STATE_GYRO_READING,
    IMU_I2C_STATE_ACCELERO_READING,
} IMUI2CState;
static IMUI2CState imu_i2c_state;

volatile unsigned int sensor_read_buff_next;
volatile unsigned char sensor_read_buff[50];

static void UpdateNextSensor(void);

static void I2CIsr(void) {
    unsigned int status;

    // Get i2c interrupt status
    status = I2CMasterIntStatus(SOC_I2C_1_REGS);

    // Clear all int status flags but recv and transmit rdy
    I2CMasterIntClearEx(SOC_I2C_1_REGS, (status &
        ~(I2C_INT_RECV_READY | I2C_INT_TRANSMIT_READY)));

    if(status & I2C_INT_RECV_READY) {
        // Read data into read buff
        sensor_read_buff[sensor_read_buff_next++] = I2CMasterDataGet(SOC_I2C_1_REGS);

        // Clear receive rdy interrupt
        I2CMasterIntClearEx(SOC_I2C_1_REGS,  I2C_INT_RECV_READY);
    }
}

static void StartGyroUpdate(void) {
    imu_i2c_state = IMU_I2C_STATE_GYRO_READING;
    sensor_do_read = sensor_do_read & ~GYRO_DO_READ_MASK;

    // Placeholder until read is performed
    UpdateNextSensor();
}

static void StartAcceleroUpdate(void) {
    imu_i2c_state = IMU_I2C_STATE_ACCELERO_READING;
    sensor_do_read = sensor_do_read & ~ACCELERO_DO_READ_MASK;

    // Placeholder until read is performed
    UpdateNextSensor();
}

static void UpdateNextSensor(void) {
    switch(imu_i2c_state) {
    case IMU_I2C_STATE_STARTING:
        StartGyroUpdate();
        break;
    case IMU_I2C_STATE_GYRO_READING:
        if(sensor_do_read & ACCELERO_DO_READ_MASK)
            StartAcceleroUpdate();
        break;
    case IMU_I2C_STATE_ACCELERO_READING:
        if(sensor_do_read & GYRO_DO_READ_MASK)
            StartGyroUpdate();
        break;
    default:
        break;
    }
}

static void SetupI2C(void) {
    // Zero out I2C State
    sensor_do_read = 0;
    sensor_read_buff_next = 0;
    imu_i2c_state = IMU_I2C_STATE_STARTING;

    // Zero our sensors
    Vector3FZero((Vector3F*)&sensor_gyro);
    Vector3FZero((Vector3F*)&sensor_accelero);

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

    // In case we got an INT during startup
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

void IMUSensorsUpdateGyro(void) {
    if(imu_i2c_state != IMU_I2C_STATE_IDLE)
        sensor_do_read |= GYRO_DO_READ_MASK;
    else
        StartGyroUpdate();
}

void IMUSensorsUpdateAccelero(void) {
    if(imu_i2c_state != IMU_I2C_STATE_IDLE)
        sensor_do_read |= ACCELERO_DO_READ_MASK;
    else
        StartAcceleroUpdate();
}

