#include "EnergyBall.h"

EnergyBall::EnergyBall(sf::Texture* texture,sf::Vector2f position, sf::Vector2f size,float speed){
	this->speed = speed;
	faceRight = true;
	spawnBall = false;
	checkBott = 0;
	body.setSize(size);
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(position);
	body.setTexture(texture);
}

void EnergyBall::Update(float elapsedTime,bool checkUP, int checkBott,bool checkLR) {
	if (checkLR && checkUP==false){
		velocity.x = speed;
	}
	else if (checkUP&&checkLR==false) {
		velocity.y = speed *checkBott;
	}
	else {
		velocity.x = -speed;
	}
	body.move(velocity * elapsedTime);
}

void EnergyBall::FollowUpdate(float elapsedTime, sf::Vector2f megamanPos)
{
	if (megamanPos.x > body.getPosition().x) {
		velocity.x = (body.getPosition().x + speed/2.2 * elapsedTime);
	}
	if (megamanPos.y > body.getPosition().y) {
		velocity.y = (body.getPosition().y + speed/2.2 * elapsedTime);
	}
	if (megamanPos.x < body.getPosition().x) {
		velocity.x = (body.getPosition().x - speed/2.2 * elapsedTime);
	}
	if (megamanPos.y < body.getPosition().y) {
		velocity.y = (body.getPosition().y - speed/2.2 * elapsedTime);
	}
	body.setPosition(velocity);
	float angle = (atan2f(megamanPos.y - velocity.y, megamanPos.x - velocity.x) * 180) / 3.14;
	body.setRotation(angle);
}

void EnergyBall::parabolaUpdtae(float elapsedTime,int face)
{
	velocity.x = 50 * face;
	velocity.y = speed;
	body.move(velocity * elapsedTime);
}

void EnergyBall::strikeUpdate(float elapsedTime, float x)
{
	velocity.x = x;
	velocity.y = speed;
	body.move(velocity * elapsedTime);
}

void EnergyBall::SetPosition(sf::Vector2f position)
{
	body.setPosition(position);
}


void EnergyBall::Draw(sf::RenderWindow& window) {
	window.draw(body);
}