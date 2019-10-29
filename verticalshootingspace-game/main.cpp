#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
#include "class/Player.h"
#include "class/Rock.h"
#include "class/Spritesheet.h"

using namespace sf;

//SFML Version 2.5.1

const int GRID_SIZE = 32, PLAYABLE_SIZE = 15; 
const int WINDOW_WIDTH = 720, WINDOW_HEIGHT = 720;

int main()
{
	srand(time(NULL));

	//Window Settings
	View view;
	VideoMode desktop = VideoMode::getDesktopMode();
	std::cout << "Resolution at: " << desktop.bitsPerPixel << std::endl;
	view.reset(FloatRect(0, 0, (float)WINDOW_WIDTH, (float)WINDOW_HEIGHT));
	RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, desktop.bitsPerPixel), "verticalshootingspace-game!");
	window.setFramerateLimit(60); //Will allow remove cap limit later

	//Clock timers
	Clock deltaClock, rockClock, shootClock;

	//Load textures
	Texture t1, t2, t3, t4, t5;
	t1.loadFromFile("sprites/BlueShip.png");
	t2.loadFromFile("sprites/DarkSpaceBackground.png");	
	t3.loadFromFile("sprites/LineBullet.png");
	t4.loadFromFile("sprites/Rubble.png");
	t5.loadFromFile("sprites/GreenPersonAnim.png");

	//Make sprites from textures
	Spritesheet greenPerson(t5, 36, 36, 50, 1, 1);
	Spritesheet shipSprite(t1, 32, 32);
	Sprite background(t2);
	Sprite lineBullet(t3); lineBullet.setOrigin(4, 4);
	Sprite rock(t4); rock.setOrigin(32, 32);

	//Make Sprite Sheets


	//Make Walls
	float wallSize = (WINDOW_WIDTH - (PLAYABLE_SIZE*GRID_SIZE)) / 2;
	RectangleShape leftBorder, rightBorder;
	leftBorder.setSize(Vector2f(wallSize, (float)WINDOW_HEIGHT));
	leftBorder.setFillColor(Color::Black);
	leftBorder.setPosition(0, 0);
	rightBorder.setSize(Vector2f(wallSize, (float)WINDOW_HEIGHT));
	rightBorder.setFillColor(Color::Black);
	rightBorder.setPosition(WINDOW_WIDTH - wallSize, 0);
	Vector2f borderUpLeft(wallSize, 0);
	Vector2f borderBottomRight(WINDOW_WIDTH - wallSize, WINDOW_HEIGHT);

	//Shaders
	Shader shader;
	shader.loadFromFile("shader.frag",Shader::Fragment);
	shader.setUniform("frag_ScreenResolution", Vector2f((float)WINDOW_WIDTH, (float)WINDOW_HEIGHT));
	shader.setUniform("frag_LightAttenuation", 50.0f);
	RenderStates states;
	states.shader = &shader;

	//Set default objects
	Rock greyRock("greyRock", rock, Vector2f(64, 64));
	greyRock.SetRadius(32);
	greyRock.SetBorder(borderUpLeft, borderBottomRight);

	float xCenter = (float)WINDOW_WIDTH/2; float yCenter = (float)WINDOW_HEIGHT/2;
	//Instatiate objects
	std::list<Object*> objects; //List for all objects on the game
	Player* blueShip = new Player("Player", shipSprite,	Vector2f(32, 32), Vector2f(xCenter, yCenter));
	blueShip->SetPoint(up);

	//Settings for the objects
	blueShip->SetRadius(16);
	blueShip->SetBorder(borderUpLeft, borderBottomRight);
	objects.push_back(blueShip);

	float shootCooldown = 0;
	//Game Loop
	while (window.isOpen()) {
		Time deltaTime = deltaClock.restart();
		Time rockCurrentTime = rockClock.getElapsedTime();
		Time shootCurrentTime = rockClock.getElapsedTime();

		Event e;
		while (window.pollEvent(e))
		{
			if (e.type == Event::Closed)
				window.close();
	
			//Close Game
			if (e.type == Event::KeyPressed)
				if (e.key.code == Keyboard::Escape) window.close(); 
		}

		if (shootCooldown > 0) {
			shootCooldown -= deltaTime.asSeconds();
		}

		//get global mouse position
		blueShip->PointAt(Mouse::getPosition(window));

		if ((Mouse::isButtonPressed(Mouse::Left) || Keyboard::isKeyPressed(Keyboard::Space)) && shootCooldown <= 0 && blueShip->GetLife() > 0 ){
			Projectile *bullet = new Projectile("bullet", lineBullet, Vector2f(8, 8), blueShip);
			shootCooldown = 0.2f;
			objects.push_back(bullet);
			
		}
	
		if (rockCurrentTime.asSeconds() >= 2.f) {
			//Make a new rock based on greyRock every 2 seconds
			Rock* newRock = new Rock({ greyRock });
			float newXPos = (rand() % PLAYABLE_SIZE) + 1; // 1 - 15
			newXPos = (newXPos * GRID_SIZE) + wallSize;
			newRock->SetPosition(Vector2f(newXPos, 0));
			newRock->SetRotation(0);
			newRock->SetLife(1);
			objects.push_back(newRock);
			rockClock.restart();
		}

		//Update 
		for (auto i = objects.begin(); i != objects.end();) {
			Object *o = *i;
			o->Update();
			if (o->GetLife() <= 0) {
				i = objects.erase(i);
				delete o; 
			}
			else i++;
		}

		//Find collisions
		for (auto a : objects) {
			for (auto b : objects) {
				if (a->GetName() == "greyRock" && b->GetName() == "bullet") {
					if (a->isCollideWith(b)) {
						a->ReduceHp(b->GetDamage());
						b->ReduceHp(a->GetDamage());
					}		
				}
				if (a->GetName() == "Player" && b->GetName() == "greyRock") {
					if (a->isCollideWith(b)) {
						a->ReduceHp(b->GetDamage());
						b->ReduceHp(a->GetDamage());
					}			
				}
			}
		}

		//Shaders
		shader.setUniform("frag_LightOrigin", blueShip->GetPosition());
		shader.setUniform("frag_LightColor", Vector3f(0, 128.f, 128.f));
		
		//Draw 
		window.clear(Color::White);
		window.setView(view);
		window.draw(background, states);
		for (auto i : objects) i->Draw(window);

		window.draw(leftBorder);
		window.draw(rightBorder);
		window.display();	
	}

	return 0;
}
