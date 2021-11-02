#include "MiniBoss.h"

MiniBoss::MiniBoss(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, sf::Vector2f position, float speed) :
	animation(texture, imageCount, switchTime) {
	row = 0;
	randomMove = 0;
	this->speed = speed;
	body.setSize(sf::Vector2f(60.0f, 80.0f));
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(position);
	body.setTexture(texture);
}

void MiniBoss::Update(float elapsedTime,float movement=0.0f) {
	velocity.y = 0.0f;
	velocity.x = movement;
	body.move(velocity );
	row = 0;
	animation.UpdateBoss(row, elapsedTime);
	body.setTextureRect(animation.currentRect);
}

void MiniBoss::Hunt(float elapsedTime)
{
	velocity.x = -speed;
	if (body.getPosition().x <= 60.0f) {
		animation.UpdateMiniBoss(2);
		speed = -200;
		//printf("\n\n\n\n%f", speed);
		body.setPosition(body.getPosition().x+5.0f, body.getPosition().y + 100.0f);
	}
	//printf("\n\n\n\n%f", speed);
	if (body.getPosition().x >= 670.0f) {
		speed = 200;
		animation.UpdateMiniBoss(3);
		body.setPosition(body.getPosition().x-5.0f, body.getPosition().y + 100.0f);
	}
	row = 0;
	//animation.UpdateMiniBoss(2);
	body.setTextureRect(animation.currentRect);
	body.move(velocity*elapsedTime);
}


void MiniBoss::Draw(sf::RenderWindow& window) {
	window.draw(body);
}

void MiniBoss::SetPosition(float x, float y)
{
	body.setPosition(x, y);
}
