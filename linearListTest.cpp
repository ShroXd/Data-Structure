#include <iostream>
#include "./linearList/arrayList.h"

using namespace std;

int main()
{
    arrayList<int> myList;

    if (myList.empty())
    {
        cout << "My list is empty" << endl;
    }
    else
    {
        cout << "My list is not empty" << endl;
    }

    cout << "The size of my list is: " << myList.size() << endl;

    myList.insert(0, 0);
    myList.insert(1, 100);
    myList.insert(2, 200);
    cout << "The size of my list is: " << myList.size() << endl;

    myList.erase(1);
    cout << myList;

    int theIndex = 200;
    if (myList.indexOf(theIndex) == -1)
    {
        cout << "未找到相关元素";
    }
    else
    {
        cout << myList.indexOf(theIndex);
    }
}