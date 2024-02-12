#pragma once

#include <array>


template <typename T, typename S>
class Mesh
{
private:
    std::array<T, S> m_mesh;

public:
    Mesh() : m_mesh{} {}

    ~Mesh() = default;

    Mesh(const Mesh<T, S>& other)
    {
        *this = other;
    }

    Mesh(const Mesh<T, S>&& other) = default;

    T& operator[](int index)
    {
        assert(index >=0 && index < m_mesh.size());
        return m_mesh[index];
    }

    const T& operator[](int index) const
    {
        assert(index >=0 && index < m_mesh.size());
        return m_mesh[index];
    }

    Mesh<T, S>& operator=(const Mesh<T, S>& other)
    {
        if(this != &other)
            m_mesh = other.m_mesh;
        return *this;
    }

    Mesh<T, S>& operator=(const Mesh<T, S>&& other) = default;
};