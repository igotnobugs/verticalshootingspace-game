#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>

#include "class/Player.h"
#include "class/Rock.h"
#include "class/Animation.h"


using namespace sf;

//Version 2.5.1

const int GRID_SIZE = 32;
const int PLAYABLE_SIZE = 15; 

bool isCollide(Entity *a, Entity *b)
{
	return (b->GetPosition().x - a->GetPosition().x)*(b->GetPosition().x - a->GetPosition().x) +
		(b->GetPosition().y - a->GetPosition().y)*(b->GetPosition().y - a->GetPosition().y) <
		(a->GetRadius() + b->GetRadius())*(a->GetRadius() + b->GetRadius());
}

int main()
{
	srand(time(NULL));
	int windowWidth = 720; int windowHeight = 720;

	View view;
	VideoMode desktop = VideoMode::getDesktopMode();
	int resFix = desktop.bitsPerPixel * 32; // Fix later
	view.reset(FloatRect(0, 0, (float)windowWidth, (float)windowHeight));
	RenderWindow window(VideoMode(windowWidth + resFix, windowHeight + resFix, desktop.bitsPerPixel), "verticalshootingspace-game!");
	window.setFramerateLimit(60);

	//Load textures
	Texture t1, t2, t3, t4, t5;
	t1.loadFromFile("sprites/BlueShip.png");
	t2.loadFromFile("sprites/DarkSpaceBackground.png");	
	t3.loadFromFile("sprites/LineBullet.png");
	t4.loadFromFile("sprites/Rubble.png");
	t5.loadFromFile("sprites/GreenPersonAnim.png");

	//Make sprites from textures
	Sprite shipSprite(t1);
	Sprite background(t2);
	Sprite lineBullet(t3);
	Sprite rock(t4);

	//Make animations
	Animation greenPerson(t5, 0, 0, 36, 36, 50, 1);

	//Make Walls
	float wallSize = (windowWidth - (PLAYABLE_SIZE*GRID_SIZE)) / 2;
	RectangleShape leftBorder, rightBorder;
	leftBorder.setSize(Vector2f(wallSize, (float)windowHeight));
	leftBorder.setFillColor(Color::Black);
	leftBorder.setPosition(0, 0);
	rightBorder.setSize(Vector2f(wallSize, (float)windowHeight));
	rightBorder.setFillColor(Color::Black);
	rightBorder.setPosition(windowWidth - wallSize, 0);
	Vector2f borderUpLeft(wallSize, 0);
	Vector2f borderBottomRight(windowWidth - wallSize, windowHeight);

	//Shaders
	Shader shader;
	shader.loadFromFile("shader.frag",Shader::Fragment);
	shader.setUniform("frag_ScreenResolution", Vector2f((float)windowWidth, (float)windowHeight));
	shader.setUniform("frag_LightAttenuation", 50.0f);
	RenderStates states;
	states.shader = &shader;

	//Set default objects
	Rock greyRock;	greyRock.SetSprite(rock, 32, 32);
	greyRock.SetName("greyRock");
	greyRock.SetRadius(32);
	greyRock.SetBorder(borderUpLeft, borderBottomRight);

	//Instatiate objects
	std::list<Entity*> entities; //List for all entities on the game
	Player* blueShip = new Player; 
	Entity* test = new Entity;

	//Settings for the objects
	float xCenter = (float)windowWidth / 2; float yCenter = (float)windowHeight / 2;
	blueShip->SetName("Player");
	blueShip->SetSprite(shipSprite, 16, 16);
	blueShip->SetRadius(16);
	blueShip->Settings(Vector2f(xCenter, yCenter));
	blueShip->SetBorder(borderUpLeft, borderBottomRight);
	entities.push_back(blueShip);

	test->SetAnimation(greenPerson);
	test->SetPosition(wallSize + 32, windowHeight - 32);
	test->SetScale(2);
	entities.push_back(test);

	Clock deltaClock;
	Clock rockClock;
	Clock shootClock;

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

		if ((Keyboard::isKeyPressed(Keyboard::Space)) && shootCooldown <= 0 && blueShip->GetLife() > 0 ){
			Projectile *bullet = new Projectile;
			bullet->SetName("bullet");
			bullet->SetSprite(lineBullet, 4, 4);
			bullet->SetRadius(4);
			bullet->Settings(Vector2f(blueShip->GetPosition().x, blueShip->GetPosition().y), blueShip->GetAngle());
			bullet->mShootDirection = -90;
			shootCooldown = 0.2f;
			entities.push_back(bullet);
		}
	
		if (rockCurrentTime.asSeconds() >= 2.f) {
			//Make a new rock based on greyRock every 2 seconds
			Rock* newRock = new Rock({ greyRock });
			float newXPos = (rand() % PLAYABLE_SIZE) + 1; // 1 - 15
			newXPos = (newXPos * GRID_SIZE) + wallSize;
			newRock->Settings(Vector2f(newXPos, 0));
			entities.push_back(newRock);
			rockClock.restart();
		}

		//Update 
		//test.mAnimation->Update();
		//std::cout << test->mAnimation
		for (auto i = entities.begin(); i != entities.end();) {
			Entity *e = *i;
			e->Update();
			if (e->GetLife() <= 0) { i = entities.erase(i); e = nullptr; delete e; }
			else i++;
		}

		//get collision 
		for (auto a : entities) {
			for (auto b : entities) {		
				if (a->GetName() == "greyRock" && b->GetName() == "bullet") {
					if (isCollide(a, b)) {
						a->ReduceHp(b->GetDamage());
						b->ReduceHp(a->GetDamage());
						std::cout << a->GetName() << " has collided with " << b->GetName() << std::endl;
					}		
				}
				if (a->GetName() == "Player" && b->GetName() == "greyRock") {
					if (isCollide(a, b)) {
						a->ReduceHp(b->GetDamage());
						b->ReduceHp(a->GetDamage());
						std::cout << a->GetName() << " has collided with " << b->GetName() << std::endl;
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
		for (auto i : entities) i->Draw(window);

		window.draw(leftBorder);
		window.draw(rightBorder);
		window.display();	
	}


	return 0;
}
