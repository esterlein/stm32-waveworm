#pragma once

#include "Mesh.h"


template<typename T>
class Cube : public Mesh<T, 8>
{
    constexpr static Trianglist<T, 8> GetTriangles(T size)
    {
        constexpr T side = static_cast<T>(size / 2.f);

        return {-side, -side, -side,
                 side, -side, -side,
                -side,  side, -side,
                 side,  side, -side,
                -side, -side,  side,
                 side, -side,  side,
                -side,  side,  side,
                 side,  side,  side};
    }
};