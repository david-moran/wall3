#include "robot.h"

#include <PID_v1.h>

#include <limits.h>

namespace wall3
{

void Robot::setup() noexcept {
    Serial.println("Initializing robot setup.");
    state.stateID = StateID::STOPPED;

    Serial.println("Initializing servo setup.");
    servo.setup();

    Serial.println("Initializing MPU6050 setup.");
    mpu.setup();

    Serial.println("Setup completed.");
}

void Robot::loop(long delta) noexcept {
    move(delta);
}

void Robot::resetPID() noexcept {
    leftMotorPID.reset();
    rightMotorPID.reset();
}

void Robot::move(long delta) noexcept {
    auto gyro = mpu.gyroZ();
    int16_t leftSpeed = 0;
    int16_t rightSpeed = 0;

    switch (state.stateID)
    {
    case StateID::FORWARD:
        leftSpeed = state.desired.speed +
            leftMotorPID.calculate(state.desired.gyro, gyro, delta);

        rightSpeed = state.desired.speed -
            rightMotorPID.calculate(state.desired.gyro, gyro, delta);
        break;
    case StateID::TURNING:
        if (state.desired.turningRate > 0) {
            leftSpeed = state.desired.speed * state.desired.turningRate;
            leftSpeed = leftSpeed == 0 ? INT16_MAX : leftSpeed;
            rightSpeed = state.desired.speed;

            if (leftSpeed > 255) {
                leftSpeed = 255;
                rightSpeed /= state.desired.turningRate;
            }
        } else if (state.desired.turningRate < 0) {
            auto turningRate = abs(state.desired.turningRate);
            rightSpeed = state.desired.speed * turningRate;
            rightSpeed = rightSpeed == 0 ? INT16_MIN : rightSpeed;
            leftSpeed = state.desired.speed;

            if (rightSpeed < -255) {
                rightSpeed = -255;
                leftSpeed /= turningRate;
            }
        }
    }


    leftMotor.setSpeed(leftSpeed);
    rightMotor.setSpeed(rightSpeed);

}

void Robot::forward(int16_t speed) noexcept {
    state.desired.speed = speed > 255 ? 255 : speed < -255 ? -255 : speed;;
    state.desired.gyro = mpu.gyroZ();
    state.stateID = StateID::FORWARD;

    resetPID();
}

void Robot::turn(int16_t speed, float turningRate) {
    if (turningRate == 1.0) {
        forward(speed);
    } else {
        state.desired.speed = speed > 255 ? 255 : speed < -255 ? -255 : speed;
        state.desired.gyro = mpu.gyroZ();
        state.desired.turningRate = turningRate;
        state.stateID = StateID::TURNING;
    }

    resetPID();
}

void Robot::stop() noexcept {
    state.desired.speed = 0;
    state.desired.gyro = mpu.gyroZ();
    state.stateID = StateID::STOPPED;

    resetPID();
}

}