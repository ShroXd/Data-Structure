#ifndef maxHeap_
#define maxHeap_

#include <iostream>
#include "./maxPriorityQueue.h"
#include "../lib/changeLength1D.h"
#include "../lib/myExceptions.h"

using namespace std;

template <class T>
class maxHeap : public maxPriorityQueue<T>
{

    template <class U>
    friend ostream &operator<<(ostream &out, maxHeap<U> &);

private:
    int heapSize;
    int arrayLength;
    T *heap;

public:
    maxHeap(int initialCapacity = 10);
    ~maxHeap()
    {
        delete[] heap;
    }
    bool empty() const
    {
        return heapSize == 0;
    }
    int size() const
    {
        return heapSize;
    }

    const T &top()
    {
        if (heapSize == 0)
        {
            throw queueEmpty();
        }
        // 似乎是每 3 个为一组
        return heap[1];
    }

    void pop();
    void push(const T &);
    void initialize(T *, int);
    void deactivateArray()
    {
        heap = NULL;
        arrayLength = heapSize = 0;
    }
};

template <class T>
ostream& operator<<(ostream& out, maxHeap<T>& h)
{
    out << "The heap is: ";

    for (int i = 0; i < h.size(); i++)
    {
        out << h.heap[i] << ' ';
    }

    out << endl;

    return out;
}

template <class T>
maxHeap<T>::maxHeap(int initialCapacity)
{
    if (initialCapacity < 1)
    {
        throw illegalParameterValue("Initial capacity of heap must be > 0");
    }

    // 至少要有一个左子树
    arrayLength = initialCapacity + 1;
    heap = new T[arrayLength];
    heapSize = 0;
}

template <class T>
void maxHeap<T>::push(const T& theElement)
{
    // 当数组仅剩下一个空位的时候，是无法构造左子树的
    if (heapSize = arrayLength - 1)
    {
        changeLength1D(heap, arrayLength, 2 * arrayLength);
        arrayLength *= 2;
    }

    // 因为 size 比 index 大 1，所以 currentNode 左边有一个空位
    int currentNode = ++heapSize;

    while (currentNode != 1 && heap[currentNode / 2] < theElement)
    {
        // 将父节点下移
        heap[currentNode] = heap[currentNode / 2];
        currentNode /= 2;
    }

    heap[currentNode] = theElement;
}

template <class T>
void maxHeap<T>::pop()
{
    if (heapSize == 0)
    {
        throw queueEmpty();
    }

    // 参考特性 11-4
    // 析构根元素
    heap[1].~T();

    T lastElement = heap[heapSize--];

    int currentNode = 1, child = 2;
    while (child <= heapSize)
    {
        if (child < heapSize && heap[child] < heap[child + 1])
        {
            child++;
        }

        if (lastElement >= heap[child])
        {
            break;
        }
        else
        {
            heap[currentNode] = heap[child];
            currentNode = child;
            child *= 2;
        }

        heap[currentNode] = lastElement;
    }
}

#endif