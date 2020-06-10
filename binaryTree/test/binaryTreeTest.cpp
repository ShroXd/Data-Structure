#include <iostream>
#include "../linkedBinaryTree.h"

using namespace std;

int main()
{
    linkedBinaryTree<int> x, y, z, leave;

    x.makeTree(1, leave, leave);
    y.makeTree(2, x, leave);
    z.makeTree(3, x, y);

    z.preOrderOutput();     // 3 2 1
}