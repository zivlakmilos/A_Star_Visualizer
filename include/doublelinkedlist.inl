#include "zexception.h"

/*
 * ListNode
 */

template<typename T>
ListNode<T>::ListNode(T data)
    : m_data(data),
      m_child(nullptr),
      m_parent(nullptr)
{
}

template<typename T>
ListNode<T>::~ListNode(void)
{
}

/*
 * DoubleLinkedList
 */

template<typename T>
DoubleLinkedList<T>::DoubleLinkedList(void)
    : m_first(nullptr),
      m_last(nullptr),
      m_count(0)
{
}

template<typename T>
DoubleLinkedList<T>::~DoubleLinkedList(void)
{
    ListNode<T> *node = m_first;
    
    while(node)
    {
        ListNode<T> *tmp = node->m_child;
        delete node;
        node = tmp;
    }
}

template<typename T>
void DoubleLinkedList<T>::append(T data)
{
    appendBack(data);
}

template<typename T>
void DoubleLinkedList<T>::appendBack(T data)
{
    if(!m_last)
    {
        createRoot(data);
        return;
    }
    
    ListNode<T> *node = new ListNode<T>(data);
    m_last->m_child = node;
    node->m_parent = m_last;
    m_last = node;
    m_count++;
}

template<typename T>
void DoubleLinkedList<T>::appendFront(T data)
{
    if(!m_first)
    {
        createRoot(data);
        return;
    }
    
    ListNode<T> *node = new ListNode<T>(data);
    node->m_child = m_first;
    m_first->m_parent = node;
    m_first = node;
    m_count++;
}

template<typename T>
void DoubleLinkedList<T>::createRoot(T data)
{
    m_first = new ListNode<T>(data);
    m_last = m_first;
    m_count = 1;
}

template<typename T>
T &DoubleLinkedList<T>::operator[](unsigned int index) const
{
    ListNode<T> *node = getNode(index);
    
    return node->m_data;
}

template<typename T>
T &DoubleLinkedList<T>::operator[](unsigned int index)
{
    ListNode<T> *node = getNode(index);
    
    return node->m_data;
}

template<typename T>
ListNode<T> *DoubleLinkedList<T>::getNode(unsigned int index)
{
    if(index >= m_count)
        throw ZException("Index out of range");
    
    bool fromBegin = index > m_count / 2;
    ListNode<T> *node = fromBegin ? m_first : m_last;
    int count = fromBegin ? index : m_count - index - 1;
    
    for(int i = 0; i < count; i++)
    {
        if(!node)
            break;
        node = fromBegin ? node->m_child : node->m_parent;
    }
    
    if(!node)
        throw ZException("Internal error");
    
    return node;
}

template<typename T>
void DoubleLinkedList<T>::remove(unsigned int index)
{
    ListNode<T> *node = getNode(index);
    ListNode<T> *parent = node->m_parent;
    ListNode<T> *child = node->m_child;
    
    parent->m_child = child;
    child->m_parent = parent;
    
    delete node;
    m_count--;
}
