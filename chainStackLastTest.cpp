#include <iostream>
#include "./stack/chainStackLast.h"

using namespace std;

int main()
{
    chainStack<int> s;

    if (s.empty())
    {
        cout << "The stack is empty." << endl;
    }

    s.push(100);
    s.push(200);
    s.push(300);
    cout << s;

    s.pop();
    cout << s;

    cout << "The top element of stack is: " << s.top() << endl;
    
}