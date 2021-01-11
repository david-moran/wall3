#ifndef _ROBOT_H_
#define _ROBOT_H_

#include "drv8835.h"
#include "sr04.h"
#include "itr20001.h"
#include "wservo.h"
#include "wmpu6050.h"
#include "pid.h"

namespace wall3 {

struct Robot {
    PID rightMotorPID;
    PID leftMotorPID;

    DRV8835<8, 5> rightMotor;
    DRV8835<7, 6, -1> leftMotor;

    SR04<> ultrasonicSensor;

    ITR20001<2> leftInfrared;
    ITR20001<1> middleInfrared;
    ITR20001<0> rightInfrared;

    WServo<10> servo;

    WMPU6050<> mpu;

public:
    void setup() noexcept;
    void loop() noexcept;

    bool forwardUntilObstacle(uint16_t speed);
};

}

#endif // _ROBOT_H_