#include <iostream>
#include "../chainList.h"

using namespace std;

int main()
{
    chainList<int> s;

    s.insert(0, 1);
    s.insert(1, 2);
    s.insert(2, 3);
    s.insert(3, 4);

    cout << s;

    cout << s.get(3) << endl;

    cout << s.indexOf(3) << endl;

    s.erase(0);
    s.erase(0);
    cout << s;
}