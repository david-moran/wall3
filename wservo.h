#ifndef _WSERVO_H_
#define _WSERVO_H_

#include <Servo.h>

namespace wall3
{

template <int Pin>
class WServo {
    Servo servo;

public:
    void setup() noexcept;
    void rotate(int angle) noexcept;

};

template <int Pin>
void WServo<Pin>::setup() noexcept {
    servo.attach(Pin);
}

template <int Pin>
void WServo<Pin>::rotate(int angle) noexcept {
    servo.write(angle);
}

}

#endif // _WSERVO_H_