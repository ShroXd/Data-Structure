#ifndef hashTable_
#define hashTable_

#include <iostream>
#include "./dictionary.h"
#include "../lib/hash.h"
#include "../lib/myExceptions.h"

using namespace std;

template <class K, class E>
class hashTable : public dictionary<K, E>
{
    template <class R, class T>
    friend ostream &operator<<(ostream &out, const hashTable<R, T> &);

public:
    hashTable(int theDivisor = 3);
    ~hashTable()
    {
        delete[] table;
    }

    bool empty() const
    {
        return dSize == 0;
    }
    int size() const
    {
        return dSize;
    }
    pair<const K, E> *find(const K &) const;
    void erase(const K &);
    void insert(const pair<const K, E> &);

protected:
    int search(const K &) const;
    int searchExist(const K &) const;
    pair<const K, E> **table;
    hashFunc<K> hash;
    int dSize;
    int divisor;
};

template <class K, class E>
hashTable<K, E>::hashTable(int theDivisor)
{
    divisor = theDivisor;
    dSize = 0;

    table = new pair<const K, E> *[divisor];
    for (int i = 0; i < divisor; i++)
    {
        table[i] = NULL;
    }
}

template <class K, class E>
int hashTable<K, E>::search(const K &theKey) const
{
    int i = (int)hash(theKey) % divisor; // home bucket
    int j = i;

    // 理论上来说被放入 home 桶
    // 若桶已经满了，则需要使用 线性探查 来寻找下一个可用桶插入
    // 这里循环就是找可用桶的
    do
    {
        // 当散列到的位置为空，或者不为空，但是键名相同
        if (table[j] == NULL || table[j]->first == theKey)
        {
            return j;
        }
        // 将散列表视为环形表，查找空位
        j = (j + 1) % divisor;
    } while (j != i);

    return j;
}

template <class K, class E>
int hashTable<K, E>::searchExist(const K &theKey) const
{
    int i = (int)hash(theKey) % divisor; // home bucket
    int j = i;

    // 理论上来说被放入 home 桶
    // 若桶已经满了，则需要使用 线性探查 来寻找下一个可用桶插入
    // 这里循环就是找可用桶的
    do
    {
        // 当散列到的位置为空，或者不为空，但是键名相同
        if (table[j] != NULL && table[j]->first == theKey)
        {
            return j;
        }
        // 将散列表视为环形表，查找空位
        j = (j + 1) % divisor;
    } while (j != i);

    return j;
}

template <class K, class E>
pair<const K, E>* hashTable<K, E>::find(const K& theKey) const
{
    int b = search(theKey);

    if (table[b] == NULL || table[b]->first != theKey)
    {
        return NULL;
    }

    return table[b];
}

template <class K, class E>
void hashTable<K, E>::erase(const K& theKey)
{
    int b = searchExist(theKey);

    if (table[b] == NULL)
    {
        // 无元素可删除
        throw hashTableElementEmpty();
    }
    else if (table[b] != NULL && table[b]->first == theKey)
    {
        // 存在数对，且 b 序号就是该数对

        //! 对要删除的元素调用该类型自己的析构函数
        table[b]->second.~E();
        table[b] = NULL;
        dSize--;
    }
}

template <class K, class E>
void hashTable<K, E>::insert(const pair<const K, E>& thePair)
{
    int b = search(thePair.first);

    if (table[b] == NULL)
    {
        // 插入新元素
        table[b] = new pair<const K, E>(thePair);
        dSize++;
    }
    else
    {
        if (table[b]->first == thePair.first)
        {
            table[b]->second = thePair.second;
        }
        else
        {
            throw hashTableFull();
        }
    }
}

template <class K, class E>
ostream& operator<<(ostream& out, const hashTable<K, E>& ht)
{
    out << "The hash table is: " << endl;

    for (int i = 0; i < ht.divisor; i++)
    {
        if (ht.table[i] == NULL)
        {
            out << "NULL" << endl;
        }
        else
        {
            out << ht.table[i]->first << ": " << ht.table[i]->second << endl;
        }
    }

    return out;
}

#endif