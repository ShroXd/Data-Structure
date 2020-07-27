#include <iostream>
#include "../completeWinnerTree.h"
#include "../../lib/player.h"

using namespace std;

int main(void)
{
    int n = 5;
    player *thePlayer = new player[n + 1];
    for (int i = 1; i <= n; i++)
    {
        thePlayer[i].key = i;
        thePlayer[i].id = i;
    }

    completeWinnerTree<player> *w = new completeWinnerTree<player> (thePlayer, n);

    cout << "===================" << endl;
    w->output();
    cout << "===================" << endl;
}