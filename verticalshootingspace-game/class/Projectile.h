#pragma once
#include "class/Object.h"

class Projectile :
	public Object
{
public:
	Projectile();
	Projectile(std::string name, sf::Sprite & s, sf::Vector2f size, sf::Vector2f position = sf::Vector2f(0, 0));
	Projectile(std::string name, sf::Sprite & s, sf::Vector2f size, Object * firedFromObject);
	virtual ~Projectile();
	
	void SetShootDirection(float value);
	void SetShootDirection(sf::Vector2f vectorDirection);
	void ShootAt(Object * a);
	float GetShootDirection();

	void Update();
private:
	float m_ShootDirection = up;
};



Projectile::Projectile()
{
}

inline Projectile::Projectile(std::string name, sf::Sprite & s, sf::Vector2f size, sf::Vector2f position)
{
	m_Name = name;
	m_Sprite = s;
	m_Shape.setPosition(position);
	m_MaxSpeed = 10.f;
	m_Acceleration = 0.5f;
	m_Damage = 1;
	m_Shape.setSize(size);
	m_Shape.setOrigin(s.getOrigin());
	m_Shape.setTexture(s.getTexture());
}

inline Projectile::Projectile(std::string name, sf::Sprite & s, sf::Vector2f size, Object * firedFromObject)
{
	m_Name = name;
	m_Sprite = s;
	m_MaxSpeed = 10.f;
	m_Acceleration = 0.5f;
	m_Damage = 1;
	m_Shape.setSize(size);
	m_Shape.setPosition(firedFromObject->GetShape().getPosition());
	m_Shape.setOrigin(s.getOrigin());
	m_Shape.setTexture(s.getTexture());
	SetPoint(firedFromObject->GetPoint());
	SetShootDirection(firedFromObject->GetFiringPoint());
	m_Shape.setRotation(firedFromObject->GetShape().getRotation());
}

Projectile::~Projectile()
{
}

inline void Projectile::SetShootDirection(float value)
{
	m_ShootDirection = value;
}

inline void Projectile::SetShootDirection(sf::Vector2f vectorDirection)
{
	float theta = atan2f(vectorDirection.y , vectorDirection.x);
	m_ShootDirection = (theta*RADTODEG);
}

inline void Projectile::ShootAt(Object * a)
{
	sf::Vector2f vectorDirection = a->GetShape().getPosition() - m_Shape.getPosition();
	float theta = atan2f(vectorDirection.y, vectorDirection.x);
	m_ShootDirection = (theta*RADTODEG);
}

inline float Projectile::GetShootDirection()
{
	return m_ShootDirection;
}

inline void Projectile::Update()
{
	m_Direction.x = cos(m_ShootDirection*DEGTORAD) * 6;
	m_Direction.y = sin(m_ShootDirection*DEGTORAD) * 6;


	Object::Update();
}