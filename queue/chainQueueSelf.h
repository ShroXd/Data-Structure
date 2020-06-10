#ifndef chainQueue_
#define chainQueue_

#include <iostream>
#include "./queue.h"
#include "../lib/myExceptions.h"
#include "../lib/chainNode.h"

using namespace std;

template <class T>
class chainQueue : public queue<T>
{
    template <class U>
    friend ostream &operator<<(ostream &out, const chainQueue<U> &);

public:
    chainQueue(int initialSize = 10);
    ~chainQueue()
    {
        delete[] queueEnd;
    };
    bool empty() const
    {
        return queueSize == 0;
    };
    int size() const
    {
        return queueSize;
    };
    T &front()
    {
        if (queueSize == 0)
        {
            throw queueEmpty();
        }

        return queueEnd->element;
    }

    T &back()
    {
        if (queueSize == 0)
        {
            throw queueEmpty();
        }

        chainNode<T> *backNode = jump2TheIndex(queueSize - 1);

        return backNode->element;
    }

    void pop()
    {
        if (queueSize == 0)
        {
            throw queueEmpty();
        }

        chainNode<T> *tempNode = jump2TheIndex(queueSize - 2);
        chainNode<T> *deleteNode = tempNode->next;
        tempNode->next = NULL;
        delete deleteNode;
        queueSize--;
    }

    void push(const T &theElement);

private:
    void checkIndex(int theIndex) const;
    chainNode<T> *jump2TheIndex(int theIndex) const;
    chainNode<T> *queueEnd;
    int queueSize;
};

template <class T>
ostream &operator<<(ostream &out, const chainQueue<T> &q)
{
    out << "The queue is: ";

    chainNode<T> *p = q.queueEnd;
    while (p != NULL)
    {
        out << p->element << ' ';
        p = p->next;
    }

    out << endl;

    return out;
}

template <class T>
void chainQueue<T>::checkIndex(int theIndex) const
{
    if (theIndex < 0 || theIndex > queueSize - 1)
    {
        throw illegalParameterValue("The index of queue must be in [0, queueSize - 1]");
    }
}

template <class T>
chainNode<T> *chainQueue<T>::jump2TheIndex(int theIndex) const
{
    checkIndex(theIndex);

    chainNode<T> *p = queueEnd;
    for (int i = 0; i < theIndex; i++)
    {
        p = p->next;
    }

    return p;
}

template <class T>
chainQueue<T>::chainQueue(int initialSize)
{
    if (initialSize < 0)
    {
        throw illegalParameterValue("The initial size of queue must be > 0");
    }

    queueEnd = NULL;
    queueSize = 0;
}

template <class T>
void chainQueue<T>::push(const T &theElement)
{
    chainNode<T> *temp = queueEnd;
    queueEnd = new chainNode<T>(theElement, temp);
    queueSize++;
}

#endif