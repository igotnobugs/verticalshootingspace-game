#include <SFML/Graphics.hpp>
#include <list>
#include "class/Player.h"
#include "class/Rock.h"

using namespace sf;

//Version 2.5.1

int main()
{
	int windowWidth = 720; int windowHeight = 720;
	RenderWindow window(VideoMode(windowWidth, windowHeight), "verticalshootingspace-game!");
	window.setFramerateLimit(60);

	//Load textures
	Texture t1, t2, t3, t4;
	t1.loadFromFile("sprites/BlueShip.png");
	t2.loadFromFile("sprites/DarkSpaceBackground.png");	
	t3.loadFromFile("sprites/LineBullet.png");
	t4.loadFromFile("sprites/Rubble.png");

	//Make sprites from textures
	Sprite shipSprite(t1);
	Sprite background(t2);
	Sprite lineBullet(t3);
	Sprite rock(t4);

	//Make walls
	float leftWall = 100; float rightWall = 100;
	RectangleShape leftBorder;
	leftBorder.setSize(Vector2f(leftWall, (float)windowHeight));
	leftBorder.setFillColor(Color::Black);
	leftBorder.setPosition(0, 0);
	RectangleShape rightBorder;
	rightBorder.setSize(Vector2f(rightWall, (float)windowHeight));
	rightBorder.setFillColor(Color::Black);
	rightBorder.setPosition(windowWidth - rightWall, 0);

	//Shaders
	Shader shader;
	shader.loadFromFile("shader.frag",Shader::Fragment);
	shader.setUniform("frag_ScreenResolution", Vector2f((float)windowWidth, (float)windowHeight));
	shader.setUniform("frag_LightAttenuation", 80.f);
	RenderStates states;
	states.shader = &shader;

	//Instatiate objects
	std::list<Entity*> entities;
	Player* blueShip = new Player;
	
	//Settings for the objects
	float xPos = (float)windowWidth / 2; float yPos = (float)windowHeight / 2;
	blueShip->SetSprite(shipSprite, 16, 16);
	blueShip->Settings(xPos, yPos);
	entities.push_back(blueShip);

	Rock* rocks = new Rock;
	rocks->SetSprite(rock, 32, 32);
	rocks->Settings((float)windowWidth / 2, 0);
	entities.push_back(rocks);

	//Game Loop
	while (window.isOpen()) {
		
		Event e;
		while (window.pollEvent(e))
		{
			if (e.type == Event::Closed)
				window.close();	

			if (e.type == Event::KeyPressed)
				if (e.key.code == Keyboard::Escape) window.close(); //Close Game
		}

		if (Keyboard::isKeyPressed(Keyboard::Space)) {
			Projectile *bullet = new Projectile;
			bullet->SetSprite(lineBullet, 0, 0);
			bullet->Settings(blueShip->xPos, blueShip->yPos, blueShip->angle - 90);
			entities.push_back(bullet);
		}

		//Update 
		for (auto i = entities.begin(); i != entities.end();) {
			Entity *e = *i;
			e->Update();
			if (e->life == false) { i = entities.erase(i); delete e; }
			else i++;
		}

		//Shaders
		shader.setUniform("frag_LightOrigin", Vector2f(blueShip->xPos, blueShip->yPos));
		shader.setUniform("frag_LightColor", Vector3f(0, 128.0f, 128.0f));

		//Draw 
		window.clear(Color::White);

		window.draw(background, states);
		window.draw(leftBorder);
		window.draw(rightBorder);

		for (auto i : entities) i->Draw(window);

		window.display();
	}


	return 0;
}
