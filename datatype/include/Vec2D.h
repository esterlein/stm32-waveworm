#pragma once


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

    Vec2D<T> operator-() const {
        return Vec2D<T>(-X, -Y);
    }

    Vec2D<T>& operator=(const Vec2D<T>& other) {
        X = other.X;
        Y = other.Y;
        return *this;
    }

    Vec2D operator+(const Vec2D<T>& other) const {
        return Vec2D<T>(X + other.X, Y + other.Y);
    }
    Vec2D operator+(const T v) const {
        return Vec2D<T>(X + v, Y + v);
    }
    Vec2D<T>& operator+=(const Vec2D<T>& other) {
        X += other.X;
        Y += other.Y;
        return *this;
    }
    Vec2D<T>& operator+=(const T v) const {
        X += v;
        Y += v;
        return *this;
    }

    Vec2D<T> operator-(const Vec2D<T>& other) const {
        return Vec2D<T>(X - other.X, Y - other.Y);
    }
    Vec2D operator-(const T v) const {
        return Vec2D<T>(X - v, Y - v);
    }
    Vec2D<T>& operator-=(const Vec2D<T>& other) {
        X -= other.X;
        Y -= other.Y;
        return *this;
    }
    Vec2D<T>& operator-=(const T v) const {
        X -= v;
        Y -= v;
        return *this;
    }

    Vec2D<T> operator*(const Vec2D<T>& other) const {
        return Vec2D<T>(X * other.X, Y * other.Y);
    }
    Vec2D operator*(const T v) const {
        return Vec2D<T>(X * v, Y * v);
    }
    Vec2D<T>& operator*=(const Vec2D<T>& other) {
        X *= other.X;
        Y *= other.Y;
        return *this;
    }
    Vec2D<T>& operator*=(const T v) const {
        X *= v;
        Y *= v;
        return *this;
    }

    Vec2D<T> operator/(const Vec2D<T>& other) const {
        return Vec2D<T>(X / other.X, Y / other.Y);
    }
    Vec2D operator/(const T v) const {
        return Vec2D<T>(X / v, Y / v);
    }
    Vec2D<T>& operator/=(const Vec2D<T>& other) {
        X /= other.X;
        Y /= other.Y;
        return *this;
    }
    Vec2D<T>& operator/=(const T v) const {
        X /= v;
        Y /= v;
        return *this;
    }
};