#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include "class\Spritesheet.h"

enum direction { right = 0, down = 90, left = 180, up = 270};
const float DEGTORAD = M_PI/180;
const float RADTODEG = 180/M_PI;

//Deals with Shape Transform manipulation

class Entity
{
public:
	Entity();
	sf::Vector2f GetPosition();
	void SetPosition(float x, float y);
	void SetPosition(sf::Vector2f position);
	float GetRotation();
	void SetRotation(int value);
	void SetRotation(sf::Vector2f vectorRotation);
	float GetFiringPoint(); //Current rotation with point
	void Rotate(int value);
	void Rotate(sf::Vector2f rotate);
	float GetPoint();
	void SetPoint(float value); 
	int GetRadius();
	void SetRadius(int value);
	void PointAt(sf::Vector2f position);
	void PointAt(sf::Vector2i position); //Used mostly for pointing at mousePosition
	void IncrementByUntil(float & toChange, float increment, float max);
	float lerp(float intial, float final, float t);


	void SetBorder(float width, float height); //m_BorderUpLeft is set at (0, 0)
	void SetBorder(sf::Vector2f upperLeftPoint, sf::Vector2f bottomRightPoint);
	void Draw(sf::RenderWindow & window, sf::RenderStates states = sf::RenderStates::Default);
	virtual void Update();
	virtual ~Entity();

protected:
	float m_Size, m_Radius, m_Point;
	float m_Acceleration, m_Speed, m_MaxSpeed; //Acceleration adds to Speed until Speed >= MaxSpeed
	sf::RectangleShape m_Shape;
	sf::Vector2f m_Direction = sf::Vector2f(0, 0); //Unit Vector direction //m_Direction is handled by outside forces
	sf::Vector2f m_Velocity = sf::Vector2f(0, 0); //m_Direction multipled by a Speed
	sf::Vector2f m_BorderUpLeft = sf::Vector2f(FLT_MIN, FLT_MIN);
	sf::Vector2f m_BorderBottomRight = sf::Vector2f(FLT_MAX, FLT_MAX);
};



Entity::Entity()
{	
	m_Shape.setRotation(m_Point);
}

inline void Entity::Draw(sf::RenderWindow & window, sf::RenderStates states)
{
	window.draw(m_Shape, states);
}

inline sf::Vector2f Entity::GetPosition()
{
	return m_Shape.getPosition();
}

inline void Entity::SetPosition(float x, float y)
{
	m_Shape.setPosition(x, y);
}

inline void Entity::SetPosition(sf::Vector2f position)
{
	m_Shape.setPosition(position);
}

inline int Entity::GetRadius()
{
	return m_Radius;
}

inline void Entity::SetRadius(int value)
{
	m_Radius = value;
}

inline void Entity::PointAt(sf::Vector2f position)
{
	sf::Vector2f vectorDirection = position - this->GetPosition();
	float theta = atan2f(vectorDirection.y, vectorDirection.x);
	m_Shape.setRotation(theta*RADTODEG);
}

inline void Entity::PointAt(sf::Vector2i position)
{
	sf::Vector2i vectorDirection = position - sf::Vector2i(this->GetPosition().x, this->GetPosition().y);
	float theta = atan2f(vectorDirection.y, vectorDirection.x);
	m_Shape.setRotation((theta*RADTODEG) - m_Point);
}

inline void Entity::IncrementByUntil(float & toChange, float increment, float max)
{
	//its decreasing
	if ((toChange > max) && (increment < 0)) {
		if (toChange > max) {
			toChange += increment;
		}
		else toChange = max;
	}
	else {
		if (toChange > max) {
			toChange += increment;
		}
		else toChange = max;
	}
	return;
}

inline float Entity::lerp(float intial, float final, float t)
{
	return (1 - t) * intial + t * final;
}

inline float Entity::GetRotation()
{
	return m_Shape.getRotation();
}

inline float Entity::GetFiringPoint()
{
	return m_Shape.getRotation() + m_Point;
}

inline void Entity::SetRotation(int value)
{
	m_Shape.setRotation(value);
}

inline void Entity::SetRotation(sf::Vector2f vectorRotation)
{
	float theta = atan2f(vectorRotation.y, vectorRotation.x);
	m_Shape.setRotation(theta*RADTODEG);
}

inline void Entity::Rotate(int value)
{
	m_Shape.rotate(value);
}

inline void Entity::Rotate(sf::Vector2f rotate)
{
	float theta = atan2f(rotate.y, rotate.x);
	m_Shape.rotate((theta*RADTODEG) + m_Point);
}

inline float Entity::GetPoint()
{
	return m_Point;
}

inline void Entity::SetPoint(float value)
{
	m_Point = value;
}

inline void Entity::SetBorder(sf::Vector2f upperLeftPoint, sf::Vector2f bottomRightPoint)
{
	m_BorderUpLeft = upperLeftPoint;
	m_BorderBottomRight = bottomRightPoint;
}

inline void Entity::SetBorder(float width, float height)
{
	m_BorderUpLeft = sf::Vector2f(0, 0);
	m_BorderBottomRight = sf::Vector2f(width, height);
}

inline void Entity::Update()
{
}

Entity::~Entity()
{
}
