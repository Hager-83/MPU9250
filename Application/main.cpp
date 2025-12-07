#include <cstdio>
#include <iostream>
#include <cstdlib>
#include "pico/stdlib.h"
#include "hardware/i2c.h"

#include "../HAL/MPU9250_HAL.hpp"
#include "../Service/MPU9250_Service.hpp"

#define MPU9250_BAUD_RATE   400000

int main() 
{
    stdio_init_all();

    sleep_ms(200); // wait for USB serial

    std::cout<<"Start Pico W MPU9250 Sensor... \n";

    // Edit common layer to hal, service with configuration file, 
    MPU9250_HAL imu9250_hal(i2c_default, MPU6500_DEFAULT_ADDRESS);
    IMUService imu9250(imu9250_hal);

    //call try in try, catch 
    do
    {
        if(imu9250_hal.begin(PICO_DEFAULT_I2C_SDA_PIN, PICO_DEFAULT_I2C_SCL_PIN, MPU9250_BAUD_RATE))
        {
            std::cout<<"MPU9250 Connected successfully^^\n";
            break;
        } 
        std::cout<<"MPU9250 Connected Failed!\n";
        sleep_ms(500);
    } while (1);

    do
    {
        if(imu9250_hal.initMPU9250())
        {
            std::cout<<"MPU9250 Init successfully^^\n";
            break;
        } 
        std::cout<<"MPU9250 Configuration Failed!\n";
        sleep_ms(500);
    } while (1);

    /*
    do
    {
        if(imu9250_hal.initAK8963())
        {
            std::cout<<"AK8963 Init successfully^^\n";
            break;
        } 
        printf("AK8963 Configuration Failed!\n");
        sleep_ms(500);
    } while (1);
    */

    do
    {
        if(imu9250.begin())
        {
            std::cout<<"MPU9250 begin successfully^^\n";
            break;
        } 
        std::cout<<"MPU9250 begin Failed!\n";
        sleep_ms(500);
    } while (1);

    std::cout<<"Initialization complete.\n\n";

    while (true)
    {

        AccelData acc = imu9250.getAccelerometer();
        GyroData  gyr = imu9250.getGyroscope();
        TempData  tmp = imu9250.getTemperature();
        //MagData   mag = imu.getMagnetometer();


        std::cout<<"Acc(g): "<<acc.x_g<<"   "<<acc.y_g<<"   "<<acc.z_g<<std::endl;
        std::cout<<"GYR(dPS)(g): "<<gyr.x_dps<<"   "<<gyr.y_dps<<"   "<<gyr.z_dps<<std::endl;
        std::cout<<"TEMP(C): "<<tmp.temperature_c<<std::endl;
        sleep_ms(100);
    }

    return 0;
}
