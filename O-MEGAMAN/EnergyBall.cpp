#include "EnergyBall.h"

EnergyBall::EnergyBall(sf::Texture* texture,sf::Vector2f position,float speed){
	this->speed = speed;
	faceRight = true;
	body.setSize(sf::Vector2f(10.0f, 10.0f));
	//body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(position);
	body.setTexture(texture);
}

void EnergyBall::Update(float elapsedTime, sf::RenderWindow& window,std::vector<class EnergyBall> energyballs,bool checkUP,bool checkLR) {
	if (checkLR && checkUP==false){
		velocity.x = 100.0f ;
	}
	else if (checkUP) {
		velocity.y = -100.0f;
	}
	else{
		velocity.x = -100.0f;
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
		// ��ҹ���������觢ͧ�����ҹ���� v = 0
	}
	else if (direction.x > 0.0f) {
		velocity.x = 0.0f;//Colision on the right
		// ��ҹ���������觢ͧ�����ҹ��� v = 0
	}
	if (direction.y < 0.0f) {
		velocity.y = 0.0f;//Colision on the bottom
		// ��ҹ���������觢ͧ������ҧ , ���ⴴ�� , v = 0
	}
	else if (direction.y > 0.0f) {
		velocity.y = 0.0f;//Colision on the top
		// ��ҹ���������觢ͧ���躹 v = 0
	}
}
