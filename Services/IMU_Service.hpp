#ifndef IMU_SERVICE_HPP
#define IMU_SERVICE_HPP

#include "../HAL/MPU9250_HAL.hpp"
#include <cstdint>

struct AccelData {
    float x_g;
    float y_g;
    float z_g;
};

struct GyroData {
    float x_dps;
    float y_dps;
    float z_dps;
};

struct TempData {
    float temperature_c;
};

struct MagData {
    float x_uT;
    float y_uT;
    float z_uT;
};

struct IMUData {
    AccelData accel;
    GyroData gyro;
    TempData temp;
    MagData mag;
};

class IMUService {
public:
    IMUService(MPU9250_HAL &hal);

    bool begin();

    AccelData getAccelerometer();
    GyroData  getGyroscope();
    TempData  getTemperature();
    MagData   getMagnetometer();

    IMUData   getAll();

private:
    MPU9250_HAL &hal_;

    const float accelScale_; // LSB -> g
    const float gyroScale_;  // LSB -> deg/s
    const float magScale_;   // LSB -> µTesla (scaling from AK8963)
};

#endif // IMU_SERVICE_HPP
