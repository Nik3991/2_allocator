#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <memory>
#include <new>

#include <iostream>

using namespace std;

template <typename T, int Size = 10>
class user_allocator
{
public:
    using value_type = T;
//    using pointer = T*;
//    using const_pointer = const T*;
//    using reference = T&;
//    using const_reference = const T&;

    template <typename U>
    struct rebind
    {
        using other = user_allocator<U, Size>;
    };

    template <typename U>
    user_allocator(const user_allocator<U>&) {}

    user_allocator() = default;

    T* allocate(size_t _n)
    {
        (void)_n;

        if (!m_free)
            throw bad_alloc();

        if (!m_data)
        {
            m_data = reinterpret_cast<T*>(malloc(sizeof(T) * m_free));
        }

        T* ret_ptr = m_data + (Size - m_free);
        --m_free;

        return ret_ptr;
    }

    void deallocate(T* _ptr, size_t _n)
    {
        (void)_n;
        (void)_ptr;

        // free(_ptr);
    }

    template <typename ...Args>
    void construct(T* _ptr, Args ...args)
    {
        new (_ptr) T(std::forward<Args...>(args...));
    }

    void destroy(T* _ptr)
    {
        (void)_ptr;

        _ptr->~T();
    }

    ~user_allocator()
    {
        delete m_data;
    }

private:
    T* m_data  = nullptr;
    int m_free = Size;
};

#endif // ALLOCATOR_H
