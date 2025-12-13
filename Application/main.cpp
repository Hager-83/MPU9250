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

    IMUAllData data;

    while (true)
    {
        imu.GetAll(&data);

        printf("A:%.3f,%.3f,%.3f \n G:%.1f,%.1f,%.1f \n T:%.1f°C \n M:%.0f,%.0f,%.0f\n",
               data.acc_obj.ax, data.acc_obj.ay, data.acc_obj.az,
               data.gyro_obj.gx, data.gyro_obj.gy, data.gyro_obj.gz,
               data.temp_obj.temperature_c,
               data.meg_data.mx, data.meg_data.my, data.meg_data.mz);

        sleep_ms(MPU9250_Config::LOOP_DELAY_MS);
    }
}
/**************************************************************************************************** */
