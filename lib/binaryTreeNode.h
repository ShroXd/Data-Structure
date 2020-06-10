#ifndef binaryTreeNode_
#define binaryTreeNode_

using namespace std;

template <class T>
struct binaryTreeNode
{
    T element;
    binaryTreeNode<T> *leftChild, *rightChild;

    binaryTreeNode()
    {
        leftChild = rightChild = NULL;
    }
    binaryTreeNode(const T &theElement) : element(theElement)
    {
        leftChild = rightChild = NULL;
    }
    binaryTreeNode(const T &theElement,
                   binaryTreeNode<T> *theLeftChild,
                   binaryTreeNode<T> *theRightChild) : element(theElement)
    {
        leftChild = theLeftChild;
        rightChild = theRightChild;
    }
};

#endif