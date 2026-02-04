#pragma once
#include <cstddef>
#include <cstdlib>
#include <new>
#include <utility>

template <typename T>
class MiniVector
{
public:
    MiniVector();
    MiniVector(const MiniVector& other);
    ~MiniVector();

    void push_back(const T& value);
    void push_back(T&& value);
    void reserve(size_t newCapacity);
    void resize(size_t newSize);

    size_t size() const { return m_size; };
    size_t capacity() const { return m_capacity; };

    T& operator[](size_t index) { return m_data[index]; };
    const T& operator[](size_t index) const { return m_data[index]; };

private:
    void grow();

    T* m_data;
    size_t m_size;
    size_t m_capacity;
};

#include "MiniVector.inl"
