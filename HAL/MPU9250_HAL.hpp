#ifndef MPU9250_HAL_HPP
#define MPU9250_HAL_HPP

#include "MPU9250_Registers.hpp"
#include <cstdint>
#include "pico/stdlib.h"
#include "hardware/i2c.h"

class MPU9250_HAL {
public:
    MPU9250_HAL(i2c_inst_t* i2c = i2c0, uint8_t address = MPU6500_DEFAULT_ADDRESS);

    // initialize with I2C (baudrate in Hz)
    bool begin(uint sda_pin, uint scl_pin, uint32_t baudrate_hz = 400000);

    // Basic operations
    bool testConnection(); // reads WHO_AM_I
    bool initMPU6500(); // reset + configure

    // Read raw sensors (blocking)
    bool readAccelRaw(int16_t &ax, int16_t &ay, int16_t &az);
    bool readGyroRaw(int16_t &gx, int16_t &gy, int16_t &gz);

    // convenience: read both at once
    bool readAllRaw(int16_t &ax, int16_t &ay, int16_t &az,
                    int16_t &gx, int16_t &gy, int16_t &gz);

private:
    i2c_inst_t* i2c_;
    uint8_t address_;
    bool i2c_configured_;

    // helpers
    bool writeByte(uint8_t reg, uint8_t value);
    bool readBytes(uint8_t reg, uint8_t* buffer, size_t len);
    uint8_t readByte(uint8_t reg);
};

#endif // MPU9250_HAL_HPP