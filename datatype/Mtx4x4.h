#pragma once

#include <array>
#include <algorithm>


template <typename T>
class Mtx4x4
{
protected:
    static constexpr int s_num_elems = 16;
    std::array<T, s_num_elems> m_matrix;

public:
    Mtx4x4() : m_matrix{} {}
    
    ~Mtx4x4() = default;

    Mtx4x4(const Mtx4x4<T>& other)
    {
        *this = other;
    }

    Mtx4x4<T>& operator=(const Mtx4x4<T>& other)
    {
        if(this != &other)
            m_matrix = other.m_matrix;
        return *this;
    }
    Mtx4x4<T>& operator=(const T& scalar)
    {
        m_matrix.fill(scalar);
        return *this;
    }

    Mtx4x4<T> operator+(const Mtx4x4<T>& other) const
    {
        Mtx4x4<T> sum;
        for(auto i = 0; i < s_num_elems; ++i)
            sum[i] = m_matrix[i] + other.m_matrix[i];
        return sum;
    }
    Mtx4x4<T>& operator+=(const Mtx4x4<T>& other)
    {
        for(auto i = 0; i < s_num_elems; ++i)
            m_matri[i] += other[i];
        return *this;
    }

    Mtx4x4<T> operator-(const Mtx4x4<T>& other) const
    {
        Mtx4x4<T> diff;
        for(auto i = 0; i < s_num_elems; ++i)
            diff[i] = m_matrix[i] - other.m_matrix[i];
        return diff;
    }
    Mtx4x4<T>& operator-=(const Mtx4x4<T>& other)
    {
        for(auto i = 0; i < s_num_elems; ++i)
            m_matri[i] -= other[i];
        return *this;
    }

    Mtx4x4<T> operator*(const T& scalar) const
    {
        Mtx4x4<T> prod;
        for(auto i = 0; i < s_num_elems; ++i)
            prod[i] = m_matrix[i] * scalar;
        return prod;
    }
    Mtx4x4<T>& operator*=(const T& scalar)
    {
        for(auto i = 0; i < s_num_elems; ++i)
            m_matri[i] *= other[i];
        return *this;
    }
};

template <typename T>
class Mtx4x4Identity : Mtx4x4<T>
{
public:
    Mtx4x4Identity()
    : m_matrix{}
    {
        m_matrix[0] = m_matrix[5] = m_matrix[10] = m_matrix[15] = static_cast<T>(1);
    }

    ~Mtx4x4Identity() = default;
};