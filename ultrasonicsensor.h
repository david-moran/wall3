#ifndef _ULTRASONIC_H_
#define _ULTRASONIC_H_

#include <Arduino.h>
#include <stdint.h>

namespace wall3
{

template <int PinTrig = 13, int PinEcho = 12>
class UltrasonicSensor
{
public:
    UltrasonicSensor() noexcept;
    uint16_t ping() const noexcept;
};

template <int PinTrig, int PinEcho>
UltrasonicSensor<PinTrig, PinEcho>::UltrasonicSensor() noexcept {
    pinMode(PinEcho, INPUT);
    pinMode(PinTrig, OUTPUT);
}

template <int PinTrig, int PinEcho>
uint16_t UltrasonicSensor<PinTrig, PinEcho>::ping() const noexcept
{
    digitalWrite(PinTrig, LOW);
    delayMicroseconds(2);

    digitalWrite(PinTrig, HIGH);
    delayMicroseconds(10);
    digitalWrite(PinTrig, LOW);

    return pulseIn(PinEcho, HIGH) / 58;
}

}

#endif // _ULTRASONIC_H_