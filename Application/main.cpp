/************************************* Include Prt ********************************* */
#include <stdio.h>
#include "pico/stdlib.h"
#include "Service/MPU9250_Service.hpp"
/*********************************************************************************** */
int main()
{
    stdio_init_all();
    sleep_ms(2000);

    IMUService imu;
    printf("Starting IMU readings...\n\n");

    while (true)
    {
        auto imu_data_opt = imu.GetAll();
        if (!imu_data_opt)
        {
            printf("Failed to read IMU data\n");
            sleep_ms(500);
            continue;
        }

        auto& imu_data = imu_data_opt.value();

        printf("A:%.3f,%.3f,%.3f\n"
               "G:%.1f,%.1f,%.1f\n"
               "T:%.1f°C\n"
               "M:%.0f,%.0f,%.0f\n\n",
               imu_data.acc_obj->ax, imu_data.acc_obj->ay, imu_data.acc_obj->az,
               imu_data.gyro_obj->gx, imu_data.gyro_obj->gy, imu_data.gyro_obj->gz,
               imu_data.temp_obj->temperature_c,
               imu_data.meg_data->mx, imu_data.meg_data->my, imu_data.meg_data->mz);

        sleep_ms(MPU9250_Config::LOOP_DELAY_MS);
    }
}

/**************************************************************************************************** */
