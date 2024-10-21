#include "Game.h"

//easy access to change values
string textTitlebar = "Dungeon Dive Card Game 0.03 - LimaLima Entertainment trademark";
int windowHeight = 900, windowLenght = 1800, frameLimit = 60;

Game::Game()
{
	//init window
	window = new RenderWindow(VideoMode(windowLenght, windowHeight), textTitlebar, Style::Titlebar | Style::Close);
	window->setFramerateLimit(frameLimit);

	//init logic stuff
	currentState = new State;
	eventListener = new Event;
	
	//first starts with stateHub
	*currentState = stateHub;
	initGame(); //for first time only -> next will be determined by initGame logic in .run THIS IS RIGHT PROB, DON'T CHANGE!!!
}

Game::~Game()
{
	delete window;
	delete currentState;
	delete eventListener;

	//No need check, deleting NULL is safe
	printf("Hubptr Destructor\n");
	delete Hubptr;
	printf("Playptr Destructor\n");
	delete Playptr;
	printf("Statsptr Destructor\n");
	delete Statsptr;
}

void Game::run()//NOTE: DON'T CLEAR AND DISPLAY HERE, DO IN RENDER
{
	while (window->isOpen()) {

		//update
		updateGame();

		//render
		renderGame();

		updateState();

		initGame();
	}
}

void Game::initGame() //CHECKS WHAT STATE IT'S IN AND DELETES UNUSED STATE(WITH ITS MEMBER F(X))
{
	switch (*currentState){
	case stateHub:
		if (Hubptr == NULL)	//NOTE: deleting a pointer will call the object's destructor its pointing
			Hubptr = new Hub;

		if (Playptr != NULL) {
			delete Playptr;		//NOTE: THIS F(X) REPEATS (BECAUSE OF .run) SO,
			Playptr = NULL;		//IT WILL EXECUTE delete MORE THAN ONCE WITHOUT SOME SORT OF GUARD <- will cause error
		}						//SET PTR TO NULL AFTER executing delete THEN GUARD
		if (Statsptr != NULL) {
			delete Statsptr;		//ALSO, CHECK IF ALREADY MADE A new object, IF NOT IT WILL MAKE MORE new object
			Statsptr = NULL;		//AND THERE WILL BE MEMORY LEAK
		}
		break;

	case statePlay:

		if (Hubptr != NULL)
			tempPlayerName = Hubptr->getName();

		if(Playptr == NULL)
			Playptr = new Play(*window, tempPlayerName);

		if (Hubptr != NULL) {
			delete Hubptr;
			Hubptr = NULL;
		}
		if (Statsptr != NULL) {
			delete Statsptr;
			Statsptr = NULL;
		}
		break;

	case stateStats:
		if(Statsptr == NULL)
			Statsptr = new Stats;

		if (Hubptr != NULL) {
			delete Hubptr;
			Hubptr = NULL;
		}
		if (Statsptr != NULL) {
			delete Playptr;
			Playptr = NULL;
		}
		break;
	}
}

void Game::updateGame() //TODO REMEBER TO REKEY KEYBOARD F(X)
{
	window->pollEvent(*eventListener); //polls event

	//Make game exit warning for Play State -DONE
	if (eventListener->type == Event::Closed && (*currentState == stateHub || *currentState == stateStats))
		window->close();
	
	if (eventListener->type == Event::Closed && *currentState == statePlay) {

		do {
			window->clear();
			Playptr->exitWarning();
			window->display();

			if (Keyboard::isKeyPressed(Keyboard::Escape))
				window->close();

		} while (!(Keyboard::isKeyPressed(Keyboard::Escape)) && !(Keyboard::isKeyPressed(Keyboard::B)) && window->isOpen());
	}

	//cout << Mouse::getPosition(*window).x << " " << Mouse::getPosition(*window).y << endl; //TEST

	mousePosition = Vector2f(Mouse::getPosition(*window));

	//if (Hubptr != NULL)
	//	tempPlayerName = Hubptr->getName();

	switch (*currentState) {
	case stateHub:
		Hubptr->updateHub(*eventListener, mousePosition);
		break;

	case statePlay:
		Playptr->updatePlay(*eventListener, mousePosition);
		break;

	case stateStats:
		Statsptr->updateStats(*eventListener, mousePosition);
		break;
	}
}

void Game::renderGame()
{
	window->clear();

	switch (*currentState) {
	case stateHub:
		Hubptr->renderHub(*window);
		break;
	case statePlay:
		Playptr->renderPlay();
		break;
	case stateStats:
		Statsptr->renderStats(*window);
		break;
	}

	window->display();
}

void Game::updateState()
{
	switch (*currentState) {
	case stateHub:
		*currentState = Hubptr->updateState();
		break;

	case stateStats:
		*currentState = Statsptr->updateState();
		break;

	case statePlay:
		*currentState = Playptr->updateState();
		break;
	}

}
