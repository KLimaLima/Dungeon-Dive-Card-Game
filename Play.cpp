#include "Play.h"

Play::Play(RenderTarget& addressWindowGame, string PlayerNameGiven)
{
	PlayerName = PlayerNameGiven;

	windowGame = &addressWindowGame;
	changeToState = statePlay;

	/*-------------------Init Background----------------------------------------------------------------------------------------*/
	bgTexture = new Texture;
	bgTexture->loadFromFile("Texture/S_MATCH_GAME_CARD.png"); //BACKGROUND
	bgSprite = new Sprite;
	bgSprite->setTexture(*bgTexture);
	bgSprite->scale(1.45f, 1.3f); //BACKGROUND

	/*-------------------Init hitbox----------------------------------------------------------------------------------------*/
	hitbox_A = new RectangleShape;
	hitbox_A->setSize(Vector2f(276.f, 384.f));//Make it so it is init when it is top only by asking/calling f(x)
//	hitbox_A->setFillColor(Color::Magenta);//TEST
	hitbox_A->setFillColor(Color::Transparent);
	hitbox_A->setPosition(28.f, 490.f); //HITBOX A DEKAT KIRI

	hitbox_B = new RectangleShape;
	hitbox_B->setSize(Vector2f(276.f, 384.f));//Make it so it is init when it is top only by asking/calling f(x)
//	hitbox_B->setFillColor(Color::Magenta);//TEST
	hitbox_B->setFillColor(Color::Transparent);
	hitbox_B->setPosition(320.f, 490.f); //HITBOX B DEKAT KANAN

	/*-------------------Init bool----------------------------------------------------------------------------------------*/
	isClicked = false; //INIT BOOL
	isKeyPressed = false;
	//isClicked_B = false;

	exitMessage = new Button(Vector2f(1200.f, 300.f), Color::Red, 300.f, 300.f,
		"Are you sure you want to exit?\n\nGame will not be saved\n\nPress B to continue playing or\n\npress escape to exit game", Color::White, 35.f);
	//exitMessage->setSize(Vector2f(100.f, 100.f));
	//exitMessage->setFillColor(Color::Red);

	//playerCard = new Card;

	/*-------------------Init Library----------------------------------------------------------------------------------------*/
	Library = new CardStatsLibrary;

	/*-------------------Init stack of cards----------------------------------------------------------------------------------------*/
	stackCard_A = new Stack(15);
	for (int i = 0; i < 15; i++)	//TODO
		stackCard_A->Push(i);		//NANTI TUKAR UTK ADA NO CARD TEXTURE DI STACK B UTK STARTING SAJA
									//DAN  UTK BILA DAH HABIS AKA -1 DONE
	stackCard_B = new Stack(15);

	renderStack_A = new Card;
	renderStack_B = new Card;

	renderStack_A->setPosition(28.f, 490.f);
	renderStack_B->setPosition(320.f, 490.f);

	renderStack_A->changeTexture(Library->getpath(stackCard_A->Peak())); //make a class (that holds all data) that returns string
	renderStack_B->changeTexture(Library->getpath(stackCard_B->Peak())); //make a class (that holds all data) that returns string
	//YG ATAS NI BETUL DAH

	/*-------------------Init Acitve Space----------------------------------------------------------------------------------------*/

	//gameActiveSpace = new ActiveSpace;
	buttonActiveGame = new Button(Vector2f(260.f, 120.f), Color(0, 255, 0, 500), 700.f, 750.f, "End Turn", Color::White, 35.f);
	isActiveCard = false;

	playerActiveCard = new Queue(3);
	enemyActiveCard = new Queue(3);

	playerHp = new Button(Vector2f(200.f, 100.f), Color(255, 51, 51, 500), 620.f, 480.f, "Hp: ", Color::White, 35.f);

	enemyHp = new Button(Vector2f(400.f, 100.f), Color(0, 0, 0, 500), 920.f, 480.f, "Enemy Hp: ", Color::White, 35.f);

	//points = new int;
	points = 0;

	pointsBox = new Button(Vector2f(320.f, 120.f), Color(0, 0, 0, 500), 1000.f, 750.f, "Points: ", Color::White, 35.f);

	/*-------------------Generate random seed----------------------------------------------------------------------------------------*/
	srand((unsigned int)time(NULL));

	printf("Play init\n");
}

Play::~Play()	//TODO Check semua dah delete tak
{
	delete exitMessage;

//	delete windowGame;

	delete hitbox_A;
	delete hitbox_B;
	delete bgTexture;
	delete bgSprite;
	delete stackCard_A;
	delete stackCard_B;
	delete renderStack_A;
	delete renderStack_B;

	delete buttonActiveGame;
	delete playerActiveCard;
	delete enemyActiveCard;
	delete playerHp;
	delete enemyHp;
	delete pointsBox;
	delete Library;
	printf("Play Destructor\n");
}

State Play::updateState()
{
	return changeToState;
}

