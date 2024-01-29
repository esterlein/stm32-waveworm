#pragma once

#include <cmath>

#include "WwMath.h"


template <typename T>
class Vec3D
{
public:
    T X;
    T Y;
    T Z;

    Vec3D() : X{0}, Y{0}, Z{0} {}
    Vec3D(T x, T y) : X{x}, Y{y}, Z{z} {}
    explicit Vec3D(T n) : X{n}, Y{n}, Z{n} {}

    Vec3D(const Vec3D<T>& other) : X{other.X}, Y{other.Y}, Z{other.Z} {}

    Vec3D<T> operator-() const
    {
        return Vec3D<T>(-X, -Y, -Z);
    }

    Vec3D<T>& operator=(const Vec3D<T>& other)
    {
        X = other.X;
        Y = other.Y;
        Z = other.Z;
        return *this;
    }

    Vec3D<T> operator+(const Vec3D<T>& other) const
    {
        return Vec3D<T>(X + other.X, Y + other.Y, Z + other.Z);
    }
    Vec3D<T> operator+(const T v) const
    {
        return Vec3D<T>(X + v, Y + v, Z + v);
    }
    Vec3D<T>& operator+=(const Vec3D<T>& other)
    {
        X += other.X;
        Y += other.Y;
        Z += other.Z;
        return *this;
    }
    Vec3D<T>& operator+=(const T v) const
    {
        X += v;
        Y += v;
        Z += v;
        return *this;
    }

    Vec3D<T> operator-(const Vec3D<T>& other) const
    {
        return Vec3D<T>(X - other.X, Y - other.Y, Z - other.Z);
    }
    Vec3D<T> operator-(const T v) const
    {
        return Vec3D<T>(X - v, Y - v, Z - v);
    }
    Vec3D<T>& operator-=(const Vec3D<T>& other)
    {
        X -= other.X;
        Y -= other.Y;
        Z -= other.Z;
        return *this;
    }
    Vec3D<T>& operator-=(const T v) const
    {
        X -= v;
        Y -= v;
        Z -= v;
        return *this;
    }

    Vec3D<T> operator*(const Vec3D<T>& other) const
    {
        return Vec3D<T>(X * other.X, Y * other.Y, Z * other.Z);
    }
    Vec3D<T> operator*(const T v) const
    {
        return Vec3D<T>(X * v, Y * v, Z * v);
    }
    Vec3D<T>& operator*=(const Vec3D<T>& other)
    {
        X *= other.X;
        Y *= other.Y;
        Z *= other.Z;
        return *this;
    }
    Vec3D<T>& operator*=(const T v) const
    {
        X *= v;
        Y *= v;
        Z *= v;
        return *this;
    }

    Vec3D<T> operator/(const Vec3D<T>& other) const
    {
        return Vec3D<T>(X / other.X, Y / other.Y, Z / other.Z);
    }
    Vec3D<T> operator/(const T v) const
    {
        return Vec3D<T>(X / v, Y / v, Z / v);
    }
    Vec3D<T>& operator/=(const Vec3D<T>& other)
    {
        X /= other.X;
        Y /= other.Y;
        Z /= other.Z;
        return *this;
    }
    Vec3D<T>& operator/=(const T v) const
    {
        X /= v;
        Y /= v;
        Z /= v;
        return *this;
    }

    bool operator<(const Vec3D<T>& other) const
    {
        return (X < other.X && !Math::equal(X, other.X)) ||
               (Y < other.Y &&  Math::equal(X, other.X) && !Math::equal(Y, other.Y)) ||
               (Z < other.Z && !Math::equal(Z, other.Z) &&
               Math::equal(X, other.X) && Math::equal(Y, other.Y));
    }
    bool operator>(const Vec3D<T>& other) const
    {
        return (X > other.X && !Math::equal(X, other.X)) ||
               (Y > other.Y &&  Math::equal(X, other.X) && !Math::equal(Y, other.Y)) ||
               (Z > other.Z && !Math::equal(Z, other.Z) &&
               Math::equal(X, other.X) && Math::equal(Y, other.Y));
    }
    bool operator<=(const Vec3D<T>&other) const
    {
        return (X < other.X || Math::equal(X, other.X)) ||
              ((Y < other.Y || Math::equal(Y, other.Y)) && Math::equal(X, other.X)) ||
              ((Z < other.Z || Math::equal(Z, other.Z)) &&
              Math::equal(X, other.X) && Math::equal(Y, other.Y));
    }
    bool operator>=(const Vec3D<T>&other) const
    {
        return (X > other.X || Math::equal(X, other.X)) ||
              ((Y > other.Y || Math::equal(Y, other.Y)) && Math::equal(X, other.X)) ||
              ((Z > other.Z || Math::equal(Z, other.Z)) &&
              Math::equal(X, other.X) && Math::equal(Y, other.Y));
    }
    
    bool operator==(const Vec3D<T>& other) const
    {
        return this->equal(other);
    }
    bool operator!=(const Vec3D<T>& other) const
    {
        return !this->equal(other);
    }

    Vec3D<T>& set(T x, T y, T z)
    {
        X = x;
        Y = y;
        Z = z;
        return *this;
    }

    T length() const
    {
        return std::sqrt(X * X + Y * Y + Z * Z);
    }
    T lengthSq() const
    {
        return X * X + Y * Y + Z * Z;
    }

    T dot(const Vec3D<T>& other) const
    {
        return X * other.X + Y * other.Y + Z * other.Z;
    }

    T distance(const Vec3D<T>& other) const
    {
        return Vec3D<T>(X - other.X, Y - other.Y, Z - other.Z).length();
    }
    T distanceSq(const Vec3D<T>& other) const
    {
        return Vec3D<T>(X - other.X, Y - other.Y, Z - other.Z).lengthSq();
    }

    Vec3D<T>& normalize()
    {
        const T len = this->length();
        if(len) {
            X /= len;
            Y /= len;
            Z /= len;
        }
        return *this;
    }

private:
    bool equal(const Vec3D<T>& other) const
    {
        return Math::equal(X, other.X) &&
               Math::equal(Y, other.Y) &&
               Math::equal(Z, other.Z);
    }
};