MPU9250 IMU Driver for Raspberry Pi Pico (C++)

A layered C++ driver for the MPU9250 Inertial Measurement Unit (IMU) targeting the Raspberry Pi Pico / Pico W using the Pico SDK and I2C interface.

This project provides:

A HAL layer for low-level hardware communication.

A Service layer for scaled, physical sensor values.

Clean, modern C++ design using std::optional for safe error handling.

Features

Supports all MPU9250 sensors:

3-axis Accelerometer

3-axis Gyroscope

3-axis Magnetometer (AK8963)

Temperature sensor

Blocking I2C communication using Pico SDK

Factory magnetometer calibration (ASA)

Scaled physical units:

Acceleration → g

Angular rate → deg/s

Temperature → °C

Magnetic field → µT

Layered architecture:

HAL (Hardware Abstraction Layer)

Service Layer

Modern C++:

std::optional

RAII-style design

Strong typing with structs

Architecture
Application
   │
   ▼
IMUService  (Processed / scaled data)
   │
   ▼
MPU9250_HAL (Raw sensor + I2C)
   │
   ▼
Pico SDK I2C Driver

File Structure
/HAL
  ├── MPU9250_HAL.hpp
  ├── MPU9250_HAL.cpp
  ├── MPU9250_Registers.hpp
  ├── MPU9250_Data.hpp

/Service
  ├── IMU_Service.hpp
  ├── IMU_Service.cpp

/Application
  ├── MPU9250_config.hpp

Requirements
Hardware

Raspberry Pi Pico / Pico W

MPU9250 module

I2C wiring:

SDA → GPIO (configurable)

SCL → GPIO (configurable)

VCC → 3.3V

GND → GND

Software

Pico SDK

C++17 or higher

CMake build system

Initialization Flow

The driver initializes in this order:

I2C peripheral configuration

MPU9250 reset and wake-up

Gyroscope and accelerometer setup

Magnetometer (AK8963) configuration

Factory sensitivity calibration (ASA)

This is all handled automatically inside:

Data Structures
AccelerationData
struct AccelerationData {
    float ax;
    float ay;
    float az;
};

GyroscopeData
struct GyroscopeData {
    float gx;
    float gy;
    float gz;
};

TemperatureData
struct TemperatureData {
    float temperature_c;
};

MagnomaterData
struct MagnomaterData {
    float mx;
    float my;
    float mz;
};

IMUAllData
struct IMUAllData {
    std::optional<AccelerationData> acc_obj;
    std::optional<GyroscopeData>    gyro_obj;
    std::optional<TemperatureData>  temp_obj;
    std::optional<MagnomaterData>   meg_data;
};

Scaling & Units
Sensor	Raw → Physical Conversion
Accelerometer	raw / 16384 → g
Gyroscope	raw / 131 → deg/s
Temperature	(raw / 333.87) + 21
Magnetometer	raw × 0.15 → µT

All scaling is handled in IMUService.

Error Handling

All public APIs return:

std::optional<T>


This means:

has_value() → read successful

std::nullopt → I2C error or sensor failure

Example:

auto data = imu.GetAll();
if (!data.has_value()) {
    // Sensor error
}

Design Philosophy

This driver follows clean embedded architecture principles:

Separation of concerns:

HAL → hardware only

Service → math & units

No global variables

No macros for logic

Strong typing for sensor data

Safe failure using std::optional

Easy to port to STM32 / ESP32

Supported Sensors
Sensor	Status
Accelerometer	Supported
Gyroscope	Supported
Magnetometer (AK8963)	Supported
Temperature	Supported
Limitations

Blocking I2C (no DMA / IRQ yet)

No sensor fusion (Kalman / Madgwick not included)

No offset calibration (only factory ASA)

No FIFO / DMP support

Future Improvements

Add non-blocking I2C (DMA / IRQ)

Add calibration routines

Add Madgwick / Mahony filter

Add quaternion & Euler output

Add FreeRTOS compatibility

Authors

Sara Saad

Hager Shohieb

Embedded Systems Engineers
MPU9250 Driver Project – 2025

License

This project is released under the MIT License.
You are free to use, modify, and distribute it in academic and commercial projects.

Target Use Cases

Robotics

Self-balancing robots

Drones

Inertial navigation systems

Attitude estimation

Sensor fusion projects

Embedded systems education
