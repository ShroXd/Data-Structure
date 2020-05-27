#ifndef changeLength1D_
#define changeLength1D_

#include "../myExceptions.h"

using namespace std;

// 此处 arr 使用引用指针，是为了直接改变外部的数组，而不是返回一个新数组
// 直接传入指针的话，函数完成后相关局部变量都会被销毁
template <class T>
void changeLength1D(T* &arr, int oldLength, int newLength)
{
    if (newLength < 0)
    {
        throw illegalParameterValue("The length of array must be > 0");
    }
    
    T* temp = new T[newLength];
    int length = min(oldLength, newLength);
    copy(arr, arr + length, temp);
    delete [] arr;
    arr = temp;

}

#endif