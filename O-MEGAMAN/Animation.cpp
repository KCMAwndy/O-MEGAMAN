#include "Animation.h"

Animation::Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime) {
	this->imageCount = imageCount;
	this->switchTime = switchTime;
	totalTime = 0.0f;
	currentImage.x = 0;
	currentRect.width = texture->getSize().x / float(imageCount.x);
	currentRect.height = texture->getSize().y / float(imageCount.y);
}

void Animation::Update(int row, float elapsedTime, bool faceRight){
	currentImage.y = row;
	totalTime += elapsedTime;
	if (totalTime >= switchTime) {
		totalTime -= switchTime;
		currentImage.x++;
		if (currentImage.x >= imageCount.x) {
			currentImage.x = 0;
		}
	}
	currentRect.top = currentImage.y * currentRect.height;
	if (faceRight) {
		currentRect.left = currentImage.x * currentRect.width;
		currentRect.width = abs(currentRect.width);
	}
	else {
		currentRect.left = (currentImage.x + 1) * abs(currentRect.width);
		currentRect.width = -abs(currentRect.width);
	}
}

void Animation::UpdateBoss(int row, float elapsedTime){
	currentImage.y = row;
	totalTime += elapsedTime;
	if (totalTime >= switchTime) {
		totalTime -= switchTime;
		currentImage.x++;
		if (currentImage.x >= 2) {
			currentImage.x = 0;
		}
	}
	currentRect.top = currentImage.y * currentRect.height;
	currentRect.left = currentImage.x * currentRect.width;
}

void Animation::UpdateMiniBoss(int column) {
	currentImage.y = 0;
	currentImage.x = column;
	currentRect.top = currentImage.y * currentRect.height;
	currentRect.left = currentImage.x * currentRect.width;
}

void Animation::limitUpdate(int row, float elapsedTime,bool faceRight)
{
	currentImage.y = row;
	totalTime += elapsedTime;
	if (totalTime >= switchTime) {
		totalTime -= switchTime;
		currentImage.x++;
	}
	if (currentImage.x >= imageCount.x) {
		currentImage.x = imageCount.x-1;
	}
	currentRect.top = currentImage.y * currentRect.height;
	if (faceRight) {
		currentRect.left = currentImage.x * currentRect.width;
		currentRect.width = abs(currentRect.width);
	}
	else {
		currentRect.left = (currentImage.x + 1) * abs(currentRect.width);
		currentRect.width = -abs(currentRect.width);
	}
}
