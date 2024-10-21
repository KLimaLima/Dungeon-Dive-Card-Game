#pragma once

class Stack
{
public:
    Stack(int cardTotal);
    ~Stack();
    void Push(int Value);
    int Pop();
    void Clear();
    void Display();
    int Peak();

private:
    int* Array;
    int MaxCapacity;
    int CurrentPosition;

};

