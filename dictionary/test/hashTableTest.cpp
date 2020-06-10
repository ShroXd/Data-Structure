#include <iostream>
#include "../hashTable.h"

using namespace std;

int main()
{
    hashTable<string, int> s;
    pair<string, int> p;

    p.first = "spike";
    p.second = 24;
    s.insert(p);

    p.first = "Hesea";
    p.second = 26;
    s.insert(p);

    p.first = "Duch";
    p.second = 26;
    s.insert(p);

    s.erase("spike");
    s.erase("Hesea");
    s.erase("Duch");
    cout << s;
}