#include <cstdio>
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

    printf("Start Pico W MPU9250 Sensor... \n");

    // HAL instance
    MPU9250_HAL imu_hal(i2c_default, MPU6500_DEFAULT_ADDRESS);
    IMUService imu_service(imu_hal);

    do
    {
        if(imu_hal.begin(PICO_DEFAULT_I2C_SDA_PIN, PICO_DEFAULT_I2C_SCL_PIN, MPU9250_BAUD_RATE))
        {
            printf("MPU9250 Connected successfully^^\n");
            break;
        } 
        printf("MPU9250 Connected Failed!\n");
        sleep_ms(500);
    } while (1);

    do
    {
        if(imu_hal.initMPU9250())
        {
            printf("MPU9250 Init successfully^^\n");
            break;
        } 
        printf("MPU9250 Configuration Failed!\n");
        sleep_ms(500);
    } while (1);

    do
    {
        if(imu_hal.initAK8963())
        {
            printf("AK8963 Init successfully^^\n");
            break;
        } 
        printf("AK8963 Configuration Failed!\n");
        sleep_ms(500);
    } while (1);

    do
    {
        if(imu_service.begin())
        {
            printf("MPU9250 begin successfully^^\n");
            break;
        } 
        printf("MPU9250 begin Failed!\n");
        sleep_ms(500);
    } while (1);

    printf("Initialization complete.\n\n");

    while (true)
    {

        AccelData acc = imu_service.getAccelerometer();
        GyroData  gyr = imu_service.getGyroscope();
        TempData  tmp = imu_service.getTemperature();
        //MagData   mag = imu.getMagnetometer();

        printf(
            "ACC(g):    %.3f  %.3f  %.3f | "
            "GYR(dps):  %.2f  %.2f  %.2f | "
            "TEMP(C):   %.2f  "
            //"| MAG(uT): %.2f  %.2f  %.2f\n",
            ,acc.x_g, acc.y_g, acc.z_g,
            gyr.x_dps, gyr.y_dps, gyr.z_dps,
            tmp.temperature_c
            //mag.x_uT, mag.y_uT, mag.z_uT
        );

        sleep_ms(100);
    }

    return 0;
}
