#ifndef _WMPU6050_H_
#define _WMPU6050_H_

#include <Wire.h>
namespace wall3
{
class WMPU6050 {
    int gyroOffsetZ;

    void calibrate() noexcept;
    int16_t rawGyroZ() noexcept;
public:
    void setup() noexcept;
    int16_t gyroZ() noexcept;
};

}

#endif // _WMPU6050_H_