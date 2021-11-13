#include "BatBoss.h"

BatBoss::BatBoss(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, sf::Vector2f position,float speed) :
	animation(texture, imageCount, switchTime) {
	row = 0;
	this->speed = speed;
	checkLR = false;
	checkUP = true;
	bossShoot = true;
	spawnbossBall = false;
	deadBoss = false;
	checkBott = 0;
	ballBossCount = 5;
	body.setSize(sf::Vector2f(240.0f, 120.0f));
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(position);
	body.setTexture(texture);
}

//void BatBoss::Update(float elapsedTime, sf::RenderWindow& window) {
	//energyballBossTexture.loadFromFile("Images/MegaBossEnergyBall2.png");
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
	//	energyballs.push_back(EnergyBall(&energyballBossTexture, sf::Vector2f(body.getPosition()), sf::Vector2f(40.0f, 80.0f), 200.0f));
	//}
	//energyballs.push_back(EnergyBall(&energyballBossTexture, sf::Vector2f(body.getPosition()), sf::Vector2f(30.0f, 40.0f), 200.0f));
	//velocity.x = 0.0f;
	//row = 0;
	//checkBott = 1;
	//animation.UpdateBoss(row, elapsedTime);
	//body.setTextureRect(animation.currentRect);
	//body.move(velocity * elapsedTime);

	//for (size_t i = 0; i < energyballs.size(); i++) {
	//	energyballs[i].Update(elapsedTime, window, energyballs, checkUP,checkBott,checkLR); //bottom
	//	if (energyballs[i].GetPosition().y >= window.getSize().y  - 230.0f) {
	//		energyballs.erase(energyballs.begin() + i);
	//	}
	//}
//}

void BatBoss::Update(float elapsedTime,float movement, bool dead) {
	if (dead) {
	row = 1;
	animation.limitUpdate(row, elapsedTime,false);
	body.setTextureRect(animation.currentRect);
	}
	else {
	velocity.y = 0.0f;
	velocity.x = movement;
	row = 0;
	animation.UpdateBoss(row, elapsedTime);
	body.setTextureRect(animation.currentRect);
	body.move(velocity);
	}
}


void BatBoss::Draw(sf::RenderWindow& window) {
	window.draw(body);
	for (size_t i = 0; i < energyballs.size(); i++) {
		energyballs[i].Draw(window);
	}
}

void BatBoss::SetPosition(sf::Vector2f position)
{
	body.setPosition(position);
}

//void Megaman::OnCollision(sf::Vector2f direction)
//{
//	if (direction.x < 0.0f) {
//		velocity.x = 0.0f;//Colision on the left
		// ��ҹ���������觢ͧ�����ҹ���� v = 0
//	}
//	else if (direction.x > 0.0f) {
//		velocity.x = 0.0f;//Colision on the right
		// ��ҹ���������觢ͧ�����ҹ��� v = 0
//	}
//	if (direction.y < 0.0f ) {
//		velocity.y = 0.0f;//Colision on the bottom
//		canjump = true;
		// ��ҹ���������觢ͧ������ҧ , ���ⴴ�� , v = 0
//	}
//	else if (direction.y > 0.0f) {
//		velocity.y = 0.0f;//Colision on the top
		// ��ҹ���������觢ͧ���躹 v = 0
//	}
//}