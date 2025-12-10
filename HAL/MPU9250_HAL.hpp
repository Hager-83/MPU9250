/**
 * @file : MPU9250_HAL.hpp
 * @brief: Hardware Abstraction Layer (HAL) for the MPU9250 motion sensor.
 * 
 * This header defines the MPU9250_HAL class, providing a simple interface for
 * communicating with the MPU9250 sensor (which includes an accelerometer, gyroscope,
 * temperature sensor, and AK8963 magnetometer) via I2C on a Raspberry Pi Pico w.
 * The class handles initialization, configuration, and raw data reading.
 * 
 * @author :[Sara Saad , Hager Shohieb]
 * @version:1.0
 * @date   :December 01, 2025
 *
 **/


#ifndef MPU9250_HAL_HPP
#define MPU9250_HAL_HPP

/* ************************************** Include Part **************************************** */
#include <cstdint>
#include <memory>
#include <optional>
/* pico/stdlib.h: Pico SDK standard library */
#include "pico/stdlib.h"
/* hardware/i2c.h: Pico SDK I2C hardware interface.*/
#include "hardware/i2c.h"
/* MPU9250_Registers.hpp: Register definitions*/
#include "MPU9250_Registers.hpp"
#include "MPU9250_Data.hpp"
/* ******************************************************************************************** */

/***********************************************************************************
 * @class :MPU9250_HAL
 * @brief :Hardware Abstraction Layer for MPU9250 sensor.
 * 
 * This class provides methods to initialize the I2C interface, test connection,
 * configure the sensor, and read raw sensor data (accelerometer, gyroscope,
 * temperature, and magnetometer). All read operations are blocking.
 * 
 **********************************************************************************/
class MPU9250_HAL 
{
    public:

    /****************************************************************************
     * @struct: MPU9250Initilize
     * @brief :Configuration structure used to initialize the MPU9250 sensor.
     *
     * This structure contains all initialization parameters required for 
     * setting up communication with the MPU9250 using the I2C interface.
     *
     * @details
     * Members include:
     * - Shared pointer to the I2C instance used for communication.
     * - Sensor I2C address.
     * - SDA and SCL pin numbers to be configured on the microcontroller.
     * - I2C bus speed (baud rate).
     ***************************************************************************/
    struct MPU9250Initilize
    {
        std::shared_ptr<i2c_inst_t> i2c = nullptr;
        uint8_t address;
        uint8_t sda_pin;
        uint8_t scl_pin;
        uint32_t baudrate_hz;
    };

    /********************************************************************************************
     * @brief Stores factory sensitivity adjustment values for the AK8963 magnetometer.
     *
     * The AK8963 (inside the MPU9250) provides three ASA (Adjustment Sensitivity Values)
     * for X, Y, and Z axes. These values are used to compensate and calibrate the raw
     * magnetometer readings to improve accuracy.
     *
     * Members:
     *  - asa_x : Sensitivity adjustment factor for X-axis
     *  - asa_y : Sensitivity adjustment factor for Y-axis
     *  - asa_z : Sensitivity adjustment factor for Z-axis
     *********************************************************************************************/
    struct MagAdjustment 
    {
        float asa_x;
        float asa_y;
        float asa_z;
    };
    /**
     * @brief:Constructor for MPU9250_HAL.
     * 
     * Initializes the class with the I2C instance and device address.
     * 
     * @param init: Structure has MPU9250 Intialization.
     */
    MPU9250_HAL(MPU9250Initilize *init);


    /*********************************************************************************************
     * @brief :Test connection to the MPU9250.
     * 
     * Reads the WHO_AM_I register (0x75) and verifies the device ID (expected: 0x71, 0x72, 0x73).
     * 
     * @return :true if connection is valid, false otherwise.
     ********************************************************************************************/
    std::optional<bool> IsConnected(); 


    /***********************************************************************************
     * @brief :Read raw accelerometer data.
     * 
     * Reads 16-bit signed values from ACCEL_XOUT_H/L, ACCEL_YOUT_H/L, ACCEL_ZOUT_H/L.
     * 
     * @param ax :Reference to store X-axis acceleration (raw).
     * @param ay :Reference to store Y-axis acceleration (raw).
     * @param az :Reference to store Z-axis acceleration (raw).
     * @return   :true if read succeeded, false otherwise.
     ************************************************************************************/
    std::optional<bool>  ReadAccelRaw(AccelerationData * acc_data); 


    /********************************************************************************
     * @brief :Read raw gyroscope data.
     * 
     * Reads 16-bit signed values from GYRO_XOUT_H/L, GYRO_YOUT_H/L, GYRO_ZOUT_H/L.
     * 
     * @param gx :Reference to store X-axis gyro (raw).
     * @param gy :Reference to store Y-axis gyro (raw).
     * @param gz :Reference to store Z-axis gyro (raw).
     * @return   :true if read succeeded, false otherwise.
     *********************************************************************************/
    std::optional<bool> ReadGyroRaw(GyroscopeData *gyro_data);


