#pragma once

#include <cmath>

#include "WwMath.h"


template <typename T>
class Vec2D
{
public:
    T X;
    T Y;

    Vec2D() : X{0}, Y{0} {}
    Vec2D(T x, T y) : X{x}, Y{y} {}
    explicit Vec2D(T n) : X{n}, Y{n} {}

    Vec2D(const Vec2D<T>& other) : X{other.X}, Y{other.Y} {}

    Vec2D<T> operator-() const
    {
        return Vec2D<T>(-X, -Y);
    }

    Vec2D<T>& operator=(const Vec2D<T>& other)
    {
        X = other.X;
        Y = other.Y;
        return *this;
    }

    Vec2D<T> operator+(const Vec2D<T>& other) const
    {
        return Vec2D<T>(X + other.X, Y + other.Y);
    }
    Vec2D<T> operator+(const T v) const
    {
        return Vec2D<T>(X + v, Y + v);
    }
    Vec2D<T>& operator+=(const Vec2D<T>& other)
    {
        X += other.X;
        Y += other.Y;
        return *this;
    }
    Vec2D<T>& operator+=(const T v) const
    {
        X += v;
        Y += v;
        return *this;
    }

    Vec2D<T> operator-(const Vec2D<T>& other) const
    {
        return Vec2D<T>(X - other.X, Y - other.Y);
    }
    Vec2D<T> operator-(const T v) const
    {
        return Vec2D<T>(X - v, Y - v);
    }
    Vec2D<T>& operator-=(const Vec2D<T>& other)
    {
        X -= other.X;
        Y -= other.Y;
        return *this;
    }
    Vec2D<T>& operator-=(const T v) const
    {
        X -= v;
        Y -= v;
        return *this;
    }

    Vec2D<T> operator*(const Vec2D<T>& other) const
    {
        return Vec2D<T>(X * other.X, Y * other.Y);
    }
    Vec2D<T> operator*(const T v) const
    {
        return Vec2D<T>(X * v, Y * v);
    }
    Vec2D<T>& operator*=(const Vec2D<T>& other)
    {
        X *= other.X;
        Y *= other.Y;
        return *this;
    }
    Vec2D<T>& operator*=(const T v) const
    {
        X *= v;
        Y *= v;
        return *this;
    }

    Vec2D<T> operator/(const Vec2D<T>& other) const
    {
        return Vec2D<T>(X / other.X, Y / other.Y);
    }
    Vec2D<T> operator/(const T v) const
    {
        return Vec2D<T>(X / v, Y / v);
    }
    Vec2D<T>& operator/=(const Vec2D<T>& other)
    {
        X /= other.X;
        Y /= other.Y;
        return *this;
    }
    Vec2D<T>& operator/=(const T v) const
    {
        X /= v;
        Y /= v;
        return *this;
    }

    bool operator<(const Vec2D<T>& other) const
    {
        return (X < other.X && !Math::equal(X, other.X)) ||
               (Math::equal(X, other.X) && Y < other.Y && !Math::equal(Y, other.Y));
    }
    bool operator>(const Vec2D<T>& other) const
    {
        return (X > other.X && !Math::equal(X, other.X)) ||
               (Math::equal(X, other.X) && Y > other.Y && !Math::equal(Y, other.Y));
    }
    bool operator<=(const Vec2D<T>& other) const
    {
        return (X < other.X || Math::equal(X, other.X)) ||
               (Math::equal(X, other.X) && !Math::equal(Y, other.Y) && Y < other.Y)
    }
    bool operator>=(const Vec2D<T>&other) const
    {
        return (X>other.X || Math::equal(X, other.X)) ||
               (Math::equal(X, other.X) && (Y>other.Y || Math::equal(Y, other.Y)));
    }
    
    bool operator==(const Vec2D<T>& other) const
    {
        return this->equal(other);
    }
    bool operator!=(const Vec2D<T>& other) const
    {
        return !this->equal(other);
    }

    Vec2D<T>& set(T x, T y)
    {
        X = x;
        Y = y;
        return *this;
    }

    T length() const
    {
        return std::sqrt(X * X + Y * Y);
    }
    T lengthSq() const
    {
        return X * X + Y * Y;
    }

    T dot(const Vec2D<T>& other) const
    {
        return X * other.X + Y * other.Y;
    }

    T distance(const Vec2D<T>& other) const
    {
        return Vec2D<T>(X - other.X, Y - other.Y).length();
    }
    T distanceSq(const Vec2D<T>& other) const
    {
        return Vec2D<T>(X - other.X, Y - other.Y).lengthSq();
    }

    Vec2D& normalize()
    {
        const T len = this->length();
        if(len){
            X /= len;
            Y /= len;
        }
        return *this;
    }

private:
    bool equal(const Vec2D<T>& other) const
    {
        return Math::equal(X, other.X) && Math::equal(Y, other.Y);
    }
};