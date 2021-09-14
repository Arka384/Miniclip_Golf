#pragma once
#include <SFML/Graphics.hpp>

sf::Sprite bg, ui_bg, title, finished;
sf::Texture bg_tex, ui_bg_tex, title_tex, finished_tex;

sf::Font font;
sf::Text meter, currLevelText, strokesLeftText;
sf::Text currLevel, strokesLeft;
sf::Text  levelCompleteText, levelFailedText;

bool start_state = true, finished_state = false;

void loadUi(sf::Vector2u app_size)
{
	font.loadFromFile("Resources/font.ttf");

	//sprites
	bg_tex.loadFromFile("Resources/sprites/bg.png");
	bg.setTexture(bg_tex);

	ui_bg_tex.loadFromFile("Resources/sprites/ui_bg.png");
	ui_bg.setTexture(ui_bg_tex);
	ui_bg.setPosition(0, app_size.y);

	title_tex.loadFromFile("Resources/sprites/title_screen.png");
	title.setTexture(title_tex);
	finished_tex.loadFromFile("Resources/sprites/finished.png");
	finished.setTexture(finished_tex);

	//texts
	meter.setFont(font);
	meter.setCharacterSize(30.f);
	meter.setStyle(sf::Text::Bold);
	meter.setFillColor(sf::Color::Black);
	meter.setString("Power Meter");
	meter.setPosition(10, app_size.y);

	currLevelText.setFont(font);
	currLevelText.setCharacterSize(30.f);
	currLevelText.setStyle(sf::Text::Bold);
	currLevelText.setFillColor(sf::Color::Black);
	currLevelText.setString("Level:");
	currLevelText.setPosition(app_size.x - currLevelText.getGlobalBounds().width - 50, app_size.y);

	currLevel.setFont(font);
	currLevel.setCharacterSize(30.f);
	currLevel.setStyle(sf::Text::Bold);
	currLevel.setFillColor(sf::Color::Black);
	currLevel.setPosition(app_size.x - 40, app_size.y);

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

	levelCompleteText.setFont(font);
	levelCompleteText.setCharacterSize(150.f);
	levelCompleteText.setStyle(sf::Text::Bold);
	levelCompleteText.setFillColor(sf::Color::White);
	levelCompleteText.setString("Level Complete");
	levelCompleteText.setPosition(200, app_size.y - 300);
	levelCompleteText.setRotation(-30.f);

	levelFailedText.setFont(font);
	levelFailedText.setCharacterSize(150.f);
	levelFailedText.setStyle(sf::Text::Bold);
	levelFailedText.setFillColor(sf::Color::White);
	levelFailedText.setString("Failed");
	levelFailedText.setPosition(300, app_size.y - 400);
	levelFailedText.setRotation(-30.f);

}

void renderUi(sf::RenderWindow &app, bool complete, int currStrokes, Ball b)
{
	app.draw(meter);
	app.draw(strokesLeftText);
	app.draw(strokesLeft);
	app.draw(currLevelText);
	app.draw(currLevel);
	if (complete) {
		app.draw(levelCompleteText);
	}
	else if (b.trigger && b.ballNotMoving()) {
		app.draw(levelFailedText);
	}

	if (start_state)
		app.draw(title);
	else if (finished_state)
		app.draw(finished);
		
}