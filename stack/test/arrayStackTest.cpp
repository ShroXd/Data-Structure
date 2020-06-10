#include <iostream>
#include "../arrayStack.h"

using namespace std;

int main()
{
    arrayStack<int> s;

    if (s.empty())
    {
        cout << "s is empty" << endl;
    }
    
    s.push(100);
    s.push(200);
    s.push(300);

    cout << "Size of stack is: " << s.size() << endl;
    cout << "Top element of stack is: " << s.top() << endl;

    cout << s;
    s.pop();
    cout << s;

    if (!s.empty())
    {
        cout << "s is not empty" << endl;
    }
}