#pragma once

#include <cmath>
#include <cassert>

#include <array>
#include <algorithm>


template <typename T>
class Mtx4x4
{
private:
    static constexpr int s_size = 16;
    std::array<T, s_size> m_mtx;

public:
    Mtx4x4() : m_mtx{} {}
    
    ~Mtx4x4() = default;

    Mtx4x4(const Mtx4x4<T>& other)
    {
        *this = other;
    }

    T& operator[](int index)
    {
        assert(index >= 0 && index < s_size);
        return m_mtx[index];
    }

    const T& operator[](int index) const
    {
        assert(index >= 0 && index < s_size);
        return m_mtx[index];
    }

    Mtx4x4<T>& operator=(const Mtx4x4<T>& other)
    {
        if(this != &other)
            m_mtx = other.m_mtx;
        return *this;
    }

    Mtx4x4<T>& operator=(const T& scalar)
    {
        m_mtx.fill(scalar);
        return *this;
    }

    Mtx4x4<T> operator+(const Mtx4x4<T>& other) const
    {
        Mtx4x4<T> sum;
        for(auto i = 0; i < s_size; ++i)
            sum[i] = m_mtx[i] + other[i];
        return sum;
    }

    Mtx4x4<T>& operator+=(const Mtx4x4<T>& other)
    {
        for(auto i = 0; i < s_size; ++i)
            m_mtx[i] += other[i];
        return *this;
    }

    Mtx4x4<T> operator-(const Mtx4x4<T>& other) const
    {
        Mtx4x4<T> diff;
        for(auto i = 0; i < s_size; ++i)
            diff[i] = m_mtx[i] - other[i];
        return diff;
    }

    Mtx4x4<T>& operator-=(const Mtx4x4<T>& other)
    {
        for(auto i = 0; i < s_size; ++i)
            m_mtx[i] -= other[i];
        return *this;
    }

    Mtx4x4<T> operator*(const T& scalar) const
    {
        Mtx4x4<T> prod;
        for(auto i = 0; i < s_size; ++i)
            prod[i] = m_mtx[i] * scalar;
        return prod;
    }

    Mtx4x4<T>& operator*=(const T& scalar)
    {
        for(auto i = 0; i < s_size; ++i)
            m_mtx[i] *= scalar[i];
        return *this;
    }

    Mtx4x4<T> operator*(const Mtx4x4<T>& other) const
    {
        Mtx4x4<T> prod;

        prod[0]  = m_mtx[0] * other[0]  + m_mtx[4] * other[1]  + m_mtx[8]  * other[2]  + m_mtx[12] * other[3];
        prod[1]  = m_mtx[1] * other[0]  + m_mtx[5] * other[1]  + m_mtx[9]  * other[2]  + m_mtx[13] * other[3];
        prod[2]  = m_mtx[2] * other[0]  + m_mtx[6] * other[1]  + m_mtx[10] * other[2]  + m_mtx[14] * other[3];
        prod[3]  = m_mtx[3] * other[0]  + m_mtx[7] * other[1]  + m_mtx[11] * other[2]  + m_mtx[15] * other[3];
 
        prod[4]  = m_mtx[0] * other[4]  + m_mtx[4] * other[5]  + m_mtx[8]  * other[6]  + m_mtx[12] * other[7];
        prod[5]  = m_mtx[1] * other[4]  + m_mtx[5] * other[5]  + m_mtx[9]  * other[6]  + m_mtx[13] * other[7];
        prod[6]  = m_mtx[2] * other[4]  + m_mtx[6] * other[5]  + m_mtx[10] * other[6]  + m_mtx[14] * other[7];
        prod[7]  = m_mtx[3] * other[4]  + m_mtx[7] * other[5]  + m_mtx[11] * other[6]  + m_mtx[15] * other[7];
 
        prod[8]  = m_mtx[0] * other[8]  + m_mtx[4] * other[9]  + m_mtx[8]  * other[10] + m_mtx[12] * other[11];
        prod[9]  = m_mtx[1] * other[8]  + m_mtx[5] * other[9]  + m_mtx[9]  * other[10] + m_mtx[13] * other[11];
        prod[10] = m_mtx[2] * other[8]  + m_mtx[6] * other[9]  + m_mtx[10] * other[10] + m_mtx[14] * other[11];
        prod[11] = m_mtx[3] * other[8]  + m_mtx[7] * other[9]  + m_mtx[11] * other[10] + m_mtx[15] * other[11];
 
        prod[12] = m_mtx[0] * other[12] + m_mtx[4] * other[13] + m_mtx[8]  * other[14] + m_mtx[12] * other[15];
        prod[13] = m_mtx[1] * other[12] + m_mtx[5] * other[13] + m_mtx[9]  * other[14] + m_mtx[13] * other[15];
        prod[14] = m_mtx[2] * other[12] + m_mtx[6] * other[13] + m_mtx[10] * other[14] + m_mtx[14] * other[15];
        prod[15] = m_mtx[3] * other[12] + m_mtx[7] * other[13] + m_mtx[11] * other[14] + m_mtx[15] * other[15];

        return prod;
    }

