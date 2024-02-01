#pragma once

#include <Vec3D.h>


template <typename T>
class Triangle
{
public:
    Vec3D<T> A;
    Vec3D<T> B;
    Vec3D<T> C;

    Triangle() = default;
    ~Triangle() = default;

    Triangle(const Vec3D<T>& a, const Vec3D<T>& b, const Vec3D<T>& c)
    : A{a}
    , B{b}
    , C{c}
    {}

    Triangle(const Triangle<T>& other)
    : A{other.A}
    , B{other.B}
    , C{other.C}
    {}

    Triangle(Triangle<T>&& other)
    : A{other.A}
    , B{other.B}
    , C{other.C}
    {
        other.A = {0, 0, 0};
        other.B = {0, 0, 0};
        other.C = {0, 0, 0};
    }

    Triangle<T>& operator=(const Triangle<T>& other)
    {
        A = other.A;
        B = other.B;
        C = other.C;
        return *this;
    }

    Triangle<T>& operator=(Triangle<T>&& other)
    {
        if(this != &other){
            A = other.A;
            B = other.B;
            C = other.C;
            other.A = {0, 0, 0};
            other.B = {0, 0, 0};
            other.C = {0, 0, 0};
        }
        return *this;
    }
};