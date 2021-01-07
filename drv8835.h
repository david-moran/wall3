#ifndef _DRV8835_H_
#define _DRV8835_H_

#include <stdint.h>
#include <Arduino.h>

namespace wall3
{

template <int PinIn, int PinPWM, int DIR = 1>
class DRV8835 {
    int16_t currentSpeed;

public:
    DRV8835() noexcept;

    void setSpeed(int16_t) noexcept;
    int16_t getSpeed() const noexcept;
};


template <int PinIn, int PinPWM, int DIR>
DRV8835<PinIn, PinPWM, DIR>::DRV8835() noexcept {
    pinMode(PinIn, OUTPUT);
    pinMode(PinPWM, OUTPUT);
}

template <int PinIn, int PinPWM, int DIR>
void DRV8835<PinIn, PinPWM, DIR>::setSpeed(int16_t speed) noexcept {
    speed = speed * DIR;
    if (speed < 0) {
        digitalWrite(PinIn, HIGH);
        analogWrite(PinPWM, -speed);
    } else if (speed > 0) {
        digitalWrite(PinIn, LOW);
        analogWrite(PinPWM, speed);
    } else {
        digitalWrite(PinIn, LOW);
        analogWrite(PinPWM, 0);
    }

    currentSpeed = speed;
}

template <int PinIn, int PinPWM, int DIR>
inline int16_t DRV8835<PinIn, PinPWM, DIR>::getSpeed() const noexcept {
    return currentSpeed;
}

}

#endif // _DRV8835_H_