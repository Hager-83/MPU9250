
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

bool IMUService::IsConnected() const
{
    if (!hal_) 
    {
        return (false);
    }
    auto conn = (hal_->IsConnected());
    return (conn.has_value() && conn.value());
}
/****************************************************************************************************** */

void IMUService::GetAccelerometer(AccelerationData *Acc_data) 
{

    if (!hal_->ReadAccelRaw(Acc_data))
    {
       Acc_data->ax = 0;
       Acc_data->ay = 0;
       Acc_data->az = 0;
    }
    else
    {
       Acc_data->ax *= accelScale_;
       Acc_data->ay *= accelScale_;
       Acc_data->az *= accelScale_;
    }
}
/****************************************************************************************************** */

void IMUService::GetGyroscope(GyroscopeData *gyro_data)
{

    if (!hal_->ReadGyroRaw(gyro_data))
    {
        gyro_data->gx = 0;
        gyro_data->gy = 0;
        gyro_data->gz = 0;
    }
    else
    {
        gyro_data->gx *= gyroScale_;
        gyro_data->gy *= gyroScale_;
        gyro_data->gz *= gyroScale_;
    };
}
/****************************************************************************************************** */

void IMUService::GetTemperature(TemperatureData*temp_data) 
{
    if (!hal_->ReadTempRaw(temp_data))
    {
        temp_data->temperature_c = 0;
    }
    else
    {
        temp_data->temperature_c *= tempScale_ + 21.0f;
    }
}
/****************************************************************************************************** */

void IMUService::GetMagnetometer(MagnomaterData *meg_data) 
{
    if (!hal_->ReadMagRaw(meg_data))
    {
        meg_data ->mx = 0;
        meg_data ->my = 0;
        meg_data ->mz = 0;
    }
    else
    {
        meg_data ->mx *= magScale_;
        meg_data ->my *= magScale_;
        meg_data ->mz *= magScale_;
    }
}

/****************************************************************************************************** */

void IMUService::GetAll(IMUAllData *all_data) 
{
    if(!hal_->ReadAllRaw(all_data))
    {
        all_data->acc_obj  = {0,0,0};
        all_data->gyro_obj = {0,0,0};
        all_data->temp_obj = {0};
        all_data->meg_data = {0,0,0};
    }

    all_data->acc_obj.ax *= accelScale_;
    all_data->acc_obj.ay *= accelScale_;
    all_data->acc_obj.az *= accelScale_;

    all_data->gyro_obj.gx *= gyroScale_;
    all_data->gyro_obj.gy *= gyroScale_;
    all_data->gyro_obj.gz *= gyroScale_;

    all_data->temp_obj.temperature_c *= tempScale_ + 21.0f;
} 

/****************************************************************************************************** */
bool IMUService::Begin()
{
    auto init_struct = MPU9250_Config::GetInitStruct();
    hal_ = new MPU9250_HAL(&init_struct);
    if (!(hal_->IsConnected().value_or(false)))
    {
        printf("ERROR: MPU9250 not detected! Check wiring.\n");
        return(false);
    }

    //mag_asa_ = hal_.GetMagAdjustment();

    printf("MPU9250 initialized successfully by IMUService!\n");
    return true;
}

/****************************************************************************************************** */
