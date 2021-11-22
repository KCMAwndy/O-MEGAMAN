#include "BatBoss.h"

BatBoss::BatBoss(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, sf::Vector2f position,float speed) :
	animation(texture, imageCount, switchTime) {
	row = 0;
	this->speed = speed;
	checkLR = false;
	checkUP = true;
	bossShoot = true;
	spawnbossBall = false;
	deadBoss = false;
	checkBott = 0;
	ballBossCount = 5;
	body.setSize(sf::Vector2f(240.0f, 120.0f));
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(position);
	body.setTexture(texture);
}

void BatBoss::Update(float elapsedTime,float movement, bool dead) {
	if (dead) {
	row = 1;
	deadBoss = true;
	animation.limitUpdate(row, elapsedTime,false);
	body.setTextureRect(animation.currentRect);
	}
	else {
	velocity.y = 0.0f;
	velocity.x = movement;
	row = 0;
	animation.UpdateBoss(row, elapsedTime);
	body.setTextureRect(animation.currentRect);
	body.move(velocity);
	}
}

void BatBoss::Draw(sf::RenderWindow& window) {
	window.draw(body);
	for (size_t i = 0; i < energyballs.size(); i++) {
		energyballs[i].Draw(window);
	}
}

void BatBoss::SetPosition(sf::Vector2f position)
{
	body.setPosition(position);
}
