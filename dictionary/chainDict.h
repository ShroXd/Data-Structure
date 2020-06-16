#ifndef chainDict_
#define chainDict_

#include <iostream>
#include "../virtualClass/dictionary.h"
#include "../lib/pairNode.h"

using namespace std;

template <class K, class E>
class chainDict : public dictionary<K, E>
{
    template <class R, class T>
    friend ostream &operator<<(ostream &out, const chainDict<R, T> &);

public:
    chainDict()
    {
        firstNode = NULL;
        dictSize = 0;
    }
    ~chainDict();

    bool empty() const
    {
        return dictSize == 0;
    }
    int size() const
    {
        return dictSize;
    }
    pair<const K, E> *find(const K &) const;
    void erase(const K &);
    void insert(const pair<const K, E> &);

protected:
    pairNode<K, E> *firstNode;
    int dictSize;
};

template <class K, class E>
ostream &operator<<(ostream &out, const chainDict<K, E> &cd)
{
    out << "The dictionary is: " << endl;

    pairNode<K, E> *p = cd.firstNode;

    while (p != NULL)
    {
        out << p->element.first << ": " << p->element.second << endl;
        p = p->next;
    }

    out << endl;

    return out;
}

template <class K, class E>
chainDict<K, E>::~chainDict()
{
    while (firstNode != NULL)
    {
        pairNode<K, E> *nextNode = firstNode->next;
        delete firstNode;
        firstNode = nextNode;
    }
}

template <class K, class E>
pair<const K, E> *chainDict<K, E>::find(const K &theKey) const
{
    pairNode<K, E> *currentNode = firstNode;

    while (currentNode != NULL && currentNode->element.first != theKey)
    {
        currentNode = currentNode->next;
    }

    if (currentNode != NULL && currentNode->element.first == theKey)
    {
        // 为何此处要返回引用的
        // return &currentNode->element;
        return &(currentNode->element);
    }

    return NULL;
}

template <class K, class E>
void chainDict<K, E>::insert(const pair<const K, E> &thePair)
{
    pairNode<K, E> *p = firstNode,
                   *tp = NULL;

    // 为何可以使用 < 来限制
    // 是否考虑到了各种类型的可能性
    while (p != NULL && p->element.first < thePair.first)
    {
        tp = p;
        p = p->next;
    }

    // 存在旧键值对
    if (p != NULL && p->element.first == thePair.first)
    {
        p->element.second = thePair.second;
        return;
    }

    // 不存在旧键值对
    pairNode<K, E> *newNode = new pairNode<K, E>(thePair, p);

    if (tp == NULL)
    {
        firstNode = newNode;
    }
    else
    {
        tp->next = newNode;
    }

    dictSize++;
}

template <class K, class E>
void chainDict<K, E>::erase(const K &theKey)
{
    pairNode<K, E> *p = firstNode,
                   *tp = NULL;

    while (p != NULL && p->element.first < theKey)
    {
        tp = p;
        p = p->next;
    }

    if (p != NULL & p->element.first == theKey)
    {
        if (tp == NULL)
        {
            firstNode = p->next;
        }
        else
        {
            tp->next = p->next;
        }

        delete p;
        dictSize--;
    }
}

#endif