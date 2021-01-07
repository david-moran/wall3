#ifndef _DRV8835_H_
#define _DRV8835_H_

#include <stdint.h>
#include <Arduino.h>

namespace wall3
{

template <uint8_t InputPin, uint8_t PWMPin, int8_t DIR = 1>
class DRV8835 {
    int16_t currentSpeed;

public:
    DRV8835() noexcept;

    void setSpeed(int16_t) noexcept;
    int16_t getSpeed() const noexcept;
};


template <uint8_t InputPin, uint8_t PWMPin, int8_t DIR>
DRV8835<InputPin, PWMPin, DIR>::DRV8835() noexcept {
    pinMode(InputPin, OUTPUT);
    pinMode(PWMPin, OUTPUT);
}

template <uint8_t InputPin, uint8_t PWMPin, int8_t DIR>
void DRV8835<InputPin, PWMPin, DIR>::setSpeed(int16_t speed) noexcept {
    speed = speed * DIR;
    if (speed < 0) {
        digitalWrite(InputPin, HIGH);
        analogWrite(PWMPin, -speed);
    } else if (speed > 0) {
        digitalWrite(InputPin, LOW);
        analogWrite(PWMPin, speed);
    } else {
        digitalWrite(InputPin, LOW);
        analogWrite(PWMPin, 0);
    }

    currentSpeed = speed;
}

template <uint8_t InputPin, uint8_t PWMPin, int8_t DIR>
inline int16_t DRV8835<InputPin, PWMPin, DIR>::getSpeed() const noexcept {
    return currentSpeed;
}

}

#endif // _DRV8835_H_