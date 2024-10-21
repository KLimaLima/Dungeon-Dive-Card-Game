#pragma once

#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>
using namespace std;
using namespace sf;

class Card
{
public:
	Card();
	~Card();
	void update(Vector2f& mousePosition, float xPosition, float yPosition);
	void renderCardTexture(RenderTarget& windowGame);
	void moveHere(float xPosition, float yPosition);
	void changeTexture(string fileLocation);
	void setPosition(float xPosition, float yPosition);
	void setId(int changeTo);
	int getId();
	void setCurrentHp(int valueHp);
	int getCurrentHp();

private:
	Texture* texture;
	Sprite* sprite;
	bool isMoving;

	int id;
	int currentHp;


};

