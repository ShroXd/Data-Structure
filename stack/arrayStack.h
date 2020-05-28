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
    friend ostream &operator<<(ostream &out, const arrayStack<U> &s);

public:
    arrayStack(int initialSize = 10);
    ~arrayStack()
    {
        delete[] stack;
    }

    bool empty() const
    {
        return stackTop == -1;
    }
    int size() const
    {
        return stackTop + 1;
    }

    T &top()
    {
        if (stackTop == -1)
        {
            throw stackEmpty();
        }
        return stack[stackTop];
    }
    void pop()
    {
        if (stackTop == -1)
        {
            throw stackEmpty();
        }
        stack[stackTop--].~T();
    }
    void push(const T &theElement);

private:
    void checkIndex(const int theIndex);
    void checkInitialSize(const int initialSize);

    T *stack;
    int stackTop;
    int arrayLength;
};

template <class T>
ostream &operator<<(ostream &out, const arrayStack<T> &s)
{
    out << "The stack is: ";
    for (int i = 0; i <= s.stackTop; i++)
    {
        out << s.stack[i] << ' ';
    }
    out << endl;

    return out;
}

template <class T>
void arrayStack<T>::checkIndex(const int theIndex)
{
    if (theIndex < 0 || theIndex > stackTop)
    {
        throw illegalParameterValue("The index of stack must be in [0, stackTop]");
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

    arrayLength = initialSize;
    stack = new T[arrayLength];
    stackTop = -1;
}

template <class T>
void arrayStack<T>::push(const T &theElement)
{
    if (stackTop == arrayLength - 1)
    {
        changeLength1D(stack, arrayLength, 2 * arrayLength);
        arrayLength *= 2;
    }

    stack[++stackTop] = theElement;
}

#endif