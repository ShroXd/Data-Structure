#ifndef chainList_
#define chainList_
#include <iostream>

#include "../myExceptions.h"
#include "../lib/chainNode.h"
#include "./linearList.h"

using namespace std;

template <class T>
class chainList : public linearList<T>
{
    template <class U>
    friend ostream &operator<<(ostream &out, chainList<U> &);

public:
    chainList(int initialSize = 10);
    chainList(const chainList<T> &);
    ~chainList()
    {
        delete[] element;
    }

    bool empty() const
    {
        return listSize == 0;
    }
    int size() const
    {
        return listSize;
    }

    T& get(int theIndex) const;
    int indexOf(const T& theElement) const;
    void erase(int theIndex);
    void insert(int theIndex, const T& theElement);

private:
    void checkIndex(int theIndex) const;
    void checkInitialSize(int theInitialSize) const;

    chainNode<T>* firstNode;    // 指向链表第一个元素的指针
    int listSize;
};

template <class T>
void chainList<T>::checkInitialSize(int theInitialSize) const
{
    if (theInitialSize < 0)
    {
        throw illegalParameterValue("The initial size of list must be > 0");
    }
}

template <class T>
void chainList<T>::checkIndex(int theIndex) const
{
    if (theIndex < 0 || theIndex > listSize)
    {
        throw illegalParameterValue("The index must in [0, listSize]");
    }
}

template <class T>
chainList<T>::chainList(int initialSize)
{
    checkInitialSize(initialSize);

    firstNode = NULL;
    listSize = 0;
}

template <class T>
chainList<T>::chainList(const chainList<T> &chain)
{
    listSize = chain.listSize;
    
    if (lsitSize == 0)
    {
        firstNode = NULL;
        return;
    }

    chainNode<T>* sourceNode = chain.firstNode;
    firstNode = new chainNode<T>(sourceNode->element);
    sourceNode = sourceNode->next;
    
    // firstNode 指向的应当是链表的第一个元素，所以不能用这个指针来迭代
    chainNode<T>* targetNode = firstNode;

    while(sourceNode != NULL)
    {
        targetNode->next = new chainNode<T>(sourceNode->element);
        targetNode = sourceNode->next;
        sourceNode = sourceNode->next;
    }
    targetNode->next = NULL;
}

template <class T>
chainList<T>::~chainList()
{
    while(firstNode != NULL)
    {
        chainNode<T>* nextNode = firstNode->next;
        delete firstNode;
        firstNode = nextNode;
    }
}

#endif