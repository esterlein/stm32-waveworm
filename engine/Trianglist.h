#pragma once

#include <array>


template<typename T, size_t N>
class Trianglist
{
private:
    std::array<T, N> m_vtxs;
    std::array<size_t, N> m_idxs;

public:
    Trianglist() = default;
};