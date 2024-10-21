#include "Card.h"

Card::Card()
{
	texture = new Texture;

	sprite = new Sprite;
	sprite->scale(0.3f, 0.3f);

	printf("init Card\n");

	isMoving = false;

	id = -1;
	currentHp = -1;
}

Card::~Card()
{
	delete texture;
	delete sprite;
}

void Card::update(Vector2f &mousePosition, float xPosition, float yPosition)
{
}

void Card::renderCardTexture(RenderTarget &windowGame) //REMIDER use set position
{
	windowGame.draw(*sprite);
	//printf("Render Card\n");
}

void Card::moveHere(float xPosition, float yPosition)		//Upgrade for better moving
{
	if (sprite->getPosition().x == 300.f || sprite->getPosition().y == 300.f)
		//isMoving = false;

	if(sprite->getPosition().x <= 300.f || sprite->getPosition().y <= 300.f)
		sprite->move(12.f, 12.f);

	if (sprite->getPosition().x > 300.f || sprite->getPosition().y > 300.f)
		sprite->move(-1.f, -1.f);

	printf("move\n");

}

void Card::changeTexture(string fileLocation)
{
	texture->loadFromFile(fileLocation);
	sprite->setTexture(*texture);
}

void Card::setPosition(float xPosition, float yPosition)
{
	sprite->setPosition(xPosition, yPosition);
}

void Card::setId(int changeTo)
{
	id = changeTo;
}

int Card::getId()
{
	return id;
}

void Card::setCurrentHp(int valueHp)
{
	currentHp = valueHp;
}

int Card::getCurrentHp()
{
	return currentHp;
}

