#pragma once

#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include <Windows.h>
#include <fstream>

#include "Card.h"
#include "Stack.h"
#include "CardStatsLibrary.h"
#include "Button.h"
#include "Queue.h"
#include "StateScript.h"

using namespace sf;

class Play
{
public:
	Play(RenderTarget &windowGame, string PlayerNameGiven);
	~Play();
	State updateState();
	void updatePlay(Event &eventListener, Vector2f &mousePosition);
	void renderPlay();
	void exitWarning();
	void updateHp();
	void prepareState(Vector2f& mousePosition);
	void fightState();
	void gameLogic(Queue& attackingCard, Queue& attackedCard, int index, bool getPoint);

private:
	string PlayerName;

	Button* exitMessage;
	
	RenderTarget* windowGame;
	State changeToState;

	RectangleShape* hitbox_A;
	RectangleShape* hitbox_B;
	bool isClicked;
	bool isKeyPressed;

	Texture* bgTexture;
	Sprite* bgSprite;
	//Card* playerCard;

	Stack* stackCard_A;
	Card* renderStack_A;
	Stack* stackCard_B;
	Card* renderStack_B;

	Button* buttonActiveGame;
	//ActiveSpace* gameActiveSpace;
	bool isActiveCard;

	Queue* playerActiveCard;
	Queue* enemyActiveCard;
	Button* playerHp;
	Button* enemyHp;
	int points;
	Button* pointsBox;

	CardStatsLibrary *Library;

	ifstream readFile;
	ofstream writeFile;
};

