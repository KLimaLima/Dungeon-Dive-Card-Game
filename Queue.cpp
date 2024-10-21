#include "Queue.h"

int
Queue::Check(int index)
{
    if (Array[index].getId() != -1)
        return true;

    return false;
}

int Queue::getCardId(int index)
{
    return Array[index].getId();
}

int Queue::getCardHp()
{
    return Array[0].getCurrentHp();
}

int Queue::getAttack(int index)
{
    return Library.getAttack(Array[index].getId());
}

bool Queue::isFull()
{
    if (Count >= Arraysize)
        return true;
    else return false;
}

bool Queue::isEmpty()
{
    if (Count == 0)
        return true;
    else return false;
}

void Queue::renderCardQueue(RenderTarget& windowGame, float j, bool toLeft)
{

    if (toLeft) {

        for (int i = 0; i < Arraysize ; i++) {

            Array[i].setPosition(j, 50.f);
            Array[i].renderCardTexture(windowGame);

            j += 292.f;
        }
    }
    else {

        for (int i = 0; i < Arraysize ; i++) {

            Array[i].setPosition(j, 50.f);
            Array[i].renderCardTexture(windowGame);

            j -= 292.f;
        }
    }
}

void Queue::changeTexture()
{
    for (int i = 0; i < Arraysize; i++) {

        Array[i].changeTexture(Library.getpath(Array[i].getId()));
    }
}

void Queue::changeHp(int damageTaken)
{
    Array[0].setCurrentHp(Array[0].getCurrentHp() - damageTaken);
}

void
Queue::Remove()
{
    Array[0].setId(-1);

    for (int i = 1; i < Arraysize; i++) {
        
        Array[i - 1].setId(Array[i].getId()); //Array[i - 1] = Array[i];
        Array[i - 1].setCurrentHp(Array[i].getCurrentHp());
    }

    Array[Arraysize - 1].setId(-1);
    Array[Arraysize - 1].setCurrentHp(-1);

    changeTexture();

    Count--;

}

Queue::Queue(int Queuesize)
{
    Array = new Card[Queuesize];
    Arraysize = Queuesize;

    for (int i = 0; i < Arraysize; i++) {
        
        Array[i].setId(-1);
        Array[i].changeTexture(Library.getpath(Array[i].getId()));
        Array[i].setCurrentHp(Library.getHP(Array[i].getId()));
    }

    Count = 0;

    cout << "Queue creaeted!!!\n";

}

Queue::~Queue()
{
    delete[]Array;

    cout << "Dectruct!\n";
}

void
Queue::insert(int value)
{
    for (int i = 0; value != -1 && i < Arraysize && !(isFull()); i++) {

        if (Array[i].getId() == -1) {
            Array[i].setId(value);
            Array[i].setCurrentHp(Library.getHP(Array[i].getId()));
            Count++;
            break;
        }
    }

    changeTexture();
}
