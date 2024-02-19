#pragma once

#include <assert.h>

#include <array>
#include <algorithm>


template <typename T>
class Mtx3x3
{
private:
    static constexpr int s_size = 9;
    std::array<T, s_size> m_mtx;

public:
    Mtx3x3() : m_mtx{} {}
    
    ~Mtx3x3() = default;

    Mtx3x3(const Mtx3x3<T>& other)
    {
        *this = other;
    }

    T& operator[](int index)
    {
        assert(index >=0 && index < s_size);
        return m_mtx[index];
    }

    const T& operator[](int index) const
    {
        assert(index >=0 && index < s_size);
        return m_mtx[index];
    }

    Mtx3x3<T>& operator=(const Mtx3x3<T>& other)
    {
        if(this != &other)
            m_mtx = other.m_mtx;
        return *this;
    }

    Mtx3x3<T>& operator=(const T& scalar)
    {
        m_mtx.fill(scalar);
        return *this;
    }

    Mtx3x3<T> operator+(const Mtx3x3<T>& other) const
    {
        Mtx3x3<T> sum;
        for(auto i = 0; i < s_size; ++i)
            sum[i] = m_mtx[i] + other[i];
        return sum;
    }

    Mtx3x3<T>& operator+=(const Mtx3x3<T>& other)
    {
        for(auto i = 0; i < s_size; ++i)
            m_mtx[i] += other[i];
        return *this;
    }

    Mtx3x3<T> operator-(const Mtx3x3<T>& other) const
    {
        Mtx3x3<T> diff;
        for(auto i = 0; i < s_size; ++i)
            diff[i] = m_mtx[i] - other[i];
        return diff;
    }

    Mtx3x3<T>& operator-=(const Mtx3x3<T>& other)
    {
        for(auto i = 0; i < s_size; ++i)
            m_mtx[i] -= other[i];
        return *this;
    }

    Mtx3x3<T> operator*(const T& scalar) const
    {
        Mtx3x3<T> prod;
        for(auto i = 0; i < s_size; ++i)
            prod[i] = m_mtx[i] * scalar;
        return prod;
    }

    Mtx3x3<T>& operator*=(const T& scalar)
    {
        for(auto i = 0; i < s_size; ++i)
            m_mtx[i] *= scalar[i];
        return *this;
    }

    Mtx3x3<T> operator*(const Mtx3x3<T>& other) const
    {
        Mtx3x3<T> prod;

        prod[0] = m_mtx[0] * other[0] + m_mtx[3] * other[1] + m_mtx[6] * other[2];
        prod[1] = m_mtx[1] * other[0] + m_mtx[4] * other[1] + m_mtx[7] * other[2];
        prod[2] = m_mtx[2] * other[0] + m_mtx[5] * other[1] + m_mtx[8] * other[2];
 
        prod[3] = m_mtx[0] * other[3] + m_mtx[3] * other[4] + m_mtx[6] * other[5];
        prod[4] = m_mtx[1] * other[3] + m_mtx[4] * other[4] + m_mtx[7] * other[5];
        prod[5] = m_mtx[2] * other[3] + m_mtx[5] * other[4] + m_mtx[8] * other[5];
 
        prod[6] = m_mtx[0] * other[6] + m_mtx[3] * other[7] + m_mtx[6] * other[8];
        prod[7] = m_mtx[1] * other[6] + m_mtx[4] * other[7] + m_mtx[7] * other[8];
        prod[8] = m_mtx[2] * other[6] + m_mtx[5] * other[7] + m_mtx[8] * other[8];

        return prod;
    }

    Mtx3x3<T> operator*=(const Mtx3x3<T>& other) const
    {
        std::array<T, s_size> prod;

        prod[0] *= m_mtx[0] * other[0] + m_mtx[3] * other[1] + m_mtx[6] * other[2];
        prod[1] *= m_mtx[1] * other[0] + m_mtx[4] * other[1] + m_mtx[7] * other[2];
        prod[2] *= m_mtx[2] * other[0] + m_mtx[5] * other[1] + m_mtx[8] * other[2];
 
        prod[3] *= m_mtx[0] * other[3] + m_mtx[3] * other[4] + m_mtx[6] * other[5];
        prod[4] *= m_mtx[1] * other[3] + m_mtx[4] * other[4] + m_mtx[7] * other[5];
        prod[5] *= m_mtx[2] * other[3] + m_mtx[5] * other[4] + m_mtx[8] * other[5];
 
        prod[6] *= m_mtx[0] * other[6] + m_mtx[3] * other[7] + m_mtx[6] * other[8];
        prod[7] *= m_mtx[1] * other[6] + m_mtx[4] * other[7] + m_mtx[7] * other[8];
        prod[8] *= m_mtx[2] * other[6] + m_mtx[5] * other[7] + m_mtx[8] * other[8];

        m_mtx = prod;
        return *this;
    }
};