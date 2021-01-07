#ifndef _SR04_H_
#define _SR04_H_

#include <Arduino.h>
#include <stdint.h>

namespace wall3
{

template <int TrigPin = 13, int EchoPin = 12>
class SR04
{
public:
    SR04() noexcept;
    uint16_t ping() const noexcept;
};

template <int TrigPin, int EchoPin>
SR04<TrigPin, EchoPin>::SR04() noexcept {
    pinMode(EchoPin, INPUT);
    pinMode(TrigPin, OUTPUT);
}

template <int TrigPin, int EchoPin>
uint16_t SR04<TrigPin, EchoPin>::ping() const noexcept
{
    digitalWrite(TrigPin, LOW);
    delayMicroseconds(2);

    digitalWrite(TrigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(TrigPin, LOW);

    return pulseIn(EchoPin, HIGH) / 58;
}

}

#endif // _SR04_H_