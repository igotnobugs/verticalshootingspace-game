#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include "class\Spritesheet.h"

enum direction { right = 0, down = 90, left = 180, up = 270};
const float DEGTORAD = M_PI/180;
const float RADTODEG = 180/M_PI;

class Entity
{
public:
	Entity();
	virtual ~Entity();

	sf::RectangleShape & GetShape();

	void SetRot(sf::Vector2f vectorRotation);
	const float & GetFiringPoint();
	void Rotate(sf::Vector2f rotate);

	const float & GetPoint();
	void SetPoint(float value);

	void PointAt(sf::Vector2f position);

	void Draw(sf::RenderWindow & win, sf::RenderStates stat = sf::RenderStates::Default);
	virtual void Update() = 0;
	

protected:
	float m_Size, m_Radius, m_Point;
	sf::RectangleShape m_Shape;
};



Entity::Entity()
{	
	m_Shape.setRotation(m_Point);
}

Entity::~Entity()
{
}

inline void Entity::Draw(sf::RenderWindow & win, sf::RenderStates stat)
{
	win.draw(m_Shape, stat);
}

inline void Entity::PointAt(sf::Vector2f position)
{
	sf::Vector2f vectorDir = position - m_Shape.getPosition();
	float theta = atan2f(vectorDir.y, vectorDir.x);
	m_Shape.setRotation(theta*RADTODEG - m_Point);
}

inline sf::RectangleShape & Entity::GetShape()
{
	return m_Shape;
}

inline const float & Entity::GetFiringPoint()
{
	return m_Shape.getRotation() + m_Point;
}

inline void Entity::SetRot(sf::Vector2f vectorRotation)
{
	float theta = atan2f(vectorRotation.y, vectorRotation.x);
	m_Shape.setRotation(theta*RADTODEG);
}

inline void Entity::Rotate(sf::Vector2f rotate)
{
	float theta = atan2f(rotate.y, rotate.x);
	m_Shape.rotate((theta*RADTODEG) + m_Point);
}

inline const float & Entity::GetPoint()
{
	return m_Point;
}

inline void Entity::SetPoint(float value)
{
	m_Point = value;
}