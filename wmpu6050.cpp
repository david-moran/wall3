#include "wmpu6050.h"

#include <Arduino.h>
#include <Wire.h>

#define MPU6050_ADRESS      0b1101000
#define POWER_MGMT_1_ADDR   0x6b
#define GYRO_Z_REG          0x47

namespace wall3 {

void WMPU6050::calibrate() noexcept {
    gyroOffsetZ = 0;
    for (int i = 0; i < 100; i++) {
        gyroOffsetZ += rawGyroZ();
        delay(10);
    }

    gyroOffsetZ /= 100;
}

void WMPU6050::setup() noexcept {
    Wire.begin();

    // Enable power on MPU6050
    Wire.beginTransmission(MPU6050_ADRESS);
    Wire.write(POWER_MGMT_1_ADDR);
    Wire.write(0); 
    Wire.endTransmission(true);

    calibrate();
}

int16_t WMPU6050::rawGyroZ() noexcept {
    uint8_t b1, b2;

    Wire.beginTransmission(MPU6050_ADRESS);
    Wire.write(GYRO_Z_REG);
    Wire.endTransmission(false);

    Wire.requestFrom(MPU6050_ADRESS, 2, true);
    b1 = Wire.read();
    b2 = Wire.read();

    // Sensor data is in C2 format
    return (~((b1 << 8) | b2)) + 1;
}

int16_t WMPU6050::gyroZ() noexcept {
    return rawGyroZ() - gyroOffsetZ;
}

}