#pragma once
#include <SFML/Graphics.hpp>

sf::Font font;
sf::Text meter, currLevelText, strokesLeftText;
sf::Text currLevel, strokesLeft;

void loadUi(sf::Vector2u app_size)
{
	font.loadFromFile("Resources/font.ttf");

	meter.setFont(font);
	meter.setCharacterSize(30.f);
	meter.setStyle(sf::Text::Bold);
	meter.setFillColor(sf::Color::Black);
	meter.setString("Power Meter");
	meter.setPosition(10, app_size.y);

	currLevel.setFont(font);
	currLevelText.setFont(font);

	strokesLeftText.setFont(font);
	strokesLeftText.setCharacterSize(30.f);
	strokesLeftText.setStyle(sf::Text::Bold);
	strokesLeftText.setFillColor(sf::Color::Black);
	strokesLeftText.setString("Strokes Left:");
	strokesLeftText.setPosition(app_size.x / 2 - strokesLeftText.getGlobalBounds().width / 2 - 20, app_size.y);

	strokesLeft.setFont(font);
	strokesLeft.setCharacterSize(30.f);
	strokesLeft.setStyle(sf::Text::Bold);
	strokesLeft.setFillColor(sf::Color::Black);
	strokesLeft.setPosition(app_size.x / 2 - strokesLeftText.getGlobalBounds().width / 2 + 160, app_size.y);

}

void renderUi(sf::RenderWindow &app)
{
	app.draw(meter);
	app.draw(strokesLeftText);
	app.draw(strokesLeft);
}