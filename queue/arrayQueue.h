#ifndef arrayQueue_
#define arrayQueue_

#include <iostream>
#include "./queue.h"
#include "../lib/myExceptions.h"

using namespace std;

template <class T>
class arrayQueue : public queue<T>
{
    template <class U>
    friend ostream &operator<<(ostream &out, const arrayQueue<U> &);

public:
    arrayQueue(int initialSize = 10);
    ~arrayQueue()
    {
        delete[] queue;
    }
    bool empty() const
    {
        return theFront == theBack;
    }
    int size() const
    {
        return (theBack - theFront + arrayLength) % arrayLength;
    }

    T &front()
    {
        if (theFront == theBack)
        {
            throw queueEmpty();
        }

        return queue[(theFront + 1) % arrayLength];
    }
    T &back()
    {
        if (theFront == theBack)
        {
            throw queueEmpty();
        }

        return queue[theBack];
    }
    void pop()
    {
        if (theFront == theBack)
        {
            throw queueEmpty();
        }

        theFront = (theFront + 1) % arrayLength;
        queue[theFront].~T();
    }
    void push(const T &theElement);

private:
    int theFront;
    int theBack;
    int arrayLength;
    T *queue;
};

template <class T>
ostream &operator<<(ostream &out, const arrayQueue<T> &q)
{
    out << "The queue is: ";
    for (int i = (q.theFront + 1) % q.arrayLength; i <= q.theBack; i++)
    {
        out << q.queue[i] << ' ';
    }
    out << endl;

    return out;
}

template <class T>
arrayQueue<T>::arrayQueue(int initialSize)
{
    if (initialSize < 0)
    {
        throw illegalParameterValue("The inital size of queue must be > 0");
    }

    theFront = 0;
    theBack = 0;
    arrayLength = initialSize;
    queue = new T[arrayLength];
}

template <class T>
void arrayQueue<T>::push(const T &theElement)
{
    if ((theFront + 1) % arrayLength == theBack)
    {
        // 数组加倍
        T* newQueue = new T[2 * arrayLength];

        int start = (theFront + 1) % arrayLength;
        if (start < 2)
        {
            copy(queue + start, queue + start + arrayLength - 1, newQueue);
        }
        else
        {
            copy(queue + start, queue + arrayLength, newQueue);
            // arrayLength - start = (queue + arrayLength) - (queue + start);
            copy(queue, queue + theBack + 1, newQueue + arrayLength - start);
        }

        theFront = 2 * arrayLength - 1;

        // 队列长度 arrayLength - 1
        theBack = arrayLength - 2;
        arrayLength *= 2;
        delete[] queue;
        queue  = newQueue;
    }

    theBack = (theBack + 1) % arrayLength;
    queue[theBack] = theElement;
}

#endif