    /*********************************************************
     * @brief :Read raw temperature data.
     * 
     * Reads 16-bit signed value from TEMP_OUT_H/L.
     * 
     * @param temp :Reference to store temperature (raw).
     * @return :true if read succeeded, false otherwise.
     *********************************************************/
    std::optional<bool> ReadTempRaw(TemperatureData*temp_data);


    /************************************************************************
     * @brief :Read raw magnetometer data from AK8963.
     * 
     * Reads 16-bit signed values from the AK8963 registers (e.g., XOUT_L).
     * 
     * @param mx :Reference to store X-axis magnetic field (raw).
     * @param my :Reference to store Y-axis magnetic field (raw).
     * @param mz :Reference to store Z-axis magnetic field (raw).
     * @return :true if read succeeded, false otherwise.
     ***********************************************************************/ 


    std::optional<bool> ReadMagRaw(MagnomaterData *meg_data);
    /**
     * @brief :Read all raw MPU9250 data at once (accelerometer, gyro, temperature).
     * 
     * Convenience method combining readAccelRaw, readGyroRaw, and readTempRaw.
     * 
     * @param ax :Reference to store X-axis acceleration (raw).
     * @param ay :Reference to store Y-axis acceleration (raw).
     * @param az :Reference to store Z-axis acceleration (raw).
     * @param gx :Reference to store X-axis gyro (raw).
     * @param gy :Reference to store Y-axis gyro (raw).
     * @param gz :Reference to store Z-axis gyro (raw).
     * @param temp :Reference to store temperature (raw).
     * @return :true if read succeeded, false otherwise.
     */
    std::optional<bool> ReadAllRaw(IMUAllData *all_data);


    private:

    struct MPU9250Initilize init_;
    MagAdjustment mag_asa_ = {1.0f, 1.0f, 1.0f};

    /*******************************************************************************
     * @brief :Initialize I2C interface.
     * 
     * Configures the I2C pins and baudrate for communication with the sensor.
     * Must be called before any other operations.
     * 
     * @param sda_pin :GPIO pin for SDA (data line).
     * @param scl_pin :GPIO pin for SCL (clock line).
     * @param baudrate_hz :I2C baudrate in Hz (e.g., 400000 for 400 kHz).
     * @return :true if initialization succeeded, false otherwise.
     ******************************************************************************/
    std::optional<bool> Begin();


    /**********************************************************************************
     * @brief I:nitialize and configure the MPU9250 sensor.
     * 
     * Performs a device reset, sets clock source, and enables basic sensor operation
     * (e.g., via PWR_MGMT_1, SMPLRT_DIV, CONFIG, etc.).
     * 
     * @return t:rue if initialization succeeded, false otherwise.
     **********************************************************************************/
    std::optional<bool> InitMPU9250(); 


    /***********************************************************************************
     * @brief :Initialize the AK8963 magnetometer.
     * 
     * Configures the magnetometer via I2C Master mode (e.g., using I2C_SLV4_ADDR).
     * 
     * @return t:rue if initialization succeeded, false otherwise.
     **********************************************************************************/
    std::optional<bool> InitAK8963();


/* ********************************************** Helper Function ********************************************** */

    /************************************************************
     * @brief :Write a single byte to a register.
     * 
     * Internal helper for I2C write operation.
     * 
     * @param reg :Register address.
     * @param value :Value to write.
     * @return :true if write succeeded, false otherwise.
    * ***********************************************************/
    std::optional<bool>  WriteByte(uint8_t reg, uint8_t value);


    /********************************************************************
     * @brief :Read multiple bytes from a register.
     * 
     * Internal helper for burst I2C read (e.g., 6 bytes for 3 axes).
     * 
     * @param reg :Starting register address.
     * @param buffer :Buffer to store read data.
     * @param len :Number of bytes to read.
     * @return :true if read succeeded, false otherwise.
     ********************************************************************/
    std::optional<bool> ReadBytes(uint8_t reg, uint8_t* buffer, size_t len); 

    /****************************************************************************
     * @brief Reads multiple bytes from the AK8963 magnetometer through I2C.
     *
     * @param[in]  reg Starting register address in the AK8963.
     * @param[out] buf Pointer to buffer to store the received bytes.
     * @param[in]  len Number of bytes to read.
     *
     * @return true  → Read success  
     * @return false → I2C write/read error  
     ******************************************************************************/
    std::optional<bool> ReadBytesAK8963(uint8_t reg, uint8_t* buf, size_t len);

    /****************************************************************************
     * @brief :Write a single byte to AK8963 register.
     *
     * @param reg :Register address.
     * @param value :Value to write.
     * @return :true if write succeeded, false otherwise.
     ******************************************************************************/
    std::optional<bool> WriteByteAK8963(uint8_t reg, uint8_t value);
};

/********************************************************************************************************* */
#endif // MPU9250_HAL_HPP_
