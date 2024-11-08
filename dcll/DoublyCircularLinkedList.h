#pragma once
#include <iostream>

typedef unsigned int uint;

template<typename T>
struct DoublyNode
{
    T data;
    DoublyNode<T> *prev = this;
    DoublyNode<T> *next = this;
};

template<typename T>
class DoublyCircularLinkedList
{
protected:
    typedef DoublyNode<T> Node;

protected:
    uint m_Size  = 0u;
    Node *m_Root = nullptr;

public:
    virtual ~DoublyCircularLinkedList() { clear(); }

    bool pop()
    {
        if (empty()) {
            return false;
        }
        if (m_Size == 1u) {
            delete m_Root;
            m_Root = nullptr;
        } else {
            Node *last  = m_Root->prev;
            Node *first = m_Root->next;
            last->next  = first;
            first->prev = last;
            delete m_Root;
            m_Root = first;
        }
        --m_Size;
        return true;
    }

    void push(const T &value)
    {
        Node *fresh = new Node(value);
        if (empty()) {
            m_Root = fresh;
        } else {
            Node *last   = m_Root->prev;
            last->next   = fresh;
            m_Root->prev = fresh;
            fresh->prev  = last;
            fresh->next  = m_Root;
        }
        ++m_Size;
    }

    void print() const
    {
        if (empty()) {
            std::cout << "No node available to print!" << std::endl;
            return;
        }
        Node *curr = m_Root;
        std::cout << "Addr\t\t| Prev\t\t\t| Next\t\t\t| Payload" << std::endl;
        std::cout << "-------------------------------------"
                     "------------------------------------"
                  << std::endl;
        for (uint i = 0u; i != m_Size; ++i) {
            std::cout << curr << "\t| " << curr->prev << "\t| " << curr->next
                      << "\t| " << curr->data << std::endl;
            curr = curr->next;
        }
    }

    uint size() const { return m_Size; }
    bool empty() const { return m_Size == 0u; }
    void clear() { while (pop()); }
};
