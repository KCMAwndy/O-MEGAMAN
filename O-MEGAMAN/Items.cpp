#include "Items.h"

Items::Items(sf::Texture* texture, sf::Vector2f position, sf::Vector2f size) {
	body.setSize(size);
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(position);
	body.setTexture(texture);
}

void Items::Update(float elapsedTime,int itemSlot,int *score) {
	switch (itemSlot) {
	case 1:
		*score += 30;
		break;
	case 2:
		*score += 20;
		break;
	case 3:
		*score -= 20;
		break;
	}
	
}

void Items::Draw(sf::RenderWindow& window) {
	window.draw(body);
}