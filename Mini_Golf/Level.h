#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

static void loadLevel(int currentLevel, sf::Sprite &hole)
{
	switch (currentLevel)
	{
	case 1:
		hole.setPosition(1000, 350);
		break;
	case 2:
		hole.setPosition(500, 150);
		break;
	default:
		break;
	}
}