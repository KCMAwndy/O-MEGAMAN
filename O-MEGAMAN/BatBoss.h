#pragma once
#include<SFML\Graphics.hpp>
#include<vector>
#include"Animation.h"
#include"Collider.h"
#include"EnergyBall.h"
#include"Megaman.h"

class BatBoss
{
public:
	BatBoss(sf::Texture* texture, sf::Vector2u imageCount, float switchTime,sf::Vector2f position, float speed);
	void Update(float elapsedTime,float movement,bool dead);
	void Draw(sf::RenderWindow& window);
	std::vector<class EnergyBall>	energyballs;
	void SetPosition(sf::Vector2f position);
	sf::Vector2f GetPosition() {
		return body.getPosition();
	}
	sf::Vector2f GetOrigin() {
		return body.getOrigin();
	}
	Collider GetCollider() {
		return Collider(body);
	}
public:
	int ballBossCount;
	bool bossShoot;
	bool spawnbossBall;
	bool deadBoss;
private:
	sf::RectangleShape body;
	Animation animation;
	sf::Texture energyballBossTexture;
	bool checkLR;
	bool checkUP;
	int checkBott;
	unsigned int row;
	float speed;
	sf::Vector2f velocity;
};