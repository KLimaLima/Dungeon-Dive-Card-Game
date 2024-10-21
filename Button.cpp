#include "Button.h"

Button::Button(Vector2f size, Color fillColor, float xPosition, float yPosition, string text, Color textColor, float textPosition)
{
	buttonBox = new RectangleShape;
	buttonBox->setSize(size);
	DefaultColor = fillColor;			//TODO Check if this is right
	buttonBox->setFillColor(fillColor);
	buttonBox->setPosition(xPosition, yPosition);		//TODO make fx if it is clicked then return confirmation

	font = new Font;
	font->loadFromFile("Font/04B_30__.TTF");

	textString = new stringstream;
	textDefault = text;

	buttonText = new Text;
	buttonText->setString(textDefault);
	buttonText->setFillColor(textColor);
	buttonText->setCharacterSize(30);
	buttonText->setPosition(
		buttonBox->getPosition().x + textPosition,
		buttonBox->getPosition().y + textPosition);		//TODO give it a font DONE
	buttonText->setFont(*font);

	isHold = false;
}

Button::~Button()
{
	delete buttonBox;
	delete font;
	delete buttonText;
	delete textString;
}

void Button::mouseHover(Vector2f mousePosition, Color colorWhenHover)
{
	if (buttonBox->getGlobalBounds().contains(mousePosition))
		buttonBox->setFillColor(colorWhenHover);
	else
		buttonBox->setFillColor(DefaultColor);
}

void Button::renderButton(RenderTarget& windowGame)
{
	windowGame.draw(*buttonBox);
	windowGame.draw(*buttonText);
}

bool Button::isClicked(Vector2f mousePosition)
{
	if (isHold && !(Mouse::isButtonPressed(Mouse::Left)))
		isHold = false;

	if (!isHold && buttonBox->getGlobalBounds().contains(mousePosition) && Mouse::isButtonPressed(Mouse::Left)) {
		isHold = true;
		return true;
	}
	else return false;

}

void Button::addText(string textToAdd)
{
	if (textString != NULL)
		delete textString;

	textString = new stringstream;

	*textString << textDefault << textToAdd;

	buttonText->setString(textString->str());
}

void Button::changeText(string changeToThis)
{
	buttonText->setString(changeToThis);
}

void Button::changeBoxColor(Color changeToThis)
{
	buttonBox->setFillColor(changeToThis);
}
