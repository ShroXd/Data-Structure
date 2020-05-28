#include <iostream>
#include "./stack/arrayStack.h"

using namespace std;

int main()
{
    arrayStack<int> s;

    s.push(100);
    s.push(200);
    s.push(300);

    cout << s << endl;

    s.pop();
    cout << s << endl;

    cout << s.top();
}