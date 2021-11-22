#include "Items.h"

Items::Items(sf::Texture* texture, sf::Vector2f position, sf::Vector2f size) {
	body.setSize(size);
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(position);
	body.setTexture(texture);
}

void Items::SetPosition(sf::Vector2f position)
{
	body.setPosition(position);
}

void Items::Move(float elapsedTime){
	velocity.x = 0.0f;
	velocity.y = 200.0f;
	return body.move(velocity * elapsedTime);
}

void Items::Draw(sf::RenderWindow& window) {
	window.draw(body);
}