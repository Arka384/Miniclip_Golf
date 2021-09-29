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
	int currentLevel = 6, maxStrokes = 10, currentStrokes = maxStrokes;

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
			case sf::Event::KeyPressed:
				if(e.key.code == sf::Keyboard::R)
					golfBall.ball.setPosition(200, app_size.y / 2);
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
	b.trigger = false;
	currentStrokes = maxStrokes;
	hole.setPosition(1000, 350);
	b.ball.setPosition(200, app_size.y / 2);
	switch (currentLevel)
	{
	case 1:
		hole.setPosition(1000, 350);
		break;
	case 2:
		i = rand() % 2;
		tiles64[i].setPosition(640 - 32, 360 - 32);
		blocks.push_back(tiles64[i]);
		break;
	case 3:
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
		hole.setPosition(950, 350);
		i = rand() % 2;
		tiles64[i].setPosition(405 - 32, 80);
		blocks.push_back(tiles64[i]);
		tiles64[i].setPosition(app_size.x - 500, app_size.y - (80 + 40));
		blocks.push_back(tiles64[i]);
		tiles64[i].setPosition(app_size.x - 345, app_size.y/2 - 90);
		blocks.push_back(tiles64[i]);
		i = rand() % 2;
		tiles32[i].setPosition(500 - 16, app_size.y / 2 - 10);
		blocks.push_back(tiles32[i]);
		tiles32[i].setPosition(app_size.x - 500 - 16, app_size.y / 2 - 10);
		blocks.push_back(tiles32[i]);
		break;
	case 5:
		hole.setPosition(app_size.x / 2 + 200 - 32, app_size.y / 2 - 32 - 80);
		i = rand() % 2;
		tiles64[i].setPosition(app_size.x / 2 + 100 - 32, app_size.y / 2 - 32 - 100);
		blocks.push_back(tiles64[i]);
		tiles64[i].setPosition(app_size.x / 2 - 200 - 32, 80);
		blocks.push_back(tiles64[i]);

		i = rand() % 2;
		tiles64[i].setPosition(app_size.x / 2 - 200 - 32, 5);
		blocks.push_back(tiles64[i]);
		tiles64[i].setPosition(app_size.x / 2 + 180 - 32, app_size.y / 2 - 32 - 200);
		blocks.push_back(tiles64[i]);
		tiles64[i].setPosition(app_size.x / 2 + 180 - 32, app_size.y / 2 - 32);
		blocks.push_back(tiles64[i]);
		i = rand() % 2;
		tiles32[i].setPosition(200, app_size.y / 2 + 50);
		blocks.push_back(tiles32[i]);
		tiles32[i].setPosition(240, app_size.y / 2 + 50);
		blocks.push_back(tiles32[i]);
		tiles32[i].setPosition(280, app_size.y / 2 + 50);
		blocks.push_back(tiles32[i]);
		i = rand() % 2;
		tiles64[i].setPosition(app_size.x - 64, 0);
		blocks.push_back(tiles64[i]);
		tiles64[i].setPosition(app_size.x - 64, app_size.y - 64);
		blocks.push_back(tiles64[i]);
		break;
	case 6:
		i = rand() % 2;
		tiles32[i].setPosition(140, app_size.y / 2);
		blocks.push_back(tiles32[i]);
		tiles32[i].setPosition(170, app_size.y / 2 - 60);
		blocks.push_back(tiles32[i]);
		tiles32[i].setPosition(200, app_size.y / 2 - 120);
		blocks.push_back(tiles32[i]);
		tiles32[i].setPosition(230, app_size.y / 2 - 180);
		blocks.push_back(tiles32[i]);
		tiles32[i].setPosition(260, app_size.y / 2 - 240);
		blocks.push_back(tiles32[i]);
		tiles32[i].setPosition(290, app_size.y / 2 - 300);
		blocks.push_back(tiles32[i]);
		tiles32[i].setPosition(320, app_size.y / 2 - 360);
		blocks.push_back(tiles32[i]);
		i = rand() % 2;
		tiles32[i].setPosition(260, app_size.y / 2);
		blocks.push_back(tiles32[i]);
		tiles32[i].setPosition(290, app_size.y / 2 - 60);
		blocks.push_back(tiles32[i]);
		tiles32[i].setPosition(320, app_size.y / 2 - 120);
		blocks.push_back(tiles32[i]);
		tiles32[i].setPosition(350, app_size.y / 2 - 180);
		blocks.push_back(tiles32[i]);
		tiles32[i].setPosition(380, app_size.y / 2 - 240);
		blocks.push_back(tiles32[i]);

		i = rand() % 2;
		tiles32[i].setPosition(450, 0);
		blocks.push_back(tiles32[i]);
		tiles32[i].setPosition(480, 60);
		blocks.push_back(tiles32[i]);
		tiles32[i].setPosition(510, 120);
		blocks.push_back(tiles32[i]);
		tiles32[i].setPosition(540, 180);
		blocks.push_back(tiles32[i]);
		tiles32[i].setPosition(570, 240);
		blocks.push_back(tiles32[i]);
		tiles32[i].setPosition(600, 300);
		blocks.push_back(tiles32[i]);
		i = rand() % 2;
		tiles32[i].setPosition(420, 180);
		blocks.push_back(tiles32[i]);
		tiles32[i].setPosition(450, 240);
		blocks.push_back(tiles32[i]);
		tiles32[i].setPosition(480, 300);
		blocks.push_back(tiles32[i]);
		tiles32[i].setPosition(510, 360);
		blocks.push_back(tiles32[i]);

		i = rand() % 2;
		tiles64[i].setPosition(app_size.x / 2 - 270, app_size.y/2 + 100);
		blocks.push_back(tiles64[i]);
		tiles64[i].setPosition(app_size.x / 2 - 270, app_size.y / 2 + 190);
		blocks.push_back(tiles64[i]);
		tiles64[i].setPosition(app_size.x / 2 - 270, app_size.y / 2 + 280);
		blocks.push_back(tiles64[i]);

		i = rand() % 2;
		tiles64[i].setPosition(app_size.x / 2 + 150, app_size.y / 2 + 80);
		blocks.push_back(tiles64[i]);
		tiles64[i].setPosition(app_size.x / 2 + 240, app_size.y / 2 + 80);
		blocks.push_back(tiles64[i]);
		tiles64[i].setPosition(app_size.x / 2 + 330, app_size.y / 2 + 80);
		blocks.push_back(tiles64[i]);
		tiles64[i].setPosition(app_size.x / 2 + 410, app_size.y / 2 + 80);
		blocks.push_back(tiles64[i]);
		tiles64[i].setPosition(app_size.x / 2 + 500, app_size.y / 2 + 80);
		blocks.push_back(tiles64[i]);
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

