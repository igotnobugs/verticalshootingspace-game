#pragma once
#include "class/Entity.h"
#include "class/Projectile.h"

class Player :
	public Entity
{
public:
	float maxSpeed;
	float acceleration;

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
}

inline void Player::Controls() 
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			mDirection.y -= acceleration;
		else
			mDirection.y += acceleration;
		vertical = true;
	}
	else vertical = false;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) 
			mDirection.x -= acceleration;
		else 
			mDirection.x += acceleration;
		horizontal = true;
	}
	else horizontal = false;
}

inline void Player::Update()
{
	Controls();

	if (!vertical) 
		mDirection.y *= 0.95f;
	if (!horizontal) 
		mDirection.x *= 0.95f;

	float speed = sqrt(mDirection.x*mDirection.x + mDirection.y * mDirection.y);
	if (speed > maxSpeed) {
		mDirection *= maxSpeed / speed;
	}

	mPosition += mDirection;

	if ((mPosition.x < mBorderUpLeft.x || mPosition.x  > mBorderBottomRight.x) ||
		(mPosition.y < mBorderUpLeft.y || mPosition.y > mBorderBottomRight.y)) {
		mLife = false;
	}
}


Player::~Player()
{
}
