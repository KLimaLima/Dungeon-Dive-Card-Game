#pragma once

#include <iostream>

#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "Button.h"
#include "StateScript.h"
#include "TextPrompt.h"

#include <fstream>
#include <sstream>
#include <iomanip>

using namespace sf;

struct PlayerStats {
	string name = "-         ";
	int points = 0;
};

class Stats
{
public:
	Stats();
	~Stats();
	void updateStats(Event eventListener, Vector2f mousePosition);
	void renderStats(RenderTarget &windowGame);
	State updateState();
	void displayLeaderboard(int startingPoint);
	void SortingLeaderboard(int NumberOfPlayer);
	int SearchingStartingIndex(int searchForThis);
	void CustomSort(int startingIndex, int searchForThis);

private:
	Texture* bgTexture;
	Sprite* bgSprite;
	Button* buttonHub;
	State changeToState;
	Button* buttonNext;
	Button* buttonPrevious;
	Button* buttonFilter;

	Button* displayStats;

	ifstream readFile;
	PlayerStats* arrayList;

	TextPrompt* numberInput;

	stringstream* leaderboardStream;

	bool pageLeaderboard;
	int page;
	int pageLimit;
	bool mouseHold;

	bool normalSort;
	int SearchThisvalue = 0;
};

