#pragma once
#include "class/Object.h"
#include "class/Projectile.h"

class Player :
	public Object
{
public:
	Player();
	Player(std::string name, Spritesheet & s, sf::Vector2f size, sf::Vector2f position = sf::Vector2f(0, 0));
	void Controls();
	void Update();
	virtual ~Player();

private:
	bool vertical = false; bool horizontal = false;
};



Player::Player()
{
}

inline Player::Player(std::string name, Spritesheet & s, sf::Vector2f size, sf::Vector2f position)
{
	m_Name = name;
	m_Sprite = s.sprite;
	m_MaxSpeed = 5.f;
	m_Acceleration = 0.3f;
	m_Shape.setSize(size);
	m_Shape.setPosition(position);
	m_Shape.setOrigin(s.sprite.getOrigin());
	m_Shape.setTexture(s.sprite.getTexture());
}

inline void Player::Controls() 
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			m_Direction.y -= m_Acceleration;
		else
			m_Direction.y += m_Acceleration;
		vertical = true;
	}
	else vertical = false;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) 
			m_Direction.x -= m_Acceleration;
		else 
			m_Direction.x += m_Acceleration;
		horizontal = true;
	}
	else horizontal = false;
}

inline void Player::Update()
{
	Controls();

	if (!vertical) 
		m_Direction.y *= 0.95f;
	if (!horizontal) 
		m_Direction.x *= 0.95f;

	Object::Update();
}


Player::~Player()
{
}
