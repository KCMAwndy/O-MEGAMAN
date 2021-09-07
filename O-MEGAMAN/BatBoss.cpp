#include "BatBoss.h"

BatBoss::BatBoss(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed) :
	animation(texture, imageCount, switchTime) {
	row = 0;
	this->speed = speed;
	checkLR = false;
	checkUP = true;
	checkBott = 0;
	body.setSize(sf::Vector2f(240.0f, 120.0f));
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(360.0f, 140.0f);
	body.setTexture(texture);
}

void BatBoss::Update(float elapsedTime, sf::RenderWindow& window) {
	energyballBossTexture.loadFromFile("Images/MegaBossEnergyBall2.png");
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
		energyballs.push_back(EnergyBall(&energyballBossTexture, sf::Vector2f(body.getPosition()), sf::Vector2f(40.0f, 80.0f), 200.0f));
	}
	//energyballs.push_back(EnergyBall(&energyballBossTexture, sf::Vector2f(body.getPosition()), sf::Vector2f(30.0f, 40.0f), 200.0f));
	velocity.x = 0.0f;
	row = 0;
	checkBott = 1;
	animation.UpdateBoss(row, elapsedTime);
	body.setTextureRect(animation.currentRect);
	body.move(velocity * elapsedTime);

	for (size_t i = 0; i < energyballs.size(); i++) {
		energyballs[i].Update(elapsedTime, window, energyballs, checkUP,checkBott,checkLR); //bottom
		if (energyballs[i].GetPosition().y >= window.getSize().y  - 230.0f) {
			energyballs.erase(energyballs.begin() + i);
		}
	}
}

void BatBoss::Draw(sf::RenderWindow& window) {
	window.draw(body);
	for (size_t i = 0; i < energyballs.size(); i++) {
		energyballs[i].Draw(window);
	}
}

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