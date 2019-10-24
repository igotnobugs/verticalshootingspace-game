#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <list>

class Animation
{
public:
	float curFrame, mFrameSpeed;
	sf::Sprite sprite;
	std::vector<sf::IntRect> frames;
	bool isAnimationOn;

	Animation();
	Animation(sf::Texture &texture, int xPosition, int yPosition, int width, int height, int frameCount, float frameSpeed);
	void Update();
	bool IsEnd();
	~Animation();
};



Animation::Animation()
{
}

Animation::Animation(sf::Texture &texture, int xPosition, int yPosition, int width, int height, int frameCount, float frameSpeed)
{
	curFrame = 0;
	mFrameSpeed = frameSpeed;

	for (int i = 0; i < frameCount; i++)
		frames.push_back(sf::IntRect(xPosition + i * width, yPosition, width, height));

	isAnimationOn = true;
	sprite.setTexture(texture);
	sprite.setOrigin(width / 2, height / 2);
	sprite.setTextureRect(frames[0]);
}

inline void Animation::Update()
{
	curFrame += mFrameSpeed;
	int totalFrames = frames.size();
	if (curFrame >= totalFrames) curFrame -= totalFrames;
	if (totalFrames > 0) sprite.setTextureRect(frames[int(curFrame)]);
}

inline bool Animation::IsEnd()
{
	return curFrame + mFrameSpeed >= frames.size();
}


Animation::~Animation()
{
}