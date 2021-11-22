#include "Megaman.h"

Megaman::Megaman(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float jumpHeight) :
	animation(texture, imageCount, switchTime){
	this->speed = speed;
	this->jumpHeight = jumpHeight;
	row = 0;
	faceRight = true;
	iceHit = false;
	fireHit = false;
	dead = false;
	body.setSize(sf::Vector2f(75.0f, 75.0f));
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(360.0f, 500.0f);
	body.setTexture(texture);
}

void Megaman::Update(float elapsedTime, sf::RenderWindow& window, bool iceHit, bool fireHit, bool dead){
	if (dead) {
	row = 4;
	if (velocity.x > 0.0f) {
		faceRight = true;
	}
	else {
		faceRight = false;
	}
	animation.limitUpdate(row, elapsedTime, faceRight);
	body.setTextureRect(animation.currentRect);
	velocity.x =0;
	velocity.y += 5;
	body.move(velocity * elapsedTime);
	}
	else if (iceHit) {
		row = 2;
		if (velocity.x > 0.0f) {
			faceRight = true;
		}
		else {
			faceRight = false;
		}
		animation.limitUpdate(row, elapsedTime,faceRight);
		body.setTextureRect(animation.currentRect);
	}
	else if(fireHit) {
		row = 3;
		velocity.y = -40.0f;
		body.move(velocity * elapsedTime);
			if (velocity.x > 0.0f) {
				faceRight = true;
			}
			else {
				faceRight = false;
			}
		velocity.x = 0;
		animation.limitUpdate(row, elapsedTime, faceRight);
		body.setTextureRect(animation.currentRect);
	}
	else {
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
	}
	if (body.getPosition().x <= body.getOrigin().x + 20.0f)		//LEFT
		body.setPosition(sf::Vector2f(body.getOrigin().x + 20.0f, body.getPosition().y));
	if(body.getPosition().x>=window.getSize().x- body.getOrigin().x - 20.0f)	//RIGHT
		body.setPosition(window.getSize().x- body.getOrigin().x - 20.0f,body.getPosition().y);
	if (body.getPosition().y <= 80)		//TOP
		body.setPosition(sf::Vector2f(body.getPosition().x, 80.0f));
	if (body.getPosition().y >= window.getSize().y - body.getOrigin().y - 175.0f) {		//BOTTOM
		canjump = true;
		body.setPosition(body.getPosition().x, window.getSize().y - body.getOrigin().y - 175.0f);
	}
}

void Megaman::SetPosition(float x, float y)
{
	body.setPosition(x, y);
}

void Megaman::Hit(float elapsedTime, float scale)
{
	canjump = false;
	velocity.y = scale;
	body.move(velocity * elapsedTime);
}

void Megaman::Draw(sf::RenderWindow& window) {
	window.draw(body);
}
