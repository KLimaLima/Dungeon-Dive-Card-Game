 #pragma once

#include <iostream>
#include "Card.h"
#include "CardStatsLibrary.h"

using namespace std;

class Queue
{
public:
    Queue(int Queuesize);   //DONE
    ~Queue();               //DONE
    void Remove();          //DONE
    void insert(int value); //DONE
    //    void clear();
    //void display();         //JUST FOR TEST
    //int First();
    int Check(int index);
    int getCardId(int index);
    int getCardHp();
    int getAttack(int index);
    bool isFull();
    bool isEmpty();
    void renderCardQueue(RenderTarget& windowGame, float j, bool toLeft);
    void changeTexture();
    void changeHp(int damageTaken);

private:
    Card* Array;
    int Arraysize;
    int Count;
    CardStatsLibrary Library;
    //int Front;
    //int Rear;
};

