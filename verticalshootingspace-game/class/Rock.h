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
	mDirection.y = 1;
	maxSpeed = 5.f;
	mDamage = 1.f;
}

inline void Rock::Update() {
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


Rock::~Rock()
{
}
