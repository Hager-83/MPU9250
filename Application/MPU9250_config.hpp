#ifndef _MPU9250_CONFIG_HPP_
#define _MPU9250_CONFIG_HPP_
/**************************** Include ***************************** */
#include <cstdint>
#include <memory>              
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "hardware/gpio.h"
#include "HAL/MPU9250_HAL.hpp"

/**************************** Macros ******************************* */
#define I2C0_SDA_PIN 0
#define I2C0_SCL_PIN 1
#define I2C1_SDA_PIN 2
#define I2C1_SCL_PIN 3
#define BAUD_RATE 400000

/****************************************************************** */
namespace MPU9250_Config
{
    // -------------- I2C Settings ---------------
    constexpr uint32_t Baud_Rate = BAUD_RATE ;
    constexpr uint8_t SDA_PIN = I2C0_SDA_PIN ;
    constexpr uint8_t SCL_PIN = I2C0_SCL_PIN;
    constexpr uint32_t I2C_BAUDRATE = Baud_Rate;

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
        init.baudrate_hz = I2C_BAUDRATE;
        return init;
    }
}
#endif
