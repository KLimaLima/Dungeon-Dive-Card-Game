#pragma once

#include <fstream>
#include <iostream>

#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "Button.h"
#include "StateScript.h"
#include "TextPrompt.h"

using namespace sf;
using namespace std;

class Hub
{
public:
	Hub();
	~Hub();
	void updateHub(Event eventListener, Vector2f mousePosition);
	void renderHub(RenderTarget& windowGame);
	State updateState();
	string getName();

private:
	Texture* bgTexture;
	Sprite* bgSprite;
	Button* buttonPlay;
	Button* buttonStats;
	State changeToState;
	TextPrompt* playerNameInput;

	ifstream readFile;
	ofstream writeFile;

};

