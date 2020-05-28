#ifndef chainStackLast_
#define chainStackLast_

#include <iostream>
#include "./stack.h"
#include "../myExceptions.h"
#include "../lib/chainNode.h"

using namespace std;

template <class T>
class chainStack : stack<T>
{
    template <class U>
    friend ostream &operator<<(ostream &out, const chainStack<U> &);

public:
    chainStack(int initialSize = 10);
    ~chainStack();
    bool empty() const
    {
        return stackSize == 0;
    }
    int size() const
    {
        return stackSize;
    }
    T &top();
    void pop();
    void push(const T &theElement);

private:
    chainNode<T> *jump2TheIndex(int theIndex) const;
    void checkIndex(const int theIndex);

    chainNode<T> *firstNode;
    int stackSize;
};

template <class T>
ostream &operator<<(ostream &out, const chainStack<T> &s)
{
    out << "The stack is: ";
    chainNode<T> *node = s.firstNode;
    while (node != NULL)
    {
        out << node->element << ' ';
        node = node->next;
    }
    out << endl;

    return out;
}

template <class T>
chainNode<T> *chainStack<T>::jump2TheIndex(int theIndex) const
{
    chainNode<T> *p = firstNode;
    for (int i = 0; i < theIndex; i++)
    {
        p = p->next;
    }

    return p;
}

template <class T>
void chainStack<T>::checkIndex(const int theIndex)
{
    if (theIndex < 0 || theIndex > stackSize)
    {
        throw illegalParameterValue("The index of stack must be in [0, stackSize - 1]");
    }
}

template <class T>
chainStack<T>::chainStack(int initialSize)
{
    if (initialSize < 0)
    {
        throw illegalParameterValue("The initial size of stack must be > 0");
    }

    firstNode = NULL;
    stackSize = 0;
}

template <class T>
chainStack<T>::~chainStack()
{
    chainNode<T> *deleteNode;

    while (firstNode != NULL)
    {
        deleteNode = firstNode;
        firstNode = firstNode->next;
        delete deleteNode;
    }
}

template <class T>
T &chainStack<T>::top()
{
    if (stackSize == 0)
    {
        throw stackEmpty();
    }

    chainNode<T> *p = jump2TheIndex(stackSize - 1);

    return p->element;
}

template <class T>
void chainStack<T>::pop()
{
    if (stackSize == 0)
    {
        throw stackEmpty();
    }

    chainNode<T> *p = jump2TheIndex(stackSize - 2);
    chainNode<T> *temp = p->next;
    p->next = NULL;
    delete temp;
    --stackSize;
}

template <class T>
void chainStack<T>::push(const T &theElement)
{
    chainNode<T> *lastNode = new chainNode<T>(theElement, NULL);

    if (stackSize == 0)
    {
        firstNode = lastNode;
        stackSize++;
        return;
    }

    chainNode<T> *p = jump2TheIndex(stackSize - 1);
    p->next = lastNode;
    stackSize++;
}

#endif