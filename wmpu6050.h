#ifndef _WMPU6050_H_
#define _WMPU6050_H_

#include <TinyMPU6050.h>

namespace wall3
{

using MPU6050_GyronAngFn = float (MPU6050::*)();

template <MPU6050_GyronAngFn F = &MPU6050::GetAngZ>
class WMPU6050 {
    MPU6050 mpu {Wire};

public:
    void setup() noexcept;
    void loop() noexcept;
    float gyro() noexcept;
};

template <MPU6050_GyronAngFn F>
void WMPU6050<F>::setup() noexcept {
    mpu.Initialize();
    mpu.Calibrate();
}

template <MPU6050_GyronAngFn F>
void WMPU6050<F>::loop() noexcept {
    mpu.Execute();
}

template <MPU6050_GyronAngFn F>
float WMPU6050<F>::gyro() noexcept {
    return ((mpu).*(F))();
}

}

#endif // _WMPU6050_H_