    Mtx4x4<T> operator*=(const Mtx4x4<T>& other) const
    {
        std::array<T, s_size> prod;

        prod[0]  *= m_mtx[0] * other[0]  + m_mtx[4] * other[1]  + m_mtx[8]  * other[2]  + m_mtx[12] * other[3];
        prod[1]  *= m_mtx[1] * other[0]  + m_mtx[5] * other[1]  + m_mtx[9]  * other[2]  + m_mtx[13] * other[3];
        prod[2]  *= m_mtx[2] * other[0]  + m_mtx[6] * other[1]  + m_mtx[10] * other[2]  + m_mtx[14] * other[3];
        prod[3]  *= m_mtx[3] * other[0]  + m_mtx[7] * other[1]  + m_mtx[11] * other[2]  + m_mtx[15] * other[3];
 
        prod[4]  *= m_mtx[0] * other[4]  + m_mtx[4] * other[5]  + m_mtx[8]  * other[6]  + m_mtx[12] * other[7];
        prod[5]  *= m_mtx[1] * other[4]  + m_mtx[5] * other[5]  + m_mtx[9]  * other[6]  + m_mtx[13] * other[7];
        prod[6]  *= m_mtx[2] * other[4]  + m_mtx[6] * other[5]  + m_mtx[10] * other[6]  + m_mtx[14] * other[7];
        prod[7]  *= m_mtx[3] * other[4]  + m_mtx[7] * other[5]  + m_mtx[11] * other[6]  + m_mtx[15] * other[7];
 
        prod[8]  *= m_mtx[0] * other[8]  + m_mtx[4] * other[9]  + m_mtx[8]  * other[10] + m_mtx[12] * other[11];
        prod[9]  *= m_mtx[1] * other[8]  + m_mtx[5] * other[9]  + m_mtx[9]  * other[10] + m_mtx[13] * other[11];
        prod[10] *= m_mtx[2] * other[8]  + m_mtx[6] * other[9]  + m_mtx[10] * other[10] + m_mtx[14] * other[11];
        prod[11] *= m_mtx[3] * other[8]  + m_mtx[7] * other[9]  + m_mtx[11] * other[10] + m_mtx[15] * other[11];
 
        prod[12] *= m_mtx[0] * other[12] + m_mtx[4] * other[13] + m_mtx[8]  * other[14] + m_mtx[12] * other[15];
        prod[13] *= m_mtx[1] * other[12] + m_mtx[5] * other[13] + m_mtx[9]  * other[14] + m_mtx[13] * other[15];
        prod[14] *= m_mtx[2] * other[12] + m_mtx[6] * other[13] + m_mtx[10] * other[14] + m_mtx[14] * other[15];
        prod[15] *= m_mtx[3] * other[12] + m_mtx[7] * other[13] + m_mtx[11] * other[14] + m_mtx[15] * other[15];

        m_mtx = prod;
        return *this;
    }

    constexpr static Mtx4x4<T> Projection(T fov, T aspect, T near, T far)
    {
        Mtx4x4<T> mtx;

        T fovRad = static_cast<T>(1.0f / tanf(static_cast<float>(fov) * 0.5f / 180.0f * 3.1415927f));
        
        mtx[0][0] = aspect * fovRad;
        mtx[1][1] = fovRad;
        mtx[2][2] = static_cast<T>(far / (far - near));
        mtx[3][2] = static_cast<T>((-far * near) / (far - near));
        mtx[2][3] = static_cast<T>(1.0f);
        mtx[3][3] = static_cast<T>(0.0f);

        return mtx;
    }
};