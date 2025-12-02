#include <cstdio>
#include <cstdlib>
#include "pico/stdlib.h"
#include "hardware/i2c.h"

#include "../HAL/MPU9250_HAL.hpp"
#include "../Service/MPU9250_Service.hpp"

int main() {
    stdio_init_all();
    sleep_ms(200); // wait for USB serial

    printf("Pico W MPU9250 I2C - Raw Sensor Reading Example\n");

    const uint32_t I2C_BAUD = 400000;

    // HAL instance
    MPU9250_HAL sensor(i2c_default, MPU6500_DEFAULT_ADDRESS);

    if(!sensor.begin(PICO_DEFAULT_I2C_SDA_PIN, PICO_DEFAULT_I2C_SCL_PIN, I2C_BAUD)) {
        printf("sensor begin failed! Check wiring.\n");
        while(1) sleep_ms(500);
    }

    printf("MPU9250 detected. Initializing...\n");

    if(!sensor.initMPU6500()) {
        printf("MPU6500 init failed!\n");
        while(1) sleep_ms(500);
    }

    if(!sensor.initAK8963()) {
        printf("AK8963 (Magnetometer) init failed!\n");
        while(1) sleep_ms(500);
    }

    IMUService imu(sensor);

    if(!imu.begin()) {
        printf("IMUService begin failed!\n");
        while(1) sleep_ms(500);
    }

    printf("Initialization complete.\n\n");

    const uint32_t loop_ms = 100; // 10Hz

    while (true) {

        AccelData acc = imu.getAccelerometer();
        GyroData  gyr = imu.getGyroscope();
        TempData  tmp = imu.getTemperature();
        MagData   mag = imu.getMagnetometer();

        printf(
            "ACC(g): %.3f  %.3f  %.3f | "
            "GYR(dps): %.2f  %.2f  %.2f | "
            "TEMP(C): %.2f | "
            "MAG(uT): %.2f  %.2f  %.2f\n",
            acc.x_g, acc.y_g, acc.z_g,
            gyr.x_dps, gyr.y_dps, gyr.z_dps,
            tmp.temperature_c,
            mag.x_uT, mag.y_uT, mag.z_uT
        );

        sleep_ms(loop_ms);
    }

    return 0;
}
