#include "EnergyBall.h"

EnergyBall::EnergyBall(sf::Texture* texture,sf::Vector2f position, sf::Vector2f size,float speed){
	this->speed = speed;
	faceRight = true;
	checkBott = 0;
	body.setSize(size);
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(position);
	body.setTexture(texture);
}

void EnergyBall::Update(float elapsedTime, sf::RenderWindow& window,std::vector<class EnergyBall> energyballs,bool checkUP, int checkBott,bool checkLR) {
	if (checkLR && checkUP==false){
		velocity.x = 250.0f ;
	}
	else if (checkUP&&checkLR==false) {
		velocity.y = 250.0f*checkBott;
	}
	else {
		velocity.x = -250.0f;
	}
	//if (body.getPosition().x <= 20)		//LEFT
	//	body.setPosition(sf::Vector2f(20.0f, body.getPosition().y));		
	//if (body.getPosition().x >= window.getSize().x - body.getGlobalBounds().width - 20) {	//RIGHT 
	//	energyballs.erase(energyballs.begin() + i);
	//}
	//if (body.getPosition().y <= 60)		//TOP
	//	body.setPosition(sf::Vector2f(body.getPosition().x, 60.0f));
	body.move(velocity * elapsedTime);
}

	void EnergyBall::Draw(sf::RenderWindow& window) {
	window.draw(body);
}

void EnergyBall::OnCollision(sf::Vector2f direction)
{
	if (direction.x < 0.0f) {
		velocity.x = 0.0f;//Colision on the left
		// ผ่านไม่ได้มีสิ่งของอยู่ด้านช้าย v = 0
	}
	else if (direction.x > 0.0f) {
		velocity.x = 0.0f;//Colision on the right
		// ผ่านไม่ได้มีสิ่งของอยู่ด้านขวา v = 0
	}
	if (direction.y < 0.0f) {
		velocity.y = 0.0f;//Colision on the bottom
		// ผ่านไม่ได้มีสิ่งของอยู่ล่าง , กระโดดได้ , v = 0
	}
	else if (direction.y > 0.0f) {
		velocity.y = 0.0f;//Colision on the top
		// ผ่านไม่ได้มีสิ่งของอยู่บน v = 0
	}
}
