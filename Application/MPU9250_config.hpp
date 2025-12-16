#ifndef _MPU9250_CONFIG_HPP_
#define _MPU9250_CONFIG_HPP_
/**************************** Include ***************************** */
#include <cstdint>
#include <memory>              
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "hardware/gpio.h"
#include "HAL/MPU9250_HAL.hpp"

/****************************************************************** */
namespace MPU9250_Config
{
    // -------------- I2C Settings ---------------
    constexpr uint8_t SDA_PIN = 4;
    constexpr uint8_t SCL_PIN = 5;
    constexpr uint32_t kBaudRate = 400000;

    // -------------------------- MPU9250 Address -------------------------
    constexpr uint8_t MPU_ADDRESS = MPU6500_DEFAULT_ADDRESS;

    // -------------------- Sampling & Output Rate ------------------
    constexpr uint32_t LOOP_DELAY_MS  = 100;
    constexpr bool SERIAL_PLOTTER     = false;

    // --------------------------- HAL -------------------------------
    inline i2c_inst_t* I2C_INSTANCE = i2c_default;

    inline MPU9250_HAL::MPU9250Initilize GetInitStruct()
    {
        MPU9250_HAL::MPU9250Initilize init;

        init.i2c = std::shared_ptr<i2c_inst_t>(
            I2C_INSTANCE, 
            [](i2c_inst_t*){}   
        );

        init.address     = MPU_ADDRESS;
        init.sda_pin     = SDA_PIN;
        init.scl_pin     = SCL_PIN;
        init.baudrate_hz = kBaudRate;
        return init;
    }
}
#endif
