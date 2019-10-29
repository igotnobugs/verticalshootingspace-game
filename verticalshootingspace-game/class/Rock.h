#pragma once
#include "Object.h"

class Rock :
	public Object
{
public:
	Rock();
	Rock(std::string name, sf::Sprite & s, sf::Vector2f size, sf::Vector2f position = sf::Vector2f(0, 0));
	void Update();
	virtual ~Rock();
};



Rock::Rock()
{	
}

inline Rock::Rock(std::string name, sf::Sprite & s, sf::Vector2f size, sf::Vector2f position)
{
	m_Name = name;
	m_Sprite = s;
	m_Direction.y = 1;
	m_MaxSpeed = 5.f;
	m_Damage = 1.f;
	m_Shape.setSize(size);
	m_Shape.setPosition(position);
	m_Shape.setOrigin(s.getOrigin());
	m_Shape.setTexture(s.getTexture());
}

inline void Rock::Update() {
	Object::Update();
}


Rock::~Rock()
{
}
