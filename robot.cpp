#include "robot.h"

namespace wall3
{

void Robot::setSpeed(int16_t leftMotorSpeed, int16_t rightMotorSpeed) noexcept {
    rightMotor.setSpeed(leftMotorSpeed);
    leftMotor.setSpeed(rightMotorSpeed);
}

uint16_t Robot::ping() const noexcept {
    return ultrasonicSensor.ping();
}

}