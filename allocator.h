#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <stddef.h>
#include <memory>
#include <new>

#ifdef WIN32
#include <iostream>
using namespace std;
#endif

template <typename T, int S>
class user_allocator
{
public:
    using value_type = T;

    template <typename U>
    struct rebind
    {
        using other = user_allocator<U, S>;
    };

    T* allocate(size_t _n)
    {
        #ifdef WIN32
        cout << __PRETTY_FUNCTION__ << endl;
        #endif

        (void)_n;

        if (!m_Data)
        {
            m_Data = reinterpret_cast<T*>(malloc(sizeof(T) * m_Count));
        } else {
            ++m_Data;
            --m_Count;
            if (!m_Count)
                throw bad_alloc();
        }

        return m_Data;
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

        // _ptr->~T();
    }

    ~user_allocator()
    {
        delete [] (m_Data-(S-m_Count));
    }

private:
    T* m_Data   = nullptr;
    int m_Count = S;
};

#endif // ALLOCATOR_H
