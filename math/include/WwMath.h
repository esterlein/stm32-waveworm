#include "MathDefs.h"

namespace Math
{
    constexpr bool equals(const float a, const float b, const float tolerance = RoundErrFloat)
    {
        return (a + tolerance >= b) && (a - tolerance <= b);
    }
}