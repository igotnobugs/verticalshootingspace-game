#pragma once
#include <math.h>
#include <iostream>
#include "class\Animation.h"

class Entity
{
public:
	Entity();
	std::string GetName();
	void SetName(std::string name);
	int GetLife();
	void SetLife(int value);
	sf::Vector2f GetPosition();
	void SetPosition(float x, float y);
	void SetPosition(sf::Vector2f position);
	int GetDamage();
	void SetDamage(int value);
	void ReduceHp(int value);
	int GetRadius();
	void SetRadius(int value);
	int GetAngle();
	void SetAngle(int value);
	void SetBorder(sf::Vector2f upperLeftPoint, sf::Vector2f bottomRightPoint);
	void SetSprite(sf::Sprite & s, float xOrg, float yOrg);
	void SetAnimation(Animation & animation);
	void SetScale(int value);

	
	void Settings(sf::Vector2f position, float angle = 0);
	void Draw(sf::RenderWindow & window, sf::RenderStates states = sf::RenderStates::Default);
	virtual void Update();
	virtual ~Entity();
protected:
	std::string mName;
	int mLife;
	sf::Vector2f mPosition; sf::Vector2f mDirection;
	int mDamage;
	float mRadius, mAngle;
	sf::Vector2f mBorderUpLeft, mBorderBottomRight;
	sf::Sprite mSprite;
	Animation mAnimation;
};



Entity::Entity()
{
	mLife = 1;
	mPosition.x = 0.f; mPosition.y = 0.f;
	mDirection.x = 0.f; mDirection.y = 0.f;
	mBorderUpLeft.x = 0.f; mBorderUpLeft.y = 0.f;
	mBorderBottomRight.x = FLT_MAX; mBorderBottomRight.y = FLT_MAX;
}

inline std::string Entity::GetName()
{
	return mName;
}

inline void Entity::SetName(std::string name)
{
	mName = name;
}

inline int Entity::GetLife()
{
	return mLife;
}

inline void Entity::SetLife(int value)
{
	mLife = value;
}

inline void Entity::SetSprite(sf::Sprite & s, float xOrg, float yOrg)
{
	s.setOrigin(xOrg, yOrg);
	mSprite = s;
}

inline void Entity::SetAnimation(Animation & animation)
{
	mAnimation = animation;
}

inline void Entity::SetScale(int value)
{
	mAnimation.sprite.setScale(sf::Vector2f(value, value));
}

inline void Entity::Settings(sf::Vector2f position, float angle)
{
	mPosition = position;
	mAngle = angle;
}

inline void Entity::Draw(sf::RenderWindow & window, sf::RenderStates states)
{
	if (mAnimation.isAnimationOn) {
		mAnimation.Update();
		mAnimation.sprite.setPosition(mPosition.x, mPosition.y);
		mAnimation.sprite.setRotation(mAngle);
		window.draw(mAnimation.sprite);
	}
	else {
		mSprite.setPosition(mPosition.x, mPosition.y);
		mSprite.setRotation(mAngle);
		window.draw(mSprite, states);
	}
}

inline sf::Vector2f Entity::GetPosition()
{
	return mPosition;
}

inline void Entity::SetPosition(float x, float y)
{
	mPosition.x = x; mPosition.y = y;
}

inline void Entity::SetPosition(sf::Vector2f position)
{
	mPosition = position;
}

inline int Entity::GetDamage()
{
	return mDamage;
}

inline void Entity::SetDamage(int value)
{
	mDamage = value;
}

inline void Entity::ReduceHp(int value)
{
	mLife -= value;
}

inline int Entity::GetRadius()
{
	return mRadius;
}

inline void Entity::SetRadius(int value)
{
	mRadius = value;
}

inline int Entity::GetAngle()
{
	return mAngle;
}

inline void Entity::SetAngle(int value)
{
	mAngle = value;
}

inline void Entity::SetBorder(sf::Vector2f upperLeftPoint, sf::Vector2f bottomRightPoint)
{
	mBorderUpLeft = upperLeftPoint;
	mBorderBottomRight = bottomRightPoint;
}

inline void Entity::Update()
{
}

Entity::~Entity()
{
	std::cout << mName << " destroyed at Position " << mPosition.x << ", " << mPosition.y << "." << std::endl;
}
