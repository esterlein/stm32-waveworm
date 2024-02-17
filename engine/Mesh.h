#pragma once

#include <array>


template <typename T, size_t N>
class Mesh
{
private:
    std::array<T, N> m_mesh;

public:
    Mesh() : m_mesh{} {}

    ~Mesh() = default;

    Mesh(const Mesh<T, N>& other)
    {
        *this = other;
    }

    // Mesh(const Mesh<T, N>&& other) = default;

    T& operator[](int index)
    {
        assert(index >= 0 && index < m_mesh.size());
        return m_mesh[index];
    }

    const T& operator[](int index) const
    {
        assert(index >= 0 && index < m_mesh.size());
        return m_mesh[index];
    }

    Mesh<T, N>& operator=(const Mesh<T, N>& other)
    {
        if(this != &other)
            m_mesh = other.m_mesh;
        return *this;
    }

    // Mesh<T, N>& operator=(const Mesh<T, N>&& other) = default;
};