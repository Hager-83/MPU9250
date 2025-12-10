/************************************************** Include Part ********************************************* */
#include "MPU9250_HAL.hpp"
#include <cstring>
#include <stdexcept>

using namespace std;

/*********************************************** Class Defenition ******************************************** */
MPU9250_HAL::MPU9250_HAL(MPU9250Initilize *init)
{
    init_ = *init;
    this->Begin();
    this->InitMPU9250();
    this->InitAK8963();
}

/************************************************************************************************************** */
std::optional<bool> MPU9250_HAL::IsConnected()
{
    uint8_t who;

    if(!(init_.i2c))
    {
        return (std::nullopt);
    }

    auto res = ReadBytes(WHO_AM_I,&who,1);
    if((!res.has_value()) || (!res.value()))
    {
        return (std::nullopt);
    }

    /* WHO_AM_I for MPU6500 typically 0x70 or 0x71 or 0x73 etc depending on part; accept non-zero */
    if((who != 70) && (who != 71) && (who != 73)) 
    {
        return (std::nullopt);
    }
    
    return (true);     
}

/************************************************************************************************************ */
std::optional<bool> MPU9250_HAL::ReadAccelRaw(AccelerationData * acc_data) 
{
    uint8_t buf[6];
    if(!ReadBytes(ACCEL_XOUT_H, buf, 6)) 
    {
        return (std::nullopt);
    }

    acc_data-> ax = ((buf[0] << 8) | buf[1]);
    acc_data-> ay = ((buf[2] << 8) | buf[3]);
    acc_data-> az = ((buf[4] << 8) | buf[5]);

    return (true);
}

/************************************************************************************************************ */
std::optional<bool> MPU9250_HAL::ReadGyroRaw(GyroscopeData*gyro_data) 
{
    uint8_t buf[6];
    if(!ReadBytes(GYRO_XOUT_H, buf, 6)) 
    {
        return (std::nullopt);
    }

    gyro_data->gx = ((buf[0] << 8) | buf[1]);
    gyro_data->gy = ((buf[2] << 8) | buf[3]);
    gyro_data->gz = ((buf[4] << 8) | buf[5]);

    return (true);
}

/************************************************************************************************************ */
std::optional<bool> MPU9250_HAL::ReadTempRaw(TemperatureData *temp_data) 
{
    uint8_t buf[2];

    if (!ReadBytes(TEMP_OUT_H, buf, 2))
    {
        return (std::nullopt);
    }
    temp_data->temperature_c = ((buf[0] << 8) | buf[1]);

    return (true);
}

/*********************************************************************************************************** */
std::optional<bool> MPU9250_HAL::ReadMagRaw(MagnomaterData *meg_data) 
{
    uint8_t buf[7];

    if(!ReadBytesAK8963(AK8963_XOUT_L, buf, 7))
    {
        return std::nullopt;
    }

    if (buf[6] & 0x08)
    {
        return std::nullopt;
    }

    meg_data->mx = (int16_t)((buf[1] << 8) | buf[0]);
    meg_data->my = (int16_t)((buf[3] << 8) | buf[2]);
    meg_data->mz = (int16_t)((buf[5] << 8) | buf[4]);

    return true;
}

/************************************************************************************************************ */
std::optional<bool> MPU9250_HAL::ReadAllRaw(IMUAllData *all_data)
{
    bool flag = true;

    auto acc  = ReadAccelRaw(&(all_data->acc_obj));
    auto gyro = ReadGyroRaw(&(all_data->gyro_obj));
    auto temp = ReadTempRaw(&(all_data->temp_obj));
    auto mag  = ReadMagRaw(&(all_data->meg_data));

    flag &= (acc.has_value() && acc.value());
    flag &= (gyro.has_value() && gyro.value());
    flag &= (temp.has_value() && temp.value());
    flag &= (mag.has_value() && mag.value());

    if(!flag)
    {
        return (std::nullopt);
    }
        
    return (true);
}

/************************************************************************************************************** */
std::optional<bool> MPU9250_HAL::Begin()
{
    i2c_init(init_.i2c.get(), init_.baudrate_hz);
    
    gpio_set_function(init_.sda_pin, GPIO_FUNC_I2C);
    gpio_set_function(init_.scl_pin, GPIO_FUNC_I2C);

    gpio_pull_up(init_.sda_pin);
    gpio_pull_up(init_.scl_pin);

    sleep_ms(10);

    return(IsConnected());
}

