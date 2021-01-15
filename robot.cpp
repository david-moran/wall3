#include "robot.h"

#include <PID_v1.h>

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
    mpu.loop();
    move(delta);
}

void Robot::resetPID() noexcept {
    leftMotorPID.reset();
    rightMotorPID.reset();
}

void Robot::move(long delta) noexcept {
    auto gyro = mpu.gyro();
    auto leftSpeed = 0;
    auto rightSpeed = 0;

    switch (state.stateID)
    {
    case StateID::FORWARD:
        leftSpeed = state.desired.speed +
            leftMotorPID.calculate(state.desired.gyro, gyro, delta);

        rightSpeed = state.desired.speed -
            rightMotorPID.calculate(state.desired.gyro, gyro, delta);
        break;
    }

    leftMotor.setSpeed(leftSpeed);
    rightMotor.setSpeed(rightSpeed);

}

void Robot::forward(int16_t speed) noexcept {
    state.desired.speed = speed;
    state.desired.gyro = mpu.gyro();
    state.stateID = StateID::FORWARD;

    resetPID();
}

void Robot::turn(int16_t speed, float turningRate) {
    if (turningRate == 0.0) {
        forward(speed);
    } else {
        state.desired.speed = speed;
        state.desired.gyro = mpu.gyro();
        state.desired.turningRate = turningRate;
        state.stateID = StateID::TURNING;
    }

    resetPID();
}

void Robot::stop() noexcept {
    state.desired.speed = 0;
    state.desired.gyro = mpu.gyro();
    state.stateID = StateID::STOPPED;

    resetPID();
}

}