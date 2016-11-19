#ifndef _DOUBLE_LINKED_LIST_H_
#define _DOUBLE_LINKED_LIST_H_

#include <iostream>

template<typename T>
class ListNode;

template<typename T>
class DoubleLinkedList
{
public:
    DoubleLinkedList(void);
    virtual ~DoubleLinkedList(void);
    
    virtual void append(T data);
    virtual void appendBack(T data);
    virtual void appendFront(T data);
    virtual void remove(unsigned int index);
    virtual void pop(void);
    virtual void popBack(void);
    virtual void popFront(void);
    
    T &operator[](unsigned int index) const;
    T &operator[](unsigned int index);
    
    inline unsigned int count(void) { return m_count; };
    inline unsigned int size(void) { return count(); };
    
private:
    void createRoot(T data);
    ListNode<T> *getNode(unsigned int index);
    
    ListNode<T> *m_first;
    ListNode<T> *m_last;
    unsigned int m_count;
};

template<typename T>
class ListNode
{
    friend DoubleLinkedList<T>;
public:
    ListNode(T data);
    virtual ~ListNode(void);
    
    inline T &data(void) { return m_data; };
    
private:
    T m_data;
    ListNode *m_child;
    ListNode *m_parent;
};

#include "doublelinkedlist.inl"

#endif // _DOUBLE_LINKED_LIST_H_
