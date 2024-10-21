#pragma once

#include <iostream>
#include <fstream>

#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "Hub.h"
#include "Play.h"
#include "Stats.h"
#include "StateScript.h"

using namespace sf;
using namespace std;

class Game
{
public:
	Game();
	~Game();
	void run();
	void initGame();
	void updateGame();
	void renderGame();
	void updateState();

private:
	RenderWindow* window;
	State* currentState;
	Event* eventListener;
	Vector2f mousePosition;
	Hub* Hubptr;
	Play* Playptr;
	Stats* Statsptr;
	ofstream writeFile;
	ifstream readFile;
	string tempPlayerName;

};

