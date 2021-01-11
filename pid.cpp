#include "pid.h"

#include <Arduino.h>

namespace wall3
{

using ReducedIntegral = Integral;

static ReducedIntegral reduceIntegral(Integral integral[5], uint8_t integralCount);

inline float PID::error(float desired, float current) const noexcept {
    return current - desired;
}

long PID::delta() {
    long currentMillis = millis();
    long delta = currentMillis - lastMillis;
    lastMillis = currentMillis;
    return delta;
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

float PID::calculate(float desired, float current) noexcept {
    const auto error = this->error(desired, current);
    const auto delta = this->delta();
    const auto reducedIntegral = reduceIntegral(integral, integralCount);

    const auto p = Kp * error;
    const auto i = (Ki / reducedIntegral.delta) * reducedIntegral.error * delta;
    const auto d = Kd * ((error - lastError) / delta);

    lastError = error;
    addIntegral(error, delta);

    /*
    Serial.print("current: "); Serial.print(current);
    Serial.print("\tdesired: "); Serial.print(desired);
    Serial.print("\terror: "); Serial.print(error);
    Serial.print("\tdelta: "); Serial.print(delta);
    Serial.print("\tintegral error: "); Serial.print(reducedIntegral.error);
    Serial.print("\tintegral time: "); Serial.print(reducedIntegral.delta);
    Serial.print("\tp: "); Serial.print(p);
    Serial.print("\ti: "); Serial.print(i);
    Serial.print("\td: "); Serial.print(d);
    Serial.print("\toutput: "); Serial.println(p + i + d);
    */

    return p + i + d;
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
