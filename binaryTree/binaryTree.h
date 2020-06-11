#ifndef binaryTree_
#define binaryTree_

using namespace std;

template <class T>
class binaryTree
{
public:
    virtual ~binaryTree() {}
    virtual bool empty() const = 0;
    virtual int size() const = 0;

    // https://stackoverflow.com/questions/30095846/meaning-of-void-void
    // parameter is a pointer to a function whose return
    // type is void and has a single argument of type T*
    virtual void preOrder(void (*)(T *)) = 0;
    virtual void postOrder(void (*)(T *)) = 0;
    virtual void levelOrder(void (*)(T *)) = 0;
};

#endif