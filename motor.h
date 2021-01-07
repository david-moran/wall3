#ifndef _MOTOR_H_
#define _MOTOR_H_

#include <stdint.h>
#include <Arduino.h>

namespace wall3
{

template <int PinIn, int PinPWM, int DIR = 1>
class Motor 
{
    int16_t currentSpeed;

public:
    Motor() noexcept;

    void setSpeed(int16_t) noexcept;
    int16_t getSpeed() const noexcept;
};


template <int PinIn, int PinPWM, int DIR>
Motor<PinIn, PinPWM, DIR>::Motor() noexcept {
    pinMode(PinIn, OUTPUT);
    pinMode(PinPWM, OUTPUT);
}

template <int PinIn, int PinPWM, int DIR>
void Motor<PinIn, PinPWM, DIR>::setSpeed(int16_t speed) noexcept {
    speed = speed * DIR;
    if (speed < 0) {
        digitalWrite(PinIn, HIGH);
        analogWrite(PinPWM, -speed);
    } else if (speed > 0) {
        digitalWrite(PinIn, LOW);
        analogWrite(PinPWM, speed);
    } else {
        digitalWrite(PinIn, LOW);
        analogWrite(PinPWM, speed);
    }

    currentSpeed = speed;
}

template <int PinIn, int PinPWM, int DIR>
inline int16_t Motor<PinIn, PinPWM, DIR>::getSpeed() const noexcept {
    return currentSpeed;
}

}

#endif // _MOTOR_H_