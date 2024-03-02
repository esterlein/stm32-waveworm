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

    Vec4D<T> PerspectiveTransform(const Vec4D<T>& vertex) const
    {
        constexpr static Mtx4x4<T> mtxProj = Mtx4x4<T>::PerspectiveProjection(
                                                        static_cast<T>(90.f),
                                                        m_aspectRatio,
                                                        static_cast<T>(1.f),
                                                        static_cast<T>(10.f));
        
        Vec4D<T> vtxTrans = mtxProj * vertex;

        if(!vtxTrans.W)
            return vtxTrans;

        const float inverseW = 1.f / static_cast<float>(vtxTrans.W);

        vtxTrans.X *= inverseW;
        vtxTrans.Y *= inverseW;
        vtxTrans.Z *= inverseW;

        return vtxTrans;
    }
};