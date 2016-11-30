#ifndef _DOUBLE_LINKED_LIST_H_
#define _DOUBLE_LINKED_LIST_H_

#include <iostream>

template<typename T>
class ListNode;
template<typename T>
class DoubleLinkedListIterator;

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
    virtual void clear(void);
    virtual bool isEmpty(void);
    
    virtual DoubleLinkedListIterator<T> start(void);
    virtual DoubleLinkedListIterator<T> end(void);
    
    T &operator[](unsigned int index) const;
    T &operator[](unsigned int index);
    
    inline const unsigned int &count(void) const { return m_count; };
    inline const unsigned int &size(void) const { return count(); };
    
    typedef DoubleLinkedListIterator<T> iterator;
    
protected:
    void createRoot(T data);
    ListNode<T> *getNode(unsigned int index);
    
    ListNode<T> *m_first;
    ListNode<T> *m_last;
    unsigned int m_count;
};

template<typename T>
class DoubleLinkedListIterator
{
    friend DoubleLinkedList<T>;
public:
    explicit DoubleLinkedListIterator(ListNode<T> *node);
    virtual ~DoubleLinkedListIterator(void);
    
    virtual DoubleLinkedListIterator<T> &operator++(void);
    virtual DoubleLinkedListIterator<T> &operator--(void);
    virtual DoubleLinkedListIterator<T> operator++(int);
    virtual DoubleLinkedListIterator<T> operator--(int);
    virtual bool operator==(const DoubleLinkedListIterator<T> &rhs);
    virtual bool operator!=(const DoubleLinkedListIterator<T> &rhs);
    
    virtual inline const T &value(void) const { return m_node->m_data; } ;
    
protected:
    ListNode<T> *m_node;
};

template<typename T>
class ListNode
{
    friend DoubleLinkedList<T>;
    friend DoubleLinkedListIterator<T>;
public:
    ListNode(T data);
    virtual ~ListNode(void);
    
    inline T &data(void) { return m_data; };
    
protected:
    T m_data;
    ListNode<T> *m_child;
    ListNode<T> *m_parent;
};

#include "doublelinkedlist.inl"

#endif // _DOUBLE_LINKED_LIST_H_
