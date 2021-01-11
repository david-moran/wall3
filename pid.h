#ifndef _PID_H_
#define _PID_H_

#include <stdint.h>

namespace wall3 {

struct Integral {
    float error;
    long delta;
};

class PID {
    const float Kp, Ki, Kd;

    Integral integral[5];
    uint8_t integralCount;

    unsigned long lastMillis;
    float lastError;

    void addIntegral(float error, unsigned long delta) noexcept;

    long delta() noexcept;
    constexpr float error(float desired, float current) const noexcept;

public:
    PID(float Kp = 2.0, float Ki = 5.0, float Kd = 100.0) noexcept;
    float calculate(float desired, float current) noexcept;
};

}

#endif // _PID_H_