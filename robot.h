#ifndef _ROBOT_H_
#define _ROBOT_H_

#include "drv8835.h"
#include "sr04.h"
#include "itr20001.h"


namespace wall3 {

class Robot {
    DRV8835<8, 5> rightMotor;
    DRV8835<7, 6, -1> leftMotor;

    SR04<> ultrasonicSensor;

    ITR20001<2> leftInfrared;
    ITR20001<1> middleInfrared;
    ITR20001<0> rightInfrared;
public:
    void setSpeed(int16_t, int16_t) noexcept;
    uint16_t ping() const noexcept;
};

}

#endif // _ROBOT_H_