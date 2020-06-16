#include <iostream>
#include "../maxHblt.h"

using namespace std;

int main(void)
{
    maxHblt<int> h, j;

    h.push(10);
    h.push(20);
    h.push(30);
    h.push(5);
    h.preOrderOutput();
}