void Play::updatePlay(Event &eventListener, Vector2f &mousePosition)
{

	if (stackCard_A->Peak() == -1 && stackCard_B->Peak() == -1 && playerActiveCard->isEmpty() && !isActiveCard) {

		Sleep(2000);

		writeFile.open("dumpGameData.txt", ios::app);

		writeFile << PlayerName << endl << points << endl;

		writeFile.close();

		//isFinishedIndicator = true;

		changeToState = stateHub;
	}
	else if (!isActiveCard)
		prepareState(mousePosition);
	else
		fightState();
}

void Play::renderPlay() //THIS IS RENDERING EVERYTHING
{
	windowGame->draw(*bgSprite);//BACKGORUND

	renderStack_A->renderCardTexture(*windowGame);//STACK OF CARDS
	renderStack_B->renderCardTexture(*windowGame);//STACK OF CARDS

	playerActiveCard->renderCardQueue(*windowGame, 612.f, false);

	enemyActiveCard->renderCardQueue(*windowGame, 912.f, true);

	buttonActiveGame->renderButton(*windowGame);

	playerHp->renderButton(*windowGame);
	enemyHp->renderButton(*windowGame);

	windowGame->draw(*hitbox_A);//INVISIBLE HITBOX
	windowGame->draw(*hitbox_B);//INVISIBLE HITBOX

	pointsBox->renderButton(*windowGame);

	//playerCard->renderCardTexture(windowGame);
	//printf("Play Render\n");
}

void Play::exitWarning() //EXIT WARNING
{
	renderPlay();
	exitMessage->renderButton(*windowGame);
	printf("Play: Exit Warning\n");
}

void Play::updateHp()
{
	string textHp;

	textHp = to_string(playerActiveCard->getCardHp());
	playerHp->addText(textHp);

	//cout << textHp << endl;

	textHp = to_string(enemyActiveCard->getCardHp());
	enemyHp->addText(textHp);

	//cout << textHp << endl;

}

void Play::prepareState(Vector2f& mousePosition)
{
	hitbox_A->setPosition(28.f, 490.f); //HITBOX A DEKAT KIRI
	hitbox_A->setFillColor(Color::Transparent);
	hitbox_B->setPosition(320.f, 490.f); //HITBOX B DEKAT KANAN
	hitbox_B->setFillColor(Color::Transparent);

	//cout << points << endl;


		/*-------------------Navigate thorugh card the stack of cards----------------------------------------------------------------------------------------*/
	if (Keyboard::isKeyPressed(Keyboard::Right) && stackCard_A->Peak() != -1) {
		stackCard_B->Push(stackCard_A->Pop());
		//cout << Library->getpath(stackCard_A->Peak()) << endl;//TEST
		renderStack_A->changeTexture(Library->getpath(stackCard_A->Peak()));
		//cout << Library->getpath(stackCard_B->Peak());//TEST
		renderStack_B->changeTexture(Library->getpath(stackCard_B->Peak()));

		////TEST
		//static int test = 0;
		//playerActiveCard->insert(test);
		//test++;

		////TEST
		//enemyActiveCard->insert(test);
		//test++;
//		playerActiveCard->changeTexture

		printf("right\n");
	}
	else if (Keyboard::isKeyPressed(Keyboard::Left) && stackCard_B->Peak() != -1) {
		//cout << Library->getpath(stackCard_A->Peak());//TEST
		stackCard_A->Push(stackCard_B->Pop());
		renderStack_A->changeTexture(Library->getpath(stackCard_A->Peak()));
		//cout << Library->getpath(stackCard_B->Peak());//TEST
		renderStack_B->changeTexture(Library->getpath(stackCard_B->Peak()));
	}
	/*-------------------Get user input if clicked LMB on either stack of card------------------------------------------------------------------------*/

	if (hitbox_A->getGlobalBounds().contains(mousePosition) && Mouse::isButtonPressed(Mouse::Left) && !isClicked) {

		if (!(playerActiveCard->isFull())) {

			playerActiveCard->insert(stackCard_A->Pop());
			renderStack_A->changeTexture(Library->getpath(stackCard_A->Peak()));
		}

		isClicked = true;
		printf("hitbox A\n");
	}
	else if (hitbox_B->getGlobalBounds().contains(mousePosition) && Mouse::isButtonPressed(Mouse::Left) && !isClicked) {

		if (!(playerActiveCard->isFull())) {

			playerActiveCard->insert(stackCard_B->Pop());
			renderStack_B->changeTexture(Library->getpath(stackCard_B->Peak()));
		}

		isClicked = true;
		printf("hitbox B\n");
	}
	else if (buttonActiveGame->isClicked(mousePosition) && !(playerActiveCard->isEmpty()) && !isClicked) {

		/*-------------------GAME LOGIC START------------------------------------------------------------------------------------------*/
		//TODO make so that if there is no playerActiveCard it will not execute DONE
		//TODO Finish fighting sequence
		//TODO DISPLAY POINTS

		isActiveCard = true;

		/*-------------------GAME LOGIC END------------------------------------------------------------------------------------------*/
		isClicked = true;
		printf("Not out yet\n");
		//Sleep(6000);

	}


	/*-------------------GUARD: Avoid taking hold LMB as input------------------------------------------------------------------------------------------*/
	if (!(Mouse::isButtonPressed(Mouse::Left))) //Act as guard so that holding does not affect input
		isClicked = false;

	/*-------------------Mouse Hover------------------------------------------------------------------------------------------*/
	if (playerActiveCard->isEmpty())
		buttonActiveGame->mouseHover(Vector2f(800.f, 800.f), Color(70, 70, 70, 200));
	else
		buttonActiveGame->mouseHover(mousePosition, Color(70, 70, 70, 200));

	/*-------------------Real time update hp------------------------------------------------------------------------------------------*/

	updateHp();

	/*-------------------Randomize enemy generation------------------------------------------------------------------------------------------*/
	if (!(enemyActiveCard->isFull()))
		enemyActiveCard->insert(15 + (std::rand() % (24 - 15 + 1)));	//rand is to get random number

	//playerCard->update(mousePosition, 1, 1);
	//printf("Play Update\n");

}

