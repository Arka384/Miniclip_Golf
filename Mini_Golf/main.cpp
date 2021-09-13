#include <sstream>
#include "Ball.hpp"
#include "Ui.hpp"

sf::Sprite tiles32[2], tiles64[2];
sf::Texture tiles[4];
std::vector<sf::Sprite> blocks;

void loadLevel(int &currentLevel, sf::Sprite &hole, int &currentStrokes);
void loadTiles(void);

int main()
{
	srand(time(NULL));
	sf::Vector2u app_size(1280, 720);
	sf::RenderWindow app(sf::VideoMode(app_size.x, app_size.y + 40), "Mini Golf", sf::Style::Close);
	sf::Vector2i mousepos;
	bool mousePressed = false;
	sf::Clock clk;
	sf::Time time;
	float dt = 0;

	sf::Sprite bg, hole, ui_bg;
	sf::Texture bg_tex, hole_tex, ui_bg_tex;
	bg_tex.loadFromFile("Resources/sprites/bg.png");
	bg.setTexture(bg_tex);
	hole_tex.loadFromFile("Resources/sprites/hole.png");
	hole.setTexture(hole_tex);
	hole.setScale(2, 2);
	ui_bg_tex.loadFromFile("Resources/sprites/ui_bg.png");
	ui_bg.setTexture(ui_bg_tex);
	ui_bg.setPosition(0, app_size.y);
	bool init_set = true, levelComplete = false;
	int currentLevel = 1, currentStrokes = 5;
	//level
	loadTiles();
	loadLevel(currentLevel, hole, currentStrokes);
	//ui
	loadUi(app_size);

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

		std::stringstream strokes;
		strokes << currentStrokes;
		strokesLeft.setString(strokes.str());

		if (levelComplete) {
			levelComplete = false;
			currentLevel++;
			loadLevel(currentLevel, hole, currentStrokes);
		}
		if (currentStrokes == 0) {
			loadLevel(currentLevel, hole, currentStrokes);
		}

		if (mousePressed && init_set) {	//setting initial mouse pos
			golfBall.setInitialPos(mousepos);
			init_set = false;
		}
		else if (mousePressed && golfBall.ballNotMoving()) {
			golfBall.setLaunchVelocity(mousepos);
		}
		else	//launch the ball and collision detections
			golfBall.update(dt, app_size, &init_set, hole, &levelComplete, blocks, currentStrokes);


		///////////////////////

		app.clear();

		app.draw(ui_bg);
		app.draw(bg);
		renderUi(app);
		app.draw(hole);
		for (int i = 0; i < blocks.size(); i++)
			app.draw(blocks[i]);
		golfBall.renderBall(app);

		app.display();
	}
}

void loadLevel(int &currentLevel, sf::Sprite &hole, int &currentStrokes)
{
	int i = 0;
	hole.setPosition(1000, 350);
	switch (currentLevel)
	{
	case 1:
		currentStrokes = 5;
		hole.setPosition(1000, 350);
		break;
	case 2:
		currentStrokes = 5;
		//hole.setPosition(1000, 350);
		i = rand() % 2;
		tiles64[i].setPosition(640 - 32, 360 - 32);
		blocks.push_back(tiles64[i]);
		break;
	case 3:
		blocks.clear();
		currentStrokes = 5;
		i = rand() % 2;
		tiles64[i].setPosition(900 - 32, 370 - 32);
		blocks.push_back(tiles64[i]);
		break;
	default:
		break;
	}
}

void loadTiles(void)
{
	tiles[0].loadFromFile("Resources/sprites/tile32_dark.png");
	tiles[1].loadFromFile("Resources/sprites/tile32_light.png");
	tiles[2].loadFromFile("Resources/sprites/tile64_dark.png");
	tiles[3].loadFromFile("Resources/sprites/tile64_light.png");

	for (int i = 0; i < 2; i++)
		tiles32[i].setTexture(tiles[i]);
	for (int i = 2, j = 0; i < 4; i++, j++)
		tiles64[j].setTexture(tiles[i]);
}

