#pragma once
#include <math.h>
#include <iostream>
#include "class\Animation.h"

class Entity
{
public:
	std::string mName;
	int mLife;
	sf::Vector2f mPosition; sf::Vector2f mDirection;
	int mDamage;
	float mRadius, mAngle;
	sf::Vector2f mBorderUpLeft, mBorderBottomRight;
	sf::Sprite mSprite;
	Animation mAnimation;

	Entity();
	void SetSprite(sf::Sprite & s, float xOrg, float yOrg);
	void Settings(sf::Vector2f position, float angle = 0);
	void Draw(sf::RenderWindow & window, sf::RenderStates states = sf::RenderStates::Default);
	sf::Vector2f GetPosition();
	virtual void Update();
	virtual ~Entity();
protected:
	std::list<Entity*> listEntities;
};



Entity::Entity()
{
	mLife = 1;
	mPosition.x = 0.f; mPosition.y = 0.f;
	mDirection.x = 0.f; mDirection.y = 0.f;
	mBorderUpLeft.x = 0.f; mBorderUpLeft.y = 0.f;
	mBorderBottomRight.x = FLT_MAX; mBorderBottomRight.y = FLT_MAX;
}

inline void Entity::SetSprite(sf::Sprite & s, float xOrg, float yOrg)
{
	s.setOrigin(xOrg, yOrg);
	mSprite = s;
}

inline void Entity::Settings(sf::Vector2f position, float angle)
{
	mPosition = position;
	mAngle = angle;
}

inline void Entity::Draw(sf::RenderWindow & window, sf::RenderStates states)
{
	//mAnimation.sprite.setPosition(mPosition.x, mPosition.y);
	//mAnimation.sprite.setRotation(mAngle + 90);
	//window.draw(mAnimation.sprite);

	mSprite.setPosition(mPosition.x, mPosition.y);
	mSprite.setRotation(mAngle);
	window.draw(mSprite, states);
}

inline sf::Vector2f Entity::GetPosition()
{
	return mPosition;
}

inline void Entity::Update()
{
}

Entity::~Entity()
{
	std::cout << mName << " destroyed at Position " << mPosition.x << ", " << mPosition.y << "." << std::endl;
}
