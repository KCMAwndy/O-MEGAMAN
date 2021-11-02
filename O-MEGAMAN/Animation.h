#pragma once
#include<SFML\Graphics.hpp>

class Animation
{
public:
	Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime);
	void Update(int row, float elapsedTime, bool faceRight);
	void UpdateBoss(int row, float elapsedTime);
	void UpdateMiniBoss(int column);
	void limitUpdate(int row, float elapsedTime,bool faceRight);
public:
	sf::IntRect currentRect;
private:
	sf::Vector2u imageCount;
	sf::Vector2f currentImage;
	float totalTime;
	float switchTime;
};