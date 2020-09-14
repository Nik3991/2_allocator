#ifndef LIST_H
#define LIST_H

#include <memory>

template <typename T, typename Alloc = std::allocator<T>>
class List
{
    template <typename U>
    struct Node
    {
        U m_value;

        Node(U&& _value) : m_value(_value){}

        Node<U>* m_next = nullptr;
    };

    typename Alloc::template rebind<Node<T>>::other alloc;
    Node<T>* m_head = nullptr;
    Node<T>* m_tail = nullptr;

public:
    List(T value)
    {
        m_head = alloc.allocate(1);
        alloc.construct(m_head, std::move(value));
        m_tail = m_head;
    }

    void add(T value)
    {
        m_tail->m_next = alloc.allocate(1);
        alloc.construct(m_tail->m_next, std::move(value));
        m_tail = m_tail->m_next;
    }

    ~List()
    {
        Node<T>* node = m_head;
        while (node)
        {
            Node<T>* to_remove = node;
            node = node->m_next;
            alloc.destroy(to_remove);
            alloc.deallocate(to_remove, 1);
        }
    }
};

#endif // LIST_H
