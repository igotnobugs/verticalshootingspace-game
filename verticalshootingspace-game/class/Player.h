#pragma once
#include "class/Entity.h"
#include "class/Projectile.h"

class Player :
	public Entity
{
public:
	float maxSpeed;
	float acceleration;
	Projectile bullet;

	Player();
	void Controls();
	void Update();
	virtual ~Player();

private:
	bool vertical = false; bool horizontal = false;
};



Player::Player()
{
	maxSpeed = 5.f;
	acceleration = 0.3f;
	bullet.damage = 5;
}

inline void Player::Controls() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) 
			yDir -= acceleration;
		else 
			yDir += acceleration;
		vertical = true;
	}
	else vertical = false;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) 
			xDir -= acceleration;
		else 
			xDir += acceleration;
		horizontal = true;
	}
	else horizontal = false;
}

inline void Player::Update()
{
	Controls();

	if (!vertical) 
		yDir *= 0.95f;
	if (!horizontal) 
		xDir *= 0.95f;

	float speed = sqrt(xDir*xDir + yDir * yDir);
	if (speed > maxSpeed)
	{
		xDir *= maxSpeed / speed;
		yDir *= maxSpeed / speed;
	}

	xPos += xDir;
	yPos += yDir;
}


Player::~Player()
{
}