/************************************************************************************************************** */
std::optional<bool> MPU9250_HAL::InitMPU9250()
{
    if(!(init_.i2c))
    {
        return(std::nullopt); 
    }

    /* Reset device : write 1 on bit 7 */
    if(!WriteByte(PWR_MGMT_1, 0x80)) 
    {
        return(std::nullopt); 
    }
    sleep_ms(100);

    /* Wake up and set clock source to PLL with X axis gyroscope reference: write 1 on bit 0 */
    if(!WriteByte(PWR_MGMT_1, 0x01))
    {
       return(std::nullopt); 
    }
    sleep_ms(50);

    /* Set gyro full scale ±250 dps */
    if(!WriteByte(0x1B, GYRO_FS_250))
    {
        return(std::nullopt); 
    }
    sleep_ms(50);

    if(!WriteByte(0x1C, ACCEL_FS_2G))
    {
        return(std::nullopt); 
    }
    sleep_ms(50);

    /* CONFIG: disable FSYNC, set DLPF (0) , enable LPS */
    if(!WriteByte(CONFIG, 0x03)) 
    {
        return(std::nullopt); 
    }
    
    /* Set sample rate divider (SMPLRT_DIV) */
    if(!WriteByte(SMPLRT_DIV, 0x04))
    {
        return(std::nullopt); 
    } 

    /* ACCEL_CONFIG2: set DLPF for accel */
    if(!WriteByte(ACCEL_CONFIG2, 0x03))
    {
       return(std::nullopt); 
    }

   return(true);
}

/************************************************************************************************************ */
std::optional<bool> MPU9250_HAL::InitAK8963()
{
    if (!WriteByte(INT_PIN_CFG, 0x02)) 
    {
        return (std::nullopt);
    }

    if (!WriteByteAK8963(0x0A, 0x00))
    {
        return (std::nullopt);
    }
    sleep_ms(10);

    if (!WriteByteAK8963(0x0A, 0x0F))
    {
        return (std::nullopt);
    }
    sleep_ms(10);

    uint8_t asa_buf[3];
    auto res = ReadBytesAK8963(0x10, asa_buf, 3);  // ASAX, ASAY, ASAZ
    if (!res.has_value() || !res.value())
    {
        return (std::nullopt);
    }

    // Calculate adjustment factors: (ASA + 128) / 256.0
    mag_asa_.asa_x = (asa_buf[0] + 128) / 256.0f;
    mag_asa_.asa_y = (asa_buf[1] + 128) / 256.0f;
    mag_asa_.asa_z = (asa_buf[2] + 128) / 256.0f;

    if (!WriteByteAK8963(0x0A, 0x00))
    {
        return (std::nullopt);
    }
    sleep_ms(10);

    if (!WriteByteAK8963(0x0A, 0x16))
    {
        return (std::nullopt);
    }
    sleep_ms(10);

    return (true);
}

/************************************************************************************************************ */
std::optional<bool> MPU9250_HAL::WriteByte(uint8_t reg, uint8_t value) 
{
    uint8_t buf[2] = {reg, value};
    int ret = i2c_write_blocking(init_.i2c.get(),init_.address, buf, 2, false); // send with stop
    if(ret != 2)
    {
        return (std::nullopt);
    }
    
    return (true);
}

/************************************************************************************************************ */
std::optional<bool> MPU9250_HAL::ReadBytes(uint8_t reg, uint8_t* buffer, size_t len)
{
    int ret = i2c_write_blocking(init_.i2c.get(),init_.address, &reg, 1, true); 
    if(ret != 1)
    {
        return (std::nullopt);
    }
    int r = i2c_read_blocking(init_.i2c.get(),init_.address, buffer, len, false);
    if (ret != (int)len)
    {
        return (std::nullopt);
    }

    return (true);
}

/************************************************************************************************************ */
std::optional<bool>  MPU9250_HAL::ReadBytesAK8963(uint8_t reg, uint8_t* buf, size_t len)
{
    int ret = i2c_write_blocking(init_.i2c.get(), AK8963_DEFAULT_ADDRESS, &reg, 1, true);
    if (ret != 1)
    {
        return (std::nullopt);
    }

    ret = i2c_read_blocking(init_.i2c.get(), AK8963_DEFAULT_ADDRESS, buf, len, false);
    if (ret != (int)len)
    {
        return (std::nullopt);
    }

    return (true);
}

/************************************************************************************************************ */
std::optional<bool> MPU9250_HAL::WriteByteAK8963(uint8_t reg, uint8_t value)
{
    uint8_t buf[2] = {reg, value};

    int ret = i2c_write_blocking(init_.i2c.get(), AK8963_DEFAULT_ADDRESS, buf, 2, false);
    if (ret != 2) 
    {
        return std::nullopt;
    }
    return true;
}
/********************************************************************************************************* */
