#pragma once

#include <cmath>
#include <limits>

#include "MathDefs.h"


namespace Math
{
    template<typename T>
    constexpr bool equal(T a, T b)
    { 
        return std::abs(a - b) <= std::numeric_limits<T>::epsilon() * std::max(std::abs(a), std::abs(b));
    }

    enum class Angle
    {
        Deg,
        Rad
    };
}