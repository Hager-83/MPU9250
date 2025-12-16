/**
 * @file  :IMU_SERVICE_HPP
 * @brief :IMU Service Layer for processed sensor data from MPU9250.
 * 
 * This header defines data structures for IMU sensor readings (accelerometer, gyroscope,
 * temperature, and magnetometer) and the IMUService class. The service provides
 * scaled and processed data in physical units (e.g., g, dps, °C, µT) on top of the
 * raw HAL interface.
 * 
 * @author  :[Hager Shohieb, Sara Saad]
 * @version :1.0
 * @date    :December 01, 2025
 *
 **/

#ifndef IMU_SERVICE_HPP
#define IMU_SERVICE_HPP

/****************************************** include part ********************************************* */
#include "../HAL/MPU9250_HAL.hpp"
#include "../HAL/MPU9250_Data.hpp"
#include "../Application/MPU9250_config.hpp"
/**************************************** User Data Types Part *************************************** */

/********************************************************************************
 * @class :IMUService
 * @brief :Service layer for retrieving scaled IMU sensor data.
 * 
 * This class wraps the MPU9250_HAL to provide convenient access to processed
 * sensor readings in physical units. It handles scaling from raw LSB values
 * to meaningful units. Initialization via begin() ensures the HAL is ready.
 * 
 * @note :Scaling factors are constant members; they must be initialized in the
 *       constructor with values based on the sensor's full-scale range
 *       (e.g., accelScale_ = 1.0f / 16384.0f for ±2g).
 *******************************************************************************/
class IMUService 
{
    
    public:

    /***************************************************************************
     * @brief :Constructor for IMUService.
     * 
     * Initializes the service with a reference to the HAL instance.
     * Scaling factors should be computed here based on HAL configuration.
     * 
     * @param hal :Reference to the MPU9250_HAL instance.
     **************************************************************************/
    IMUService();

    /**************************************************************************
     * @brief Destructor for IMUService.
     * 
     * Frees any dynamically allocated resources used by the service,
     * specifically the internal HAL pointer if it was created in begin().
     *************************************************************************/
    ~IMUService();

    /*************************************************************************
     * @brief Check whether the IMU sensor is currently connected.
     * 
     * Uses the internal HAL object to verify connectivity. Returns false if
     * the HAL has not been initialized yet (i.e., begin() was not called).
     * 
     * @return true if the sensor is connected, false otherwise.
     ***********************************************************************/
    std::optional<bool> IsConnected() const;

    /*****************************************************************************
     * @brief :Get processed accelerometer data.
     * 
     * Reads raw accel data from HAL, applies scaling, and returns in g units.
     * 
     * @return :AccelData structure with scaled values.
    ****************************************************************************/
    std::optional<AccelerationData>  GetAccelerometer(void);

    /****************************************************************************
     * @brief Get processed gyroscope data.
     * 
     * Reads raw gyro data from HAL, applies scaling, and returns in dps.
     * 
     * @return GyroData structure with scaled values.
     ***************************************************************************/
    std::optional<GyroscopeData> GetGyroscope(void);

    /***********************************************************************************
     * @brief :Get processed temperature data.
     * 
     * Reads raw temp data from HAL and converts to °C.
     * Formula: temp_c = (raw_temp / 333.87f) + 21.0f (example; adjust per datasheet).
     * 
     * @return :TempData structure with scaled value.
     ***********************************************************************************/
   std::optional<TemperatureData> GetTemperature(void);

    /*************************************************************************************
     * @brief :Get processed magnetometer data.
     * 
     * Reads raw mag data from AK8963 via HAL, applies scaling, and returns in µT.
     * 
     * @return :MagData structure with scaled values.
     ************************************************************************************/
   std::optional<MagnomaterData> GetMagnetometer(void);

    /***********************************************************************************
     * @brief :Get all processed IMU data at once.
     * 
     * Convenience method calling all getters and combining into IMUData.
     * 
     * @return :IMUData structure with all scaled values.
     ***********************************************************************************/
    std::optional<IMUAllData> GetAll(void);

private:
    MPU9250_HAL* hal_;
    MPU9250_HAL::MagAdjustment mag_asa_;

    const float accelScale_; 
    const float gyroScale_; 
    const float magScale_;   
    const float tempScale_;

    /**************************************************************************
     * @brief Initialize the IMU service and create the HAL instance.
     * 
     * This function sets up the internal MPU9250_HAL object, performs any
     * necessary initialization, and checks that the sensor is connected.
     * Must be called before reading any sensor data.
     * 
     * @return true if the sensor was detected and initialized successfully,
     *         false otherwise.
     *************************************************************************/
    std::optional<bool> Begin();
};

/****************************************************************************************************** */
#endif // IMU_SERVICE_HPP
