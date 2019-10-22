#pragma once
#include <math.h>


class Entity
{
public:
	float xPos, yPos, xDir, yDir, R, angle;
	int life;
	sf::Sprite sprite;

	Entity();
	void SetSprite(sf::Sprite & s, float xOrg, float yOrg);
	void Settings(float xPosition, float yPosition, float angle = 0, float radius = 1);
	void Draw(sf::RenderWindow & window, sf::RenderStates states = sf::RenderStates::Default);
	virtual ~Entity();
	virtual void Update();
protected:
	std::list<Entity*> listEntities;
};



Entity::Entity()
{
	life = 1;
	xPos = 0.0f; yPos = 0.0f;
	xDir = 0.0f; yDir = 0.0f;
}

inline void Entity::SetSprite(sf::Sprite & s, float xOrg, float yOrg)
{
	s.setOrigin(xOrg, yOrg);
	sprite = s;
}

inline void Entity::Settings(float xPosition, float yPosition, float angle, float radius)
{
	xPos = xPosition; yPos = yPosition;
	this->angle = angle;
	R = radius;
}

inline void Entity::Draw(sf::RenderWindow & window, sf::RenderStates states)
{
	sprite.setPosition(xPos, yPos);
	sprite.setRotation(angle);
	window.draw(sprite, states);
}

inline void Entity::Update()
{
}

Entity::~Entity()
{
}
