#pragma once

#include <cmath>
#include <cassert>

#include <array>
#include <numbers>
#include <algorithm>

#include "Vec4D.h"


template <typename T>
class Mtx4x4
{
private:
    static constexpr size_t s_size = 4;
    std::array<Vec4D<T>, s_size> m_mtx;

public:
    constexpr Mtx4x4() : m_mtx{} {}
    
    constexpr explicit Mtx4x4(T n) : m_mtx{}
    {
        m_mtx.fill(n);
    }

    ~Mtx4x4() = default;

    constexpr Mtx4x4(const Mtx4x4<T>& other)
    {
        *this = other;
    }

    constexpr Vec4D<T>& operator[](int index)
    {
        assert(index >= 0 && index < s_size);
        return m_mtx[index];
    }

    constexpr const Vec4D<T>& operator[](int index) const
    {
        assert(index >= 0 && index < s_size);
        return m_mtx[index];
    }

    constexpr Mtx4x4<T>& operator=(const Mtx4x4<T>& other)
    {
        if(this != &other)
            m_mtx = other.m_mtx;
        return *this;
    }

    constexpr Mtx4x4<T>& operator=(const T& scalar)
    {
        m_mtx.fill(scalar);
        return *this;
    }

    constexpr Mtx4x4<T> operator+(const Mtx4x4<T>& other) const
    {
        Mtx4x4<T> sum;
        for(auto r = 0; r < s_size; ++r)
            for(auto c = 0; c < s_size; ++c)
                sum.m_mtx[r][c] = m_mtx[r][c] + other.m_mtx[r][c];
        return sum;
    }

    constexpr Mtx4x4<T>& operator+=(const Mtx4x4<T>& other)
    {
        for(auto r = 0; r < s_size; ++r)
            for(auto c = 0; c < s_size; ++c)
                m_mtx[r][c] += other.m_mtx[r][c];
        return *this;
    }

    constexpr Mtx4x4<T> operator-(const Mtx4x4<T>& other) const
    {
        Mtx4x4<T> diff;
        for(auto r = 0; r < s_size; ++r)
            for(auto c = 0; c < s_size; ++c)
                diff.m_mtx[r][c] = m_mtx[r][c] - other.m_mtx[r][c];
        return diff;
    }

    constexpr Mtx4x4<T>& operator-=(const Mtx4x4<T>& other)
    {
        for(auto r = 0; r < s_size; ++r)
            for(auto c = 0; c < s_size; ++c)
                m_mtx[r][c] += other.m_mtx[r][c];
        return *this;
    }

    constexpr Mtx4x4<T> operator*(const T& scalar) const
    {
        Mtx4x4<T> prod;
        for(auto r = 0; r < s_size; ++r)
            for(auto c = 0; c < s_size; ++c)
                prod.m_mtx[r][c] = m_mtx[r][c] * scalar;
        return prod;
    }

    constexpr Mtx4x4<T>& operator*=(const T& scalar)
    {
        for(auto r = 0; r < s_size; ++r)
            for(auto c = 0; c < s_size; ++c)
                m_mtx[r][c] * scalar;
        return *this;
    }

    constexpr Mtx4x4<T> operator*(const Mtx4x4<T>& other) const
    {
        Mtx4x4<T> prod;

        for(auto k = 0; k < s_size; ++k)
            for(auto i = 0; i < s_size; ++i)
                for(auto j = 0; j < s_size; ++j)
                    prod.m_mtx[i][k] += m_mtx[i][j] * other.m_mtx[j][k];
                
        return prod;
    }

    constexpr Mtx4x4<T>& operator*=(const Mtx4x4<T>& other) const
    {
        std::array<Vec4D<T>, s_size> prod;

        for(auto k = 0; k < s_size; ++k)
            for(auto i = 0; i < s_size; ++i)
                for(auto j = 0; j < s_size; ++j)
                    prod[i][k] += m_mtx[i][j] * other.m_mtx[j][k];

        m_mtx = prod;
        return *this;
    }

    // Vec4D<T> operator*(const Vec4D<T>& vec) const
    // {
    //     m_mtx[]
    // }

    constexpr static Mtx4x4<T> Identity()
    {
        Mtx4x4<T> mtx;
        for(auto i = 0; i < s_size; ++i)
            mtx[i][i] = static_cast<T>(1.0f);
        return mtx;
    }

    constexpr static Mtx4x4<T> PerspectiveProjection(T fov, T aspect, T near, T far, Math::Angle unit = Math::Angle::Deg)
    {
        Mtx4x4<T> mtx;

        T fovFactor = unit == Math::Angle::Deg
            ? static_cast<T>(1.0f / tanf(static_cast<float>(fov) * 0.5f))
            : static_cast<T>(1.0f / tanf(static_cast<float>(fov) * 0.5f / 180.0f * std::numbers::pi_v<float>));

        mtx[0][0] = aspect * fovFactor;
        mtx[1][1] = fovFactor;
        mtx[2][2] = far / (far - near);
        mtx[2][3] = (-far * near) / (far - near);
        mtx[3][2] = static_cast<T>(1.0f);

        return mtx;
    }
};