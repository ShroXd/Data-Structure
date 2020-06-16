#ifndef maxHblt_
#define maxHblt_

#include "../virtualClass/maxPriorityQueue.h"
#include "../lib/myExceptions.h"
#include "../lib/binaryTreeNode.h"
#include "../binaryTree/linkedBinaryTree.h"

using namespace std;


template <class T>
class maxHblt : public maxPriorityQueue<T>
{
protected:
    binaryTreeNode<pair<int, T> > *root;
    int treeSize;
    void meld(binaryTreeNode<pair<int, T> > *&,
              binaryTreeNode<pair<int, T> > *&);

public:
    maxHblt()
    {
        root = NULL;
        treeSize = 0;
    };
    ~maxHblt()
    {
        erase(root);
    };
    bool empty() const
    {
        return treeSize == 0;
    }
    int size() const
    {
        return treeSize;
    }
    /* const T &top()
    {
        if (treeSize == 0)
        {
            throw queueEmpty();
        }
        T result = root->element.second;
        return result;
    } */
    void pop();
    void push(const T &theElement)
    {
        binaryTreeNode<pair<int, T> > *q = new binaryTreeNode<pair<int, T> >(pair<int, T>(1, theElement));
            meld(root, q);
        treeSize++;
    };
    void erase(binaryTreeNode<pair<int, T> > *t)
    {
        if (t != NULL)
        {
            erase(t->leftChild);
            erase(t->rightChild);
            delete t;
        }
    }
    void initialize(T *, int);
    void meld(maxHblt<T> &theHblt)
    {
        meld(root, theHblt.root);
        treeSize += theHblt.treeSize;

        theHblt.root = NULL;
        theHblt.treeSize = 0;
    }
    void preOrder(binaryTreeNode<pair<int, T> > *);
    void preOrderOutput()
    {
        cout << "The hblt is: ";
        binaryTreeNode<pair<int, T> > *p = root;
        // cout << p->element.second << ' ';

        // 遍历树
        preOrder(p);
        
        cout << endl;
        cout << endl;
    }
};

template <class T>
void maxHblt<T>::preOrder(binaryTreeNode<pair<int, T> > *t)
{
    if (t != NULL)
    {

        cout << t->element.second << ' ';
        preOrder(t->leftChild);
        preOrder(t->rightChild);
    }
}

template <class T>
void maxHblt<T>::meld(binaryTreeNode<pair<int, T> > *&x,
                      binaryTreeNode<pair<int, T> > *&y)
{
    if (y == NULL)
    {
        return;
    }
    if (x == NULL)
    {
        x = y;
        return;
    }

    // 为保证合并后还是最大 HBLT，所以较大的根元素为合并后的根
    if (x->element.second < y->element.second)
    {
        swap(x, y);
    }

    meld(x->rightChild, y);

    if (x->leftChild == NULL)
    {
        // 当合并后没有左元素时，左元素的 s 为 0，所以需要交换左右子元素
        x->leftChild = x->rightChild;
        x->rightChild = NULL;
        x->element.first = 1;
    }
    else
    {
        // pair.first       s 值
        // pair.second      优先级队列的元素
        if (x->leftChild->element.first < x->rightChild->element.first)
        {
            // 保证左元素 s 值较大
            swap(x->leftChild, x->rightChild);
        }

        // 最右路径为最短路径，故右子元素 s(x) 加 1 为父元素的 s(x)
        x->element.first = x->rightChild->element.first + 1;
    }
}

template <class T>
void maxHblt<T>::pop()
{
    if (root == NULL)
    {
        throw queueEmpty();
    }

    binaryTreeNode<pair<int, T> > *left = root->leftChild,
                                 *right = root->rightChild;
    delete root;
    root = left;
    meld(root, right);
    treeSize--;
}

template <class T>
void maxHblt<T>::initialize(T *theElements, int theSize)
{
    // arrayQueue<binaryTreeNode<pair<int, T> > > q(theSize);
    // erase();

    /* for (int i = 1; i <= theSize; i++)
    {
        q.push(new binaryTreeNode<pair<int, T> >(pair<int, T>(1, theElement[i])));
    }

    for (int i = 1; i <= theSize - 1; i++)
    {
        binaryTreeNode<pair<int, T> > *b = q.front();
        q.pop();
        binaryTreeNode<pair<int, T> > *c = q.front();
        q.pop();
        meld(b, c);
        q.push(b);
    }

    if (theSize > 0)
    {
        root = q.front();
    }
    treeSize = theSize; */
}


#endif