#ifndef linkedBinaryTree_
#define linkedBinaryTree_

using namespace std;

#include <iostream>
#include <queue>
#include "./binaryTree.h"
#include "../lib/binaryTreeNode.h"
#include "../lib/myExceptions.h"

template <class T>
class linkedBinaryTree : public binaryTree<binaryTreeNode<T> >
{
public:
    linkedBinaryTree()
    {
        root = NULL;
        treeSize = 0;
    }
    ~linkedBinaryTree()
    {
        erase();
    }

    bool empty() const
    {
        return treeSize == 0;
    }
    int size() const
    {
        return treeSize;
    }

    // 对指针赋值，所以这里只需要传递进来引用就行了
    void makeTree(const T &element, linkedBinaryTree<T> &, linkedBinaryTree<T> &);

    // 前序遍历
    void preOrder(void (*theVisit)(binaryTreeNode<T> *))
    {
        visit = theVisit;
        preOrder(root);
    }
    void preOrderOutput()
    {
        preOrder(output);
        cout << endl;
    }

    // 中序遍历
    void inOrder(void (*theVisit)(binaryTreeNode<T> *))
    {
        visit = theVisit;
        inOrder(root);
    }
    void inOrderOutput()
    {
        inOrder(output);
        cout << endl;
    }

    // 后序遍历
    void postOrder(void (*theVisit)(binaryTreeNode<T> *))
    {
        visit = theVisit;
        postOrder(root);
    }
    void postOrderOutput()
    {
        postOrder(output);
        cout << endl;
    }

    // 层次遍历
    void levelOrder(void (*)(binaryTreeNode<T> *));
    void levelOrderOutput()
    {
        levelOrder(output);
        cout << endl;
    }

    // 树操作
    void erase()
    {
        postOrder(dispose);
        root = NULL;
        treeSize = 0;
    }
    int height() const
    {
        return height(root);
    }

protected:
    binaryTreeNode<T> *root;
    int treeSize;

    // 函数指针，以便于绑定不同的访问函数
    static void (*visit)(binaryTreeNode<T> *);

    // 遍历的静态函数
    static void preOrder(binaryTreeNode<T> *t);
    static void inOrder(binaryTreeNode<T> *t);
    static void postOrder(binaryTreeNode<T> *t);

    static void output(binaryTreeNode<T> *t)
    {
        cout << t->element << ' ';
    }

    static void dispose(binaryTreeNode<T> *t)
    {
        delete t;
    }
    static int height(binaryTreeNode<T>* t);
};

template <class T>
void (*linkedBinaryTree<T>::visit)(binaryTreeNode<T> *);

template <class T>
void linkedBinaryTree<T>::makeTree(const T &element,
                                   linkedBinaryTree<T> &left,
                                   linkedBinaryTree<T> &right)
{
    // 这个树的实现是从下往上长
    root = new binaryTreeNode<T>(element, left.root, right.root);
    treeSize = left.treeSize + right.treeSize + 1; // 左树，右树，根

    // 删除对原树的访问
    left.root = right.root = NULL;
    left.treeSize = right.treeSize = 0;
}

template <class T>
void linkedBinaryTree<T>::preOrder(binaryTreeNode<T> *t)
{
    if (t != NULL)
    {
        // 调用静态成员函数
        linkedBinaryTree<T>::visit(t);
        preOrder(t->leftChild);
        preOrder(t->rightChild);
    }
}

template <class T>
void linkedBinaryTree<T>::inOrder(binaryTreeNode<T> *t)
{
    if (t != NULL)
    {
        inOrder(t->leftChild);
        linkedBinaryTree<T>::visit(t);
        inOrder(t->rightChild);
    }
}

template <class T>
void linkedBinaryTree<T>::postOrder(binaryTreeNode<T> *t)
{
    if (t != NULL)
    {
        postOrder(t->leftChild);
        postOrder(t->rightChild);
        linkedBinaryTree<T>::visit(t);
    }
}

template <class T>
void linkedBinaryTree<T>::levelOrder(void (*theVisit)(binaryTreeNode<T> *))
{
    queue<binaryTreeNode<T> *> q;
    binaryTreeNode<T> *t = root;

    while (t != NULL)
    {
        theVisit(t);

        // 将该层的元素推入队列
        // 队列中的元素是按照左右子树，依层级排列下来的
        if (t->leftChild != NULL)
        {
            q.push(t->leftChild);
        }
        if (t->rightChild != NULL)
        {
            q.push(t->rightChild);
        }

        if (q.empty())
        {
            return;
        }
        // 依次从队列中取出
        t = q.front();
        q.pop();
    }
}

template <class T>
int linkedBinaryTree<T>::height(binaryTreeNode<T> *t)
{
    if (t == NULL)
    {
        return 0;
    }

    int hl = height(t->leftChild);      // height of left
    int hr = height(t->rightChild);     // height of right

    if (hl > hr)
    {
        return ++hl;
    }
    else
    {
        return ++hr;
    }
}

#endif