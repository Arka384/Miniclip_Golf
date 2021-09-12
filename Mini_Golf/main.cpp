#include <SFML/Graphics.hpp>
#include "Ball.hpp"
#include <iostream>

int main()
{
	sf::Vector2u app_size(1280, 720);
	sf::RenderWindow app(sf::VideoMode(app_size.x, app_size.y), "Mini Golf", sf::Style::Close);
	sf::Vector2i mousepos;
	bool mousePressed = false, init_set = true;
	sf::Clock clk;
	sf::Time time;
	float dt = 0;

	sf::Sprite bg;
	sf::Texture bg_tex;
	bg_tex.loadFromFile("Resources/sprites/bg.png");
	bg.setTexture(bg_tex);

	Ball golfBall;
	golfBall.init(app_size);

	while (app.isOpen())
	{
		time = clk.restart();
		dt = time.asSeconds();

		sf::Event e;
		while (app.pollEvent(e))
		{
			switch (e.type)
			{
			case sf::Event::Closed:
				app.close();
			case sf::Event::MouseButtonPressed:
				mousePressed = true;
				break;
			case sf::Event::MouseButtonReleased:
				mousePressed = false;
				break;
			default:
				break;
			}
		}

		////////////////////////
		mousepos = sf::Mouse::getPosition(app);
		
		golfBall.ball_sprite.setPosition(golfBall.ball.getPosition());
		if (mousePressed && init_set) {	//setting initial mouse pos
			golfBall.setInitialPos(mousepos);
			init_set = false;
		}
		else if (mousePressed && golfBall.ballNotMoving()) {
			golfBall.setLaunchVelocity(mousepos);
		}
		else	//launch the ball and update
			golfBall.update(dt, app_size, init_set);


		///////////////////////

		app.clear();

		app.draw(bg);
		app.draw(golfBall.ball_sprite);

		app.display();
	}
}