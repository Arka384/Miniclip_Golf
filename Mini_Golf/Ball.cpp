#include "Ball.hpp"

void Ball::init(sf::Vector2u app_size)
{
	ball_tex.loadFromFile("Resources/sprites/ball.png");
	ball_sprite.setTexture(ball_tex);
	ball_sprite.setScale(2, 2);
	ball.setRadius(size);
	ball.setFillColor(sf::Color::White);
	ball.setPosition(100, app_size.y / 2);
}

void Ball::setInitialPos(sf::Vector2i pos)
{
	initialMousePos.x = pos.x;
	initialMousePos.y = pos.y;
}

void Ball::setLaunchVelocity(sf::Vector2i mouse)
{
	launchVelocity.x = initialMousePos.x - mouse.x;
	launchVelocity.y = initialMousePos.y - mouse.y;
}

void Ball::setBallVelocity(sf::Vector2i mouse)
{
	velocity = launchVelocity;
}

bool Ball::mouseOnBall(sf::Vector2i mouse)
{
	return (mouse.x > ball.getPosition().x && mouse.x < ball.getPosition().x + size &&
		mouse.y > ball.getPosition().y && mouse.y < ball.getPosition().y + size);
}

bool Ball::ballNotMoving(void)
{
	if (velocity.x == 0 && velocity.y == 0)
		return true;
	return false;
}

void Ball::update(float dt, sf::Vector2u app_size, bool *init_set, sf::Sprite &hole, int &currentLevel)
{
	if (!launched) { //if ball is not launched and moving
		velocity = launchVelocity;
		launchVelocity = sf::Vector2f(0.f, 0.f);
		launched = true;
		return;
	}

	//if ball is launched the update ball velocity
	float f = 0.996;
	float x = ball.getPosition().x + velocity.x*dt*10;
	float y = ball.getPosition().y + velocity.y*dt*10;

	if (x >= app_size.x - size*2) {
		velocity.x = -velocity.x;
		x = app_size.x - size*2;
	} else if (x <= 0) {
		velocity.x = -velocity.x;
		x = 0;
	}
		
	if (y >= app_size.y - size*2) {
		velocity.y = -velocity.y;
		y = app_size.y - size*2;
	} else if (y <= 0) {
		velocity.y = -velocity.y;
		y = 0;
	}

	if (x >= hole.getPosition().x - 5 && x <= hole.getPosition().x + hole.getGlobalBounds().width + 5 &&
		y >= hole.getPosition().y - 5 && y <= hole.getPosition().y + hole.getGlobalBounds().height + 5) {
		loadLevel(currentLevel++, hole);
	}
		
	velocity.x = velocity.x * f;
	velocity.y = velocity.y * f;
	
	if (abs(int(velocity.x)) == 0 && abs(int(velocity.y)) == 0) {
		velocity = sf::Vector2f(0.f, 0.f);
		launched = false;
		*init_set = true;
	}
	ball.setPosition(x, y);
}
