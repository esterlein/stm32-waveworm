#pragma once


template <class T>
class Vec2
{
public:
    T X;
    T Y;

    Vec2() : X{0}, Y{0} {}
    Vec2(T x, T y) : X{x}, Y{y} {}
    explicit Vec2(T n) : X{n}, Y{n} {}
};