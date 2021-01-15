#include "pid.h"

#include <Arduino.h>

namespace wall3
{

using ReducedIntegral = Integral;

static ReducedIntegral reduceIntegral(Integral integral[5], uint8_t integralCount);

inline float PID::error(float desired, float current) const noexcept {
    return current - desired;
}

void PID::addIntegral(float error, unsigned long delta) noexcept {
    if (integralCount < 5) {
        integral[integralCount++] = {error, delta};
    } else {
        for (uint8_t i = 1; i < 5; i++) {
            integral[i - 1] = integral[i];
        }

        integral[4] = {error, delta};
    }
}


PID::PID(float Kp, float Ki, float Kd) noexcept
    : Kp{Kp}, Ki{Ki}, Kd{Kd} {

}

float PID::calculate(float desired, float current, long delta) noexcept {
    const auto error = this->error(desired, current);
    const auto reducedIntegral = reduceIntegral(integral, integralCount);

    const auto p = Kp * error;
    const auto i = (Ki / reducedIntegral.delta) * reducedIntegral.error * delta;
    const auto d = Kd * ((error - lastError) / delta);

    lastError = error;
    addIntegral(error, delta);

    return p + i + d;
}

void PID::reset() noexcept {
    integralCount = 0;
    lastError = 0;
}

static ReducedIntegral reduceIntegral(Integral integral[5], uint8_t count) {
    ReducedIntegral reducedIntegral = {0, 0};

    for (uint8_t i = 0; i < count; i++) {
        reducedIntegral.delta += integral[i].delta;
        reducedIntegral.error += integral[i].error;
    }
        
    return reducedIntegral;
}

}
