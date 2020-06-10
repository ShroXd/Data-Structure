#ifndef chainStack_
#define chainStack_

#include <iostream>
#include "./stack.h"
#include "../lib/myExceptions.h"
#include "../lib/chainNode.h"

using namespace std;

template <class T>
class chainStack : public stack<T>
{
    template <class U>
    friend ostream& operator<<(ostream& out, const chainStack<U>&);

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

        T& top()
        {
            if (stackSize == 0)
            {
                throw stackEmpty();
            }

            return stackTop->element;
        }
        void pop();
        void push(const T& theElement);

    private:
        chainNode<T>* stackTop;
        int stackSize;
};

template <class T>
ostream& operator<<(ostream& out, const chainStack<T>& s)
{
    out << "The stack is: ";

    chainNode<T>* p = s.stackTop;
    while(p != NULL)
    {
        out << p->element << ' ';
        p = p->next;
    }
    out << endl;

    return out;
}

template <class T>
chainStack<T>::chainStack(int initialSize)
{
    if (initialSize < 0)
    {
        throw illegalParameterValue("The initial size of stack must be > 0");
    }

    stackTop = NULL;
    stackSize = 0;
}

template <class T>
chainStack<T>::~chainStack()
{
    chainNode<T>* deleteNode;

    while(stackTop != NULL)
    {
        deleteNode = stackTop;
        stackTop = stackTop->next;
        delete deleteNode;
    }
}

template <class T>
void chainStack<T>::pop()
{
    if (stackSize == 0)
    {
        throw stackEmpty();
    }

    chainNode<T>* temp = stackTop;
    stackTop = stackTop->next;
    delete temp;
    stackSize--;
}

template <class T>
void chainStack<T>::push(const T& theElement)
{
    chainNode<T>* newNode = new chainNode<T>(theElement, stackTop);
    stackTop = newNode;
    stackSize++;
}

#endif