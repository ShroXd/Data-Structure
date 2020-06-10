#include <iostream>
#include "../chainQueue.h"

using namespace std;

int main()
{
    chainQueue<int> s;

    if (s.empty())
    {
        cout << "The queue is empty." << endl;
    }

    s.push(100);
    s.push(200);
    s.push(300);

    cout << s;

    s.pop();
    cout << s;

    cout << "The front of queue is: " << s.front() << endl;
    cout << "The back of queue is: " << s.back() << endl;
}