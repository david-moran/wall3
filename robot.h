#ifndef _ROBOT_H_
#define _ROBOT_H_

#include "motor.h"
#include "ultrasonicsensor.h"


namespace wall3 {

class Robot {
    Motor<8, 5> rightMotor;
    Motor<7, 6, -1> leftMotor;

    UltrasonicSensor<> ultrasonicSensor;

public:
    void setSpeed(int16_t, int16_t) noexcept;
    uint16_t ping() const noexcept;
};

}

#endif // _ROBOT_H_