#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <list>

//SpriteSheet
class Spritesheet
{
public:
	bool isAnimated;
	float curFrame, mFrameSpeed;
	sf::Sprite sprite;
	std::vector<sf::IntRect> frames;

	Spritesheet();
	Spritesheet(sf::Texture &texture, int width, int height, int frameCount = 1, int columns = 1, float frameSpeed = 0.5f);
	Spritesheet(sf::Texture &texture, sf::Vector2i position, int width, int height, int frameCount = 1, int columns = 1, float frameSpeed = 0.5f);
	void Update();
	bool IsEnd();
	~Spritesheet();
};



Spritesheet::Spritesheet()
{
}

Spritesheet::Spritesheet(sf::Texture &texture, int width, int height, int frameCount, int columns, float frameSpeed)
{
	isAnimated = (frameCount == 1) ? false : true;
	while (frameCount > 0) {
		int rows = frameCount / columns;
		for (int r = 0; r < rows; r++)		
			for (int c = 0; c < columns; c++) {
				frames.push_back(sf::IntRect(c * width, r * height, width, height));
				frameCount--;
			}
	}
	curFrame = 0;
	mFrameSpeed = frameSpeed;
	sprite.setTexture(texture);
	sprite.setOrigin(width / 2, height / 2);
	sprite.setTextureRect(frames[0]);
}

Spritesheet::Spritesheet(sf::Texture &texture, sf::Vector2i position, int width, int height, int frameCount, int columns, float frameSpeed)
{
	isAnimated = (frameCount == 1) ? false : true;
	while (frameCount > 0) {
		int rows = frameCount / columns;
		for (int r = 0; r < rows; r++)
			for (int c = 0; c < columns; c++) {
				frames.push_back(sf::IntRect((c * width) + position.x, (r * height) + position.y, width, height));
				frameCount--;
			}
	}
	curFrame = 0;
	mFrameSpeed = frameSpeed;
	sprite.setTexture(texture);
	sprite.setOrigin(width / 2, height / 2);
	sprite.setTextureRect(frames[0]);
}

inline void Spritesheet::Update()
{
	curFrame += mFrameSpeed;
	int totalFrames = frames.size();
	if (curFrame >= totalFrames) curFrame -= totalFrames;
	if (totalFrames > 0) sprite.setTextureRect(frames[int(curFrame)]);
}

inline bool Spritesheet::IsEnd()
{
	return curFrame + mFrameSpeed >= frames.size();
}

Spritesheet::~Spritesheet()
{
}