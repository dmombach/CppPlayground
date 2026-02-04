#include "MiniVector.h"
template <typename T>
MiniVector<T>::MiniVector()
    : m_data(nullptr), m_size(0), m_capacity(0)
{
}

template<typename T>
MiniVector<T>::MiniVector(const MiniVector& other)
    : m_data(nullptr), m_size(0), m_capacity(0)
{
    if (other.m_size == 0)
    {
        return;
    }

    m_capacity = other.m_capacity;
    m_size = other.m_size;

    m_data = static_cast<T*>(std::malloc(m_capacity * sizeof(T)));

    for (size_t i = 0; i < m_size; ++i)
    {
        new (m_data + i) T(other.m_data[i]); // copy-construct
    }
}

template <typename T>
MiniVector<T>::~MiniVector()
{
    for (size_t i = 0; i < m_size; ++i)
    {
        m_data[i].~T();
    }

    std::free(m_data);
}

template <typename T>
void MiniVector<T>::grow()
{
    size_t newCapacity = (m_capacity == 0 ? 1 : m_capacity * 2);

    T* newData = static_cast<T*>(std::malloc(newCapacity * sizeof(T)));

    for (size_t i = 0; i < m_size; ++i)
    {
        new (newData + i) T(std::move(m_data[i]));
    }

    for (size_t i = 0; i < m_size; ++i)
    {
        m_data[i].~T();
    }

    std::free(m_data);

    m_data = newData;
    m_capacity = newCapacity;
}

template <typename T>
void MiniVector<T>::reserve(size_t newCapacity)
{
    if (newCapacity <= m_capacity)
    {
        return;
    }

    T* newData = static_cast<T*>(std::malloc(newCapacity * sizeof(T)));

    for (size_t i = 0; i < m_size; ++i)
    {
        new (newData + i) T(std::move(m_data[i]));
    }

    for (size_t i = 0; i < m_size; ++i)
    {
        m_data[i].~T();
    }

    std::free(m_data);

    m_data = newData;
    m_capacity = newCapacity;
}

template<typename T>
inline void MiniVector<T>::resize(size_t newSize)
{
    if (newSize < m_size)
    {
        // Destroy extra elements
        for (size_t i = newSize; i < m_size; ++i)
        {
            m_data[i].~T();
        }
    }
    else
    {
        if (newSize > m_capacity)
        {
            // Ensure enough capacity
            reserve(newSize);
        }

        // Default-construct new elements
        for (size_t i = m_size; i < newSize; ++i)
        {
            new (m_data + i) T();
        }
    }

    m_size = newSize;
}

template <typename T>
void MiniVector<T>::push_back(const T& value)
{
    if (m_size == m_capacity)
    {
        grow();
    }

    new (m_data + m_size) T(value);
    ++m_size;
}

template <typename T>
void MiniVector<T>::push_back(T&& value)
{
    if (m_size == m_capacity)
    {
        grow();
    }

    new (m_data + m_size) T(std::move(value));
    ++m_size;
}
