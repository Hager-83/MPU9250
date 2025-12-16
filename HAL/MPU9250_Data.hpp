#ifndef _MPU9250_DATA_HPP_
#define _MPU9250_DATA_HPP_

/****************************************************************************/
/* cmath: Standard integer types.*/
#include <cmath>
#include <optional>
/****************************************************************************
     * @struct: ReadAccData
     * @brief : Structure holding raw or processed accelerometer data from MPU9250.
     *
     * This structure is used to store the acceleration values measured along
     * the X, Y, and Z axes in units of g (or m/s² depending on scaling).
     *
     * @details
     * Members:
     * - ax : Acceleration along X-axis
     * - ay : Acceleration along Y-axis
     * - az : Acceleration along Z-axis
     ***************************************************************************/
    struct AccelerationData
    {
        float ax;
        float ay;
        float az;
    };


    /****************************************************************************
     * @struct: ReadGyroData
     * @brief : Structure holding raw or processed gyroscope data from MPU9250.
     *
     * This structure contains angular velocity measurements around the X, Y,
     * and Z axes, typically in degrees per second (dps) or radians per second.
     *
     * @details
     * Members:
     * - gx : Angular velocity around X-axis
     * - gy : Angular velocity around Y-axis
     * - gz : Angular velocity around Z-axis
     ***************************************************************************/
    struct GyroscopeData
    {
        float gx;
        float gy;
        float gz;
    };


    /****************************************************************************
     * @struct: ReadTempData
     * @brief : Structure holding the MPU9250 internal temperature sensor reading.
     *
     * This structure is used to store the die temperature of the MPU9250 in degrees Celsius.
     * The temperature value is calculated from the raw register data using the
     * official formula: Temp(°C) = (raw_temp / 333.87) + 21.0
     *
     * @details
     * Member:
     * - temperature_c : Sensor temperature in degrees Celsius (°C)
     ***************************************************************************/
    struct TemperatureData
    {
        float temperature_c;
    };


    /****************************************************************************
     * @struct: ReadMagData
     * @brief : Structure holding magnetometer (compass) data from MPU9250's AK8963/AK09916.
     *
     * Contains magnetic field strength measurements along X, Y, and Z axes,
     * typically in micro-Tesla (µT) after calibration and scaling.
     *
     * @details
     * Members:
     * - mx : Magnetic field strength along X-axis
     * - my : Magnetic field strength along Y-axis
     * - mz : Magnetic field strength along Z-axis
     ***************************************************************************/
    struct MagnomaterData
    {
        float mx;
        float my;
        float mz;
    };

    /****************************************************************************
     * @struct: ReadAllData
     * @brief : Structure aggregating all sensor readings from the MPU9250.
     *
     * This structure combines data from accelerometer, gyroscope, temperature,
     * and magnetometer sensors into a single object for comprehensive access.
     *
     * @details
     * Members:
     * - acc_obj : Accelerometer data (ReadAccData)
     * - gyro_obj : Gyroscope data (ReadGyroData)
     * - temp_obj : Temperature data (ReadTempData)
     * - meg_data : Magnetometer data (ReadMagData)
     ***************************************************************************/
    struct IMUAllData
    {
        std::optional<AccelerationData> acc_obj;
        std::optional<GyroscopeData> gyro_obj;
        std::optional<TemperatureData> temp_obj;
        std::optional<MagnomaterData> meg_data;
    };
    
#endif /*_MPU9250_DATA_HPP_*/
