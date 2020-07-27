#ifndef winnerTree_
#define winnerTree_

using namespace std;

template <class T>
class winnerTree
{
public:
    virtual ~winnerTree() {}
    virtual void initialize(T *thePlayer, int theNumberOfPlayers) = 0;
    virtual int winner() const = 0;
    virtual void rePlay(int thePlayer) = 0;
};

#endif