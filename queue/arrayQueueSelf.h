#ifndef arrayQueueSelf_
#define arrayQueueSelf_

#include <iostream>
#include "./queue.h"
#include "../myExceptions.h"
#include "../lib/changeLength1D.h"

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
        return queueEnd == -1;
    }
    int size() const
    {
        return queueEnd;
    }
    T &front()
    {
        if (queueEnd == -1)
        {
            throw queueEmpty();
        }

        return queue[0];
    }
    T &back()
    {
        if (queueEnd == -1)
        {
            throw queueEmpty();
        }

        return queue[queueEnd];
    }
    void pop()
    {
        if (queueEnd == -1)
        {
            throw queueEmpty();
        }

        // 注意区分索引和步移
        copy(queue + 1, queue + queueEnd + 1, queue);
        queue[queueEnd--].~T();
    }
    void push(const T &theElement);

private:
    T *queue;
    int queueEnd;
    int arrayLength;
};

template <class T>
ostream &operator<<(ostream &out, const arrayQueue<T> &q)
{
    out << "The queue is: ";
    for (int i = 0; i <= q.queueEnd; i++)
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
        throw illegalParameterValue("The initial size of queue must be > 0");
    }
    arrayLength = initialSize;
    queue = new T[arrayLength];
    queueEnd = -1;
}

template <class T>
void arrayQueue<T>::push(const T &theElement)
{
    if (queueEnd == arrayLength)
    {
        changeLength1D(queue, arrayLength, 2 * arrayLength);
        arrayLength *= 2;
    }

    queue[++queueEnd] = theElement;
}

#endif