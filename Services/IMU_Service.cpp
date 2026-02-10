
/******************************************** Include Part ********************************************* */
#include "MPU9250_Service.hpp"
#include <cmath>
#include <stdio.h>
#include <optional>
#include "pico/stdlib.h"

/****************************************** Function Definition *************************************** */

IMUService::IMUService() 
:hal_(nullptr),
  //Physical_Value = Raw_Value × Scale_Factor
  accelScale_(1.0f / 16384.0f),   
  gyroScale_(1.0f / 131.0f),      
  tempScale_(1.0f / 333.87f),     
  magScale_(0.15f)
{
    if (!(this->Begin())) 
    {
        while (true) 
        {
            tight_loop_contents(); 
        }  
    }
}         
/****************************************************************************************************** */

IMUService::~IMUService()
{
        if (hal_) delete hal_; 
}
/****************************************************************************************************** */

std::optional<bool> IMUService::IsConnected() const
{
    auto conn = (hal_->IsConnected());
    if (!conn.has_value()) 
    {
        return (std::nullopt);
    }
    else
    {
        return (conn.value());
    }
}
/****************************************************************************************************** */

std::optional<AccelerationData> IMUService::GetAccelerometer(void) 
{
    auto Acc_data = hal_->ReadAccelRaw();
    if (!Acc_data.has_value())
    {
       return(std::nullopt);
    }
    else
    {
        Acc_data->ax *= accelScale_;
        Acc_data->ay *= accelScale_;
        Acc_data->az *= accelScale_;
        return(Acc_data);
    }
    
}
/****************************************************************************************************** */

std::optional<GyroscopeData>  IMUService::GetGyroscope(void)
{
    auto gyro_data = hal_->ReadGyroRaw();
    if (!gyro_data.has_value())
    {
         return(std::nullopt);
    }
    else
    {
        gyro_data->gx *= gyroScale_;
        gyro_data->gy *= gyroScale_;
        gyro_data->gz *= gyroScale_;
        return(gyro_data);
    };
}
/****************************************************************************************************** */

std::optional<TemperatureData> IMUService::GetTemperature(void) 
{
    auto temp_data = hal_->ReadTempRaw();
    if (!temp_data.has_value())
    {
        return(std::nullopt);
    }
    else
    {
        temp_data->temperature_c = (temp_data->temperature_c * tempScale_) + 21.0f;
        return(temp_data);
    }
}
/****************************************************************************************************** */

std::optional<MagnomaterData> IMUService::GetMagnetometer(void) 
{
    auto meg_data = hal_->ReadMagRaw();
    if (!meg_data.has_value())
    {
        return(std::nullopt);
    }
    else
    {
        meg_data ->mx *= magScale_;
        meg_data ->my *= magScale_;
        meg_data ->mz *= magScale_;
        return(meg_data);
    }
}

/****************************************************************************************************** */

std::optional<IMUAllData> IMUService::GetAll(void) 
{
    auto all_data = hal_->ReadAllRaw();
    if(!all_data.has_value())
    {
       return(std::nullopt);
    }

    all_data->acc_obj->ax *= accelScale_;
    all_data->acc_obj->ay *= accelScale_;
    all_data->acc_obj->az *= accelScale_;

    all_data->gyro_obj->gx *= gyroScale_;
    all_data->gyro_obj->gy *= gyroScale_;
    all_data->gyro_obj->gz *= gyroScale_;

    all_data->meg_data->mx *= magScale_;
    all_data->meg_data->my *= magScale_;
    all_data->meg_data->mz *= magScale_;

    all_data->temp_obj->temperature_c = (all_data->temp_obj->temperature_c * tempScale_) + 21.0f;
    //all_data->temp_obj->temperature_c *= tempScale_ + 21.0f;
    return(all_data);
} 

/****************************************************************************************************** */
std::optional<bool> IMUService::Begin()
{
    auto init_struct = MPU9250_Config::GetInitStruct();
    hal_ = new MPU9250_HAL(&init_struct);
    if (!(hal_->IsConnected().value_or(false)))
    {
        printf("ERROR: MPU9250 not detected! Check wiring.\n");
        return(std::nullopt);
    }

    printf("MPU9250 initialized successfully by IMUService!\n");
    return true;
}

/****************************************************************************************************** */
