#include <iostream>
#include "../maxHeap.h"

using namespace std;

int main()
{
    maxHeap<int> s;
    s.push(10);
    s.push(20);
    s.push(30);

    cout << s;
}