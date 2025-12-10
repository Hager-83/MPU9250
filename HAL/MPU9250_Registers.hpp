#ifndef MPU9250_REGISTERS_HPP
#define MPU9250_REGISTERS_HPP

/**********************************************Include Part ***************************************** */
#include <cstdint>

/*************************************** Register Definition **************************************** */

/* Default I2C address for MPU6500 (part of MPU9250)*/
constexpr uint16_t MPU6500_DEFAULT_ADDRESS = 0x68;
/* Device identification register(to verify access to MPU-9250) */
constexpr uint8_t WHO_AM_I = 0x75;
/* Controls power modes, reset, clock source, and sleep/cycle status */
constexpr uint8_t PWR_MGMT_1 = 0x6B;  
/* Sets the sample rate divider to control the output data rate */
constexpr uint8_t SMPLRT_DIV = 0x19;
/* Configures FIFO behavior, digital low-pass filter for Gyro and temperature*/
constexpr uint8_t CONFIG = 0x1A;
/* Configures DLPF bypass for Accelerometer */
constexpr uint8_t ACCEL_CONFIG2 = 0x1D;


/* Sets interrupt pin polarity */
constexpr uint8_t INT_PIN_CFG = 0x37;
/* Enables/disables interrupts */
constexpr uint8_t INT_ENABLE = 0x38;


/* Upper byte of acceleration measurement on X-axis */
constexpr uint8_t ACCEL_XOUT_H = 0x3B;
/* Lower byte of acceleration measurement on X-axis */
constexpr uint8_t ACCEL_XOUT_L = 0x3C;
constexpr uint8_t ACCEL_YOUT_H = 0x3D;
constexpr uint8_t ACCEL_YOUT_L = 0x3E;
constexpr uint8_t ACCEL_ZOUT_H = 0x3F;
constexpr uint8_t ACCEL_ZOUT_L = 0x40;


/* Upper byte of temperature measuremen */
constexpr uint8_t TEMP_OUT_H = 0x41;
/* Lower byte of temperature measurement */
constexpr uint8_t TEMP_OUT_L = 0x42;


/* Upper byte of rotation measurement on X-axis */
constexpr uint8_t GYRO_XOUT_H = 0x43;
/* Lower byte of rotation measurement on X-axis */
constexpr uint8_t GYRO_XOUT_L = 0x44;
constexpr uint8_t GYRO_YOUT_H = 0x45;
constexpr uint8_t GYRO_YOUT_L = 0x46;
constexpr uint8_t GYRO_ZOUT_H = 0x47;
constexpr uint8_t GYRO_ZOUT_L = 0x48;

/* Control enables/disables FIFO and I2C Master function */
constexpr uint8_t USER_CTRL = 0x6A;
/* Configures I2C Master mode */
constexpr uint8_t I2C_MST_CTRL = 0x24;
/* Enables Slave 4, controls data transfer */
constexpr uint8_t I2C_SLV4_CTRL = 0x34;
/* ets I2C address and read/write for Slave 4 */
constexpr uint8_t I2C_SLV4_ADDR = 0x31;


/* Default I2C address for AK8963 magnetometer */
constexpr uint16_t AK8963_DEFAULT_ADDRESS = 0x0C;

/* Lower byte of magnetic field measurement on X-axis */
constexpr uint8_t AK8963_XOUT_L = 0x03;

/********************************** Gyroscope Scales *********************************** */
constexpr uint8_t GYRO_FS_250  = 0x00; 
constexpr uint8_t GYRO_FS_500  = 0x08; 
constexpr uint8_t GYRO_FS_1000 = 0x10;
constexpr uint8_t GYRO_FS_2000 = 0x18; 

/************************************ Acceleration Scales [Acceleration Range] ******************************* */

constexpr uint8_t ACCEL_FS_2G  = 0x00;
constexpr uint8_t ACCEL_FS_4G  = 0x08; 
constexpr uint8_t ACCEL_FS_8G  = 0x10; 
constexpr uint8_t ACCEL_FS_16G = 0x18; /* Acceleration range ±16 g*/

/****************************************************************************************************** */
#endif // MPU9250_REGISTERS_HPP
