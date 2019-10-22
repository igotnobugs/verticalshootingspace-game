#pragma once
#include "Entity.h"
class Rock :
	public Entity
{
public:
	float maxSpeed;

	Rock();
	void Update();
	virtual ~Rock();
};



Rock::Rock()
{
	yDir = 1;
	maxSpeed = 5.f;
}

inline void Rock::Update()
{
	float speed = sqrt(xDir*xDir + yDir * yDir);
	if (speed > maxSpeed)
	{
		xDir *= maxSpeed / speed;
		yDir *= maxSpeed / speed;
	}

	xPos += xDir;
	yPos += yDir;

	if ((GetPosition().x < borderUpLeft.x || GetPosition().x  > borderBottomRight.x) ||
		(GetPosition().y < borderUpLeft.y || GetPosition().y > borderBottomRight.y)) {
		life = false;
	}
}


Rock::~Rock()
{
}
