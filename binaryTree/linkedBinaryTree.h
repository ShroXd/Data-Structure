#ifndef linkedBinaryTree_
#define linkedBinaryTree_

using namespace std;

#include <iostream>
#include "./binaryTree.h"
#include "../lib/binaryTreeNode.h"
#include "../myExceptions.h"

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
        cout << "erase()";
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

protected:
    binaryTreeNode<T> *root;
    int treeSize;

    // 函数指针，以便于绑定不同的访问函数
    static void (*visit)(binaryTreeNode<T> *);
    static void preOrder(binaryTreeNode<T> *t);

    static void output(binaryTreeNode<T> *t)
    {
        cout << t->element << ' ';
    }
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

#endif