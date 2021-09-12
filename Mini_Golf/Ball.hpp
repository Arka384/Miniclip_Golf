#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>

class Ball
{
private:
	float size = 14.f, abs_velocity = 0;
	sf::Vector2f velocity = sf::Vector2f(0.f, 0.f), initialMousePos;
	sf::Vector2f launchVelocity = sf::Vector2f(0.f, 0.f);
	bool launched = false;
public:
	sf::CircleShape ball;
	sf::Sprite ball_sprite;
	sf::Texture ball_tex;

	void init(sf::Vector2u app_size);
	void setInitialPos(sf::Vector2i pos);
	void setBallVelocity(sf::Vector2i mouse);
	void setLaunchVelocity(sf::Vector2i mouse);
	bool mouseOnBall(sf::Vector2i mouse);
	bool ballNotMoving(void);
	void update(float dt, sf::Vector2u app_size, bool &init_set);
};

