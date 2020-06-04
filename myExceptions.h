#ifndef myExceptions_
#define myExceptions_
#include <string>

using namespace std;

class illegalParameterValue
{
public:
    illegalParameterValue(string theMessage = "Illegal parameter value")
    {
        message = theMessage;
    }
    void outputMessage()
    {
        cout << message << endl;
    }

private:
    string message;
};

class stackEmpty
{
public:
    stackEmpty(string theMessage = "stack is empty")
    {
        message = theMessage;
    }
    void outputMessage()
    {
        cout << message << endl;
    }

private:
    string message;
};

class queueEmpty
{
public:
    queueEmpty(string theMessage = "stack is empty")
    {
        message = theMessage;
    }
    void outputMessage()
    {
        cout << message << endl;
    }

private:
    string message;
};

class hashTableFull
{
public:
    hashTableFull(string theMessage = "hash table is full")
    {
        message = theMessage;
    }
    void outputMessage()
    {
        cout << message << endl;
    }

private:
    string message;
};

class hashTableElementEmpty
{
public:
    hashTableElementEmpty(string theMessage = "the hash table element is empty")
    {
        message = theMessage;
    }
    void outputMessage()
    {
        cout << message << endl;
    }

private:
    string message;
};

#endif