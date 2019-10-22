#pragma once
#include "class/Entity.h"

class Projectile :
	public Entity
{
public:
	float maxSpeed, acceleration, damage;

	Projectile();
	void Update();
	virtual ~Projectile();
};



Projectile::Projectile()
{
	maxSpeed = 10.f;
	acceleration = 0.5f;
	damage = 1.f;
}

inline void Projectile::Update()
{
	float DEGTORAD = 0.017453f;

	xDir = cos(angle*DEGTORAD) * 6;
	yDir = sin(angle*DEGTORAD) * 6;

	float speed = sqrt(xDir*xDir + yDir * yDir);
	if (speed > maxSpeed)
	{
		xDir *= maxSpeed / speed;
		yDir *= maxSpeed / speed;
	}

	xPos += xDir;
	yPos += yDir;
}


Projectile::~Projectile()
{
}
