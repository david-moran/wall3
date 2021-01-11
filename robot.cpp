#include "robot.h"

#include <PID_v1.h>

namespace wall3
{

void Robot::setup() noexcept {
    Serial.println("Initializing servo setup.");
    servo.setup();
    Serial.println("Initializing MPU6050 setup.");
    mpu.setup();
    Serial.println("Setup completed.");
}

void Robot::loop() noexcept {
    mpu.loop();
}

bool Robot::forwardUntilObstacle(uint16_t speed) {
    auto gyro = mpu.gyro();
    // Serial.print("[LEFT] ");
    const auto correctedLeftSpeed = leftMotorPID.calculate(0.0, gyro);

    // Serial.print("[RIGHT] ");
    const auto correctedRightSpeed = -rightMotorPID.calculate(0.0, gyro);

    leftMotor.setSpeed(speed + correctedLeftSpeed);
    rightMotor.setSpeed(speed + correctedRightSpeed);

    return false;
}

}