#include "Megaman.h"

Megaman::Megaman(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float jumpHeight) :
	animation(texture, imageCount, switchTime) {
	this->speed = speed;
	this->jumpHeight = jumpHeight;
	row = 0;
	faceRight = true;
	body.setSize(sf::Vector2f(60.0f, 60.0f));
	//body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(360.0f, 720.0f);
	body.setTexture(texture);
}

void Megaman::Update(float elapsedTime, sf::RenderWindow& window){
	velocity.x = 0.0f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		velocity.x -= speed;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		velocity.x += speed;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && canjump) {
		canjump = false;
		velocity.y = -sqrtf(2.0f * 981.0f * jumpHeight);
	}
	velocity.y += 981.0f * elapsedTime;
	if (velocity.x == 0.0f)
		row = 0;
	else {
		row = 1;
		if (velocity.x > 0.0f) {
			faceRight = true;
		}
		else {
			faceRight = false;
		}
	}
	animation.Update(row, elapsedTime, faceRight);
	body.setTextureRect(animation.currentRect);
	body.move(velocity * elapsedTime);

	if (body.getPosition().x <= 20)		//LEFT
		body.setPosition(sf::Vector2f(20.0f, body.getPosition().y));		//RIGHT
	if(body.getPosition().x>=window.getSize().x-body.getGlobalBounds().width-20)	
		body.setPosition(window.getSize().x-body.getGlobalBounds().width-20,body.getPosition().y);
	if (body.getPosition().y <= 60)		//TOP
		body.setPosition(sf::Vector2f(body.getPosition().x, 60.0f));
	if (body.getPosition().y >= window.getSize().y - body.getGlobalBounds().height - 180) {		//BOTTOM
		canjump = true;
		body.setPosition(body.getPosition().x, window.getSize().y - body.getGlobalBounds().height - 180);
	}
}

void Megaman::Draw(sf::RenderWindow& window) {
	window.draw(body);
}

void Megaman::OnCollision(sf::Vector2f direction)
{
	if (direction.x < 0.0f) {
		velocity.x = 0.0f;//Colision on the left
		// ผ่านไม่ได้มีสิ่งของอยู่ด้านช้าย v = 0
	}
	else if (direction.x > 0.0f) {
		velocity.x = 0.0f;//Colision on the right
		// ผ่านไม่ได้มีสิ่งของอยู่ด้านขวา v = 0
	}
	if (direction.y < 0.0f ) {
		velocity.y = 0.0f;//Colision on the bottom
		canjump = true;
		// ผ่านไม่ได้มีสิ่งของอยู่ล่าง , กระโดดได้ , v = 0
	}
	else if (direction.y > 0.0f) {
		velocity.y = 0.0f;//Colision on the top
		// ผ่านไม่ได้มีสิ่งของอยู่บน v = 0
	}
}
