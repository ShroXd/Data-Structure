#ifndef arrayStack_
#define arrayStack_

#include <iostream>
#include "./stack.h"
#include "../myExceptions.h"
#include "../lib/changeLength1D.h"

using namespace std;

template <class T>
class arrayStack : public stack<T>
{

    template <class U>
    friend ostream &operator<<(ostream &out, arrayStack<T> stack);

public:
    arrayStack(int initialSize = 10);
    arrayStack(const arrayStack<T> &);
    ~arrayStack()
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

    T &top() const;
    void pop();
    void push(const T &theElement);

private:
    void checkIndex(const int theIndex);
    void checkInitialSize(const int initialSize);

    int listSize;
    int arraySize;
    T *element;
};

template <class T>
ostream &operator<<(ostream &out, arrayStack<T> stack)
{

    return out;
}

template <class T>
void arrayStack<T>::checkIndex(const int theIndex)
{
    if (theIndex < 0 || theIndex > listSize)
    {
        throw illegalParameterValue("The index of stack must be in [0, listSize - 1]");
    }
}

template <class T>
void arrayStack<T>::checkInitialSize(const int initialSize)
{
    if (initialSize < 0)
    {
        throw illegalParameterValue("The initial size of stack must be > 0");
    }
}

template <class T>
arrayStack<T>::arrayStack(int initialSize)
{
    checkInitialSize(initialSize);

    listSize = 0;
    arraySize = initialSize;
    element = new T[initialSize];
}

template <class T>
T &arrayStack<T>::top() const
{

    return element[-1];
}

template <class T>
void arrayStack<T>::pop()
{
    // delete element[listSize - 1];

    listSize--;
}

template <class T>
void arrayStack<T>::push(const T &theElement)
{
    if (listSize == arraySize)
    {
        changeLength1D(element, arraySize, 2 * arraySize);
    }

    element[listSize] = theElement;
    listSize++;
}

#endif