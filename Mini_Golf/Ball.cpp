#include "Ball.hpp"

void Ball::init(sf::Vector2u app_size)
{
	meter_bg_tex.loadFromFile("Resources/sprites/powermeter_bg.png");
	meter_bg.setTexture(meter_bg_tex);
	meter_bg.setScale(2, 1.2);
	meter_bg.setPosition(180, app_size.y + 12);

	meter_fg_tex.loadFromFile("Resources/sprites/powermeter_fg.png");
	meter_fg.setTexture(meter_fg_tex);
	meter_fg.setScale(2, 1.2);
	meter_fg.setPosition(188, app_size.y + 16);

	meter_ov_tex.loadFromFile("Resources/sprites/powermeter_overlay.png");
	meter_ov.setTexture(meter_ov_tex);
	meter_ov.setScale(2, 1.2);
	meter_ov.setPosition(180, app_size.y + 12);

	ball_tex.loadFromFile("Resources/sprites/ball.png");
	ball_sprite.setTexture(ball_tex);
	ball_sprite.setScale(2, 2);
	ball.setRadius(size);
	ball.setFillColor(sf::Color::White);
	ball.setPosition(200, app_size.y / 2);
}

void Ball::setInitialPos(sf::Vector2i pos)
{
	initialMousePos.x = pos.x;
	initialMousePos.y = pos.y;
}

void Ball::setLaunchVelocity(sf::Vector2i mouse)
{
	stroked = false;
	launchVelocity.x = initialMousePos.x - mouse.x;
	launchVelocity.y = initialMousePos.y - mouse.y;
	abs_velocity = sqrt(pow(launchVelocity.x, 2) + pow(launchVelocity.y, 2));
	if (abs_velocity > 420) {
		launchVelocity = copy_velocity;
		return;
	}
	copy_velocity = launchVelocity;
	meter_fg.setScale(abs_velocity/200, 1.2);
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

void Ball::update(float dt, sf::Vector2u app_size, bool *init_set, sf::Sprite &hole, bool *level_complete, std::vector<sf::Sprite> blocks, int &currStrokes)
{
	if (!stroked) {	//initially true
		currStrokes--;
		stroked = true;
	}

	if (!launched) { //if ball is not launched and moving
		velocity = launchVelocity;
		launchVelocity = sf::Vector2f(0.f, 0.f);
		abs_velocity = 0;
		meter_fg.setScale(abs_velocity / 200, 1.2);
		launched = true;
		return;
	}

	//if ball is launched the update ball velocity
	float x = ball.getPosition().x + velocity.x*dt*10;
	float y = ball.getPosition().y + velocity.y*dt*10;
	
	//collision with walls
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

	//collision with blocks or tiles
	for (int i = 0; i < blocks.size(); i++) {
		float nx = x + velocity.x * dt;
		if (nx + size*2 >= blocks[i].getPosition().x && nx <= blocks[i].getPosition().x + blocks[i].getGlobalBounds().width &
			y + size * 2 >= blocks[i].getPosition().y && y <= blocks[i].getPosition().y + blocks[i].getGlobalBounds().height)
			velocity.x = velocity.x * -1;
		float ny = y + velocity.y * dt;
		if (x + size * 2 >= blocks[i].getPosition().x && x <= blocks[i].getPosition().x + blocks[i].getGlobalBounds().width &
			ny + size * 2 >= blocks[i].getPosition().y && ny <= blocks[i].getPosition().y + blocks[i].getGlobalBounds().height)
			velocity.y = velocity.y * -1;
	}

	
	velocity.x = velocity.x * f;
	velocity.y = velocity.y * f;
	
	if (abs(int(velocity.x)) == 0 && abs(int(velocity.y)) == 0) {
		velocity = sf::Vector2f(0.f, 0.f);
		launched = false;
		*init_set = true;
	}
	ball.setPosition(x, y);

	if (x >= hole.getPosition().x - 5 && x <= hole.getPosition().x + hole.getGlobalBounds().width + 5 &&
		y >= hole.getPosition().y - 5 && y <= hole.getPosition().y + hole.getGlobalBounds().height + 5) {
		if (!*level_complete) {
			velocity = sf::Vector2f(0.f, 0.f);
			ball.setPosition(100, app_size.y / 2);
			*level_complete = true;
			return;
		}
	}
}

void Ball::renderBall(sf::RenderWindow & app)
{
	app.draw(ball_sprite);
	app.draw(meter_bg);
	app.draw(meter_fg);
	app.draw(meter_ov);
}
