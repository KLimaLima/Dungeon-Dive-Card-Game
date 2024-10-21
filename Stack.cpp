#include "Stack.h"

Stack::Stack(int cardTotal)
{
    Array = new int[cardTotal];
    MaxCapacity = cardTotal;
    CurrentPosition = -1;
//    cout << "Array created\n";
}

Stack::~Stack()
{
    delete[] Array;
//    cout << "Destruct!\n";
}

void Stack::Push(int Value)
{
    if (CurrentPosition < MaxCapacity - 1)
    {
        CurrentPosition++;
        Array[CurrentPosition] = Value;
    }
//    else
//        cout << "Stack Overflow\n";
}

int Stack::Pop()
{
    int Result;
    if (CurrentPosition >= 0)
    {
        Result = Array[CurrentPosition];
        CurrentPosition--;

        return Result;
    }
    else
        return -1;
}

void Stack::Clear()
{
    CurrentPosition = -1;
//    cout << "Stack Clear!\n";
}

void Stack::Display()//TEST
{
    int i;

    for (i = 0; i <= CurrentPosition; i++)
    {
//        cout << " index " << i << "   " << Array[i] << endl;
    }
}

int Stack::Peak()
{
    if (CurrentPosition == -1)
        return -1;
    else
        return Array[CurrentPosition];
}
