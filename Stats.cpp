 #include "Stats.h"

Stats::Stats()
{
	bgTexture = new Texture;
	bgTexture->loadFromFile("Texture/S_LEADERBOARD_CARD_GAME.png");

	bgSprite = new Sprite;
	bgSprite->setTexture(*bgTexture);
	bgSprite->scale(1.45f, 1.25f);

	buttonHub = new Button(Vector2f(180.f, 100.f), Color(70, 70, 70, 500), 42.f, 56.f, "Back", Color::White, 30.f);

	buttonNext = new Button(Vector2f(180.f, 100.f), Color(70, 70, 70, 500), 508.f, 56.f, "Prev", Color::White, 30.f);

	buttonPrevious = new Button(Vector2f(180.f, 100.f), Color(70, 70, 70, 500), 708.f, 56.f, "Next", Color::White, 30.f);

	buttonFilter = new Button(Vector2f(180.f, 100.f), Color::Red, 908.f, 56.f, "Find", Color::White, 30.f);

	numberInput = new TextPrompt(1108.f, 56.f, 2, true);

	readFile.open("dumpGameData.txt", ios::in);

	int countLine = 0; char tempChar[20];
	while (!(readFile.eof())) {
		printf("counting\n");
		readFile.getline(tempChar, 20);
		countLine++;
	}

	readFile.close();

	countLine--;	//since eof will be more one than actual

	int listLimit = countLine / 2;

	while (listLimit % 12 != 0 || listLimit == 0) //genapkan jadi 12 - utk buat setiap page ada list
		listLimit++;

	pageLimit = listLimit / 12;

	cout << countLine / 2 << endl << listLimit << endl;	//TEST

	arrayList = new PlayerStats[listLimit];

	readFile.open("dumpGameData.txt", ios::in);

	char tempName[20], tempPoints[3];

	for (int j = 0; j < (countLine / 2); j++) {
		printf("assigning\n");

		readFile.getline(tempName, 20);

		arrayList[j].name = tempName;

		//readFile.getline(arrayList[j].name, 20);

		readFile.getline(tempPoints, 3);

		//tempPointsString = tempPoints;

		arrayList[j].points = stoi(tempPoints);

		//readFile.getline(arrayList[j].points, 20);
	}

	readFile.close();

	SortingLeaderboard(listLimit);

	/*----------------------------TEST ONLY---------------------------------------------------------------------------------------*/
	for (int i = 0; i < listLimit; i++) {

		cout << "index " << i << "\t" << arrayList[i].name << " - " << arrayList[i].points << endl; //TEST
	}
	/*----------------------------TEST ONLY---------------------------------------------------------------------------------------*/

	displayStats = new Button(Vector2f(1720.f, 580.f), Color::Transparent, 42.f, 300.f, "", Color::Black, 30.f);

	leaderboardStream = new stringstream;

	pageLeaderboard = true;
	page = 0;
	mouseHold = false;

	normalSort = true;

	changeToState = stateStats;

	printf("Stats init\n");
}

Stats::~Stats()
{
	delete bgTexture;
	delete bgSprite;
	delete buttonHub;
	delete buttonNext;
	delete buttonPrevious;
	delete buttonFilter;
	delete displayStats;
	delete[]arrayList;
	delete numberInput;
	delete leaderboardStream;

	printf("Stats Destructor\n");
}

void Stats::updateStats(Event eventListener, Vector2f mousePosition)
{
	numberInput->updateTextPrompt(eventListener, mousePosition);

	if (normalSort && pageLeaderboard) {

		SortingLeaderboard(pageLimit * 12);
	}
	else if (!normalSort && pageLeaderboard && !(numberInput->isEmpty())) {

		//SortingLeaderboard(pageLimit * 12);

		CustomSort(SearchingStartingIndex(stoi(numberInput->getText())), stoi(numberInput->getText()));

		cout << "Finding!\n";
		//CustomSort(SearchingStartingIndex(12), 12);
	}

	buttonHub->mouseHover(mousePosition, Color(70, 70, 70, 200));

	buttonNext->mouseHover(mousePosition, Color(70, 70, 70, 200));

	buttonPrevious->mouseHover(mousePosition, Color(70, 70, 70, 200));

	//buttonFilter->mouseHover(mousePosition, Color(70, 70, 70, 200));

	if (pageLeaderboard) {

		displayLeaderboard(page);
		
		pageLeaderboard = false;
	}

	if (buttonHub->isClicked(mousePosition))
		changeToState = stateHub;

	if (buttonNext->isClicked(mousePosition) && !mouseHold) {

		if (page < pageLimit - 1)
			page++;

		pageLeaderboard = true;
		mouseHold = true;

	}
	else if (buttonPrevious->isClicked(mousePosition) && !mouseHold) {
		
		if (page > 0)
			page--;

		pageLeaderboard = true;
		mouseHold = true;
	}

	if (buttonFilter->isClicked(mousePosition) && !mouseHold) {

		if (normalSort)
			normalSort = false;
		else if (!normalSort)
			normalSort = true;

		if (normalSort)
			buttonFilter->changeBoxColor(Color::Red);
		else if (!normalSort)
			buttonFilter->changeBoxColor(Color::Green);

		pageLeaderboard = true;

		mouseHold = true;
	}

	if (!(Mouse::isButtonPressed(Mouse::Left))) //JUST TO GUARD hold input aka not take hold mouse as input
		mouseHold = false;
	//printf("Stats Update\n");
}

