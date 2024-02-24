#pragma once

#include <cmath>
#include <cassert>

#include "WwMath.h"


template <typename T>
class Vec4D
{
private:
    static constexpr int s_size = 4;

public:
    T X;
    T Y;
    T Z;
    T W;

    Vec4D() : X{0}, Y{0}, Z{0}, W{0} {}
    Vec4D(T x, T y, T z) : X{x}, Y{y}, Z{z}, W{1} {}
    Vec4D(T x, T y, T z, T w) : X{x}, Y{y}, Z{z}, W{w} {}
    explicit Vec4D(T n) : X{n}, Y{n}, Z{n}, W{n} {}

    ~Vec4D() = default;

    Vec4D(const Vec4D<T>& other) : X{other.X}, Y{other.Y}, Z{other.Z}, W{other.W} {}

    Vec4D(Vec4D<T>&& other) = default;

    T& operator[](int index)
    {
        assert(index >= 0 && index < s_size);

        T& component;
        switch(index) {
            case 0: component = X; break;
            case 1: component = Y; break;
            case 2: component = Z; break;
            case 3: component = W; break;
        }
        return component;
    }

    const T& operator[](int index) const
    {
        assert(index >= 0 && index < s_size);

        T& component;
        switch(index) {
            case 0: component = X; break;
            case 1: component = Y; break;
            case 2: component = Z; break;
            case 3: component = W; break;
        }
        return component;
    }

    Vec4D<T>& operator=(const Vec4D<T>& other)
    {
        X = other.X;
        Y = other.Y;
        Z = other.Z;
        W = other.W;
        return *this;
    }

    Vec4D<T>& operator=(Vec4D<T>&& other) = default;

    Vec4D<T> operator-() const
    {
        return Vec4D<T>(-X, -Y, -Z, -W);
    }

    Vec4D<T> operator+(const Vec4D<T>& other) const
    {
        return Vec4D<T>(X + other.X, Y + other.Y, Z + other.Z, W + other.W);
    }

    Vec4D<T> operator+(const T v) const
    {
        return Vec4D<T>(X + v, Y + v, Z + v, W + v);
    }

    Vec4D<T>& operator+=(const Vec4D<T>& other)
    {
        X += other.X;
        Y += other.Y;
        Z += other.Z;
        W += other.W;
        return *this;
    }

    Vec4D<T>& operator+=(const T v) const
    {
        X += v;
        Y += v;
        Z += v;
        W += v;
        return *this;
    }

    Vec4D<T> operator-(const Vec4D<T>& other) const
    {
        return Vec4D<T>(X - other.X, Y - other.Y, Z - other.Z, W - other.W);
    }

    Vec4D<T> operator-(const T v) const
    {
        return Vec4D<T>(X - v, Y - v, Z - v, W - v);
    }

    Vec4D<T>& operator-=(const Vec4D<T>& other)
    {
        X -= other.X;
        Y -= other.Y;
        Z -= other.Z;
        W -= other.W;
        return *this;
    }

    Vec4D<T>& operator-=(const T v) const
    {
        X -= v;
        Y -= v;
        Z -= v;
        W -= v;
        return *this;
    }

    Vec4D<T> operator*(const Vec4D<T>& other) const
    {
        return Vec4D<T>(X * other.X, Y * other.Y, Z * other.Z, W * other.W);
    }

    Vec4D<T> operator*(const T v) const
    {
        return Vec4D<T>(X * v, Y * v, Z * v, W * v);
    }

    Vec4D<T>& operator*=(const Vec4D<T>& other)
    {
        X *= other.X;
        Y *= other.Y;
        Z *= other.Z;
        W *= other.W;
        return *this;
    }

    Vec4D<T>& operator*=(const T v) const
    {
        X *= v;
        Y *= v;
        Z *= v;
        W *= v;
        return *this;
    }

    Vec4D<T> operator/(const Vec4D<T>& other) const
    {
        return Vec4D<T>(X / other.X, Y / other.Y, Z / other.Z, W / other.W);
    }

    Vec4D<T> operator/(const T v) const
    {
        return Vec4D<T>(X / v, Y / v, Z / v, W / v);
    }

