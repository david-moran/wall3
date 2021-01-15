#ifndef _ROBOT_H_
#define _ROBOT_H_

#include "drv8835.h"
#include "sr04.h"
#include "itr20001.h"
#include "wservo.h"
#include "wmpu6050.h"
#include "pid.h"

namespace wall3 {


enum class StateID {
    STOPPED,
    FORWARD,
    TURNING
};

struct State {
    StateID stateID;

    struct Desired {
        int16_t speed;
        float gyro;
        float turningRate;
    } desired;
};

struct Robot {
    // Sensors
    SR04<> ultrasonicSensor;

    ITR20001<2> leftInfrared;
    ITR20001<1> middleInfrared;
    ITR20001<0> rightInfrared;

    WMPU6050<> mpu;

    // Motors
    WServo<10> servo;
    DRV8835<8, 5> rightMotor;
    DRV8835<7, 6, -1> leftMotor;

    // Controllers
    PID rightMotorPID;
    PID leftMotorPID;

    State state;
    
    void resetPID() noexcept;
    void move(long delta) noexcept;

public:
    void setup() noexcept;
    void loop(long delta) noexcept;

    void forward(int16_t speed) noexcept;
    void turn(int16_t speed, float turnRate) noexcept;
    void stop() noexcept;
};

}

#endif // _ROBOT_H_