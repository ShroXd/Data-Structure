#ifndef arrayList_
#define arrayList_

#include <iostream>
#include "linearList.h"
#include "../myExceptions.h"
#include "../lib/changeLength1D.h"

using namespace std;

template <class T>
class arrayList : public linearList<T>
{

    template <class U>
    friend ostream &operator<<(ostream &out, const arrayList<U> &);

public:
    arrayList(int initialSize = 10);
    arrayList(const arrayList<T> &);
    ~arrayList()
    {
        delete[] element;
    }

    bool empty() const
    {
        return false;
    }
    int size() const
    {
        return listSize;
    }

    T &get(int theIndex) const;
    int indexOf(const T &theElement) const;
    void erase(int theIndex);
    void insert(int theIndex, const T &theElement);

protected:
    void checkIndex(int theIndex) const;

    int listSize;
    int arrayLength;
    T *element;
};

template <class T>
arrayList<T>::arrayList(int initialSize)
{
    // 检查参数有效性
    if (initialSize < 0)
    {
        throw illegalParameterValue("Initial size of arrayList must be > 0");
    }

    element = new T[initialSize];
    listSize = 0;
    arrayLength = initialSize;
}

template <class T>
arrayList<T>::arrayList(const arrayList<T> &theList)
{
    listSize = theList.listSize;
    arrayLength = theList.arrayLength;
    element = new T[arrayLength];
    copy(theList.element, theList.element + listSize, element);
}

template <class T>
void arrayList<T>::checkIndex(int theIndex) const
{
    if (theIndex < 0 || theIndex >= arrayLength)
    {
        throw illegalParameterValue("Index of list must be [0, arrayLength - 1]");
    }
}

template <class T>
T &arrayList<T>::get(int theIndex) const
{
    checkIndex(theIndex);

    return element[theIndex];
}

template <class T>
int arrayList<T>::indexOf(const T &theElement) const
{
    int theIndex;
    for (int i = 0; i < arrayLength - 1; i++)
    {
        if (element[i] == theElement)
        {
            theIndex = i;
            break;
        }
        else
        {
            theIndex = -1;
        }
    }

    return theIndex;
}

template <class T>
void arrayList<T>::erase(int theIndex)
{
    checkIndex(theIndex);

    copy(element + theIndex + 1, element + listSize, element + theIndex);
    //? 这啥啊
    element[--listSize].~T();
}

template <class T>
void arrayList<T>::insert(int theIndex, const T &theElement)
{
    checkIndex(theIndex);

    if (theIndex == arrayLength - 1)
    {
        changeLength1D(element, arrayLength, 2 * arrayLength);
        arrayLength *= 2;
    }

    copy(element + theIndex, element + listSize, element + theIndex + 1);
    element[theIndex] = theElement;
    listSize++;
}

template <class T>
ostream &operator<<(ostream &out, const arrayList<T> &s)
{
    cout << s.listSize << endl;
    for (int i = 0; i < s.listSize; i++)
    {
        cout << i << '-';
        out << s.element[i] << ' ';
    }
    out << endl;

    return out;
}

#endif