    Vec4D<T>& operator/=(const Vec4D<T>& other)
    {
        X /= other.X;
        Y /= other.Y;
        Z /= other.Z;
        W /= other.W;
        return *this;
    }

    Vec4D<T>& operator/=(const T v) const
    {
        X /= v;
        Y /= v;
        Z /= v;
        W /= v;
        return *this;
    }

    bool operator==(const Vec4D<T>& other) const
    {
        return this->equal(other);
    }

    bool operator!=(const Vec4D<T>& other) const
    {
        return !this->equal(other);
    }

    bool operator<(const Vec4D<T>& other) const
    {
        return (X < other.X && !Math::equal(X, other.X)) ||
               (Y < other.Y && !Math::equal(Y, other.Y) && Math::equal(X, other.X)) ||
               (Z < other.Z && !Math::equal(Z, other.Z) &&
               Math::equal(X, other.X) && Math::equal(Y, other.Y)) ||
               (W < other.W && !Math::equal(W, other.W) &&
               Math::equal(X, other.X) && Math::equal(Y, other.Y) && Math::equal(Z, other.Z));
    }

    bool operator>(const Vec4D<T>& other) const
    {
        return (X > other.X && !Math::equal(X, other.X)) ||
               (Y > other.Y && !Math::equal(Y, other.Y) && Math::equal(X, other.X)) ||
               (Z > other.Z && !Math::equal(Z, other.Z) &&
               Math::equal(X, other.X) && Math::equal(Y, other.Y)) ||
               (W > other.W && !Math::equal(W, other.W) &&
               Math::equal(X, other.X) && Math::equal(Y, other.Y) && Math::equal(Z, other.Z));
    }

    bool operator<=(const Vec4D<T>&other) const
    {
        return (X < other.X || Math::equal(X, other.X)) ||
              ((Y < other.Y || Math::equal(Y, other.Y)) && Math::equal(X, other.X)) ||
              ((Z < other.Z || Math::equal(Z, other.Z)) &&
              Math::equal(X, other.X) && Math::equal(Y, other.Y)) ||
              ((W < other.W || Math::equal(W, other.W)) &&
              Math::equal(X, other.X) && Math::equal(Y, other.Y) && Math::equal(Z, other.Z));
    }

    bool operator>=(const Vec4D<T>&other) const
    {
        return (X > other.X || Math::equal(X, other.X)) ||
              ((Y > other.Y || Math::equal(Y, other.Y)) && Math::equal(X, other.X)) ||
              ((Z > other.Z || Math::equal(Z, other.Z)) &&
              Math::equal(X, other.X) && Math::equal(Y, other.Y)) ||
              ((W > other.W || Math::equal(W, other.W)) &&
              Math::equal(X, other.X) && Math::equal(Y, other.Y) && Math::equal(Z, other.Z));
    }

    Vec4D<T>& set(T x, T y, T z, T w)
    {
        X = x;
        Y = y;
        Z = z;
        W = w;
        return *this;
    }

    T length() const
    {
        return std::sqrt(X * X + Y * Y + Z * Z + W * W);
    }

    T lengthSq() const
    {
        return X * X + Y * Y + Z * Z, W * W;
    }

    T dot(const Vec4D<T>& other) const
    {
        return X * other.X + Y * other.Y + Z * other.Z + W * other.W;
    }

    T distance(const Vec4D<T>& other) const
    {
        return Vec4D<T>(X - other.X, Y - other.Y, Z - other.Z, W - other.W).length();
    }
    
    T distanceSq(const Vec4D<T>& other) const
    {
        return Vec4D<T>(X - other.X, Y - other.Y, Z - other.Z, W - other.W).lengthSq();
    }

    Vec4D<T>& normalize()
    {
        const T len = this->length();
        if(len) {
            X /= len;
            Y /= len;
            Z /= len;
            W /= len;
        }
        return *this;
    }

private:
    bool equal(const Vec4D<T>& other) const
    {
        return Math::equal(X, other.X) &&
               Math::equal(Y, other.Y) &&
               Math::equal(Z, other.Z) &&
               Math::equal(W, other.W);
    }
};