#ifndef hash_
#define hash_

#include <iostream>
#include <string>

using namespace std;

template <class T>
class hashFunc;

template <>
class hashFunc<string>
{
public:
    size_t operator()(const string theKey) const
    {
        // 无符号
        unsigned long hashValue = 0;
        int length = (int)theKey.length();
        for (int i = 0; i < length; i++)
        {
            hashValue = 5 * hashValue + theKey.at(i);
        }

        return size_t(hashValue);
    }
};

#endif