#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <stddef.h>
#include <memory>
#include <new>

// section for debug
// {
        #undef WIN32
        #ifdef WIN32
        #include <iostream>
        #endif
// }
using namespace std;

template <typename T, int S = 10>
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
        using other = user_allocator<U, S>;
    };

    template <typename U>
    user_allocator(const user_allocator<U>&) {}

    user_allocator() = default;

    T* allocate(size_t _n)
    {
        #ifdef WIN32
        cout << __PRETTY_FUNCTION__ << endl;
        #endif

        (void)_n;

        if (!m_data)
        {
            m_data = reinterpret_cast<T*>(malloc(sizeof(T) * m_free));
        } else {
            ++m_data;
            --m_free;
            if (!m_free)
                throw bad_alloc();
        }

        return m_data;
    }

    void deallocate(T* _ptr, size_t _n)
    {
        #ifdef WIN32
        cout << __PRETTY_FUNCTION__ << endl;
        #endif

        (void)_n;
        (void)_ptr;

        // free(_ptr);
    }

    template <typename ...Args>
    void construct(T* _ptr, Args ...args)
    {
        #ifdef WIN32
        cout << __PRETTY_FUNCTION__ << endl;
        #endif

        new (_ptr) T(std::forward<Args...>(args...));
    }

    void destroy(T* _ptr)
    {
        #ifdef WIN32
        cout << __PRETTY_FUNCTION__ << endl;
        #endif

        (void)_ptr;

        _ptr->~T();
    }

    ~user_allocator()
    {
        delete [] (m_data - (S - m_free));
    }

private:
    T* m_data   = nullptr;
    int m_free = S;
};

#endif // ALLOCATOR_H
