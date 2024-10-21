#include "TextPrompt.h"

TextPrompt::TextPrompt(float xPosition, float yPosition, int giveCharLimit, bool isNumberOnly)
{
	charLimit = giveCharLimit;

	numberOnly = isNumberOnly;

	isSelected = false;

	graphicButton.setSize(Vector2f(480.f, 100.f));
	graphicButton.setFillColor(Color::Green);
	graphicButton.setPosition(xPosition, yPosition);

	textBox.setCharacterSize(30);
	textBox.setFillColor(Color::White);
	textBox.setPosition(graphicButton.getPosition().x + 10.f, graphicButton.getPosition().y + 30.f);

	textFont = new Font;
	textFont->loadFromFile("Font/04B_30__.TTF");

	textBox.setFont(*textFont);
}

TextPrompt::~TextPrompt()
{
	delete textFont;
}

void TextPrompt::updateTextPrompt(Event eventListener, Vector2f mousePosition)
{
	if (graphicButton.getGlobalBounds().contains(mousePosition) && !isSelected) {

		graphicButton.setFillColor(Color(70, 70, 70, 200));

		if (Mouse::isButtonPressed(Mouse::Left)) {

			isSelected = true;
			textBox.setString(textStream.str() + "_");
		}
	}
	else if(!isSelected){
		graphicButton.setFillColor(Color::Green);
	}

	if (isSelected && eventListener.type == Event::TextEntered) {
		Sleep(100);
		printf("text\n");
		typing(eventListener);

	}else if (!isSelected) {
		
		if (textStream.str() != "") {

			string textTemp = textStream.str();
			string textNewTemp = "";

			for (int i = 0; i < textTemp.length(); i++)
				textNewTemp += textTemp[i];

			textBox.setString(textNewTemp);
		}
	}
}

void TextPrompt::typing(Event eventListener)
{
	int charTyped = eventListener.text.unicode;

	if (textStream.str().length() <= charLimit) {

		if (!numberOnly && charTyped < 128)
			inputLogic(charTyped);
		else if (numberOnly && ((charTyped >= 48 && charTyped <= 57) || charTyped == DELETE_KEY))
			inputLogic(charTyped);
	}
	else if (textStream.str().length() > 0 && charTyped == DELETE_KEY)
		inputLogic(charTyped);
	else if (textStream.str().length() > 0 && charTyped == ENTER_KEY || charTyped == ESCAPE_KEY)
		inputLogic(charTyped);
}

void TextPrompt::renderTextPrompt(RenderTarget& windowGame)
{
	windowGame.draw(graphicButton);
	windowGame.draw(textBox);
}

bool TextPrompt::isEmpty()
{
	if (textStream.str().length() == 0)
		return true;
	else return false;
}

string TextPrompt::getText()
{
	while (textStream.str().length() < charLimit)
		textStream << " ";

	return textStream.str();
}

void TextPrompt::inputLogic(int charTyped)
{
	string indicator = "_";

	if (charTyped != DELETE_KEY && charTyped != ENTER_KEY && charTyped != ESCAPE_KEY)
		textStream << static_cast<char>(charTyped);
	else if (charTyped == DELETE_KEY) {

		if (textStream.str().length() > 0)
			deleteLastChar();
	}
	else if (charTyped == ENTER_KEY || charTyped == ESCAPE_KEY) {

		isSelected = false;

		if (isEmpty())
			indicator = "";
	}

	textBox.setString(textStream.str() + indicator);
}

void TextPrompt::deleteLastChar()
{
	string textTemp = textStream.str();
	string textNewTemp = "";

	for (int i = 0; i < textTemp.length() - 1; i++)
		textNewTemp += textTemp[i];

	textStream.str("");
	textStream << textNewTemp;

	textBox.setString(textStream.str());
}
