#include <sstream>
#include "Ball.hpp"
#include "Ui.hpp"

sf::Sprite tiles32[2], tiles64[2];
sf::Texture tiles[4];
std::vector<sf::Sprite> blocks;

void loadLevel(int &currentLevel, sf::Sprite &hole, int &currentStrokes, Ball &b, sf::Vector2u app_size, int maxStrokes);
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
	float dt = 0, levelEndTimer = 0;

	sf::Sprite hole;
	sf::Texture hole_tex;
	hole_tex.loadFromFile("Resources/sprites/hole.png");
	hole.setTexture(hole_tex);
	hole.setScale(2, 2);
	bool init_set = true, levelComplete = false;
	int currentLevel = 3, maxStrokes = 10, currentStrokes = maxStrokes;

	Ball golfBall;
	golfBall.init(app_size);

	//level
	loadTiles();
	loadLevel(currentLevel, hole, currentStrokes, golfBall, app_size, maxStrokes);
	//ui
	loadUi(app_size);

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
				if (start_state) {
					start_state = false;
					currentStrokes = maxStrokes + 1;
				}
				break;
			case sf::Event::MouseButtonReleased:
				mousePressed = false;
				break;
			default:
				break;
			}
		}

		////////////////////////
		if (!start_state && !finished_state) 
		{
			//std::cout << golfBall.test << "\n";
			mousepos = sf::Mouse::getPosition(app);
			golfBall.ball_sprite.setPosition(golfBall.ball.getPosition());

			std::stringstream strokes, level;
			strokes << currentStrokes;
			strokesLeft.setString(strokes.str());
			level << currentLevel;
			currLevel.setString(level.str());

			if (levelComplete) {
				blocks.clear();	//clearing the tiles
				levelEndTimer += dt;
				if (levelEndTimer > 4)
				{
					levelComplete = false;
					levelEndTimer = 0;
					currentLevel++;
					loadLevel(currentLevel, hole, currentStrokes, golfBall, app_size, maxStrokes);
				}
			}
			//else if (currentStrokes == 0) {
			else if(golfBall.trigger && golfBall.ballNotMoving()){
				blocks.clear();	//clearing the tiles 
				levelEndTimer += dt;
				if (levelEndTimer > 4) {
					levelEndTimer = 0;
					loadLevel(currentLevel, hole, currentStrokes, golfBall, app_size, maxStrokes);
				}
			}
			else if (!levelComplete) {
				if (mousePressed && init_set) {	//setting initial mouse pos
					golfBall.setInitialPos(mousepos);
					init_set = false;
				}
				else if (mousePressed && golfBall.ballNotMoving()) {
					golfBall.setLaunchVelocity(mousepos);
				}
				else	//launch the ball and collision detections
					golfBall.update(dt, app_size, &init_set, hole, &levelComplete, blocks, currentStrokes);
			}
		}

		///////////////////////

		app.clear();

		if (!start_state && !finished_state) {
			app.draw(ui_bg);
			app.draw(bg);
			app.draw(hole);
			for (int i = 0; i < blocks.size(); i++)
				app.draw(blocks[i]);
			golfBall.renderBall(app);
		}
		renderUi(app, levelComplete, currentStrokes, golfBall);

		app.display();
	}
}

void loadLevel(int &currentLevel, sf::Sprite &hole, int &currentStrokes, Ball &b, sf::Vector2u app_size, int maxStrokes)
{
	int i = 0;
	hole.setPosition(1000, 350);
	b.trigger = false;
	switch (currentLevel)
	{
	case 1:
		currentStrokes = maxStrokes;
		hole.setPosition(1000, 350);
		break;
	case 2:
		currentStrokes = maxStrokes;
		b.ball.setPosition(200, app_size.y / 2);
		i = rand() % 2;
		tiles64[i].setPosition(640 - 32, 360 - 32);
		blocks.push_back(tiles64[i]);
		break;
	case 3:
		currentStrokes = maxStrokes;
		b.ball.setPosition(200, app_size.y / 2);
		i = rand() % 2;
		tiles64[i].setPosition(app_size.x / 2 - 32, 0);
		blocks.push_back(tiles64[i]);
		tiles64[i].setPosition(app_size.x / 2 - 32, app_size.y - 64);
		blocks.push_back(tiles64[i]);
		i = rand() % 2;
		tiles32[i].setPosition(app_size.x / 2 - 16, app_size.y / 2 - 16);
		blocks.push_back(tiles32[i]);
		break;
	case 4:
		currentStrokes = maxStrokes;
		b.ball.setPosition(200, app_size.y / 2);
		i = rand() % 2;
		tiles64[i].setPosition(app_size.x / 4 - 32, 100);
		blocks.push_back(tiles64[i]);
		tiles64[i].setPosition(app_size.x - app_size.x / 4 - 32, app_size.y - (100 + 40));
		blocks.push_back(tiles64[i]);
		/*
		i = rand() % 2;
		tiles32[i].setPosition(app_size.x / 4 - 16, app_size.y / 2 - 10);
		blocks.push_back(tiles32[i]);
		tiles32[i].setPosition(app_size.x - app_size.x / 4 - 16, app_size.y / 2 - 10);
		blocks.push_back(tiles32[i]);
		*/
		break;
	default:
		finished_state = true;
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

