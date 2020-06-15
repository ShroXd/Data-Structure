#include <iostream>
#include "../maxHeap.h"

using namespace std;

int main()
{
    maxHeap<int> s, h;
    for (int i = 1; i < 10; i++)
    {
        s.push(i * 10);
    }

    cout << s;

    s.pop();
    s.pop();
    cout << s;
    s.pop();
    cout << s;
    s.pop();
    cout << s;
    s.pop();
    s.pop();
    s.pop();

    cout << s;

    int z[10];
    for (int i = 1; i < 10; i++)
    {
        cout << "? " << i << ' ' << endl;
        z[i] = i;
    }
    h.initialize(z, 9);
    cout << h;
}