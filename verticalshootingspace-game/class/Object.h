#pragma once
#include "Entity.h"
#include "Spritesheet.h"
//Objects In Game
class Object :
	public Entity
{
public:
	Object();
	virtual ~Object();

	const std::string & GetName();
	void SetName(std::string name);

	const int & GetLife();
	void SetLife(int value);

	const int & GetDamage();
	void SetDamage(int value);
	void ReduceHp(int value);

	bool isCollideWith(Object * e);

	void SetBorder(float width, float height);
	void SetBorder(sf::Vector2f upperLeftPoint, sf::Vector2f bottomRightPoint);

	virtual void Update() override;

protected:
	std::string m_Name = "None";
	Spritesheet spriteSheet;
	int m_Life = 1;
	int m_Damage = 0;
	sf::Sprite m_Sprite;
	//Acceleration adds to Speed until Speed == MaxSpeed
	float m_Acceleration, m_Speed, m_MaxSpeed;
	sf::Vector2f m_Direction = sf::Vector2f(0, 0);
	sf::Vector2f m_Velocity = sf::Vector2f(0, 0);
	//first = Upper Left, Second = BottomRight
	std::pair<sf::Vector2f, sf::Vector2f> m_Border;
};



Object::Object()
{
	m_Sprite.setRotation(m_Point * -1);
	m_Border.first = sf::Vector2f(-FLT_MIN, -FLT_MIN);
	m_Border.second = sf::Vector2f(FLT_MAX, FLT_MAX);
}

Object::~Object()
{
	std::cout << m_Name << " destroyed at Position " << m_Shape.getPosition().x
		<< ", " << m_Shape.getPosition().y << std::endl;
}

inline const std::string & Object::GetName()
{
	return m_Name;
}

inline void Object::SetName(std::string name)
{
	m_Name = name;
}

inline const int & Object::GetLife()
{
	return m_Life;
}

inline void Object::SetLife(int value)
{
	m_Life = value;
}

inline const int & Object::GetDamage()
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

inline void Object::SetBorder(float width, float height)
{
	m_Border.first = sf::Vector2f(0, 0);
	m_Border.second = sf::Vector2f(width, height);
}

inline void Object::SetBorder(sf::Vector2f upperLeftPoint, sf::Vector2f bottomRightPoint)
{
	m_Border.first = upperLeftPoint;
	m_Border.second = bottomRightPoint;
}

inline void Object::Update()
{
	if (m_Speed > m_MaxSpeed)
		m_Direction *= m_MaxSpeed / m_Speed;

	m_Shape.move(m_Direction);

	if ((m_Shape.getPosition().x < m_Border.first.x 
		|| m_Shape.getPosition().x  > m_Border.second.x) 
		|| (m_Shape.getPosition().y < m_Border.first.y 
			|| m_Shape.getPosition().y > m_Border.second.y)) {
		m_Life = false;
	}
}