void Stats::renderStats(RenderTarget& windowGame)
{
	windowGame.draw(*bgSprite);
	buttonHub->renderButton(windowGame);
	buttonNext->renderButton(windowGame);
	buttonPrevious->renderButton(windowGame);
	displayStats->renderButton(windowGame);

	buttonFilter->renderButton(windowGame);
	numberInput->renderTextPrompt(windowGame);
	//printf("Stats Render\n");
}

State Stats::updateState()
{
	return changeToState;
}

void Stats::displayLeaderboard(int startingPoint)
{
	if (leaderboardStream != NULL)
		delete leaderboardStream;

	leaderboardStream = new stringstream;

	string tempName; int tempPoints;

	startingPoint *= 12;

	for (int i = 0; startingPoint + i < (startingPoint + 6); i++) {

		tempName = arrayList[startingPoint + i].name;
		tempPoints = arrayList[startingPoint + i].points;
		*leaderboardStream << "Name: " << tempName << "\tPoints: " << tempPoints << setw(12);	//LEFT COLUMN

		tempName = arrayList[startingPoint + i + 6].name;
		tempPoints = arrayList[startingPoint + i + 6].points;
		*leaderboardStream << "Name: " << tempName << "\tPoints: " << tempPoints << "\n\n\n";	//RIGHT COLUMN

	}

	displayStats->changeText(leaderboardStream->str());
}

void Stats::SortingLeaderboard(int NumberOfPlayer) //Bubble Sort
{
	int tempPoints; string tempName;

	for (int i = 0; i < NumberOfPlayer; i++)
		for (int j = 1; j < NumberOfPlayer; j++)
		{
			if (arrayList[j].points > arrayList[j - 1].points)
			{
				tempPoints = arrayList[j].points;
				tempName = arrayList[j].name;

				arrayList[j].points = arrayList[j - 1].points;
				arrayList[j].name = arrayList[j - 1].name;

				arrayList[j - 1].points = tempPoints;
				arrayList[j - 1].name = tempName;
			}
		}
}

int Stats::SearchingStartingIndex(int searchForThis)
{
	int indexMax = pageLimit * 12, indexMin = 0, indexMiddle = (indexMax + indexMin) / 2, iterateThisMuch = 0;

	cout << indexMax << endl << indexMiddle << endl;

	for (int tempIterate = indexMax; tempIterate > 0; iterateThisMuch++) { //How many times to divide by two to not get anything anymore

		tempIterate /= 2;
	}

	cout << arrayList[indexMiddle].points << endl;

	for (int i = 0; arrayList[indexMiddle].points != searchForThis && i < iterateThisMuch - 1; i++) {

		if (arrayList[indexMiddle].points > searchForThis) {
			
			cout << arrayList[indexMiddle].points << "|" << searchForThis << endl;

			indexMin = indexMiddle;
			indexMiddle = (indexMax + indexMin) / 2;
		}
		else if (arrayList[indexMiddle].points < searchForThis) {

			cout << arrayList[indexMiddle].points << "|" << searchForThis << endl;

			indexMax = indexMiddle;
			indexMiddle = (indexMax + indexMin) / 2;
		}

	}

	cout << "After binary search\t" << indexMiddle << endl;


	if (arrayList[indexMiddle].points != searchForThis) {

		int i = indexMiddle + 1;
		if (arrayList[i].points == searchForThis)
			indexMiddle = i;
		else
			indexMiddle = -1;

		cout << arrayList[indexMiddle].points << "|" << searchForThis << endl;

		cout << "If not found check ahead\t" << indexMiddle << endl;
	}
	else if (arrayList[indexMiddle].points == searchForThis) { //CHECK IF INDEX BEFORE IS EQUAL

		//int i;

		//for (i = indexMiddle - 1; arrayList[i].points == searchForThis || i > 0; i--);

		while (arrayList[indexMiddle - 1].points == searchForThis && indexMiddle > 0)
			indexMiddle--;

		//cout << i << endl;

		//indexMiddle = i;

		cout << arrayList[indexMiddle].points << "|" << searchForThis << endl;

		cout << "If found check before\t" << indexMiddle << endl;
	}

	cout << "Final\t" << indexMiddle << endl;

	return indexMiddle;
}

void Stats::CustomSort(int startingIndex, int searchForThis)
{
	if (startingIndex != -1) {

		int tempPoints; string tempName;

		cout << "Custom: Init complete\n";

		for (int i = 0; arrayList[startingIndex + i].points == searchForThis; i++) {

			cout << "Custom: Starting Putting Temp\n";
			tempPoints = arrayList[i].points;
			cout << "Custom: Line 328\n";
			tempName = arrayList[i].name;
			cout << "Custom: Line 330\n";

			cout << "Custom: Starting Swapping\n";
			arrayList[i].points = arrayList[startingIndex + i].points;
			arrayList[i].name = arrayList[startingIndex + i].name;

			cout << "Custom: Starting Using Temp\n";
			arrayList[startingIndex + i].points = tempPoints;
			arrayList[startingIndex + i].name = tempName;

			cout << "Custom Sort Finished!\n";
		}

	}
}