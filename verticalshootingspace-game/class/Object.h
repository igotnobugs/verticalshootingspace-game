#pragma once
#include "Entity.h"
#include "Spritesheet.h"

//Object specific. Name, Life, Damages

class Object :
	public Entity
{
public:
	Object();
	std::string GetName();
	void SetName(std::string name);
	int GetLife();
	void SetLife(int value);
	int GetDamage();
	void SetDamage(int value);
	void ReduceHp(int value);

	bool isCollideWith(Object * e);
	virtual void Update();
	virtual ~Object();

protected:
	std::string m_Name = "None";
	Spritesheet spriteSheet;
	int m_Life = 1;
	int m_Damage = 0;
	sf::Sprite m_Sprite;
};



Object::Object()
{
	m_Sprite.setRotation(m_Point * -1);
}

inline std::string Object::GetName()
{
	return m_Name;
}

inline void Object::SetName(std::string name)
{
	m_Name = name;
}

inline int Object::GetLife()
{
	return m_Life;
}

inline void Object::SetLife(int value)
{
	m_Life = value;
}

inline int Object::GetDamage()
{
	return m_Damage;
}

inline void Object::SetDamage(int value)
{
	m_Damage = value;
}

inline void Object::ReduceHp(int value)
{
	m_Life -= value;
}

inline bool Object::isCollideWith(Object * o)
{
	bool isCollide = m_Shape.getGlobalBounds().intersects(o->m_Shape.getGlobalBounds());
	if (isCollide) std::cout << GetName() << " has collided with " << o->GetName() << std::endl;
	return isCollide;
}

inline void Object::Update()
{
	if (m_Speed > m_MaxSpeed)
		m_Direction *= m_MaxSpeed / m_Speed;


	m_Shape.move(m_Direction);

	if ((m_Shape.getPosition().x < m_BorderUpLeft.x || m_Shape.getPosition().x  > m_BorderBottomRight.x) ||
		(m_Shape.getPosition().y < m_BorderUpLeft.y || m_Shape.getPosition().y > m_BorderBottomRight.y)) {
		m_Life = false;
	}
}

Object::~Object()
{
	std::cout << m_Name << " destroyed at Position " << m_Shape.getPosition().x << ", " << m_Shape.getPosition().y << std::endl;
}
