#ifndef _ITR200001_H_
#define _ITR200001_H_

#include <Arduino.h>

namespace wall3
{

template <uint8_t Port>
class ITR20001
{
public:
    ITR20001() noexcept;
    float value() const noexcept;
};

template <uint8_t Port>
ITR20001<Port>::ITR20001() noexcept {
    pinMode(Port, INPUT);
}

}

#endif // _ITR200001_H_