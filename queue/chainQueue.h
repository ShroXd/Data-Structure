#ifndef chainQueue_
#define chainQueue_

#include <iostream>
#include "./queue.h"
#include "../myExceptions.h"
#include "../lib/chainNode.h"

using namespace std;

template <class T>
class chainQueue : public queue<T>
{
    template <class U>
    friend ostream &operator<<(ostream &out, const chainQueue<U> &);

public:
    chainQueue(int initialSize = 10)
    {
        queueFront = queueBack = NULL;
        queueSize = 0;
    }
    ~chainQueue()
    {
        chainNode<T> *nextNode;
        while (queueFront != NULL)
        {
            nextNode = queueFront->next;
            delete queueFront;
            queueFront = nextNode;
        }
    }
    bool empty() const
    {
        return queueSize == 0;
    }
    int size() const
    {
        return queueSize;
    }
    T &front()
    {
        if (queueSize == 0)
        {
            throw queueEmpty();
        }

        return queueFront->element;
    }
    T &back()
    {
        if (queueSize == 0)
        {
            throw queueEmpty();
        }

        return queueBack->element;
    }
    void pop()
    {
        if (queueSize == 0)
        {
            throw queueEmpty();
        }

        chainNode<T> *nextNode = queueFront->next;
        delete queueFront;
        queueFront = nextNode;
        queueSize--;
    }
    void push(const T &theElement);

private:
    chainNode<T> *queueFront;
    chainNode<T> *queueBack;
    int queueSize;
};

template <class T>
ostream &operator<<(ostream &out, const chainQueue<T> &q)
{
    out << "The queue is: ";
    chainNode<T> *p = q.queueFront;

    while (p != NULL)
    {
        out << p->element << ' ';
        p = p->next;
    }
    out << endl;

    return out;
}

template <class T>
void chainQueue<T>::push(const T &theElement)
{
    chainNode<T> *newNode = new chainNode<T>(theElement, NULL);

    if (queueSize == 0)
    {
        queueFront = newNode;
    }
    else
    {
        queueBack->next = newNode;
    }
    queueBack = newNode;
    queueSize++;
}

#endif