#ifndef maxHeap_
#define maxHeap_

#include <iostream>
#include "../virtualClass/maxPriorityQueue.h"
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
ostream &operator<<(ostream &out, maxHeap<T> &h)
{
    out << "The heap is: ";

    for (int i = 1; i <= h.size(); i++)
    {
        out << i << '-' << h.heap[i] << ' ';
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
void maxHeap<T>::push(const T &theElement)
{
    // 当数组仅剩下一个空位的时候，是无法构造左子树的
    if (heapSize == arrayLength - 1)
    {
        changeLength1D(heap, arrayLength, 2 * arrayLength);
        arrayLength *= 2;
    }

    // 因为 size 比 index 大 1，所以 currentNode 左边有一个空位
    int currentNode = ++heapSize;

    // currentNode 不是根节点
    // 且父节点元素小于要插入的元素
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
    // 删除根位置的元素
    // 删除最后一个元素的位置
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
    // 寻找最后一个元素插入的位置
    {
        // 按照大根堆的定义，父节点需要大于其任意一个子节点
        // 所以需要取左右子元素的大者
        if (child < heapSize && heap[child] < heap[child + 1])
        {
            child++;
        }

        // 如果比较大的子元素还大，那么肯定是这个三元素子树的父节点
        if (lastElement >= heap[child])
        {
            break;
        }

        heap[currentNode] = heap[child];
        currentNode = child;
        // 左子树
        child *= 2;
    }

    heap[currentNode] = lastElement;
}

template <class T>
void maxHeap<T>::initialize(T *theHeap, int theSize)
{
    delete[] heap;
    heap = theHeap;
    heapSize = theSize;

    // heapSize / 2: 最后一个具有孩子的节点
    for (int root = heapSize / 2; root >= 1; root--)
    {
        T rootElement = heap[root];
        // 左子元素
        int child = 2 * root;

        // 可能会有右子元素
        while (child <= heapSize)
        {
            if (child < heapSize && heap[child] < heap[child + 1])
            {
                child++;
            }

            // 父元素大于子元素，不移动
            if (rootElement >= heap[child])
            {
                break;
            }

            // 反之则移动
            heap[child / 2] = heap[child];
            //? 单纯为了打破 while？
            child *= 2;
        }
        heap[child / 2] = rootElement;
    }
}

#endif