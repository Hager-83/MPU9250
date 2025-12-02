#ifndef MPU9250_REGISTERS_HPP
#define MPU9250_REGISTERS_HPP

// MPU9250 register addresses (subset used)
#define MPU6500_DEFAULT_ADDRESS 0x68

#define WHO_AM_I        0x75
#define PWR_MGMT_1      0x6B  //power mangement 
#define SMPLRT_DIV      0x19
#define CONFIG          0x1A
#define GYRO_CONFIG     0x1B
#define ACCEL_CONFIG    0x1C
#define ACCEL_CONFIG2   0x1D
#define INT_PIN_CFG     0x37
#define INT_ENABLE      0x38
#define ACCEL_XOUT_H    0x3B
#define ACCEL_XOUT_L    0x3C
#define ACCEL_YOUT_H    0x3D
#define ACCEL_YOUT_L    0x3E
#define ACCEL_ZOUT_H    0x3F
#define ACCEL_ZOUT_L    0x40
#define TEMP_OUT_H      0x41
#define TEMP_OUT_L      0x42
#define GYRO_XOUT_H     0x43
#define GYRO_XOUT_L     0x44
#define GYRO_YOUT_H     0x45
#define GYRO_YOUT_L     0x46
#define GYRO_ZOUT_H     0x47
#define GYRO_ZOUT_L     0x48
#define USER_CTRL       0x6A
#define I2C_MST_CTRL    0x24
#define I2C_SLV4_ADDR   0x31
#define I2C_SLV4_CTRL   0x34

// Config options
// Gyro full scale
#define GYRO_FS_250  (0x00)
#define GYRO_FS_500  (0x08)
#define GYRO_FS_1000 (0x10)
#define GYRO_FS_2000 (0x18)

// Accel full scale
#define ACCEL_FS_2G  (0x00)
#define ACCEL_FS_4G  (0x08)
#define ACCEL_FS_8G  (0x10)
#define ACCEL_FS_16G (0x18)


// Gyro self test (reg 0 to 2) 
#define SELF_TEST_X_GYRO 0x00                  
#define SELF_TEST_Y_GYRO  0x01                                                                          
#define SELF_TEST_Z_GYRO 0x02

// Accel self test (reg 13 to 15)
#define SELF_TEST_X_ACCEL 0X0D
#define SELF_TEST_Y_ACCEL 0x0E 
#define SELF_TEST_Z_ACCEL 0x0F

#endif // MPU9250_REGISTERS_HPP