#pragma once

#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include <sstream>

using namespace sf;
using namespace std;

class Button
{
public:
	Button(Vector2f size, Color DefaultColor, float xPosition, float yPosition, string text, Color textColor, float textPosition);
	~Button();
	void mouseHover(Vector2f mousePosition, Color colorWhenHover);
	void renderButton(RenderTarget& windowGame);
	bool isClicked(Vector2f mousePosition);
	void addText(string textToAdd);
	void changeText(string changeToThis);
	void changeBoxColor(Color changeToThis);

private:
	RectangleShape* buttonBox;
	Font* font;
	Text* buttonText;
	string textDefault;
	stringstream* textString;
	Color DefaultColor;
	bool isHold;
};

