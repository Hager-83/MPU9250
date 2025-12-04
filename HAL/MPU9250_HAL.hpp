#ifndef MPU9250_HAL_HPP
#define MPU9250_HAL_HPP

#include "MPU9250_Registers.hpp"
#include <cstdint>
#include "pico/stdlib.h"
#include "hardware/i2c.h"

class MPU9250_HAL 
{
    public:
    MPU9250_HAL(i2c_inst_t* i2c , uint8_t address);

    // initialize with I2C (baudrate in Hz)
    bool begin(uint sda_pin, uint scl_pin, uint32_t baudrate_hz);

    // Basic operations
    bool testConnection(); // reads WHO_AM_I

    bool initMPU9250(); // reset + configure

    bool initAK8963();

    // Read raw sensors (blocking)
    bool readAccelRaw(int16_t &ax, int16_t &ay, int16_t &az);
    bool readGyroRaw(int16_t &gx, int16_t &gy, int16_t &gz);
    bool readTempRaw(int16_t &temp);

    // convenience: read both at once
    bool readAllRaw(int16_t &ax, int16_t &ay, int16_t &az,
                    int16_t &gx, int16_t &gy, int16_t &gz,
                    int16_t &temp);

    bool readMagRaw(int16_t &mx, int16_t &my, int16_t &mz);

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
