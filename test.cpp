#include <iostream>
#include "./lib/changeLength1D.h"

using namespace std;

int main()
{
    int *myOldArr = new int[10];

    for (int i = 0; i < 10; i++)
    {
        cout << myOldArr[i] << ' ';
    }
    cout << endl;

    try
    {
        changeLength1D(myOldArr, 10, -5);
    }
    catch(illegalParameterValue e)
    {
        e.outputMessage();
    }
    
    for (int i = 0; i < 5; i++)
    {
        cout << myOldArr[i] << ' ';
    }

}