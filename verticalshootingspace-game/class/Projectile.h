#pragma once
#include "class/Entity.h"

class Projectile :
	public Entity
{
public:
	float maxSpeed, acceleration;
	float mShootDirection;

	Projectile();
	void Update();
	virtual ~Projectile();
};



Projectile::Projectile()
{
	maxSpeed = 10.f;
	acceleration = 0.5f;
	mDamage = 1;
}

inline void Projectile::Update()
{
	float DEGTORAD = 0.017453f;

	mDirection.x = cos(mShootDirection*DEGTORAD) * 6;
	mDirection.y = sin(mShootDirection*DEGTORAD) * 6;

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


Projectile::~Projectile()
{
}
