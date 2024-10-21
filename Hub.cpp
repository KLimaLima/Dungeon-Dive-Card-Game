#include "Hub.h"

Hub::Hub()
{
	bgTexture = new Texture;
	bgTexture->loadFromFile("Texture/IMG_7702.png");
	
	bgSprite = new Sprite;
	bgSprite->setTexture(*bgTexture);
	bgSprite->scale(1.41f, 1.25f);

	buttonPlay = new Button(Vector2f(260.f, 120.f), Color(70, 70, 70, 500), 800.f, 550.f, "Play", Color::White, 45.f);

	buttonStats = new Button(Vector2f(260.f, 120.f), Color(70, 70, 70, 500), 500.f, 550.f, "Stats", Color::White, 45.f);

	changeToState = stateHub;

	playerNameInput = new TextPrompt(500.f, 680.f, 10, false);

	/*
	MAKE IT ADD ANY NEW GAME DATA(DUMPGAMEDATA) TO LEADERBOARD FILE
	BY SORTING IT FIRTS THEN ADD
	REMEMBER TO ADD GUARD SO THAT IT DOES NOT READ AN EMPTY FILE
	*/

	printf("Hub init\n");
}

Hub::~Hub()
{
	delete bgTexture;
	delete bgSprite;
	delete buttonPlay;
	delete buttonStats;
	delete playerNameInput;
	printf("Hub Destructor\n");
}

void Hub::updateHub(Event eventListener, Vector2f mousePosition)
{
	buttonPlay->mouseHover(mousePosition, Color(70, 70, 70, 200));

	buttonStats->mouseHover(mousePosition, Color(70, 70, 70, 200));

	playerNameInput->updateTextPrompt(eventListener, mousePosition);

	if (buttonPlay->isClicked(mousePosition) && !(playerNameInput->isEmpty())) {

		//writeFile.open("dumpGameData.txt", ios::app);

		//writeFile << playerNameInput->getText() << endl;

		//writeFile.close();

		changeToState = statePlay;
	}
	else if (buttonStats->isClicked(mousePosition))
		changeToState = stateStats;
	//printf("Hub Update\n");
}

void Hub::renderHub(RenderTarget& windowGame)
{
	windowGame.draw(*bgSprite);
	buttonPlay->renderButton(windowGame);
	buttonStats->renderButton(windowGame);

	playerNameInput->renderTextPrompt(windowGame);

	//printf("Hub Render\n");
}

State Hub::updateState()
{
	return changeToState;
}

string Hub::getName()
{
	return playerNameInput->getText();
}

