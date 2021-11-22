#include "Minion.h"

Minion::Minion(sf::Texture* texture, sf::Vector2f position,sf::Vector2f size,float speed) {
	this->speed = speed;
	this->faceRight = faceRight;
	collectTime = 0.0f;
	body.setSize(size);
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(position);
	collectPostition = position.x;
	body.setTexture(texture);
}


void Minion::Update(float elapsedTime) {
		if (collectPostition > 360.0f) {
			velocity.x = -speed;
		}
		else if (collectPostition < 360.0f) {
			velocity.x = speed;
		}
	body.move(velocity * elapsedTime);
}

void Minion::Draw(sf::RenderWindow& window) {
	window.draw(body);
}

