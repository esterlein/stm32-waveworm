#pragma once

#include <array>


template <typename T>
class Mesh
{
public:
    constexpr int m_size;
    std::array<T, m_size> m_mesh;
};