#include <iostream>
#include "../chainDict.h"

using namespace std;

int main()
{
    chainDict<string, int> s;
    pair<string, int> p;

    p.first = "spike";
    p.second = 24;
    s.insert(p);

    p.first = "hesea";
    p.second = 26;
    s.insert(p);

    p.first = "Duch";
    p.second = 29;
    s.insert(p);

    cout << s;

    cout << "The age of spike is: " << s.find("spike")->second << endl;

    s.erase("spike");
    cout << s;
}