#include <iostream>
#include "./queue/arrayQueue.h"

using namespace std;

int main()
{
    arrayQueue<int> s(2);

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