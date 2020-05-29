#ifndef queue_
#define queue_

template <class T>
class queue
{
public:
    virtual ~queue(){};
    virtual bool empty() const = 0;
    virtual int size() const = 0;
    virtual T &front() = 0;
    virtual T &back() = 0;
    virtual void pop() = 0;
    virtual void push(const T &theElement) = 0;
};

#endif