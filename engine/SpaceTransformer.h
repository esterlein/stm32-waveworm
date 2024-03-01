#pragma once

#include "Vec4D.h"
#include "Mtx4x4.h"

#include "PerifLCD.h"


template <typename T>
class SpaceTransformer
{
private:
    const T m_xFactor;
    const T m_yFactor;
    const T m_aspectRatio;

public:
    SpaceTransformer()
    : m_xFactor{static_cast<T>(static_cast<float>(LCD::WIDTH) / 2.f)}
    , m_yFactor{static_cast<T>(static_cast<float>(LCD::HEIGHT) / 2.f)}
    , m_aspectRatio{static_cast<T>(static_cast<float>(LCD::HEIGHT) / static_cast<float>(LCD::WIDTH))}
    {}

    ~SpaceTransformer() = default;

    Vec4D<T> ProjectiveTransformation() const
    {
        Mtx4x4<T> projMtx = Mtx4x4<T>::PerspectiveProjection(static_cast<T>(90.f),
                                                             m_aspectRatio,
                                                             static_cast<T>(1.f),
                                                             static_cast<T>(10.f));

        return {};                                         
    }
};