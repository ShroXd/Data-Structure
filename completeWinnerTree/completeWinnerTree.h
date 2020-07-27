#ifndef completeWinnerTree_
#define completeWinnerTree_

#include <iostream>
#include "../virtualClass/winnerTree.h"
#include "../lib/myExceptions.h"

template <class T>
class completeWinnerTree : public winnerTree<T>
{
private:
    int lowExt; // 该子树最底层外部节点的个数
    int offset;
    int *tree;
    int numberOfPlayers;
    T *player;
    void play(int, int, int);

public:
    completeWinnerTree(T *thePlayer, int theNumberOfPlayers)
    {
        tree = NULL;
        initialize(thePlayer, theNumberOfPlayers);
    }
    ~completeWinnerTree()
    {
        delete[] tree;
    }
    void initialize(T *, int);
    int winner() const
    {
        return tree[1];
    }
    int winner(int i) const
    {
        return (i < numberOfPlayers) ? tree[i] : 0;
    }
    void rePlay(int);
    void output() const;
};

template <class T>
void completeWinnerTree<T>::initialize(T *thePlayer, int theNumberOfPlayers)
{
    int n = theNumberOfPlayers;
    if (n < 2)
    {
        throw illegalParameterValue("nust have at least 2 players");
    }

    player = thePlayer;
    numberOfPlayers = n;
    delete[] tree;
    tree = new int[n];

    // s: 最底层最左端内部节点的编号
    // s * 2 为其可能存在的左孩子编号
    // n - 1 是内部节点个数
    int i, s;
    for (s = 1; 2 * s <= n - 1; s += s)
        ;

    // 最底层内部节点的个数： n - s
    lowExt = 2 * (n - s);
    offset = 2 * s - 1;

    for (i = 2; i <= lowExt; i += 2)
    {
        // (i + offset) / 2     父节点
        play((i + offset) / 2, i - 1, i);
    }

    // 左子树
    if (n % 2 == 1)
    {
        // 整数除法自动去掉小数位
        play(n / 2, tree[n - 1], lowExt + 1);
        i = lowExt + 3;
    }
    else
    {
        i = lowExt + 2;
    }

    // 倒数第二层右端外部节点
    for (; i <= n; i += 2)
    {
        play((i - lowExt + n - 1) / 2, i - 1, i);
    }
}

template <class T>
void completeWinnerTree<T>::play(int p, int leftChild, int rightChild)
{
    tree[p] = (player[leftChild] <= player[rightChild]) ? leftChild : rightChild;

    while (p % 2 == 1 && p > 1)
    {
        tree[p / 2] = (player[tree[p - 1]] <= player[tree[p]]) ? tree[p - 1] : tree[p];

        p /= 2;
    }
}

template <class T>
void completeWinnerTree<T>::rePlay(int thePlayer)
{
    int n = numberOfPlayers;
    if (thePlayer <= 0 || thePlayer > n)
    {
        throw illegalParameterValue("Player index is illegal");
    }

    int matchNode, // node where next match is to be played
        leftChild,
        rightChild;

    // 寻找到选定玩家对应的比赛
    if (thePlayer <= lowExt)
    {
        matchNode = (thePlayer + offset) / 2;
        leftChild = 2 * matchNode - offset;
        rightChild = leftChild + 1;
    }
    else
    {
        matchNode = (thePlayer - lowExt + n - 1) / 2;
        if (2 * matchNode == n - 1)
        {
            leftChild = tree[2 * matchNode];
            rightChild = thePlayer;
        }
        else
        {
            leftChild = 2 * matchNode - n + 1 + lowExt;
            rightChild = leftChild + 1;
        }
    }

    tree[matchNode] = (player[leftChild] <= player[rightChild])
                          ? leftChild
                          : rightChild;

    if (matchNode == n - 1 && n % 2 == 1)
    {
        matchNode /= 2;
        tree[matchNode] = (player[tree[n - 1]] <= player[lowExt + 1])
                              ? tree[n - 1]
                              : lowExt + 1;
    }

    matchNode /= 2;
    for (; matchNode >= 1; matchNode /= 2)
    {
        tree[matchNode] = (player[tree[2 * matchNode]] <= player[tree[2 * matchNode + 1]])
                              ? tree[2 * matchNode]
                              : tree[2 * matchNode + 1];
    }
}

template <class T>
void completeWinnerTree<T>::output() const
{
    cout << "number of players = " << numberOfPlayers
         << "   lowExt = " << lowExt
         << "   offset = " << offset << endl;
    cout << "complete winner tree pointers are" << endl;
    for (int i = 1; i < numberOfPlayers; i++)
    {
        cout << i << ":" << tree[i] << ' ';
    }
    cout << endl;
}

#endif