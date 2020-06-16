#ifndef chainList_
#define chainList_
#include <iostream>

#include "../lib/myExceptions.h"
#include "../lib/chainNode.h"
#include "./../virtualClass/linearList.h"

using namespace std;

template <class T>
class chainList
{
    template <class U>
    friend ostream &operator<<(ostream &out, const chainList<U> &);

public:
    chainList(int initialSize = 10);
    chainList(const chainList<T> &);
    ~chainList();

    bool empty() const
    {
        return listSize == 0;
    };
    int size() const
    {
        return listSize;
    };

    int indexOf(const T &theElement) const;
    T &get(int theIndex) const;

    void erase(int theIndex);
    void insert(int theIndex, const T &theElement);

private:
    void checkIndex(int theIndex) const;
    void checkInitialSize(int initialSize);
    chainNode<T> *jump2TheIndex(int theIndex) const;

    chainNode<T> *firstNode;
    int listSize;
};

template <class T>
ostream &operator<<(ostream &out, const chainList<T> &chain)
{
    out << "The chain list is: ";
    chainNode<T> *currentNode = chain.firstNode;

    while (currentNode != NULL)
    {
        out << currentNode->element << "-";
        currentNode = currentNode->next;
    }

    out << endl;
    return out;
}

template <class T>
chainNode<T> *chainList<T>::jump2TheIndex(int theIndex) const
{
    chainNode<T> *p = firstNode;
    for (int i = 0; i < theIndex; i++)
    {
        p = p->next;
    }

    return p;
}

template <class T>
void chainList<T>::checkIndex(int theIndex) const
{
    if (theIndex < 0)
    {
        throw illegalParameterValue("the index of list must be > 0");
    }
}

template <class T>
void chainList<T>::checkInitialSize(int initialSize)
{
    if (initialSize < 1)
    {
        throw illegalParameterValue("the initialSize of list must be > 0");
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

    if (listSize == 0)
    {
        firstNode = NULL;
        return;
    }

    chainNode<T> *sourceNode = chain.firstNode;
    firstNode = new chainNode<T>(sourceNode->element);
    sourceNode = sourceNode->next;
    chainNode<T> *targetNode = firstNode;

    while (sourceNode != NULL)
    {
        targetNode->next = new chainNode<T>(sourceNode->next);
        targetNode = targetNode->next;
        sourceNode = sourceNode->next;
    }

    targetNode->next = NULL;
}

template <class T>
chainList<T>::~chainList()
{
    while (firstNode != NULL)
    {
        chainNode<T> *nextNode = firstNode->next;
        delete firstNode;
        firstNode = nextNode;
    }
}

template <class T>
T &chainList<T>::get(int theIndex) const
{
    checkIndex(theIndex);
    chainNode<T> *currentNode = jump2TheIndex(theIndex);

    return currentNode->element;
}

template <class T>
int chainList<T>::indexOf(const T &theElement) const
{
    int theIndex = 0;
    chainNode<T> *currentNode;
    currentNode = firstNode;
    for (int i = 0; i < listSize; i++)
    {
        if (currentNode->element == theElement)
        {
            theIndex = i;
            break;
        }
        else
        {
            theIndex = -1;
        }
        currentNode = currentNode->next;
    }

    return theIndex;
}

template <class T>
void chainList<T>::erase(int theIndex)
{
    checkIndex(theIndex);

    chainNode<T> *temp;
    if (theIndex == 0)
    {
        temp = firstNode;
        firstNode = firstNode->next;
    }
    else
    {
        chainNode<T> *preNode = jump2TheIndex(theIndex - 1);
        temp = preNode->next;
        preNode->next = temp->next;
    }

    delete temp;
    listSize--;
}

template <class T>
void chainList<T>::insert(int theIndex, const T &theElement)
{
    checkIndex(theIndex);

    if (theIndex == 0)
    {
        firstNode = new chainNode<T>(theElement, firstNode);
    }
    else
    {
        chainNode<T> *preNode = jump2TheIndex(theIndex - 1);
        preNode->next = new chainNode<T>(theElement, preNode->next);
    }

    listSize++;
}

#endif