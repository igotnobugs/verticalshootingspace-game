#pragma once
#include <math.h>

class Entity
{
public:
	std::string name;
	float xPos, yPos, xDir, yDir, R, angle;
	sf::Vector2f borderUpLeft;
	sf::Vector2f borderBottomRight;
	int life;
	sf::Sprite sprite;

	Entity();
	void SetSprite(sf::Sprite & s, float xOrg, float yOrg);
	void Settings(float xPosition, float yPosition, float angle = 0, float radius = 1);
	void Draw(sf::RenderWindow & window, sf::RenderStates states = sf::RenderStates::Default);
	sf::Vector2f GetPosition();
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
	borderUpLeft.x = 0; borderUpLeft.y = 0;
	borderBottomRight.x = FLT_MAX; borderBottomRight.y = FLT_MAX;
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

inline sf::Vector2f Entity::GetPosition()
{
	return sf::Vector2f(xPos, yPos);
}

inline void Entity::Update()
{
}

Entity::~Entity()
{
}