void Play::fightState()
{
	int static actionFinishedCounter = 0;

	hitbox_A->setPosition(612.f, 50.f); //HITBOX A reused as hit indicator
	hitbox_B->setPosition(912.f, 50.f); //HITBOX B reused as hit indicator


	switch (actionFinishedCounter) {

	case 0:
		gameLogic(*playerActiveCard, *enemyActiveCard, 0, true);	//This is always true since in prepare already guard only if there is card will execute
		updateHp();
		hitbox_B->setFillColor(Color::Red);


		renderPlay();

		printf("player attcked\n");
		actionFinishedCounter++;

		break;

	case 1:

		Sleep(200);

		hitbox_B->setFillColor(Color::Transparent);
		renderPlay();

		actionFinishedCounter++;

		break;

	case 2:

		Sleep(200);

		if (playerActiveCard->Check(1)) {

			gameLogic(*playerActiveCard, *enemyActiveCard, 1, true);
			updateHp();
			hitbox_B->setFillColor(Color::Red);
			renderPlay();
		}



		printf("player attcked\n");
		actionFinishedCounter++;

		break;

	case 3:

		Sleep(200);

		hitbox_B->setFillColor(Color::Transparent);
		renderPlay();

		actionFinishedCounter++;

		break;

	case 4:
		
		Sleep(200);

		if (playerActiveCard->Check(2)) {

			gameLogic(*playerActiveCard, *enemyActiveCard, 2, true);
			updateHp();
			hitbox_B->setFillColor(Color::Red);
			renderPlay();
		}

		printf("player attcked\n");
		actionFinishedCounter++;

		break;

	case 5:

		Sleep(200);

		hitbox_B->setFillColor(Color::Transparent);
		renderPlay();

		actionFinishedCounter++;

		break;

	case 6:

		Sleep(200);

		if (enemyActiveCard->Check(0) && !(playerActiveCard->isEmpty())) {

			printf("enemy starting attack\n");
			gameLogic(*enemyActiveCard, *playerActiveCard, 0, false);
			updateHp();
			hitbox_A->setFillColor(Color::Red);
			renderPlay();
			printf("enemy attacked\n");
		}



		actionFinishedCounter++;

		break;

	case 7:

		Sleep(200);

		hitbox_A->setFillColor(Color::Transparent);
		renderPlay();

		actionFinishedCounter++;

		break;

	case 8:

		Sleep(200);

		if (enemyActiveCard->Check(1) && !(playerActiveCard->isEmpty())) {

			printf("enemy starting attack\n");
			gameLogic(*enemyActiveCard, *playerActiveCard, 1, false);
			updateHp();
			hitbox_A->setFillColor(Color::Red);
			renderPlay();
			printf("enemy attacked\n");
		}



		actionFinishedCounter++;

		break;

	case 9:

		Sleep(200);

		hitbox_A->setFillColor(Color::Transparent);
		renderPlay();

		actionFinishedCounter++;

		break;

	case 10:

		Sleep(200);

		if (enemyActiveCard->Check(2) && !(playerActiveCard->isEmpty())) {

			printf("enemy starting attack\n");
			gameLogic(*enemyActiveCard, *playerActiveCard, 2, false);
			updateHp();
			hitbox_A->setFillColor(Color::Red);
			renderPlay();
			printf("enemy attacked\n");
		}

		actionFinishedCounter++;

		break;

	case 11:


		Sleep(200);

		hitbox_A->setFillColor(Color::Transparent);
		renderPlay();

		actionFinishedCounter = 0;	//since static so reset to zero
		isActiveCard = false;	//BASICALLY REDIRECTS BACK TO PREPARE STATE
		break;
	}


}

void Play::gameLogic(Queue& attackingCard, Queue& attackedCard, int index, bool getPoint)	//MAKE POINT SYSTEM
{
	if (attackingCard.getAttack(index) >= attackedCard.getCardHp())
		attackedCard.Remove();
	else {

		attackedCard.changeHp(attackingCard.getAttack(index));

		if (attackedCard.getCardHp() <= 0)
			attackedCard.Remove();
		else getPoint = false;
	}

	if (getPoint) {

		string pointsString;

		points++;

		pointsString = to_string(points);
		pointsBox->addText(pointsString);
	}
}
