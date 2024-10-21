#pragma once

#include <SFML/Graphics.hpp>

#include <sstream>
#include <Windows.h>

using namespace sf;
using namespace std;

#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27

class TextPrompt
{
public:
	TextPrompt(float xPosition, float yPosition, int charLimit, bool isNumberOnly);
	~TextPrompt();

	void updateTextPrompt(Event eventListener, Vector2f mousePosition);
	void typing(Event eventListener);
	void renderTextPrompt(RenderTarget& windowGame);
	bool isEmpty();
	string getText();

private:
	Text textBox;
	stringstream textStream;
	bool isSelected;
	Font* textFont;
	RectangleShape graphicButton;
	int charLimit;
	bool numberOnly;
	
	void inputLogic(int charTyped);
	void deleteLastChar();

};

