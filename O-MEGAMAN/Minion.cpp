#include "Minion.h"

Minion::Minion(sf::Texture* texture, sf::Vector2f position,sf::Vector2f size,float speed){
	this->speed = speed;
	body.setSize(size);
	//body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(position);
	collectPostition = position.x;
	body.setTexture(texture);
}

void Minion::Update(float elapsedTime) {
	if (collectPostition > 360.0f) {
		velocity.x = -100.0f;
	}
	else if(collectPostition < 360.0f){
		velocity.x = 100.0f;
	}
	body.move(velocity * elapsedTime);
}

void Minion::Draw(sf::RenderWindow& window) {
	window.draw(body);
}

//bool Minion::CheckLR(std::vector<Minion> minions,int i)
//{
//	if (minions[i].GetPosition().x < 620.0f) {
//		return false;
//	}
//	else {
//		return true;
//	}
//}

//void Megaman::OnCollision(sf::Vector2f direction)
//{
//	if (direction.x < 0.0f) {
//		velocity.x = 0.0f;//Colision on the left
		// ผ่านไม่ได้มีสิ่งของอยู่ด้านช้าย v = 0
//	}
//	else if (direction.x > 0.0f) {
//		velocity.x = 0.0f;//Colision on the right
		// ผ่านไม่ได้มีสิ่งของอยู่ด้านขวา v = 0
//	}
//	if (direction.y < 0.0f ) {
//		velocity.y = 0.0f;//Colision on the bottom
//		canjump = true;
		// ผ่านไม่ได้มีสิ่งของอยู่ล่าง , กระโดดได้ , v = 0
//	}
//	else if (direction.y > 0.0f) {
//		velocity.y = 0.0f;//Colision on the top
		// ผ่านไม่ได้มีสิ่งของอยู่บน v = 0
//	}
//}
